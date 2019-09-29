#include <ctime>
#include <iostream>
#include <string>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

std::string make_daytime_string() {
    std:: time_t now = std::time(0);
    return std::ctime(&now);
}

class tcp_connection
    // Using shared_ptr and enable_shared_from_this because we want to keep the tcp_connection object alive
    // as long as there is an operation that refers to it.
        : public boost::enable_shared_from_this<tcp_connection>
{
public:
    typedef boost::shared_ptr<tcp_connection> pointer;

    static pointer create(boost::asio::io_service& io_service) {
        return pointer(new tcp_connection(io_service));
    }

    tcp::socket& socket() {
        return socket_;
    }

    // Call boost::asio::async_write() to serve the data to the client. We are using boost::asio::async_write(),
    // rather than ip::tcp::socket::async_write_some(), to ensure that the entire block of data is sent.
    void start() {
        std::cout << "New connection started..." <<std::endl;
        // The data to be sent is stored in the class member m_message
        // as we need to keep the data valid until the asynchronous operation is complete.
        //m_message = make_daytime_string();
        const std::string& message = "Hi client!";

        // When initiating the asynchronous operation, and if using boost::bind(), we must specify only the arguments
        // that match the handler's parameter list. In this code, both of the argument placeholders
        // (boost::asio::placeholders::error and boost::asio::placeholders::bytes_transferred) could potentially have been removed,
        // since they are not being used in handle_write().
        boost::asio::async_write(socket_, boost::asio::buffer("Hi client!", 10),
                                 boost::bind(&tcp_connection::handle_write, shared_from_this(),
                                             boost::asio::placeholders::error,
                                             boost::asio::placeholders::bytes_transferred));
    }

private:
    explicit tcp_connection(boost::asio::io_service& io_service): socket_(io_service) {
    }
    // handle_write() is responsible for any further actions for this client connection.
    void handle_write(const boost::system::error_code& error, const size_t bytes_transferred) {
        if (error) {
            std::cerr << "could not write: " << boost::system::system_error(error).what() << std::endl;
            return;
        } else {
            while(1);
        }
    }
    tcp::socket socket_;
    std::string m_message;
};

class tcp_server
{
public:
    // Constructor: initialises an acceptor to listen on TCP port (0 means random).
    explicit tcp_server(boost::asio::io_service& io_service)
                        : acceptor_(io_service, tcp::endpoint(tcp::v4(), 6574)) {
        start_accept(); //creates a socket and initiates an asynchronous accept operation to wait for a new connection.
    }

private:
    void start_accept()
    {
        // creates a socket
        tcp_connection::pointer new_connection = tcp_connection::create(acceptor_.get_io_service());
        std::cout << "Waiting for clients..." <<std::endl;
        // initiates an asynchronous accept operation to wait for a new connection.
        acceptor_.async_accept(new_connection->socket(),
                               boost::bind(&tcp_server::handle_accept, this, new_connection,
                                           boost::asio::placeholders::error));
    }

    // handle_accept() is called when the asynchronous accept operation initiated by start_accept() finishes.
    // It services the client request
    void handle_accept(const tcp_connection::pointer& new_connection, const boost::system::error_code& error) {
        if (!error) {
            new_connection->start();
        }
        start_accept(); //initiate the next accept operation.
    }
    tcp::acceptor acceptor_;
};

int main() {
    try {
        boost::asio::io_service io_service; //create a server object to accept incoming client connections.
        tcp_server server(io_service); //io_service object provides I/O services, such as sockets, that the server object will use.
        io_service.run(); //Run the io_service object to perform asynchronous operations.
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}

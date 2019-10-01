#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class session
        : public std::enable_shared_from_this<session>
{
public:
    explicit session(tcp::socket socket)
            : socket_(std::move(socket))
    {
    }

    void handle_accept()
    {
        do_write(10);
    }

private:
    void do_read()
    {
        auto self(shared_from_this());
        socket_.async_read_some(boost::asio::buffer(data_, max_length),
                                [this, self](boost::system::error_code ec, std::size_t length)
                                {
                                    if (!ec)
                                    {
                                        do_write(10);
                                    }
                                });
    }

    void do_write(std::size_t length)
    {
        auto self(shared_from_this());
        strcpy(this->data_, "Hi client!");
        boost::asio::async_write(socket_, boost::asio::buffer(data_, length),
                                 [this, self](boost::system::error_code ec, std::size_t /*length*/)
                                 {
                                     if (!ec)
                                     {
                                         do_read();
                                     }
                                 });
    }

    tcp::socket socket_;
    enum { max_length = 1024 };
    char data_[max_length];
};

class server
{
public:
    server(boost::asio::io_context& io_context, short port)
            : acceptor_(io_context, tcp::endpoint(tcp::v4(), port))
    {
        accept_connection();
    }

private:
#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"
    void accept_connection()
    {
        std::cout << "Waiting for clients..." << std::endl;
        //if(acceptor_.is_open())
        //acceptor_.close(); // Verify socket is in a closed state.
        acceptor_.async_accept(
                [this](boost::system::error_code ec, tcp::socket socket)
                {
                    if (ec) {
                        std::cout << "Error before handle_accept: " << ec.message() << std::endl;
                        return; //TODO Server never return. Maybe is better to change this behaviour
                    }
                    std::make_shared<session>(std::move(socket))->handle_accept(); //start new socket for the new client
                    accept_connection(); //server socket continue accepting new connections
                });
    }
#pragma clang diagnostic pop

    tcp::acceptor acceptor_;
};

int main(int argc, char* argv[])
{
    try
    {
        boost::asio::io_context io_context;

        server s(io_context, std::atoi("63504"));

        io_context.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
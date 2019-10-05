//
// Created by giova on 01/10/2019.
//

#ifndef SERVERMODULE_SESSION_H
#define SERVERMODULE_SESSION_H

using boost::asio::ip::tcp;

class session : public std::enable_shared_from_this<session> {

private:
    tcp::socket socket_;
    enum { max_length = 1024 };
    char data_[max_length];
    void do_read();
    void do_write(std::size_t length);

public:
    explicit session(tcp::socket socket);
    void handle_accept();
};

#endif //SERVERMODULE_SESSION_H

//
// Created by giova on 01/10/2019.
//

#include <memory>
#include <utility>
#include <boost/asio.hpp>
#include "session.h"

using boost::asio::ip::tcp;

session::session(tcp::socket socket) : socket_(std::move(socket)) { } //constructor

void session::handle_accept() {
    do_write(10);
}

void session::do_read() {
    auto self(shared_from_this());
    socket_.async_read_some(boost::asio::buffer(data_, max_length),
                            [this, self](boost::system::error_code ec, std::size_t length) {
        if (!ec) {
            do_write(10);
        }
    });
}

void session::do_write(std::size_t length) {
    auto self(shared_from_this());
    strcpy(this->data_, "Hi client!");
    boost::asio::async_write(socket_, boost::asio::buffer(data_, length),
                             [this, self](boost::system::error_code ec, std::size_t /*length*/) {
         if (!ec) {
             do_read();
         }
     });
}


//
// Created by giova on 01/10/2019.
//

#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <utility>
#include "header_files/myServer.h"
#include "header_files/session.h"

using boost::asio::ip::tcp;

myServer::myServer(boost::asio::io_context& io_context, const tcp::endpoint& endpoint)
                        : acceptor_(io_context, endpoint) {
    accept_connection();
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"
void myServer::accept_connection()
{
    std::cout << "Waiting for clients..." << std::endl;
    acceptor_.async_accept([this](boost::system::error_code ec, tcp::socket socket) {
        if (ec) {
            std::cout << "Error before handle_accept: " << ec.message() << std::endl;
            return; //TODO Server never return. Maybe is better to change this behaviour
        }
        std::make_shared<session>(std::move(socket), room_)->session_start(); //start new socket for the new client
        accept_connection(); //server socket continue accepting new connections
    });
}
#pragma clang diagnostic pop


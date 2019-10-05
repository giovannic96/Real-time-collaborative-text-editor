//
// Created by giova on 01/10/2019.
//

#include <memory>
#include <utility>
#include <boost/asio.hpp>
#include <iostream>
#include "session.h"
#include "json.hpp"
#include "jsonUtility.h"

using boost::asio::ip::tcp;
using json = nlohmann::json;

session::session(tcp::socket socket) : socket_(std::move(socket)) {
} //constructor

void session::handle_accept() {
    do_read();
}

void session::do_read() {
    auto self(shared_from_this());
    socket_.async_read_some(boost::asio::buffer(jdata_in.dump(), max_length),
                            [this, self](boost::system::error_code ec, std::size_t length) {
        if (!ec) {
            std::cout << "JSON read: " << std::string(jdata_in.dump()) << std::endl;
            std::string opJSON;
            std::string userJSON;
            std::string passJSON;
            jsonUtility::from_json(jdata_in, opJSON, userJSON, passJSON); //get json value and put into JSON variables
            /*
                DATABASE FRA -> get userDB and passDB
             */
            json j;
            jsonUtility::to_json(j, "LOGIN_RESPONSE", "LOGIN_OK");
            do_write(j, sizeof(j));
        }
    });
}

void session::do_write(const json& jdata_out, std::size_t json_size) {
    auto self(shared_from_this());
    //strcpy(this->data_, "Hi client!");
    //create json object from a raw string literal
    /*
    std::ostringstream oss;
    oss << "{ \"operation\": \"LOGIN\", \"username\": \"" << "username" << "\", \"password\": \"" << "password" << "\" }";
    std::string data = oss.str();
    std::cout << "INIZIO:" << data << "FINE";
    auto j = json::parse(data);
     */

    /*
     * DA METTERE IN QT
     * json j;
    jsonUtility::to_json(j, "LOGIN_OK", "giovanni", "giovanni");
     */
    boost::asio::async_write(socket_, boost::asio::buffer(jdata_out.dump(), json_size),
                             [this, self](boost::system::error_code ec, std::size_t /*length*/) {
         if (!ec) {
             do_read(); //continue reading
         }
     });
}


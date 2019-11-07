//
// Created by giova on 01/10/2019.
//

#ifndef SERVERMODULE_SESSION_H
#define SERVERMODULE_SESSION_H

#include "json.hpp"
#include "dbService.h"
#include <boost/asio.hpp>
#include "message.h"
#include "room.h"

using boost::asio::ip::tcp;
using json = nlohmann::json;

class session : public participant, public std::enable_shared_from_this<session> {

private:
    tcp::socket socket_;
    room& room_;
    message read_msg_;
    message_queue write_msgs_;
    dbService dbService_;
    void do_read_header();
    void do_read_body();
    void do_write(); //for the editor
    void do_write(message m); //for single client
    std::string handleRequests(const std::string& opJSON, const json& jdata_in);
    void sendMsg(const std::string& response);
    void sendMsgAll(const std::string& response);
    static message constructMsg(const std::string& response);

public:
    explicit session(tcp::socket socket, room& room);
    void session_start();
    void deliver(const message& msg);

};

#endif //SERVERMODULE_SESSION_H

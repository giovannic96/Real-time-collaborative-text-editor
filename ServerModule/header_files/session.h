//
// Created by giova on 01/10/2019.
//

#ifndef SERVERMODULE_SESSION_H
#define SERVERMODULE_SESSION_H

#include "json.hpp"
#include "dbService.h"
#include <boost/asio.hpp>
#include <boost/filesystem.hpp>
#include <boost/thread.hpp>
#include "message.h"
#include "room.h"
#include "email.h"

#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds

using boost::asio::ip::tcp;
using json = nlohmann::json;
typedef std::pair<int,int> sId;

class session : public participant, public std::enable_shared_from_this<session> {

private:
    tcp::socket socket_;
    message read_msg_;
    message_queue write_msgs_;
    std::string fullBody;
    dbService dbService_;
    void do_read_header();
    void do_read_body();
    void do_write(); //for the editor
    std::string handleRequests(const std::string& opJSON, const json& jdata_in, int& edId, std::string& curFile, bool& onlyToThisEditor);
    void sendMsg(const std::string& response);
    void sendMsgAll(const std::string& response, const int& edId, const std::string& curFile, bool includeThisEditor=false); //send msg to all the clients except client with id 'edId' having the curFile opened

public:
    explicit session(tcp::socket socket);
    void session_start(int editorId);
    void deliver(const message& msg);
};

#endif //SERVERMODULE_SESSION_H

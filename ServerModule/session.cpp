//
// Created by giova on 01/10/2019.
//

#include <memory>
#include <utility>
#include <boost/asio.hpp>
#include <boost/filesystem.hpp>
#include <iostream>
#include <QtSql/QSqlDatabase>
#include "sqlite3.h"
#include "header_files/json.hpp"
#include "header_files/message.h"
#include "header_files/session.h"
#include "header_files/room.h"
#include "header_files/jsonUtility.h"
#include "header_files/dbService.h"
#include "header_files/File.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"

using boost::asio::ip::tcp;
using json = nlohmann::json;

session::session(tcp::socket socket, room &room)
                            : socket_(std::move(socket)), room_(room) {}

void session::session_start() {
    room_.join(shared_from_this());
    do_read_header();
}

void session::deliver(const message &msg) {
    bool write_in_progress = !write_msgs_.empty();
    write_msgs_.push_back(msg);
    if (!write_in_progress) {
        do_write();
    }
}

void session::do_read_header()
{
    memset(read_msg_.data(), 0, read_msg_.length()); //VERY IMPORTANT, otherwise rubbish remains inside socket!
    auto self(shared_from_this());
    boost::asio::async_read(socket_,
                            boost::asio::buffer(read_msg_.data(), message::header_length),
                            [this, self](boost::system::error_code ec, std::size_t /*length*/) {
        if (!ec && read_msg_.decode_header()) {
            do_read_body();
        }
        else {
            room_.leave(shared_from_this());
        }
    });
}

void session::do_read_body()
{
    auto self(shared_from_this());
    boost::asio::async_read(socket_,
                            boost::asio::buffer(read_msg_.body(), read_msg_.body_length()),
                            [this, self](boost::system::error_code ec, std::size_t /*length*/) {
        if (!ec) {
            std::cout << "data:" << read_msg_.data() << "END" << std::endl;
            std::string opJSON;
            json jdata_in;
            try {
                jdata_in = json::parse(read_msg_.body());
                jsonUtility::from_json(jdata_in, opJSON); //get json value and put into JSON variables
            } catch (json::type_error& e) {
                std::cerr << e.what() << '\n';
            }
            const char* response = this->handleRequests(opJSON, jdata_in);
            this->sendMsg(response);
            do_read_header(); //continue reading loop
        }
        else {
            room_.leave(shared_from_this());
        }
    });
}

void session::do_write() {
    auto self(shared_from_this());
    boost::asio::async_write(socket_,
                             boost::asio::buffer(write_msgs_.front().data(),write_msgs_.front().length()),
                             [this, self](boost::system::error_code ec, std::size_t /*length*/) {
         if (!ec) {
             write_msgs_.pop_front();
             if (!write_msgs_.empty()) {
                 do_write();
             }
         }
         else {
             room_.leave(shared_from_this());
         }
     });
}

void session::do_write(message m) {
    std::cout << "sending:" << m.data() << "END" << std::endl;
    auto self(shared_from_this());
    boost::asio::async_write(socket_,
                             boost::asio::buffer(m.data(), m.length()),
                             [this, self](boost::system::error_code ec, std::size_t /*length*/) {
         if (!ec) {
            //do nothing
         }
         else {
             room_.leave(shared_from_this());
         }
     });
}

void session::sendMsg(const char* response) {
    //Send data (header and body)
    message msg;
    msg.body_length(std::strlen(response));
    std::memcpy(msg.body(), response, msg.body_length());
    msg.encode_header();
    shared_from_this()->deliver(msg); //deliver msg only to the participant
}

const char* session::handleRequests(const std::string& opJSON, const json& jdata_in) {
    if(opJSON == "LOGIN_REQUEST") {
        std::string userJSON;
        std::string passJSON;
        jsonUtility::from_json(jdata_in, userJSON, passJSON); //get json value and put into JSON variables

        //Get data from db
        //const char *db_res = dbService::enumToStr(dbService::tryLogin(userJSON, passJSON));
        const char *db_res;
        dbService::DB_RESPONSE resp = dbService::tryLogin(userJSON, passJSON);
        QSqlDatabase::removeDatabase("MyConnect2");

        if(resp == dbService::LOGIN_OK)
            db_res = "LOGIN_OK";
        else if(resp == dbService::LOGIN_FAILED)
            db_res = "LOGIN_FAILED";
        else if(resp == dbService::DB_ERROR)
            db_res = "DB_ERROR";
        else if(resp == dbService::QUERY_ERROR)
            db_res = "QUERY_ERROR";
        else if(resp == dbService::ALREADY_LOGGED)
            db_res = "ALREADY_LOGGED_ERROR";
        else
            db_res = "DB_ERROR";

        //Serialize data
        json j;
        jsonUtility::to_json_usernameLogin(j, "LOGIN_RESPONSE", db_res, userJSON);
        const char* response = j.dump().c_str();
        return response;

    } else if (opJSON == "SIGNUP_REQUEST"){
        std::string userJSON;
        std::string passJSON;
        std::string emailJSON;
        jsonUtility::from_json(jdata_in, userJSON, passJSON, emailJSON); //get json value and put into JSON variables

        //Get data from db
        //const char *db_res = dbService::enumToStr(dbService::tryLogin(userJSON, passJSON));
        const char *db_res;
        dbService::DB_RESPONSE resp = dbService::trySignup(userJSON, passJSON, emailJSON);
        QSqlDatabase::removeDatabase("MyConnect");

        if(resp == dbService::SIGNUP_OK)
            db_res = "SIGNUP_OK";
        else if(resp == dbService::SIGNUP_FAILED)
            db_res = "SIGNUP_FAILED";
        else if(resp == dbService::DB_ERROR)
            db_res = "DB_ERROR";
        else if(resp == dbService::QUERY_ERROR)
            db_res = "QUERY_ERROR";
        else if(resp == dbService::EMAIL_ERROR)
            db_res = "EMAIL_ERROR";
        else
            db_res = "DB_ERROR";

        //Serialize data
        json j;
        jsonUtility::to_json(j, "SIGNUP_RESPONSE", db_res);
        const char* response = j.dump().c_str();
        return response;

    } else if (opJSON == "NEWFILE_REQUEST") {
        std::string userJSON;
        std::string filenameJSON;
        jsonUtility::from_json_filename(jdata_in, userJSON, filenameJSON); //get json value and put into JSON variables

        //Get data from db
        //const char *db_res = dbService::enumToStr(dbService::tryLogin(userJSON, passJSON));
        const char *db_res;

        //update tables on db
        dbService::DB_RESPONSE resp = dbService::tryNewFile(userJSON, filenameJSON);
        QSqlDatabase::removeDatabase("MyConnect3");

        //create file on local filesystem
        //TODO: change path
        boost::filesystem::ofstream(R"(../Filesystem)" + filenameJSON + ".txt");

        if(resp == dbService::NEWFILE_OK)
            db_res = "NEWFILE_OK";
        else if(resp == dbService::NEWFILE_FAILED)
            db_res = "NEWFILE_FAILED";
        else if(resp == dbService::DB_ERROR)
            db_res = "DB_ERROR";
        else if(resp == dbService::QUERY_ERROR)
            db_res = "QUERY_ERROR";
        else if(resp == dbService::FILENAME_ERROR)
            db_res = "FILENAME_ERROR";
        else
            db_res = "DB_ERROR";

        //Serialize data
        json j;
        jsonUtility::to_json(j, "NEWFILE_RESPONSE", db_res);
        const char* response = j.dump().c_str();
        return response;

    } else if (opJSON == "LISTFILE_REQUEST") {
        std::string userJSON;
        std::string filenameJSON;
        jsonUtility::from_json_username(jdata_in, userJSON); //get json value and put into JSON variables

        //Get data from db
        //const char *db_res = dbService::enumToStr(dbService::tryLogin(userJSON, passJSON));
        const char *db_res;

        //check the list of file for the current user
        std::vector<File> vectorFile;
        dbService::DB_RESPONSE resp = dbService::tryListFile(userJSON, vectorFile);
        QSqlDatabase::removeDatabase("MyConnect2");


        if(resp == dbService::LIST_EXIST)
            db_res = "LIST_EXIST";
        else if(resp == dbService::LIST_DOESNT_EXIST)
            db_res = "LIST_DOESNT_EXIST";
        else if(resp == dbService::DB_ERROR)
            db_res = "DB_ERROR";
        else if(resp == dbService::QUERY_ERROR)
            db_res = "QUERY_ERROR";
        else
            db_res = "DB_ERROR";

        //Serialize data
        json j;
        jsonUtility::to_json(j, "LISTFILE_RESPONSE", db_res);
        //TODO insert the vectorFile (that contains list of files) in the json response to the Client
        const char* response = j.dump().c_str();
        return response;

    } else if (opJSON == "OPENFILE_REQUEST") {
        std::string userJSON;
        std::string filenameJSON;
        jsonUtility::from_json_filename(jdata_in, userJSON, filenameJSON); //get json value and put into JSON variables

        //Get data from db
        //const char *db_res = dbService::enumToStr(dbService::tryLogin(userJSON, passJSON));
        const char *db_res;

        //update tables on db
        dbService::DB_RESPONSE resp = dbService::tryOpenFile(userJSON, filenameJSON); //TODO: function tryOpenFile
        QSqlDatabase::removeDatabase("MyConnect4");

        if(resp == dbService::OPENFILE_OK) {
            //TODO: update local file 'filenameJSON' in filesystem based on CRDT that server has in memory

            //TODO: send updated file to client

            //TODO: update flag! This means that while file is being sent, we have to mantain a queue containing all the modifications in between

            //TODO: after file has been sent, send to all the clients all the modifications present in previous created queue
            db_res = "OPENFILE_OK";
        }
        else if(resp == dbService::OPENFILE_FAILED)
            db_res = "OPENFILE_FAILED";
        else if(resp == dbService::DB_ERROR)
            db_res = "DB_ERROR";
        else if(resp == dbService::QUERY_ERROR)
            db_res = "QUERY_ERROR";
        else if(resp == dbService::FILENAME_ERROR)
            db_res = "FILENAME_ERROR";
        else
            db_res = "DB_ERROR";

        //Serialize data
        json j;
        jsonUtility::to_json(j, "OPENFILE_RESPONSE", db_res);
        const char* response = j.dump().c_str();
        return response;

    } else { //editor functions
        room_.deliver(read_msg_); //deliver to all the participants
    }
}
#pragma clang diagnostic pop

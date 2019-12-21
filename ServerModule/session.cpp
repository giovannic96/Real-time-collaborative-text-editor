//
// Created by giova on 01/10/2019.
//

#include <memory>
#include <utility>
#include <iostream>
#include <QtSql/QSqlDatabase>
#include "sqlite3.h"
#include "header_files/json.hpp"
#include "header_files/message.h"
#include "header_files/session.h"
#include "header_files/room.h"
#include "header_files/jsonUtility.h"
#include "header_files/dbService.h"
#include "header_files/fileUtility.h"
#include "header_files/File.h"
#include "header_files/symbol_formatting.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"

using boost::asio::ip::tcp;
using json = nlohmann::json;

session::session(tcp::socket socket, room &room)
                            : socket_(std::move(socket)), room_(room) {
}

void session::session_start(int editorId) {
    shared_from_this()->setSiteId(editorId);
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
            //Disconnect user and leave the room
            if(!shared_from_this()->getUsername().empty()) { //it can be empty at the beginning (if a crash happens)
                dbService::tryLogout(shared_from_this()->getUsername());
                QSqlDatabase::removeDatabase("MyConnect2");
                //TODO: handle response from db
            }
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
            read_msg_.data()[read_msg_.length()] = '\0'; //VERY IMPORTANT: this removes any possible letters after data

            std::string opJSON;
            json jdata_in;
            try {
                jdata_in = json::parse(read_msg_.body());
                jsonUtility::from_json(jdata_in, opJSON); //get json value and put into JSON variables

                int edId = shared_from_this()->getId();
                std::string curFile = std::string();
                bool onlyToThisEditor = false;
                const std::string response = this->handleRequests(opJSON, jdata_in, edId, curFile, onlyToThisEditor);
                if(opJSON == "INSERTION_REQUEST" || opJSON == "REMOVAL_REQUEST" || opJSON == "REMOVALRANGE_REQUEST" || opJSON == "INSERTIONRANGE_REQUEST") {
                    std::cout << "Sent:" << response << "END" << std::endl;
                    this->sendMsgAll(response, edId, curFile); //send data to all the participants in the room except to this client, having the curFile opened
                }
                else if(opJSON == "RENAMEFILE_REQUEST" && !onlyToThisEditor) {
                    std::cout << "Sent:" << response << "END" << std::endl;
                    this->sendMsgAll(response, edId, curFile, true); //send data to all the participants, having the curFile opened
                }
                else {
                    std::cout << "Sent:" << response << "END" << std::endl;
                    this->sendMsg(response); //send data only to this participant
                }
                do_read_header(); //continue reading loop
            } catch (json::exception& e) {
                std::cerr << "message: " << e.what() << '\n' << "exception id: " << e.id << std::endl;
                do_read_header();
            }
        }
        else {
            //Disconnect user and leave the room
            if(!shared_from_this()->getUsername().empty()) { //it can be empty at the beginning (if a crash happens)
                dbService::tryLogout(shared_from_this()->getUsername());
                QSqlDatabase::removeDatabase("MyConnect2");
                //TODO: handle response from db
            }
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
             //Disconnect user and leave the room
             if(!shared_from_this()->getUsername().empty()) { //it can be empty at the beginning (if a crash happens)
                 dbService::tryLogout(shared_from_this()->getUsername());
                 QSqlDatabase::removeDatabase("MyConnect2");
                 //TODO: handle response from db
             }
             room_.leave(shared_from_this());
         }
     });
}

void session::sendMsg(const std::string& response) {
    message msg = constructMsg(response);
    shared_from_this()->deliver(msg); //deliver msg only to the participant
}

void session::sendMsgAll(const std::string& response, const int& edId, const std::string& curFile, bool includeThisEditor) {
    message msg = constructMsg(response);
    room_.deliverToAll(msg, edId, curFile, includeThisEditor); //deliver msg to all the clients except the client with id 'edId' (this client)
}

message session::constructMsg(const std::string& response) {
    //Send data (header and body)
    message msg;
    msg.body_length(response.size());
    std::memcpy(msg.body(), response.data(), msg.body_length());
    msg.body()[msg.body_length()] = '\0';
    msg.encode_header();
    return msg;
}

std::string session::handleRequests(const std::string& opJSON, const json& jdata_in, int& edId, std::string& curFile, bool& onlyToThisEditor) {
    if(opJSON == "LOGIN_REQUEST") {
        std::string userJSON;
        std::string passJSON;
        jsonUtility::from_json(jdata_in, userJSON, passJSON); //get json value and put into JSON variables

        //Get data from db
        //const char *db_res = dbService::enumToStr(dbService::tryLogin(userJSON, passJSON));
        const char *db_res;
        dbService::DB_RESPONSE resp = dbService::tryLogin(userJSON, passJSON);
        QSqlDatabase::removeDatabase("MyConnect2");

        if(resp == dbService::LOGIN_OK) {
            shared_from_this()->setUsername(userJSON);
            db_res = "LOGIN_OK";
        }
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
        const std::string response = j.dump();
        return response;

    } else if (opJSON == "LOGOUT_REQUEST" || opJSON == "DISCONNECT_REQUEST") {
        std::string userJSON;
        jsonUtility::from_json_username(jdata_in, userJSON); //get json value and put into JSON variables

        //Get data from db
        //const char *db_res = dbService::enumToStr(dbService::tryLogin(userJSON, passJSON));
        const char *db_res;

        dbService::DB_RESPONSE resp = dbService::tryLogout(userJSON);
        QSqlDatabase::removeDatabase("MyConnect2");

        if(resp == dbService::LOGOUT_OK)
            db_res = "LOGOUT_OK";
        else if(resp == dbService::LOGOUT_FAILED)
            db_res = "LOGOUT_FAILED";
        else if(resp == dbService::DB_ERROR)
            db_res = "DB_ERROR";
        else if(resp == dbService::QUERY_ERROR)
            db_res = "QUERY_ERROR";
        else
            db_res = "DB_ERROR";

        json j;
        jsonUtility::to_json(j, opJSON == "LOGOUT_REQUEST" ? "LOGOUT_RESPONSE" : "DISCONNECT_RESPONSE", db_res);
        const std::string response = j.dump();
        return response;

    } else if (opJSON == "LOGOUTURI_REQUEST") {
        std::string userJSON;
        std::string uriJSON;
        jsonUtility::from_json_uri(jdata_in,userJSON, uriJSON); //get json value and put into JSON variables

        //Get data from db
        //const char *db_res = dbService::enumToStr(dbService::tryLogin(userJSON, passJSON));
        const char *db_res;

        dbService::DB_RESPONSE resp = dbService::tryLogout(userJSON, uriJSON);
        QSqlDatabase::removeDatabase("MyConnect2");

        if(resp == dbService::LOGOUT_OK) {
            fileUtility::writeFile(R"(..\Filesystem\)" + uriJSON + ".txt", room_.getMap().at(uriJSON));
            db_res = "LOGOUTURI_OK";
        }
        else if(resp == dbService::LOGOUT_FAILED)
            db_res = "LOGOUTURI_FAILED";
        else if(resp == dbService::DB_ERROR)
            db_res = "DB_ERROR";
        else if(resp == dbService::QUERY_ERROR)
            db_res = "QUERY_ERROR";
        else
            db_res = "DB_ERROR";

        json j;
        jsonUtility::to_json(j, "LOGOUTURI_RESPONSE", db_res);
        const std::string response = j.dump();
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
        const std::string response = j.dump();
        return response;

    } else if (opJSON == "NEWFILE_REQUEST") {
        std::string userJSON;
        std::string filenameJSON;
        jsonUtility::from_json_filename(jdata_in, userJSON, filenameJSON); //get json value and put into JSON variables

        //Get data from db
        //const char *db_res = dbService::enumToStr(dbService::tryLogin(userJSON, passJSON));
        const char *db_res;

        //update tables on db
        QString uri = dbService::generateURI(12);
        dbService::DB_RESPONSE resp = dbService::tryNewFile(userJSON, filenameJSON, uri);
        QSqlDatabase::removeDatabase("MyConnect3");

        //create file on local filesystem
        boost::filesystem::ofstream(R"(..\Filesystem\)" + uri.toStdString() + ".txt");

        if (resp == dbService::NEWFILE_OK) {
            db_res = "NEWFILE_OK";

            //Update session data
            shared_from_this()->setCurrentFile(uri.toStdString());
            room_.addEntryInMap(shared_from_this()->getCurrentFile(), std::vector<symbol>());

            //Serialize data
            json j;
            jsonUtility::to_json_newuri(j, "NEWFILE_RESPONSE", db_res, uri.toStdString());
            const std::string response = j.dump();
            return response;
        }
        else if(resp == dbService::NEWFILE_FAILED)
            db_res = "NEWFILE_FAILED";
        else if(resp == dbService::DB_ERROR)
            db_res = "DB_ERROR";
        else if(resp == dbService::QUERY_ERROR)
            db_res = "QUERY_ERROR";
        else
            db_res = "DB_ERROR";

        //Serialize data
        json j;
        jsonUtility::to_json(j, "NEWFILE_RESPONSE", db_res);
        const std::string response = j.dump();
        return response;

    } else if (opJSON == "LISTFILE_REQUEST") {
        std::string userJSON;
        jsonUtility::from_json_username(jdata_in, userJSON); //get json value and put into JSON variables

        //Get data from db
        //const char *db_res = dbService::enumToStr(dbService::tryLogin(userJSON, passJSON));
        const char *db_res;

        //check the list of file for the current user
        std::vector<File> vectorFile;
        dbService::DB_RESPONSE resp = dbService::tryListFile(userJSON, vectorFile);
        QSqlDatabase::removeDatabase("MyConnect2");

        if(resp == dbService::LIST_EXIST) {
            if(room_.getMap().empty()) {
                for (const auto &f: vectorFile)
                    room_.addEntryInMap(f.getidfile(), std::vector<symbol>());
            } else {
                for (const auto &f: vectorFile)
                    if (room_. getMap().count(f.getidfile()) <= 0) //key not exists
                        room_.addEntryInMap(f.getidfile(), std::vector<symbol>());
            }
            db_res = "LIST_EXIST";
        }
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
        std::vector<json> fileVectorJSON = jsonUtility::fromFileToJson(vectorFile);
        jsonUtility::to_json_fileVector(j, "LISTFILE_RESPONSE", db_res, fileVectorJSON);
        const std::string response = j.dump();
        return response;

    } else if (opJSON == "RENAMEFILE_REQUEST") {
        std::string newNameFileJson;
        std::string uriJson;
        std::string userJSON;
        jsonUtility::from_json_renameFile(jdata_in, newNameFileJson, uriJson,userJSON);

        //Get data from db
        //const char *db_res = dbService::enumToStr(dbService::tryLogin(userJSON, passJSON));
        const char *db_res;

        dbService::DB_RESPONSE resp = dbService::tryRenameFile(newNameFileJson, uriJson, userJSON);
        QSqlDatabase::removeDatabase("MyConnect3");
        curFile = shared_from_this()->getCurrentFile(); //send only the message to clients that have this currentFile opened

        if (resp == dbService::RENAME_OK)
            db_res = "RENAME_OK";
        else if(resp == dbService::RENAME_FAILED) {
            db_res = "RENAME_FAILED";
            onlyToThisEditor = true; //the error message popup must appear only to who made the request
        }
        else if(resp == dbService::QUERY_ERROR)
            db_res = "QUERY_ERROR";
        else
            db_res = "DB_ERROR";

        //Serialize data
        json j;
        jsonUtility::to_json_rename_file(j, "RENAMEFILE_RESPONSE", db_res, newNameFileJson);
        const std::string response = j.dump();
        return response;

    } else if (opJSON == "OPENFILE_REQUEST") {
        std::string userJSON;
        std::string uriJSON;
        jsonUtility::from_json_uri(jdata_in, userJSON, uriJSON); //get json value and put into JSON variables

        //Get data from db
        //const char *db_res = dbService::enumToStr(dbService::tryLogin(userJSON, passJSON));
        const char *db_res;

        //update tables on db
        dbService::DB_RESPONSE resp = dbService::tryOpenFile(userJSON, uriJSON);
        QSqlDatabase::removeDatabase("MyConnect2");

        if(resp == dbService::OPENFILE_OK) {
            //Update session data
            shared_from_this()->setCurrentFile(uriJSON);
            shared_from_this()->setSymbols(room_.getSymbolMap(uriJSON));

            //TODO: update flag! This means that while file is being sent, we have to mantain a queue containing all the modifications in between
            //TODO: after file has been sent, send to all the clients all the modifications present in previous created queue

            if(shared_from_this()->getSymbols().empty()) //file is empty (it can happen that one client save an empty file)
                db_res = "OPENFILE_FILE_EMPTY";
            else
                db_res = "OPENFILE_OK";

            //Serialize data
            json j;
            std::vector<json> symVectorJSON = jsonUtility::fromSymToJson(shared_from_this()->getSymbols());
            jsonUtility::to_json_symVector(j, "OPENFILE_RESPONSE", db_res, symVectorJSON);
            const std::string response = j.dump();
            return response;
        }
        else if(resp == dbService::OPENFILE_FAILED)
            db_res = "OPENFILE_FAILED";
        else if(resp == dbService::DB_ERROR)
            db_res = "DB_ERROR";
        else if(resp == dbService::QUERY_ERROR)
            db_res = "QUERY_ERROR";
        else
            db_res = "DB_ERROR";

        //Serialize data
        json j;
        jsonUtility::to_json(j, "OPENFILE_RESPONSE", db_res);
        const std::string response = j.dump();
        return response;

    } else if (opJSON == "OPENWITHURI_REQUEST") {
        std::string userJSON;
        std::string uriJSON;
        std::string filenameJSON;
        jsonUtility::from_json_uri(jdata_in, userJSON, uriJSON); //get json value and put into JSON variables

        //Get data from db
        //const char *db_res = dbService::enumToStr(dbService::tryLogin(userJSON, passJSON));
        const char *db_res;

        //update tables on db
        dbService::DB_RESPONSE resp = dbService::tryOpenWithURIFile(userJSON, uriJSON, filenameJSON);
        QSqlDatabase::removeDatabase("MyConnect3");

        if (resp == dbService::OPENWITHURI_OK) {
            //Update session data
            shared_from_this()->setCurrentFile(uriJSON);
            shared_from_this()->setSymbols(room_.getSymbolMap(uriJSON));

            //TODO: update flag! This means that while file is being sent, we have to mantain a queue containing all the modifications in between
            //TODO: after file has been sent, send to all the clients all the modifications present in previous created queue

            if(shared_from_this()->getSymbols().empty()) //file is empty (it can happen that one client save an empty file)
                db_res = "OPENFILE_FILE_EMPTY";
            else
                db_res = "OPENWITHURI_OK";

            //Serialize data
            json j;
            std::vector<json> symVectorJSON = jsonUtility::fromSymToJson(shared_from_this()->getSymbols());
            jsonUtility::to_json_symVectorAndFilename(j, "OPENWITHURI_RESPONSE", db_res, symVectorJSON, filenameJSON);
            const std::string response = j.dump();
            return response;
        }
        else if(resp == dbService::OPENWITHURI_FAILED)
            db_res = "OPENWITHURI_FAILED";
        else if(resp == dbService::DB_ERROR)
            db_res = "DB_ERROR";
        else if(resp == dbService::QUERY_ERROR)
            db_res = "QUERY_ERROR";
        else
            db_res = "DB_ERROR";

        //Serialize data
        json j;
        jsonUtility::to_json(j, "OPENWITHURI_RESPONSE", db_res);
        const std::string response = j.dump();
        return response;

    } else if (opJSON == "INVITE_URI_REQUEST") {
        std::string invitedJSON;
        std::string applicantJSON;
        std::string uriJSON;
        jsonUtility::from_json_inviteURI(jdata_in, invitedJSON, applicantJSON, uriJSON); //get json value and put into JSON variables

        // Get email related to that username
        const char *db_res2;
        std::string email_invited;
        dbService::DB_RESPONSE resp2 = dbService::tryGetEmail(invitedJSON, email_invited);
        QSqlDatabase::removeDatabase("MyConnect2");

        if(resp2 == dbService::GET_EMAIL_OK) {
            // Send email
            if(email::sendEmail(email_invited, uriJSON)) {
                const char *db_res;
                if(invitedJSON == applicantJSON){
                    db_res = "SAME_USER";
                } else {
                    dbService::DB_RESPONSE resp = dbService::tryAddFriend(invitedJSON, uriJSON);
                    QSqlDatabase::removeDatabase("MyConnect2");

                    if(resp == dbService::ALREADY_PARTECIPANT)
                        db_res = "ALREADY_PARTECIPANT";
                    else if(resp == dbService::INVITE_URI_SUCCESS)
                        db_res = "INVITE_URI_SUCCESS";
                    else if(resp == dbService::INVITE_URI_FAILED)
                        db_res = "INVITE_URI_FAILED";
                    else if(resp == dbService::QUERY_ERROR)
                        db_res = "QUERY_ERROR";
                    else if(resp == dbService::INVITED_NOT_EXIST)
                        db_res = "INVITED_NOT_EXIST";
                    else
                        db_res = "DB_ERROR";
                }
                json j;
                jsonUtility::to_json(j, "INVITE_URI_RESPONSE", db_res);
                const std::string response = j.dump();
                return response;
            }
            else {
                const char *db_res = "SEND_EMAIL_FAILED";
                json j;
                jsonUtility::to_json(j, "INVITE_URI_RESPONSE", db_res);
                const std::string response = j.dump();
                return response;
            }
        } else if(resp2 == dbService::INVITED_NOT_EXIST) {
            db_res2 = "INVITED_NOT_EXIST";
        } else if(resp2 == dbService::QUERY_ERROR) {
            db_res2 = "QUERY_ERROR";
        } else {
            db_res2 = "DB_ERROR";
        }
        json j;
        jsonUtility::to_json(j, "INVITE_URI_RESPONSE", db_res2);
        const std::string response = j.dump();
        return response;

    } else if (opJSON == "INSERTION_REQUEST") {
        std::pair<int, wchar_t> tupleJSON;
        jsonUtility::from_json_insertion(jdata_in, tupleJSON); //get json value and put into JSON variables
        std::cout << "tuple received: " << tupleJSON.first << "," << tupleJSON.second << std::endl;

        //Construct msgInfo
        msgInfo m = localInsert(tupleJSON.first, tupleJSON.second);
        std::cout << "msgInfo constructed: " << m.toString() << std::endl;

        //Update room symbols for this file
        room_.updateMap(shared_from_this()->getCurrentFile(),shared_from_this()->getSymbols());

        //Dispatch message to all the clients
        room_.send(m);
        room_.dispatchMessages();
        edId = m.getEditorId(); //don't send this message to this editor
        curFile = shared_from_this()->getCurrentFile(); //send only the message to clients that have this currentFile opened

        //Serialize data
        json j;
        jsonUtility::to_json_insertion(j, "INSERTION_RESPONSE", std::pair<int, wchar_t>(m.getNewIndex(), tupleJSON.second));
        const std::string response = j.dump();
        return response;

    } else if (opJSON == "REMOVAL_REQUEST") {
        int indexJSON;
        jsonUtility::from_json_removal(jdata_in, indexJSON); //get json value and put into JSON variables
        std::cout << "index received: " << std::to_string(indexJSON) << std::endl;

        //Construct msgInfo
        msgInfo m = localErase(indexJSON);
        std::cout << "msgInfo constructed: " << m.toString() << std::endl;

        //Update room symbols for this file
        room_.updateMap(shared_from_this()->getCurrentFile(),shared_from_this()->getSymbols());

        //Dispatch message to all the clients
        room_.send(m);
        room_.dispatchMessages();
        edId = m.getEditorId(); //don't send this message to this editor
        curFile = shared_from_this()->getCurrentFile(); //send only the message to clients that have this currentFile opened

        //Serialize data
        json j;
        jsonUtility::to_json_removal(j, "REMOVAL_RESPONSE", indexJSON);
        const std::string response = j.dump();
        return response;

    } else if (opJSON == "REMOVALRANGE_REQUEST") {
        int startIndexJSON;
        int endIndexJSON;
        jsonUtility::from_json_removal_range(jdata_in, startIndexJSON, endIndexJSON); //get json value and put into JSON variables
        std::cout << "[REMOVALRANGE] indexes received: " << std::to_string(startIndexJSON) << " - " << std::to_string(endIndexJSON) << std::endl;

        //Construct msgInfo
        msgInfo m = localErase(startIndexJSON, endIndexJSON);
        std::cout << "msgInfo constructed: " << m.toString() << std::endl;

        //Update room symbols for this file
        room_.updateMap(shared_from_this()->getCurrentFile(),shared_from_this()->getSymbols());

        //Dispatch message to all the clients
        room_.send(m);
        room_.dispatchMessages();
        edId = m.getEditorId(); //don't send this message to this editor
        curFile = shared_from_this()->getCurrentFile(); //send only the message to clients that have this currentFile opened

        //Serialize data
        json j;
        jsonUtility::to_json_removal_range(j, "REMOVALRANGE_RESPONSE", startIndexJSON, endIndexJSON);
        const std::string response = j.dump();
        return response;

    } else if (opJSON == "INSERTIONRANGE_REQUEST") {
        std::vector<json> formattingSymbolsJSON;
        jsonUtility::from_json_insertion_range(jdata_in, formattingSymbolsJSON);
        std::vector<symbol_formatting> formattingSymbols = jsonUtility::fromJsonToFormattingSym(formattingSymbolsJSON);
        int firstIndexRange = 0;
        bool firstTime = true;
        std::vector<symbol> symbols;

        for(symbol_formatting sf: formattingSymbols) {
            //Construct msgInfo
            msgInfo m = localInsert(sf.getIndex(), sf.getLetter()); //TODO: add formatting
            std::cout << "msgInfo constructed: " << m.toString() << std::endl;

            symbols.push_back(m.getSymbol());

            //Save first index
            if(firstTime) {
                firstIndexRange = m.getNewIndex();
                edId = m.getEditorId(); //don't send this message to this editor
                firstTime = false;
            }

            //Update room symbols for this file
            room_.updateMap(shared_from_this()->getCurrentFile(),shared_from_this()->getSymbols());

            //Dispatch message to all the clients TODO: maybe dispatch outside for loop
            room_.send(m);
            room_.dispatchMessages();
        }

        curFile = shared_from_this()->getCurrentFile(); //send only the message to clients that have this currentFile opened

        //Serialize data
        json j;
        std::vector<json> symbolsJSON = jsonUtility::fromSymToJson(symbols);
        jsonUtility::to_json_insertion_range(j, "INSERTIONRANGE_RESPONSE", firstIndexRange, symbolsJSON);
        const std::string response = j.dump();
        return response;

    } else { //editor functions
        room_.deliver(read_msg_); //deliver to all the participants
    }
}

#pragma clang diagnostic pop

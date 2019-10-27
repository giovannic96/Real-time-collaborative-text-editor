#include "myClient.h"
#include <qtextcodec.h>
#include <iostream>
#include <QMessageBox>

typedef std::deque<message> message_queue;

myClient::myClient()
        : work_(new boost::asio::io_context::work(io_context_)),
          resolver_(io_context_),
          socket_(io_context_),
          username_("") {
    worker_= std::thread([&](){
       io_context_.run(); //boost thread loop start
    });
    do_connect();
}

myClient::~myClient() {
    work_.reset();
    this->close();
    worker_.join();
}

void myClient::do_connect() {
    auto endpoints = resolver_.resolve("127.0.0.1", "63504");
    boost::asio::async_connect(socket_, endpoints,
                               [this](boost::system::error_code ec, const tcp::endpoint&) {
       if (!ec) {
           status = true;
           emit statusChanged(status);
           do_read_header();
       } else {
           qDebug() << ec.message().c_str() << endl;
           status = false;
           emit statusChanged(status);
       }
   });
}

void myClient::do_read_header() {
    memset(read_msg_.data(), 0, read_msg_.length()); //VERY IMPORTANT, otherwise rubbish remains inside socket!
    boost::asio::async_read(socket_,
                            boost::asio::buffer(read_msg_.data(), message::header_length),
                            [this](boost::system::error_code ec, std::size_t /*length*/) {
        if (!ec && read_msg_.decode_header()) {
            do_read_body();
        }
        else {
            qDebug() << ec.message().c_str() << endl;
            closeConnection();
        }
    });
}

void myClient::do_read_body() {
    boost::asio::async_read(socket_,
                            boost::asio::buffer(read_msg_.body(), read_msg_.body_length()),
                            [this](boost::system::error_code ec, std::size_t /*length*/) {
        if (!ec) {
            qDebug() << "read msg:" << read_msg_.body() << endl;

            std::string opJSON;
            json jdata_in = json::parse(read_msg_.body());
            try {
                jsonUtility::from_json(jdata_in, opJSON); //get json value and put into JSON variables
            } catch (json::type_error& e) {
                std::cerr << e.what() << '\n';
            }
            std::cout << "opJSON is:" << opJSON << "END" << std::endl;
            if(opJSON == "LOGIN_RESPONSE") {
                std::string db_responseJSON;
                jsonUtility::from_json_resp(jdata_in, db_responseJSON); //get json value and put into JSON variables

                if(db_responseJSON == "LOGIN_OK") {
                    qDebug() << "Login success" << endl;
                    std::string db_usernameLoginJSON;
                    jsonUtility::from_json_usernameLogin(jdata_in, db_usernameLoginJSON);
                    QString name_qstring = QString::fromUtf8(db_usernameLoginJSON.data(), db_usernameLoginJSON.size()); //convert to QString
                    this->setUsername(name_qstring);
                    emit changeTextUsername(this->getUsername());
                    emit formResult("LOGIN_SUCCESS", "Login Success", "Login successfully completed");
                } else {
                    qDebug() << "Wrong user or password" << endl;
                    emit formResult("LOGIN_FAILURE", "Login Failed", "Login not completed: wrong user or password");
                }
            } else if(opJSON == "SIGNUP_RESPONSE") {
                std::string db_responseJSON;
                jsonUtility::from_json_resp(jdata_in, db_responseJSON); //get json value and put into JSON variables

                if(db_responseJSON == "SIGNUP_OK") {
                    qDebug() << "Signup success" << endl;
                    emit formResult("SIGNUP_SUCCESS", "Signup Success", "Signup successfully completed");
                } else {
                    qDebug() << "Something went wrong" << endl;
                    emit formResult("SIGNUP_FAILURE", "Signup Failed", "Signup not completed: something went wrong");
                }
            }

            //TODO: NEWFILE_RESPONSE

            //TODO: OPENFILE_RESPONSE

            do_read_header(); //continue reading loop
        }
        else {
            qDebug() << ec.message().c_str() << endl;
            closeConnection();
        }
    });
}

void myClient::do_write() {
    boost::asio::async_write(socket_,
                             boost::asio::buffer(write_msgs_.front().data(), write_msgs_.front().length()),
                             [this](boost::system::error_code ec, std::size_t /*length*/) {
         if (!ec) {
             qDebug() << "Sent:" << write_msgs_.front().data() << "END" << endl;
             write_msgs_.pop_front();
             if (!write_msgs_.empty()) {
                 do_write();
             }
         }
         else {
             qDebug() << ec.message().c_str() << endl;
             closeConnection();
         }
     });
}

bool myClient::getStatus() {
    return status;
}

void myClient::closeConnection() {
    status = false;
    emit statusChanged(status);
    socket_.close();
}

void myClient::write(const message& msg) {
    boost::asio::post(io_context_, [this, msg]() {
      bool write_in_progress = !write_msgs_.empty();
      write_msgs_.push_back(msg);
      if (!write_in_progress) {
          do_write();
      }
  });
}

void myClient::close() {
    boost::asio::post(io_context_, [this]() {
        closeConnection();
    });
}

void myClient::setUsername(QString name) {
    this->username_ = name;
}

QString myClient::getUsername() {
    return this->username_;
}

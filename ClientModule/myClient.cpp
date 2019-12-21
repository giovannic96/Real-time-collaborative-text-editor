#include "myClient.h"
#include <qtextcodec.h>
#include <QMessageBox>
#include <QtWidgets/QApplication>

typedef std::deque<message> message_queue;

myClient::myClient()
        : work_(new boost::asio::io_context::work(io_context_)),
          resolver_(io_context_),
          socket_(io_context_),
          username_(""),
          mail_(""),
          fileVector_(std::vector<File>()),
          vector_() {
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
           qDebug() << ec.message().c_str();
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
            qDebug() << "Lunghezza messaggio"<<read_msg_.length();
            qDebug() << "read msg:" << read_msg_.body() << endl;
            read_msg_.data()[read_msg_.length()] = '\0';  //VERY IMPORTANT: this removes any possible letters after data

            std::string opJSON;
            try{
                json jdata_in = json::parse(read_msg_.body());
                jsonUtility::from_json(jdata_in, opJSON);

                if(opJSON == "LOGIN_RESPONSE") {
                    std::string db_responseJSON;
                    jsonUtility::from_json_resp(jdata_in, db_responseJSON);

                    if(db_responseJSON == "LOGIN_OK") {
                        qDebug() << "Login success" << endl;
                        std::string db_usernameLoginJSON;
                        jsonUtility::from_json_usernameLogin(jdata_in, db_usernameLoginJSON);
                        QString name_qstring = QString::fromUtf8(db_usernameLoginJSON.data(), db_usernameLoginJSON.size()); //convert to QString

                        this->setUsername(name_qstring);
                        emit changeTextUsername(this->getUsername());
                        emit changeTextMail(this->getMail());
                        emit formResultSuccess("LOGIN_SUCCESS");
                    } else {
                        qDebug() << "Wrong user or password" << endl;
                        emit formResultFailure("LOGIN_FAILURE");
                    }
                } else if(opJSON == "SIGNUP_RESPONSE") {
                    std::string db_responseJSON;
                    jsonUtility::from_json_resp(jdata_in, db_responseJSON);

                    if(db_responseJSON == "SIGNUP_OK") {
                        emit formResultSuccess("SIGNUP_SUCCESS");
                    } else {
                        emit formResultFailure("SIGNUP_FAILURE");
                    }
                } else if(opJSON == "LOGOUT_RESPONSE") {
                    std::string db_responseJSON;
                    jsonUtility::from_json_resp(jdata_in, db_responseJSON);

                    if(db_responseJSON == "LOGOUT_OK") {
                        emit opResultSuccess("LOGOUT_SUCCESS");
                    } else {
                        emit opResultFailure("LOGOUT_FAILURE");
                    }
                } else if(opJSON == "DISCONNECT_RESPONSE") {
                    std::string db_responseJSON;
                    jsonUtility::from_json_resp(jdata_in, db_responseJSON);

                    if(db_responseJSON == "LOGOUT_OK") {
                        emit opResultSuccess("DISCONNECT_SUCCESS");
                    } else {
                        emit opResultFailure("DISCONNECT_FAILURE");
                    }
                } else if(opJSON == "LOGOUTURI_RESPONSE") {
                    std::string db_responseJSON;
                    jsonUtility::from_json_resp(jdata_in, db_responseJSON);

                    if(db_responseJSON == "LOGOUTURI_OK") {
                        emit editorResultSuccess("LOGOUTURI_SUCCESS");
                        emit backToMenuWindow();
                    } else {
                        emit editorResultFailure("LOGOUTURI_FAILURE");
                    }
                } else if(opJSON == "NEWFILE_RESPONSE") {
                    std::string db_responseJSON;
                    jsonUtility::from_json_resp(jdata_in, db_responseJSON);

                    if(db_responseJSON == "NEWFILE_OK") {
                        std::string uriJSON;
                        jsonUtility::from_jsonUri(jdata_in, uriJSON); //get json value and put into JSON variables
                        QString uriQString = QString::fromUtf8(uriJSON.data(), uriJSON.size());

                        //Update client data
                        this->setFileURI(uriQString);
                        this->setVector(std::vector<symbol>());
                        emit opResultSuccess("NEWFILE_SUCCESS");
                    } else {
                        emit opResultFailure("NEWFILE_FAILURE");
                    }

                } else if(opJSON == "OPENFILE_RESPONSE") {
                    std::string db_responseJSON;
                    jsonUtility::from_json_resp(jdata_in, db_responseJSON);

                    if(db_responseJSON == "OPENFILE_OK") {
                        std::vector<json> jsonSymbols;
                        jsonUtility::from_json_symbols(jdata_in, jsonSymbols);

                        std::vector<symbol> symbols;
                        for(const auto& j: jsonSymbols) {
                            symbol *s = nullptr; //do not remember to delete it! (keyword 'delete')

                            s = jsonUtility::from_json_symbol(j);
                            if(s==nullptr){
                                //SHOW ERROR
                                emitMsgInCorrectWindow();
                                do_read_header();
                            }
                            symbols.push_back(*s);
                            delete s;
                        }

                        //Update client data
                        this->setVector(symbols);

                        emit opResultSuccess("OPENFILE_SUCCESS");
                    } else if(db_responseJSON == "OPENFILE_FILE_EMPTY") {

                        //Update client data
                        this->setVector(std::vector<symbol>());
                        emit opResultSuccess("OPENFILE_SUCCESS");
                    } else {
                        emit opResultFailure("OPENFILE_FAILURE");
                    }

                } else if(opJSON == "RENAMEFILE_RESPONSE") {
                    std::string db_responseJSON;
                    std::string filenameJSON;
                    jsonUtility::from_json_rename_file(jdata_in, db_responseJSON, filenameJSON);

                    if(db_responseJSON == "RENAME_OK") {
                        emit editorResultSuccess("RENAME_SUCCESS", filenameJSON.c_str());
                    } else {
                        emit editorResultFailure("RENAME_FAILURE");
                    }

                } else if(opJSON == "OPENWITHURI_RESPONSE") {
                    std::string db_responseJSON;
                    jsonUtility::from_json_resp(jdata_in, db_responseJSON);

                    if(db_responseJSON == "OPENWITHURI_OK") {
                        std::vector<json> jsonSymbols;
                        std::string filenameJSON;
                        jsonUtility::from_json_symbolsAndFilename(jdata_in, jsonSymbols, filenameJSON);

                        std::vector<symbol> symbols;
                        for(const auto& j: jsonSymbols) {
                            symbol *s = nullptr; //do not remember to delete it! (keyword 'delete')
                            s = jsonUtility::from_json_symbol(j);
                            if(s==nullptr){
                                //SHOW ERROR
                                emitMsgInCorrectWindow();
                                do_read_header();
                            }
                            symbols.push_back(*s);
                            delete s;
                        }

                        //Update client data
                        this->setFilename(QString::fromStdString(filenameJSON));
                        this->setVector(symbols);

                        qDebug() << "OPENWITHURI success" << endl;
                        emit opResultSuccess("OPENWITHURI_SUCCESS");
                    } else if(db_responseJSON == "OPENFILE_FILE_EMPTY") {
                        std::string filenameJSON;
                        jsonUtility::from_json_filename(jdata_in, filenameJSON);

                        //Update client data
                        this->setFilename(QString::fromStdString(filenameJSON));
                        this->setVector(std::vector<symbol>());
                        emit opResultSuccess("OPENFILE_SUCCESS");
                    } else {
                        qDebug() << "Something went wrong" << endl;
                        emit opResultFailure("OPENWITHURI_FAILURE");
                    }
                } else if(opJSON == "LISTFILE_RESPONSE") {
                    std::string db_responseJSON;
                    jsonUtility::from_json_resp(jdata_in, db_responseJSON);

                    if(db_responseJSON == "LIST_EXIST") {
                        qDebug() << "La lista esiste" << endl;

                        std::vector<json> jsonFiles;
                        jsonUtility::from_json_files(jdata_in, jsonFiles);

                        std::vector<File> files;
                        for(const auto& j: jsonFiles) {
                            File *f = nullptr; //do not remember to delete it! (keyword 'delete')
                            f = jsonUtility::from_json_file(j);
                            if(f==nullptr){
                                //SHOW ERROR
                                emitMsgInCorrectWindow();
                                do_read_header();
                            }
                            files.push_back(*f);
                            delete f;
                        }
                        emit listFileResult(files);

                        qDebug() << "Listfile success" << endl;
                        emit opResultSuccess("LISTFILE_SUCCESS");
                    } else if (db_responseJSON == "LIST_DOESNT_EXIST"){
                        qDebug() << "Non ha nessuna lista di file" << endl;
                        emit opResultFailure("LISTFILE_FAILURE_LISTNOTEXIST");
                    } else {
                        qDebug() << "Something went wrong" << endl;
                        emit opResultFailure("LISTFILE_FAILURE");
                    }
                } else if(opJSON == "INVITE_URI_RESPONSE") {
                    std::string db_responseJSON;
                    jsonUtility::from_json_inviteURI(jdata_in, db_responseJSON);

                    if(db_responseJSON == "INVITE_URI_SUCCESS") {
                        emit editorResultSuccess("INVITE_URI_SUCCESS");
                    } else if(db_responseJSON == "ALREADY_PARTECIPANT") {
                        emit editorResultFailure("ALREADY_PARTECIPANT");
                    } else if(db_responseJSON == "INVITED_NOT_EXIST") {
                        emit editorResultFailure("INVITED_NOT_EXIST");
                    } else if(db_responseJSON == "SAME_USER") {
                        emit editorResultFailure("SAME_USER");
                    } else if(db_responseJSON == "SEND_EMAIL_FAILED") {
                        emit editorResultFailure("SEND_EMAIL_FAILED");
                    } else {
                        emit editorResultFailure("INVITE_URI_FAILURE");
                    }
                } else if(opJSON == "INSERTION_RESPONSE") {
                    std::pair<int, wchar_t> tupleJSON;
                    jsonUtility::from_json_insertion(jdata_in, tupleJSON);
                    emit insertSymbol(tupleJSON);
                } else if(opJSON == "INSERTIONRANGE_RESPONSE") {
                    int firstIndex;
                    std::vector<json> jsonSymbols;
                    jsonUtility::from_json_insertion_range(jdata_in, firstIndex, jsonSymbols);
                    std::vector<symbol> symbols;

                    //generate symbols vector from json vector
                    for(const auto& j: jsonSymbols) {
                        symbol *s = nullptr; //do not remember to delete it! (keyword 'delete')
                        s = jsonUtility::from_json_symbol(j);
                        if(s==nullptr){
                            //SHOW ERROR
                            emitMsgInCorrectWindow();
                            do_read_header();
                        }
                        symbols.push_back(*s);
                        delete s;
                    }
                    emit insertSymbols(firstIndex, symbols);
                } else if(opJSON == "REMOVAL_RESPONSE") {
                    int indexJSON;
                    jsonUtility::from_json_removal(jdata_in, indexJSON);
                    emit eraseSymbol(indexJSON);
                } else if(opJSON == "REMOVALRANGE_RESPONSE") {
                    int startIndexJSON;
                    int endIndexJSON;
                    jsonUtility::from_json_removal_range(jdata_in, startIndexJSON, endIndexJSON);
                    emit eraseSymbols(startIndexJSON, endIndexJSON);
                } else {
                    qDebug() << "Something went wrong" << endl;
                    emit opResultFailure("RESPONSE_FAILURE");
                }
                do_read_header(); //continue reading loop

            } catch (json::exception& e){
                // output exception information
                         std::cerr << "message: " << e.what() << '\n' << "exception id: " << e.id << std::endl;
                emitMsgInCorrectWindow();
                do_read_header();
            }
        }
        else {
            qDebug() << ec.message().c_str() << endl;
            closeConnection();
        }
    });

}

void myClient::emitMsgInCorrectWindow(){
    emit jsonMsgFailure("StartWindow","Si è verificato un errore nel parsing del json.");
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

void myClient::setMail(QString mail) {
    this->mail_ = mail;
}

QString myClient::getUsername() {
    return this->username_;
}

QString myClient::getMail() {
    return this->mail_;
}

void myClient::setVector(std::vector<symbol> symbols){
    this->vector_ = symbols;
}

void myClient::setVectorFile(std::vector<File> files){
    this->fileVector_ = files;
}

std::vector<File> myClient::getVectorFile(){
    return this->fileVector_;
}

std::vector<symbol> myClient::getVector(){
    return this->vector_;
}

void myClient::setFilename(QString filename) {
    this->filename_ = filename;
}

QString myClient::getFilename() {
    return this->filename_;
}

void myClient::setFileURI(QString uri) {
    this->uri_ = uri;
}

QString myClient::getFileURI() {
    return this->uri_;
}

#include "myClient.h"
#include <qtextcodec.h>
#include <iostream>

typedef std::deque<message> message_queue;

myClient::myClient()
        : work_(new boost::asio::io_context::work(io_context_)),
          resolver_(io_context_),
          socket_(io_context_) {
    worker_= std::thread([&](){
       io_context_.run();
    });
}

myClient::~myClient() {
    work_.reset();
    this->close();
    worker_.join();
}

/*
myClient::myClient(
        const QString hostAddress,
        int portNumber,
        QObject *parent
        ) : QObject(parent), m_nNextBlockSize(0)
{
    status = false;

    host = hostAddress;
    port = portNumber;

    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket, &QTcpSocket::disconnected, this, &myClient::closeConnection);

    timeoutTimer = new QTimer();
    timeoutTimer->setSingleShot(true);
    connect(timeoutTimer, &QTimer::timeout, this, &myClient::connectionTimeout);
}
*/

void myClient::do_connect() {
    auto endpoints = resolver_.resolve("127.0.0.1", "63504");
    boost::asio::async_connect(socket_, endpoints,
                               [this](boost::system::error_code ec, const tcp::endpoint&) {
       if (!ec) {
           do_read_header();
       } else {
           qDebug() << ec.message().c_str() << endl;
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
            socket_.close();
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
                std::cout << "Db response received:" << db_responseJSON << "END" << std::endl;

                if(db_responseJSON == "LOGIN_OK") {
                    qDebug() << "Login success" << endl;
                    //POPUP MESSAGE: "Login success"
                    //Go to the next window
                } else {
                    qDebug() << "Wrong user or password" << endl;
                    //POPUP MESSAGE: "WRONG USER AND PASSWORD"
                    //Stay in the same window
                }
            }
            do_read_header(); //continue reading loop
        }
        else {
            socket_.close();
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
             socket_.close();
         }
     });
}

void myClient::connect2host()
{
    /*
    timeoutTimer->start(3000);

    tcpSocket->connectToHost(host, port);
    connect(tcpSocket, &QTcpSocket::connected, this, &myClient::connected);
    connect(tcpSocket, &QTcpSocket::readyRead, this, &myClient::readyRead);
    */
}

void myClient::connectionTimeout() {
    if(tcpSocket->state() == QAbstractSocket::ConnectingState)
    {
        tcpSocket->abort();
        emit tcpSocket->error(QAbstractSocket::SocketTimeoutError);
    }
}

void myClient::connected() {
    status = true;
    emit statusChanged(status);
}

bool myClient::getStatus() {
    return status;
}

void myClient::readyRead()
{
    QDataStream in(tcpSocket);
    //in.setVersion(QDataStream::Qt_5_10);
    //for (;;)
    //{
        tcpSocket->bytesAvailable();
        qDebug() << "recvd signal data. bytesAvailable:" << tcpSocket->bytesAvailable();
        QString str = QString::fromUtf8(tcpSocket->readAll());
        //QString str = QString::fromStdString(tcpSocket->readAll().toStdString());
        qDebug() << "recvd: " << str;
        if (str == "0") {
            str = "Connection closed";
            closeConnection();
        }
        emit hasReadSome(str);

        /*

        if (!m_nNextBlockSize)
        {
            if (tcpSocket->bytesAvailable() < sizeof(quint16)) { break; }
            in >> m_nNextBlockSize;
        }

        if (tcpSocket->bytesAvailable() < m_nNextBlockSize) { break; }

        QString str; in >> str;

        if (str == "0")
        {
            str = "Connection closed";
            closeConnection();
        }

        emit hasReadSome(str);
        m_nNextBlockSize = 0;
        */
    //}
}

//void ClientStuff::gotDisconnection()
//{
//    status = false;
//    emit statusChanged(status);
//}

void myClient::closeConnection()
{
    timeoutTimer->stop();

    //qDebug() << tcpSocket->state();
    disconnect(tcpSocket, &QTcpSocket::connected, nullptr, nullptr);
    disconnect(tcpSocket, &QTcpSocket::readyRead, nullptr, nullptr);

    bool shouldEmit = false;
    switch (tcpSocket->state())
    {
        case 0:
            tcpSocket->disconnectFromHost();
            shouldEmit = true;
            break;
        case 2:
            tcpSocket->abort();
            shouldEmit = true;
            break;
        default:
            tcpSocket->abort();
    }

    if (shouldEmit)
    {
        status = false;
        emit statusChanged(status);
    }
}

void myClient::write(const message& msg)
{
    boost::asio::post(io_context_, [this, msg]() {
      bool write_in_progress = !write_msgs_.empty();
      write_msgs_.push_back(msg);
      if (!write_in_progress) {
          do_write();
      }
  });
}

void myClient::close()
{
    boost::asio::post(io_context_, [this]() { socket_.close(); });
}

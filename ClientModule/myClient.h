#ifndef MYCLIENT_H
#define MYCLIENT_H

#include <boost/asio.hpp>
#include <QString>
#include <QTcpSocket>
#include <QDataStream>
#include <QTimer>
#include <thread>
#include <memory>
#include "message.h"
#include <deque>
#include "jsonUtility.h"

using boost::asio::ip::tcp;
typedef std::deque<message> message_queue;

class myClient : public QObject
{
    Q_OBJECT

public:
    myClient();
    virtual ~myClient();
    void do_connect();

    QTcpSocket *tcpSocket;
    bool getStatus();
    QString getUsername();
    void setUsername(QString name);
    void close();
    void write(const message& msg);    

signals:
    void statusChanged(bool);
    void formResult(QString result, QString title, QString msg);
    void changeTextUsername(QString text);

private:
    boost::asio::io_context io_context_;
    std::shared_ptr<boost::asio::io_context::work> work_;
    std::thread worker_;
    tcp::resolver resolver_;
    tcp::socket socket_;
    message read_msg_;
    message_queue write_msgs_;
    void do_read_header();
    void do_read_body();
    void do_write();
    void closeConnection();
    bool status;
    QString username_;
};

#endif // MYCLIENT_H

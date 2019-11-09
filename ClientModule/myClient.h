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
#include "symbol.h"
#include "File.h"

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
    QString getFilename();
    QString getFileURI();
    void setUsername(QString name);
    void setFilename(QString filename);
    void setFileURI(QString uri);
    void close();
    void write(const message& msg);    

signals:
    void statusChanged(bool);
    void formResultSuccess(QString result);
    void formResultFailure(QString result);
    void opResultSuccess(QString result);
    void opResultFailure(QString result);
    void editorResultSuccess(QString result);
    void editorResultFailure(QString result);
    void changeTextUsername(QString text);
    void listFileResult(std::vector<File> files);

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
    QString filename_;
    QString uri_;
};

#endif // MYCLIENT_H

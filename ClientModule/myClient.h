#ifndef MYCLIENT_H
#define MYCLIENT_H

#include <boost/asio.hpp>
#include <QString>
#include <QDataStream>
#include <QTimer>
#include <thread>
#include <memory>
#include "message.h"
#include <deque>
#include "jsonUtility.h"
#include "symbol.h"
#include "symbolInfo.h"
#include "File.h"
#include <QDebug>
#include <iostream>


using boost::asio::ip::tcp;
typedef std::deque<message> message_queue;

class myClient : public QObject
{
    Q_OBJECT

public:
    myClient();
    virtual ~myClient();
    void do_connect();

    bool getStatus();
    QString getUsername();
    QString getMail();
    QString getFilename();
    QString getFileURI();
    std::vector<File> getVectorFile();
    std::vector<symbol> getVector();
    void setUsername(QString name);
    void setMail(QString mail);
    void setFilename(QString filename);
    void setFileURI(QString uri);
    void setVector(std::vector<symbol> symbols);
    void setVectorFile(std::vector<File> fileVector);
    void close();
    void write(const message& msg);

signals:
    void statusChanged(bool);
    void formResultSuccess(QString result);
    void formResultFailure(QString result);
    void opResultSuccess(QString result);
    void opResultFailure(QString result);
    void editorResultSuccess(QString result, std::string filename = "");
    void editorResultFailure(QString result);
    void backToMenuWindow();
    void changeTextUsername(QString text);
    void changeTextMail(QString mail);
    void listFileResult(std::vector<File> files);
    void insertSymbol(std::pair<int, wchar_t> tuple, symbolStyle style);
    void insertSymbols(int firstIndex, std::vector<symbol> symbols);
    void eraseSymbol(int index);
    void eraseSymbols(int startIndex, int endIndex);
    void formatSymbols(int startIndex, int endIndex, int format);
    void jsonMsgFailure(QString windowName, QString msg);

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
    void emitMsgInCorrectWindow();
    bool status;
    QString username_;
    QString filename_;
    QString uri_;
    QString mail_;
    std::vector<File> fileVector_;
    std::vector<symbol> vector_;
};

#endif // MYCLIENT_H

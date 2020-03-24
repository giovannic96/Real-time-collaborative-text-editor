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
typedef std::map<std::string, std::pair<std::string,bool>> myCollabColorsMap;
Q_DECLARE_METATYPE(myCollabColorsMap)

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
    QString getColor();
    std::vector<File> getVectorFile();
    std::vector<symbol> getVector();
    void setUsername(QString name);
    void setMail(QString mail);
    void setFilename(QString filename);
    void setFileURI(QString uri);
    void setColor(QString color);
    void setVector(std::vector<symbol> symbols);
    void setVectorFile(std::vector<File> fileVector);
    void close();
    void write(const message& msg);
    void sendRequestMsg(std::string request);

signals:
    void statusChanged(bool);
    void formResultSuccess(QString result);
    void formResultFailure(QString result);
    void opResultSuccess(QString result);
    void opResultFailure(QString result);
    void editorResultSuccess(QString result, std::string filename = "");
    void editorResultFailure(QString result);
    void backToMenuWindow();
    /*
    void changeTextUsername(QString text);
    void changeTextMail(QString mail);
    */
    void listFileResult(std::vector<File> files);
    void insertSymbol(std::pair<int, wchar_t> tuple, symbolStyle style);
    void insertSymbols(int firstIndex, std::vector<symbol> symbols);
    void eraseSymbols(int startIndex, int endIndex);
    void formatSymbols(int startIndex, int endIndex, int format);
    void changeFontSize(int startIndex, int endIndex, int fontSize);
    void changeFontFamily(int startIndex, int endIndex, std::string fontFamily);
    void changeAlignment(int startBlock, int endBlock, int alignment);
    void jsonMsgFailure(QString windowName, QString msg);
    void removeRemoteCursor(std::string username);
    void getUserOffline(myCollabColorsMap collabColorsMap);
    void getUserOnline(myCollabColorsMap collabColorsMap);
    void changeRemoteCursor(std::string username, std::string color, int pos);
    void showCollabColorsMap(myCollabColorsMap collabColorsMap);

private:
    boost::asio::io_context io_context_;
    std::shared_ptr<boost::asio::io_context::work> work_;
    std::thread worker_;
    tcp::resolver resolver_;
    tcp::socket socket_;
    std::string fullBody;
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
    QString color_;
    std::vector<File> fileVector_;
    std::vector<symbol> vector_;
};

#endif // MYCLIENT_H

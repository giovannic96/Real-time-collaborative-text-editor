//  CLASS StartMenu - v0.1.4a
#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QMainWindow>
#include <QtGui>            //QPoint
#include <boost/asio.hpp>
#include <deque>
#include "versioninfo.h"
#include "myClient.h"
#include "json.hpp"
#include "jsonUtility.h"

namespace Ui {class StartWindow;}

class StartWindow : public QMainWindow{
    Q_OBJECT

public:
    StartWindow(QWidget *parent = nullptr); //Constructor
    ~StartWindow();                         //Destructor

private slots:
    void on_exitButton_clicked();
    void on_ForgotPasswordButton_clicked();
    void on_LoginAdmin_clicked();
    void on_RegisterButton_clicked();
    void on_LoginButton_clicked();
    void on_SignUpButton_clicked();
    void on_AccediButton_clicked();
    void on_openDoc_clicked();
    void on_listFiles_clicked();

public slots:
    void setStatus(bool newStatus);
    void labelChangeText(QString text);
    void showFormPopup(QString result, QString title, QString msg);

private:
    Ui::StartWindow *ui;            //"ui" (user interface)
    //For mouse related event
    QPoint oldPos;                  //This "oldPos" object is used to save the old position of the windows for the translation of windows
    //For "version" QString
    VersionInfo version;
    QString qstr = version.getVersion();
    //For client
    myClient *client;
    void sendRequestMsg(const char* req);

protected:
    //Function for mouse related event
    void mousePressEvent(QMouseEvent *evt);
    void mouseMoveEvent(QMouseEvent *evt);

};
#endif // STARTWINDOW_H

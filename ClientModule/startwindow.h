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
    void on_RegisterButton_clicked();
    void on_LoginButton_clicked();
    void on_SignUpButton_clicked();
    void on_AccediButton_clicked();
    //FOR LOGIN PAGE
    void on_LoginPasswordForm_returnPressed();
    void on_LoginUsernameForm_returnPressed();
    //FOR REG PAGE
    void on_RegUsernameForm_returnPressed();
    void on_RegPasswordForm_returnPressed();
    void on_RegMailForm_returnPressed();
    void on_RegPasswordForm_editingFinished();
    void on_RegMailForm_editingFinished();

    void on_RegUsernameForm_editingFinished();

    void on_eyeButton_clicked();

public slots:
    void setStatus(bool newStatus);
    void showPopupSuccess(QString result);
    void showPopupFailure(QString result);
    void showJsonPopupFailure(QString windowName,QString msg);

private:
    Ui::StartWindow *ui;            //"ui" (user interface)
    QPoint oldPos;                  //This "oldPos" object is used to save the old position of the windows for the translation of windows
    VersionInfo version;
    QString qstr = version.getVersion();
    myClient *_client;
    bool regMat;
    void sendRequestMsg(std::string req);

protected:
    //Function for mouse related event
    void mousePressEvent(QMouseEvent *evt);
    void mouseMoveEvent(QMouseEvent *evt);

};
#endif // STARTWINDOW_H

#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "versioninfo.h"
#include <QtGui>
#include <QMessageBox>
#include "jsonUtility.h"
#include <QDebug>
#include <iostream>
#include <thread>
#include "message.h"

using json = nlohmann::json;
using boost::asio::ip::tcp;
typedef std::deque<message> message_queue;

LoginWindow::LoginWindow(QWidget *parent):
                            QMainWindow(parent, Qt::FramelessWindowHint | Qt::WindowSystemMenuHint),
                            ui(new Ui::LoginWindow),
                            client(new myClient) {
    ui->setupUi(this);
    ui->version->setText(qstr);
    frame->setGeometry(0,0, 390,670);
    frame->setStyleSheet("background-image: url(:/image/SfondoTotal.png)");
    //setStatus(client->getStatus());
    //connect(client, &myClient::hasReadSome, this, &LoginWindow::receivedSomething);
    //connect(client, &myClient::statusChanged, this, &LoginWindow::setStatus);
    // FIXME change this connection to the new syntax
    //connect(client->tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            //this, SLOT(gotError(QAbstractSocket::SocketError)));
}

LoginWindow::~LoginWindow() {
    delete frame;
    delete ui;
    delete client;
}

void LoginWindow::setStatus(bool newStatus)
{
    if(newStatus)
    {
        ui->label_status->setText(tr("<font color=\"green\">CONNECTED</font>"));
        ui->pushButton_connect->setVisible(false);
        ui->pushButton_disconnect->setVisible(true);
    }
    else
    {
        ui->label_status->setText(tr("<font color=\"red\">DISCONNECTED</font>"));
        ui->pushButton_connect->setVisible(true);
        ui->pushButton_disconnect->setVisible(false);
    }
}

void LoginWindow::receivedSomething(QString msg) {
    ui->textEdit_log->append("[SERVER] " + msg);
}

void LoginWindow::gotError(QAbstractSocket::SocketError err)
{
    //qDebug() << "got error";
    QString strError = "unknown";
    switch (err)
    {
        case 0:
            strError = "Connection was refused";
            break;
        case 1:
            strError = "Remote host closed the connection";
            break;
        case 2:
            strError = "Host address was not found";
            break;
        case 5:
            strError = "Connection timed out";
            break;
        default:
            strError = "Unknown error";
    }

    ui->textEdit_log->append(strError);
}

void LoginWindow::on_pushButton_connect_clicked()
{
    //client->connect2host();
    client->do_connect();
}

void LoginWindow::on_exitButton_clicked(){
    QApplication::quit(); //TODO: Il programma finisce "male"?
}

void LoginWindow::mousePressEvent(QMouseEvent *evt){
     oldPos = evt->globalPos();
}

void LoginWindow::on_pushButton_disconnect_clicked()
{
    client->closeConnection();
}

void LoginWindow::mouseMoveEvent(QMouseEvent *evt){
    const QPoint delta = evt->globalPos() - oldPos;
    move(x()+delta.x(), y()+delta.y());
    oldPos = evt->globalPos();
}

void LoginWindow::on_ForgotPasswordButton_clicked(){
    QMessageBox msgBox;
    msgBox.setText("Function not implemented");
    msgBox.exec();
}

void LoginWindow::on_LoginButton_clicked() {

    //Get data from the form
    QString user = ui->LineEditUsernameForm->text();
    QByteArray ba_user = user.toLocal8Bit();
    const char *c_user = ba_user.data();
    QString pass = ui->LineEditPasswordForm->text();
    QByteArray ba_pass = pass.toLocal8Bit();
    const char *c_pass = ba_pass.data();

    //Serialize data
    json j;
    jsonUtility::to_json(j, "LOGIN_REQUEST", c_user, c_pass);
    const char* req = j.dump().c_str();

    //Send data (header and body)
    message msg;
    msg.body_length(std::strlen(req));
    std::memcpy(msg.body(), req, msg.body_length());
    msg.encode_header();
    client->write(msg);
}

void LoginWindow::on_RegistratiButton_clicked() {
    RegWindow *l = new RegWindow();
    l->show();
    this->hide();
}

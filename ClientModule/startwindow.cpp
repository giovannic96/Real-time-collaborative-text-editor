#include "startwindow.h"
#include "ui_startwindow.h"
#include <QMessageBox>
#include <iostream>
#include <thread>
#include "userprofile.h"
#include "jsonUtility.h"
#include "message.h"

using json = nlohmann::json;
using boost::asio::ip::tcp;
typedef std::deque<message> message_queue;

//CONSTRUCTOR
StartWindow::StartWindow(QWidget *parent): QMainWindow(parent, Qt::FramelessWindowHint | Qt::WindowSystemMenuHint),
    ui(new Ui::StartWindow), client(new myClient)
{
    ui->setupUi(this);
    ui->version->setText(qstr);
    setStatus(client->getStatus());
    connect(client, &myClient::statusChanged, this, &StartWindow::setStatus);
    connect(client, &myClient::formResult, this, &StartWindow::showFormPopup);
}

//DESTRUCTOR
StartWindow::~StartWindow(){
    delete ui;
    delete client;
}

//EXIT BUTTON
void StartWindow::on_exitButton_clicked(){
    QApplication::exit();   //I've used exit() instead quit() or close() for this reason --> https://ux.stackexchange.com/questions/50893/do-we-exit-quit-or-close-an-application
}

//FUNCTION FOR MAKE DRAGGABLE THE WINDOW
void StartWindow::mousePressEvent(QMouseEvent *evt){
     oldPos = evt->globalPos();
}

//FUNCTION FOR MAKE DRAGGABLE THE WINDOW
void StartWindow::mouseMoveEvent(QMouseEvent *evt){
    const QPoint delta = evt->globalPos() - oldPos;
    move(x()+delta.x(), y()+delta.y());
    oldPos = evt->globalPos();
}

//LOGIN BUTTON
void StartWindow::on_LoginButton_clicked(){
    //Get data from the form
    QString user = ui->LoginUsernameForm->text();
    QByteArray ba_user = user.toLocal8Bit();
    const char *c_user = ba_user.data();
    QString pass = ui->LoginPasswordForm->text();
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

//SIGNUP BUTTON
void StartWindow::on_SignUpButton_clicked(){
    //Get data from the form
    QString user = ui->RegUsernameForm->text();
    QByteArray ba_user = user.toLocal8Bit();
    const char *c_user = ba_user.data();
    QString pass = ui->RegPasswordForm->text();
    QByteArray ba_pass = pass.toLocal8Bit();
    const char *c_pass = ba_pass.data();
    QString email = ui->RegMailForm->text();
    QByteArray ba_email = email.toLocal8Bit();
    const char *c_email = ba_email.data();

    //Serialize data
    json j;
    jsonUtility::to_json(j, "SIGNUP_REQUEST", c_user, c_pass, c_email);
    const char* req = j.dump().c_str();

    //Send data (header and body)
    message msg;
    msg.body_length(std::strlen(req));
    std::memcpy(msg.body(), req, msg.body_length());
    msg.encode_header();
    client->write(msg);
}

/*
void StartWindow::on_NewFileButton_clicked(){ // when press ok
    //Get data from the form
    QString user = ui->NewFileUsernameForm->text();
    QByteArray ba_user = user.toLocal8Bit();
    const char *c_user = ba_user.data();
    QString filename = ui->NewFileFilenameForm->text();
    QByteArray ba_filename = filename.toLocal8Bit();
    const char *c_filename = ba_filename.data();

    //Serialize data
    json j;
    jsonUtility::to_jsonFilename(j, "NEWFILE_REQUEST", c_user, c_filename);
    const char* req = j.dump().c_str();

    //Send data (header and body)
    message msg;
    msg.body_length(std::strlen(req));
    std::memcpy(msg.body(), req, msg.body_length());
    msg.encode_header();
    client->write(msg);
}*/

//FORGOT PASSWORD BUTTON
void StartWindow::on_ForgotPasswordButton_clicked(){
    QMessageBox msgBox;
    msgBox.setText("Funzione non implementata"); //Todo --> Show popup to send email
    msgBox.exec();
}

//ADMIN LOGIN BUTTON --> Is for debugging, it will deleted when we reached a beta verision
void StartWindow::on_LoginAdmin_clicked(){
    ui->stackedWidget->setCurrentIndex(2);
}

//REGISTER BUTTON
void StartWindow::on_RegisterButton_clicked(){
    ui->stackedWidget->setCurrentIndex(1);
}

//ACCEDI BUTTON
void StartWindow::on_AccediButton_clicked(){
    ui->stackedWidget->setCurrentIndex(0);
}

//LOGOUT BUTTON
void StartWindow::on_LogoutButton_clicked(){
    //TODO --> Handle really the logout of the user
    ui->stackedWidget->setCurrentIndex(0);
}

//USERNAME BUTTON
void StartWindow::on_Username_clicked(){
    UserProfile *up = new UserProfile("Superior Administrator"); //with parameters //TODO --> The parameter will become the "username" of who are logged into the system.
    up->show();
}

//SET STATUS LABEL
void StartWindow::setStatus(bool newStatus) {
    if(newStatus) {
        ui->label_status->setText(tr("<font color=\"green\">CONNECTED</font>"));
    }
    else {
        ui->label_status->setText(tr("<font color=\"red\">DISCONNECTED</font>"));
    }
}

void StartWindow::showFormPopup(QString result, QString title, QString msg) {
    if(result == "LOGIN_SUCCESS") {
        QMessageBox messageBox;
        messageBox.information(nullptr, title, msg);
        messageBox.setFixedSize(500,200);
        ui->stackedWidget->setCurrentIndex(2);
    } else if(result == "LOGIN_FAILURE") {
        QMessageBox messageBox;
        messageBox.critical(nullptr, title, msg);
        messageBox.setFixedSize(500,200);
        //Stay in the same window
    } else if(result == "SIGNUP_SUCCESS") {
        QMessageBox messageBox;
        messageBox.critical(nullptr, title, msg);
        messageBox.setFixedSize(500,200);
        ui->stackedWidget->setCurrentIndex(0);
    } else if(result == "SIGNUP_FAILURE") {
        QMessageBox messageBox;
        messageBox.critical(nullptr, title, msg);
        messageBox.setFixedSize(500,200);
        //Stay in the same window
    } else {
        QMessageBox messageBox;
        messageBox.information(nullptr, title, msg);
        messageBox.setFixedSize(500,200);
    }
}

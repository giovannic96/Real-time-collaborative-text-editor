#include "startwindow.h"
#include "ui_startwindow.h"
#include "menuwindow.h"
#include <QMessageBox>
#include <iostream>
#include <thread>
#include <QInputDialog>
#include "userprofile.h"
#include "jsonUtility.h"
#include "editorwindow.h"
#include "message.h"

using json = nlohmann::json;
using boost::asio::ip::tcp;
typedef std::deque<message> message_queue;

//CONSTRUCTOR
StartWindow::StartWindow(QWidget *parent): QMainWindow(parent, Qt::FramelessWindowHint | Qt::WindowSystemMenuHint),
    ui(new Ui::StartWindow), _client(new myClient)
{
    ui->setupUi(this);
    ui->version->setText(qstr);
    setStatus(_client->getStatus());
    connect(_client, &myClient::statusChanged, this, &StartWindow::setStatus);
    connect(_client, &myClient::formResultSuccess, this, &StartWindow::showPopupSuccess);
    connect(_client, &myClient::formResultFailure, this, &StartWindow::showPopupFailure);
    connect(_client, &myClient::changeTextUsername, this, &StartWindow::labelChangeText);
    setFixedSize(size());   //IS AN HALF HELP WITH THE DPI-Related-BUG - DON'T DELETE ME FOR NOW
}

//DESTRUCTOR
StartWindow::~StartWindow(){
    delete ui;
    delete _client;
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

    //update client data
    _client->setUsername(user);

    //Serialize data
    json j;
    jsonUtility::to_json(j, "LOGIN_REQUEST", c_user, c_pass);
    const std::string req = j.dump();

    //Send data (header and body)
    sendRequestMsg(req);
}

//SIGNUP BUTTON
void StartWindow::on_SignUpButton_clicked() {
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
    const std::string req = j.dump();

    //Send data (header and body)
    sendRequestMsg(req);
}

//FORGOT PASSWORD BUTTON
void StartWindow::on_ForgotPasswordButton_clicked(){
//    QMessageBox msgBox;
//    msgBox.setText("Funzione non implementata"); //Todo --> Show popup to send email
//    msgBox.exec();
}

//ADMIN LOGIN BUTTON --> Is for debugging, it will deleted when we reached a beta verision
void StartWindow::on_LoginAdmin_clicked() {
    MenuWindow *m = new MenuWindow(_client);
    m->show();
    this->close();
}

//REGISTER BUTTON
void StartWindow::on_RegisterButton_clicked() {
    ui->stackedWidget->setCurrentIndex(1);
}

//ACCEDI BUTTON
void StartWindow::on_AccediButton_clicked() {
    ui->stackedWidget->setCurrentIndex(0);
}

void StartWindow::on_exitButton_clicked() {
    QApplication::exit(); //TODO: show warning popup!
}

void StartWindow::setStatus(bool newStatus) {
    if(newStatus) {
        ui->label_status->setText(tr("<font color=\"green\">CONNECTED</font>"));
    }
    else {
        ui->label_status->setText(tr("<font color=\"red\">DISCONNECTED</font>"));
    }
}

void StartWindow::labelChangeText(QString text) {
    //ui->Username->setText(text);
}

void StartWindow::showPopupFailure(QString result) {
    if(result == "LOGIN_FAILURE") {
        QMessageBox messageBox;
        messageBox.critical(nullptr, "LOGIN FAILURE", "Error: Login NOT completed!");
        messageBox.setFixedSize(500,200);
        //Stay in the same window
    } else if(result == "SIGNUP_FAILURE") {
        QMessageBox messageBox;
        messageBox.critical(nullptr, "SIGNUP FAILURE", "Error: Signup NOT completed!");
        messageBox.setFixedSize(500,200);
        //Stay in the same window
    } else {
        QMessageBox messageBox;
        messageBox.information(nullptr, "GENERIC FAILURE", "Error: Something went wrong!");
        messageBox.setFixedSize(500,200);
    }
}

void StartWindow::showPopupSuccess(QString result) {
    if(result == "LOGIN_SUCCESS") {
        QMessageBox messageBox;
        messageBox.information(nullptr, "LOGIN SUCCESS", "Login successfully completed.");
        messageBox.setFixedSize(500,200);
        MenuWindow *m = new MenuWindow(_client);
        this->close(); //this startWindow will be then created when user press Exit on menuWindow
        m->show();
    } else if(result == "SIGNUP_SUCCESS") {
        QMessageBox messageBox;
        messageBox.critical(nullptr, "SIGNUP SUCCESS", "Signup successfully completed.");
        messageBox.setFixedSize(500,200);
        ui->stackedWidget->setCurrentIndex(0);
    }
}

void StartWindow::sendRequestMsg(std::string req) {
    message msg;
    msg.body_length(req.size());
    std::memcpy(msg.body(), req.data(), msg.body_length());
    msg.body()[msg.body_length()] = '\0'; //TODO: do we have to leave it??
    msg.encode_header();
    _client->write(msg);
}

//FOR LOGIN PAGE
void StartWindow::on_LoginPasswordForm_returnPressed(){
    on_LoginButton_clicked();
}

void StartWindow::on_LoginUsernameForm_returnPressed(){
    on_LoginButton_clicked();
}

//FOR REG PAGE
void StartWindow::on_RegUsernameForm_returnPressed(){
    on_SignUpButton_clicked();
}

void StartWindow::on_RegPasswordForm_returnPressed(){
    on_SignUpButton_clicked();
}

void StartWindow::on_RegMailForm_returnPressed(){
    on_SignUpButton_clicked();
}

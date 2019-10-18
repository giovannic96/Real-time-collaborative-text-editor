#include "startwindow.h"
#include "ui_startwindow.h"
#include <QMessageBox>      //For Alert Message
#include <iostream>         //GIOVANNI --> Needed???
#include <thread>           //GIOVANNI --> For what?
#include "userprofile.h"    //Show the userprofile window
#include "jsonUtility.h"    //GIOVANNI --> What is do it?
#include "message.h"        //GIOVANNI --> Spiegami

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
    //Le due seguenti connect li metterei in una funzione standalone che richiamerei dentro il pulsante "accedi" e la funzione viene circondata da un try-catch che riprova la connessione per n-volte e poi tira l'eccezione che viene gestita.
    connect(client, &myClient::statusChanged, this, &StartWindow::setStatus);
    connect(client, &myClient::formResult, this, &StartWindow::showFormPopup);
}

//DESTRUCTOR
StartWindow::~StartWindow(){
    delete ui;
}

//EXIT BUTTON
void StartWindow::on_exitButton_clicked(){
    QApplication::exit();   //I've used exit() instead quit() or close() for this reason --> https://ux.stackexchange.com/questions/50893/do-we-exit-quit-or-close-an-application
    //TODO --> Valutate the possibility to add a "delete this;" instruction for calling the destructor
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

//REGISTRATI BUTTON
void StartWindow::on_RegistratiButton_clicked(){
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
        ui->label_status->setText(tr("<font color=\"green\">CONNESSO</font>"));
    }
    else {
        ui->label_status->setText(tr("<font color=\"red\">DISCONNESSO</font>"));
    }
}

//SHOW FORM POPUP --> Cosa fa????
void StartWindow::showFormPopup(QString result, QString title, QString msg) {
    if(result == "SUCCESS") {
        QMessageBox messageBox;
        messageBox.information(nullptr, title, msg);
        messageBox.setFixedSize(500,200);
        //TODO: Go to the next window
    } else if(result == "FAILURE") {
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

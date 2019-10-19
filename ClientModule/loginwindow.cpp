#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QtGui>            //For QPoint
#include <QDebug>
#include <QMessageBox>      //For Alert Message
#include "jsonUtility.h"
#include <iostream>
#include <thread>
#include "message.h"

using json = nlohmann::json;
using boost::asio::ip::tcp;
typedef std::deque<message> message_queue;

//CONSTRUCTOR
LoginWindow::LoginWindow(QWidget *parent): QMainWindow(parent, Qt::FramelessWindowHint | Qt::WindowSystemMenuHint),
                                                                       ui(new Ui::LoginWindow), client(new myClient) {
    ui->setupUi(this);
    ui->version->setText(qstr);
    setStatus(client->getStatus());
    //Le due seguenti connect li metterei in una funzione standalone che richiamerei dentro il pulsante "accedi" e la funzione viene circondata da un try-catch che riprova la connessione per n-volte e poi tira l'eccezione che viene gestita.
    connect(client, &myClient::statusChanged, this, &LoginWindow::setStatus);
    connect(client, &myClient::formResult, this, &LoginWindow::showFormPopup);
}

//DISTRUCTOR
LoginWindow::~LoginWindow(){
    delete ui;
    delete client;

    qDebug() << "Hello from LoginDestructor!";
}

//SET STATUS LABEL
void LoginWindow::setStatus(bool newStatus) {
    if(newStatus) {
        ui->label_status->setText(tr("<font color=\"green\">CONNECTED</font>"));
    }
    else {
        ui->label_status->setText(tr("<font color=\"red\">DISCONNECTED</font>"));
    }
}


void LoginWindow::showFormPopup(QString result, QString title, QString msg) {
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

//EXIT BUTTON
void LoginWindow::on_exitButton_clicked(){
    QApplication::exit();   //I've used exit() instead quit() or close() for this reason --> https://ux.stackexchange.com/questions/50893/do-we-exit-quit-or-close-an-application
}

//FUNCTION FOR MAKE DRAGGABLE THE WINDOW
void LoginWindow::mousePressEvent(QMouseEvent *evt){
     oldPos = evt->globalPos();
}

//FUNCTION FOR MAKE DRAGGABLE THE WINDOW
void LoginWindow::mouseMoveEvent(QMouseEvent *evt){
    const QPoint delta = evt->globalPos() - oldPos;
    move(x()+delta.x(), y()+delta.y());
    oldPos = evt->globalPos();
}

//FORGOT PASSWORD BUTTON
void LoginWindow::on_ForgotPasswordButton_clicked(){
    QMessageBox msgBox;
    msgBox.setText("Funzione non implementata"); //Todo --> Show popup to send email
    msgBox.exec();
}

//LOGIN BUTTON
void LoginWindow::on_LoginButton_clicked()
{
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

//REGISTER BUTTON --> handle the switch beetween this window and the "registration window"
void LoginWindow::on_RegisterButton_clicked(){
    RegWindow *l = new RegWindow();
    l->show();
    this->hide();
}

//LOGIN ADMIN BUTTON --> Avoid database connection and start the "startmenu window" like there was an Admin logged in
void LoginWindow::on_LoginAdmin_clicked(){
    StartMenu *start = new StartMenu("Superior Administrator"); //new window with parameters //TODO --> The parameter will become the "username" of who are logged into the system.
    start->show();
    this->hide();
}

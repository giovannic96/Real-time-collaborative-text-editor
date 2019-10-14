#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "versioninfo.h"
//#include "loggeduserinfo.h"   //DOVE CAZZO LA USAVO QUESTA LIBRERIA ORA? LASCIAMI E NON CANCELLARMI, POTREI AVERE QUALCHE IDEA RELATIVA AD ESSO
#include <QtGui>            //For QPoint
#include <QDebug>           //TODO --> CREDO SIA INUTILE
#include <QMessageBox>      //For Alert Message
#include "jsonUtility.h"
#include <QDebug>
#include <iostream>
#include <thread>
#include "message.h"

using json = nlohmann::json;
using boost::asio::ip::tcp;
typedef std::deque<message> message_queue;

//CONSTRUCTOR --> The FramelessWindowsHint and WindowSystemMenuHint options is needed for make bordless the window
LoginWindow::LoginWindow(QWidget *parent): QMainWindow(parent, Qt::FramelessWindowHint | Qt::WindowSystemMenuHint), ui(new Ui::LoginWindow), client(new myClient) {
    ui->setupUi(this);
    ui->version->setText(qstr);
    //setStatus(client->getStatus());
    //connect(client, &myClient::hasReadSome, this, &LoginWindow::receivedSomething);
    //connect(client, &myClient::statusChanged, this, &LoginWindow::setStatus);
    // FIXME change this connection to the new syntax
    //connect(client->tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            //this, SLOT(gotError(QAbstractSocket::SocketError)));
}

//DESTRUCTION
LoginWindow::~LoginWindow(){
    delete ui;
    delete client;
}

//TODO --> CAN I HAVE SOME TITLE OR COMMENT RELATED TO IT?
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

//TODO --> CAN I HAVE SOME TITLE OR COMMENT RELATED TO IT?
void LoginWindow::receivedSomething(QString msg) {
    ui->textEdit_log->append("[SERVER] " + msg);
}

//TODO --> CAN I HAVE SOME TITLE OR COMMENT RELATED TO IT?
void LoginWindow::gotError(QAbstractSocket::SocketError err)
{
    //qDebug() << "got error";
    QString strError = "unknown";
    switch (err)
    {
        case 0:
            strError = "Connessione rifiutata";
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
            strError = "Errore sconosciuto";
    }
    ui->textEdit_log->append(strError);
}


//TODO --> CAN I HAVE SOME TITLE OR COMMENT RELATED TO IT?
void LoginWindow::on_pushButton_connect_clicked()
{
    //client->connect2host();
    client->do_connect();
}

//TODO --> CAN I HAVE SOME TITLE OR COMMENT RELATED TO IT?
void LoginWindow::on_pushButton_disconnect_clicked()
{
    client->closeConnection();
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
    msgBox.setText("Funzione non implementata");
    msgBox.exec();
}

//TODO --> CAN I HAVE SOME TITLE OR COMMENT RELATED TO IT?
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

//REGISTRATI BUTTON --> handle the switch beetween this window and the "registration window"
void LoginWindow::on_RegistratiButton_clicked(){
    RegWindow *l = new RegWindow();
    l->show();
    this->hide();
}

/**************************************************************************************************************************************
 * IMPORTANT NOTE FOR GIOVANNI OR WHOEVER IS FIXING THIS MESS
 * Questa era la vecchia versione del bottone login. Mi sono necessarie le righe
 * che gestiscono il cambio di schermata e il passaggio di parametro (username) che ora non so da dove prendere
 * PRIMA di modificare/cancellare la seguente versione chiamatemi a telefono, 24h su 24
***************************************************************************************************************************************/
/*
//LOGIN BUTTON
void LoginWindow::on_LoginButton_clicked(){

       db = QSqlDatabase::addDatabase("QSQLITE", "MyConnect");
       db.setDatabaseName("D:/Progetti C++/LoginToRealtime/LoginTo/Db/texteditor_users.sqlite");  //IMPORTANTE SENNO' NON PARTE (NOTA 2: il path va con questi slash --> "/")
       if(db.open()) {

           //Retrieve data from input fields
           QString username = ui->LineEditUsernameForm->text();
           QString password = ui->LineEditPasswordForm->text();

           //Run our query
           QSqlQuery query(QSqlDatabase::database("MyConnect"));
           query.prepare(QString("SELECT * FROM users WHERE username = :username AND password = :password"));
           query.bindValue(":username", username);
           query.bindValue(":password", password);


           if(query.exec()) {
               while(query.next()) {
                   QString usernameFromDb = query.value(0).toString();
                   QString passwordFromDb = query.value(1).toString();

                   if(usernameFromDb == username && passwordFromDb == password) {
                       //handle the switch beetween this window and the "startmenu window"
                       StartMenu *start = new StartMenu(username); //new window with parameters
                       start->show();
                       this->hide();
                   } else {
                       QMessageBox::information(this, "Failure", "Login failed");
                   }
               }
               db.close();
           } else {
               QMessageBox::information(this, "Failed", "Error: Query failed to execute!");
               db.close();
           }
       } else {
           QSqlError error = db.lastError();
           QMessageBox::information(this, "Error during connection", error.databaseText());
       }
*/

//LOGIN ADMIN BUTTON    --> Avoid database connection and start the "startmenu window" like there was an Admin logged in
void LoginWindow::on_LoginAdmin_clicked(){
    StartMenu *start = new StartMenu("Superior Administrator"); //new window with parameters //TODO --> The parameter will become the "username" of who are logged into the system.
    start->show();
    this->hide();
}

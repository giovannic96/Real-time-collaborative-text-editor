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
    ui(new Ui::StartWindow), client(new myClient)
{
    ui->setupUi(this);
    ui->version->setText(qstr);
    setStatus(client->getStatus());
    connect(client, &myClient::statusChanged, this, &StartWindow::setStatus);
    connect(client, &myClient::formResult, this, &StartWindow::showFormPopup);
    connect(client, &myClient::changeTextUsername, this, &StartWindow::labelChangeText);
    //adjustSize(); //CUT EVERYTHING
    setFixedSize(size());   //IS AN HALF HELP WITH THE DPI-Related-BUG - DON'T DELETE ME FOR NOW
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
    const std::string req = j.dump();

    //Send data (header and body)
    sendRequestMsg(req);
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
void StartWindow::on_LoginAdmin_clicked(){
    MenuWindow *m= new MenuWindow();
    m->show();
    this->close();
}

//REGISTER BUTTON
void StartWindow::on_RegisterButton_clicked(){
    ui->stackedWidget->setCurrentIndex(1);
}

//ACCEDI BUTTON
void StartWindow::on_AccediButton_clicked(){
    ui->stackedWidget->setCurrentIndex(0);
}

void StartWindow::on_listFiles_clicked()
{
    //Get data from the form
    QString user = ui->Username->text();
    QByteArray ba_user = user.toLocal8Bit();
    const char *c_user = ba_user.data();

    //Serialize data
    json j;
    jsonUtility::to_jsonUser(j, "LISTFILE_REQUEST", c_user);
    const std::string req = j.dump();

    //Send data (header and body)
    qDebug() << "Client is sending: START" << req.data() << "END";
    sendRequestMsg(req);

    //TODO: receive file list from server

    //TODO: don't open file right now! First check the NEWFILE_RESPONSE from the server.
    //EditorWindow *ew = new EditorWindow(text);
    //ew->show();
    //delete this;

}

void StartWindow::on_openDoc_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Titolo documento"),
                                         tr("Inserisci il nome del documento da aprire:"), QLineEdit::Normal,
                                         "", &ok);
    if (ok && !text.isEmpty() && text.size()<=15){
        //TODO controllo file database -> quali controlli?
        QMessageBox messageBox;
        messageBox.information(nullptr, "Apri documento", "Apertura in corso..");
        messageBox.setFixedSize(600,400);
        messageBox.show();

        //Get data from the form
        QString user = ui->Username->text();
        QByteArray ba_user = user.toLocal8Bit();
        const char *c_user = ba_user.data();
        QString filename = text;
        QByteArray ba_filename = filename.toLocal8Bit();
        const char *c_filename = ba_filename.data();

        //Serialize data
        json j;
        jsonUtility::to_jsonFilename(j, "OPENFILE_REQUEST", c_user, c_filename);
        const std::string req = j.dump();

        //Send data (header and body)
        qDebug() << "Client is sending: START" << req.data() << "END";
        sendRequestMsg(req);

        //TODO: receive (updated) file from server

        //TODO: don't open file right now! First check the NEWFILE_RESPONSE from the server.
        EditorWindow *ew = new EditorWindow(text);
        ew->show();
        delete this;
    }
    else if (ok && !text.isEmpty() && text.size()>15){
        QMessageBox messageBox;
        messageBox.critical(nullptr,"Errore","Inserire un nome minore di 15 caratteri!");
        messageBox.setFixedSize(600,400);
        on_openDoc_clicked();
    }
    else if (ok && text.isEmpty()){
        QMessageBox messageBox;
        messageBox.critical(nullptr,"Errore","Inserire un nome!");
        messageBox.setFixedSize(600,400);
        on_openDoc_clicked();
    }
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

void StartWindow::labelChangeText(QString text) {
    ui->Username->setText(text);
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
    } else if(result == "OPENFILE_SUCCESS") {
        QMessageBox messageBox;
        messageBox.critical(nullptr, title, msg);
        messageBox.setFixedSize(500,200);
        ui->stackedWidget->setCurrentIndex(2);
    } else if(result == "OPENFILE_FAILURE") {
        QMessageBox messageBox;
        messageBox.critical(nullptr, title, msg);
        messageBox.setFixedSize(500,200);
        //Stay in the same window
    }else {
        QMessageBox messageBox;
        messageBox.information(nullptr, title, msg);
        messageBox.setFixedSize(500,200);
    }
}

void StartWindow::sendRequestMsg(std::string req) {
    message msg;
    msg.body_length(req.size());
    std::memcpy(msg.body(), req.data(), msg.body_length());
    msg.body()[msg.body_length()] = '\0'; //TODO: do we have to leave it??
    msg.encode_header();
    client->write(msg);
}

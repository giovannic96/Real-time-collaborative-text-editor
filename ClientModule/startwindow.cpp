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
    ui->LoginUsernameForm->setFocus();
    ui->usernameERR->hide();
    ui->passERR->hide();
    ui->mailERR->hide();

    setStatus(_client->getStatus());
    connect(_client, &myClient::statusChanged, this, &StartWindow::setStatus);
    connect(_client, &myClient::formResultSuccess, this, &StartWindow::showPopupSuccess);
    connect(_client, &myClient::formResultFailure, this, &StartWindow::showPopupFailure);
    connect(_client, &myClient::jsonMsgFailure, this, &StartWindow::showJsonPopupFailure);
    setFixedSize(size());   //IS AN HALF HELP WITH THE DPI-Related-BUG - DON'T DELETE ME FOR NOW
}

//DESTRUCTOR
StartWindow::~StartWindow() {
    delete ui;
    delete _client;
}

void StartWindow::mousePressEvent(QMouseEvent *evt){
     oldPos = evt->globalPos();
}

void StartWindow::mouseMoveEvent(QMouseEvent *evt){
    const QPoint delta = evt->globalPos() - oldPos;
    move(x()+delta.x(), y()+delta.y());
    oldPos = evt->globalPos();
}

void StartWindow::on_LoginButton_clicked(){
    if(_client->getStatus()==false){
        QMessageBox::warning(nullptr, "Attenzione", "Non sono riuscito a contattare il server!\n"
                                                        "Riprova più tardi");
    } else {
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
        _client->sendRequestMsg(req);
    }
}

void StartWindow::on_SignUpButton_clicked() {
    if(_client->getStatus()==false) {
        QMessageBox::warning(nullptr, "Attenzione", "Non sono riuscito a contattare il server!\n"
                                                        "Riprova più tardi");
    } else {
        if (ui->RegUsernameForm->text().isEmpty()) {
            ui->usernameERR->show();
        } else {
            ui->usernameERR->hide();

            if (ui->RegPasswordForm->text().length() < 6) {
                ui->passERR->show();
            } else {
                ui->passERR->hide();

                QRegularExpression mailREX("^[0-9a-zA-Z]+([0-9a-zA-Z]*[-._+])*[0-9a-zA-Z]+@[0-9a-zA-Z]+([-.][0-9a-zA-Z]+)*([0-9a-zA-Z]*[.])[a-zA-Z]{2,6}$");
                regMat = mailREX.match(ui->RegMailForm->text()).hasMatch();

                if (!regMat) {
                    ui->mailERR->show();
                } else {
                    ui->mailERR->hide();

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
                    _client->sendRequestMsg(req);
                }
            }
        }
    }
}

void StartWindow::on_RegisterButton_clicked() {
    ui->stackedWidget->setCurrentIndex(1);
}

void StartWindow::on_AccediButton_clicked() {
    ui->stackedWidget->setCurrentIndex(0);
}

void StartWindow::on_exitButton_clicked() {
    QMessageBox::StandardButton reply;
      reply = QMessageBox::question(this, "Uscita", "Vuoi uscire?",
                                    QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::Yes) {
        QApplication::exit();
      }
}

void StartWindow::setStatus(bool newStatus) {
    if(newStatus)
        ui->label_status->setText(tr("<font color=\"green\">CONNECTED</font>"));
    else
        ui->label_status->setText(tr("<font color=\"red\">DISCONNECTED</font>"));
}

void StartWindow::showPopupSuccess(QString result) {
    if(result == "LOGIN_SUCCESS") {
        MenuWindow *m = new MenuWindow(_client);
        this->close(); //this startWindow will be then created (new) when user press Logout button on menuWindow
        m->show();
    } else if(result == "SIGNUP_SUCCESS") {
        QMessageBox::information(this,"Complimenti", "La registrazione è avvenuta correttamente!");
        ui->stackedWidget->setCurrentIndex(0);
    }
}

void StartWindow::showPopupFailure(QString result) {
    if(result == "LOGIN_FAILURE") {
       QMessageBox::critical(this,"Errore", "Il login non è stato completato correttamente! Riprova!");                                 //Stay in the same window
    } else if(result == "SIGNUP_FAILURE") {
        QMessageBox::critical(this,"Errore", "La registrazione non è avvenuta correttamente! Riprova!");                                //Stay in the same window
    } else {
        QMessageBox::information(nullptr, "Attenzione", "Qualcosa è andato storto! Riprova!");
    }
}

void StartWindow::showJsonPopupFailure(QString windowName,QString msg) {
    if(windowName == "StartWindow") {
        QMessageBox::critical(this, "Errore", msg);
        QApplication::exit();
    }
}

//LOGIN PAGE
void StartWindow::on_LoginPasswordForm_returnPressed() {
    on_LoginButton_clicked();
}

void StartWindow::on_LoginUsernameForm_returnPressed() {
    on_LoginButton_clicked();
}

//REG PAGE
void StartWindow::on_RegUsernameForm_returnPressed() {
    on_SignUpButton_clicked();
}

void StartWindow::on_RegPasswordForm_returnPressed() {
    on_SignUpButton_clicked();
}

void StartWindow::on_RegMailForm_returnPressed() {
    on_SignUpButton_clicked();
}

void StartWindow::on_RegPasswordForm_editingFinished() {
    if (ui->RegPasswordForm->text().length() < 6)
        ui->passERR->show();
    else
        ui->passERR->hide();
}

void StartWindow::on_RegUsernameForm_editingFinished() {
    if (ui->RegUsernameForm->text().isEmpty())
        ui->usernameERR->show();
    else
        ui->usernameERR->hide();
}

void StartWindow::on_RegMailForm_editingFinished() {
    QRegularExpression mailREX("^[0-9a-zA-Z]+([0-9a-zA-Z]*[-._+])*[0-9a-zA-Z]+@[0-9a-zA-Z]+([-.][0-9a-zA-Z]+)*([0-9a-zA-Z]*[.])[a-zA-Z]{2,6}$");
    regMat = mailREX.match(ui->RegMailForm->text()).hasMatch();

    if (!regMat)
        ui->mailERR->show();
    else
        ui->mailERR->hide();
}

void StartWindow::on_eyeButton_clicked() {
    if(ui->eyeButton->isChecked()){
        ui->LoginPasswordForm->setEchoMode(QLineEdit::Normal);
        ui->eyeButton->setStyleSheet("border-image: url(:image/hidePassword.png);");
    }
    else{
        ui->LoginPasswordForm->setEchoMode(QLineEdit::Password);
        ui->eyeButton->setStyleSheet("border-image: url(:image/showPassword.png);");
    }
}

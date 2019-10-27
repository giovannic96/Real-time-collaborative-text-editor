#include "menuwindow.h"
#include "ui_menuwindow.h"
#include <boost/asio.hpp>
#include <QMessageBox>
#include <QInputDialog>
#include "editorwindow.h"
#include "userprofile.h"
#include "startwindow.h"

MenuWindow::MenuWindow(QWidget *parent): QMainWindow(parent, Qt::FramelessWindowHint | Qt::WindowSystemMenuHint),
    ui(new Ui::MenuWindow), client(new myClient){
    ui->setupUi(this);
    setFixedSize(size());   //IS AN HALF HELP WITH THE DPI-Related-BUG - DON'T DELETE ME FOR NOW
}

//DESTRUCTOR
MenuWindow::~MenuWindow(){
    delete ui;
    delete client;
}

//EXIT BUTTON
void MenuWindow::on_exitButton_clicked(){
    QApplication::exit();   //I've used exit() instead quit() or close() for this reason --> https://ux.stackexchange.com/questions/50893/do-we-exit-quit-or-close-an-application
}

//FUNCTION FOR MAKE DRAGGABLE THE WINDOW
void MenuWindow::mousePressEvent(QMouseEvent *evt){
     oldPos = evt->globalPos();
}

//FUNCTION FOR MAKE DRAGGABLE THE WINDOW
void MenuWindow::mouseMoveEvent(QMouseEvent *evt){
    const QPoint delta = evt->globalPos() - oldPos;
    move(x()+delta.x(), y()+delta.y());
    oldPos = evt->globalPos();
}

//LOGOUT BUTTON
void MenuWindow::on_LogoutButton_clicked(){
    //TODO --> Handle really the logout of the user
    StartWindow *sw = new StartWindow();
    sw->show();
    this->hide();
}

//USERNAME BUTTON
void MenuWindow::on_Username_clicked(){
    UserProfile *up = new UserProfile("Superior Administrator"); //with parameters //TODO --> The parameter will become the "username" of who are logged into the system.
    up->show();
}

void MenuWindow::on_newDoc_clicked()
{
    bool ok;
        QString text = QInputDialog::getText(this, tr("Titolo documento"),
                                             tr("Inserisci un nome per il nuovo documento:"), QLineEdit::Normal,
                                             "", &ok);
        if (ok && !text.isEmpty() && text.size()<=15){
            //TODO controllo file database (nome e utente)
            QMessageBox messageBox;
            messageBox.information(nullptr, "Nuovo documento", "Apertura in corso..");
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
            jsonUtility::to_jsonFilename(j, "NEWFILE_REQUEST", c_user, c_filename);
            const char* req = j.dump().c_str();

            //Send data (header and body)
            sendRequestMsg(req);

            //TODO: don't open file right now! First check the NEWFILE_RESPONSE from the server.
            EditorWindow *ew = new EditorWindow(text);
            ew->show();
            delete this;
        }
        else if (ok && !text.isEmpty() && text.size()>15){
            QMessageBox messageBox;
            messageBox.critical(nullptr,"Errore","Inserire un nome minore di 15 caratteri!");
            messageBox.setFixedSize(600,400);
            on_newDoc_clicked();
        }
        else if (ok && text.isEmpty()){
            QMessageBox messageBox;
            messageBox.critical(nullptr,"Errore","Inserire un nome!");
            messageBox.setFixedSize(600,400);
            on_newDoc_clicked();
        }
}

void MenuWindow::on_openDoc_clicked()
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
            const char* req = j.dump().c_str();

            //Send data (header and body)
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

void MenuWindow::sendRequestMsg(const char* req) {
    message msg;
    msg.body_length(std::strlen(req));
    std::memcpy(msg.body(), req, msg.body_length());
    msg.encode_header();
    client->write(msg);
}



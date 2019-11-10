#include "menuwindow.h"
#include "ui_menuwindow.h"
#include <boost/asio.hpp>
#include <QMessageBox>
#include <QInputDialog>
#include "editorwindow.h"
#include "userprofile.h"
#include "startwindow.h"
#include <iostream>
#include <QListWidgetItem>

MenuWindow::MenuWindow(myClient* client, QWidget *parent)
    : QMainWindow(parent, Qt::FramelessWindowHint | Qt::WindowSystemMenuHint),
    ui(new Ui::MenuWindow), _client(client) {
    ui->setupUi(this);
    connect(_client, &myClient::opResultSuccess, this, &MenuWindow::showPopupSuccess);
    connect(_client, &myClient::opResultFailure, this, &MenuWindow::showPopupFailure);
    connect(_client, &myClient::listFileResult, this, &MenuWindow::showListFile);
    SetImage();
    this->show();
    setFixedSize(size());   //IS AN HALF HELP WITH THE DPI-Related-BUG - DON'T DELETE ME FOR NOW
    qRegisterMetaType<std::vector<File>>("std::vector<File>");
}

//DESTRUCTOR
MenuWindow::~MenuWindow() {
    delete ui;
    delete _client;
}

//LOGOUT BUTTON
void MenuWindow::on_LogoutButton_clicked(){
    //Get data from the form
    QString user = _client->getUsername();
    QByteArray ba_user = user.toLocal8Bit();
    const char *c_user = ba_user.data();

    //Serialize data
    json j;
    jsonUtility::to_jsonUser(j, "LOGOUT_REQUEST", c_user);
    const std::string req = j.dump();

    //Send data (header and body)
    sendRequestMsg(req);
}

void MenuWindow::mousePressEvent(QMouseEvent *evt){
     oldPos = evt->globalPos();
}

void MenuWindow::mouseMoveEvent(QMouseEvent *evt){
    const QPoint delta = evt->globalPos() - oldPos;
    move(x()+delta.x(), y()+delta.y());
    oldPos = evt->globalPos();
}

//USERNAME BUTTON
void MenuWindow::on_Username_clicked(){
    UserProfile *up = new UserProfile("Superior Administrator"); //with parameters //TODO --> The parameter will become the "username" of who are logged into the system.
    up->show();
}

//EXIT BUTTON
void MenuWindow::on_exitButton_clicked() {
    on_LogoutButton_clicked();  //Let disconnect the user
                                //then the application can be closed
    QApplication::exit();   //I've used exit() instead quit() or close() for this reason --> https://ux.stackexchange.com/questions/50893/do-we-exit-quit-or-close-an-application
}

//BACK BUTTON
void MenuWindow::on_backButton_clicked() {
    ui->stackedWidget->setCurrentIndex(0);
}

//NEW DOCUMENT
void MenuWindow::on_newDoc_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Titolo documento"),
                                         tr("Inserisci un nome per il nuovo documento:"), QLineEdit::Normal,
                                         "", &ok);
    if (ok && !text.isEmpty() && text.size()<=15){
        //TODO controllo file database (nome e utente)

        //Get data from the form
        QString user = _client->getUsername();
        QByteArray ba_user = user.toLocal8Bit();
        const char *c_user = ba_user.data();
        QString filename = text;
        QByteArray ba_filename = filename.toLocal8Bit();
        const char *c_filename = ba_filename.data();

        //Serialize data
        json j;
        jsonUtility::to_jsonFilename(j, "NEWFILE_REQUEST", c_user, c_filename);
        const std::string req = j.dump();

        //update client data
        _client->setUsername(user);
        _client->setFilename(filename);

        //Send data (header and body)
        sendRequestMsg(req);
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

void MenuWindow::on_listFiles_clicked()
{
    //Get data from the form
    QString user = _client->getUsername();
    QByteArray ba_user = user.toLocal8Bit();
    const char *c_user = ba_user.data();

    //Serialize data
    json j;
    jsonUtility::to_jsonUser(j, "LISTFILE_REQUEST", c_user);
    const std::string req = j.dump();

    //update client data
    _client->setUsername(user);

    //Send data (header and body)
    sendRequestMsg(req);
}

void MenuWindow::on_uriDoc_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Titolo documento"),
                                         tr("Inserisci URI del documento:"), QLineEdit::Normal,
                                         "", &ok);
    if (ok && !text.isEmpty() && text.size()<=15){ //TODO: better controls
        //TODO controllo file database (nome e utente)

        //Get data from the form
        QString user = _client->getUsername();
        QByteArray ba_user = user.toLocal8Bit();
        const char *c_user = ba_user.data();
        QString uri = text;
        QByteArray ba_uri = uri.toLocal8Bit();
        const char *c_uri = ba_uri.data();

        //Serialize data
        json j;
        jsonUtility::to_jsonUri(j, "OPENWITHURI_REQUEST", c_user, c_uri);
        const std::string req = j.dump();

        //update client data
        _client->setUsername(user);
        _client->setFileURI(uri);

        //Send data (header and body)
        sendRequestMsg(req);
    }
    else if (ok && !text.isEmpty() && text.size()>15) {
        QMessageBox messageBox;
        messageBox.critical(nullptr,"Errore","Inserire un nome minore di 15 caratteri!");
        messageBox.setFixedSize(600,400);
        on_uriDoc_clicked();
    }
    else if (ok && text.isEmpty()){
        QMessageBox messageBox;
        messageBox.critical(nullptr,"Errore","Inserire un nome!");
        messageBox.setFixedSize(600,400);
        on_uriDoc_clicked();
    }
}

void MenuWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    //TODO:
    //PRENDERE URI DALL'ITEM
    bool ok;
    QString text = QInputDialog::getText(this, tr("uri"),
                                         tr("Inserisci uri del documento:"), QLineEdit::Normal,
                                         "", &ok);
    if (ok && !text.isEmpty() && text.size()<=15){
        //TODO controllo file database -> quali controlli?
        QMessageBox messageBox;
        messageBox.information(nullptr, "Apri documento", "Apertura in corso..");
        messageBox.setFixedSize(600,400);
        messageBox.show();

        //Get data from the form
        QString user = _client->getUsername();
        QByteArray ba_user = user.toLocal8Bit();
        const char *c_user = ba_user.data();
        QString uri = text; //TODO: get uri from db directly!!!!!!!
        QByteArray ba_uri = uri.toLocal8Bit();
        const char *c_uri = ba_uri.data();

        //Serialize data
        json j;
        jsonUtility::to_jsonUri(j, "OPENFILE_REQUEST", c_user, c_uri);
        const std::string req = j.dump();

        //update client data
        _client->setUsername(user);
        _client->setFileURI(uri);

        //Send data (header and body)
        sendRequestMsg(req);
    }
    else if (ok && !text.isEmpty() && text.size()>15){
        QMessageBox messageBox;
        messageBox.critical(nullptr,"Errore","Inserire un nome minore di 15 caratteri!");
        messageBox.setFixedSize(600,400);
        on_listWidget_itemDoubleClicked(item);
    }
    else if (ok && text.isEmpty()){
        QMessageBox messageBox;
        messageBox.critical(nullptr,"Errore","Inserire un nome!");
        messageBox.setFixedSize(600,400);
        on_listWidget_itemDoubleClicked(item);
    }
}

void MenuWindow::showPopupSuccess(QString result) {
    if(result == "LOGOUT_SUCCESS") {
        QMessageBox messageBox;
        messageBox.information(nullptr, "LOGOUT SUCCESS", "Logout successfully completed.");
        messageBox.setFixedSize(500,200);
        StartWindow *s = new StartWindow();
        this->close();
        s->show();
        delete this;
    } else if(result == "NEWFILE_SUCCESS") {
        QMessageBox messageBox;
        messageBox.critical(nullptr, "NEWFILE SUCCESS", "Newfile successfully completed.");
        messageBox.setFixedSize(500,200);
        EditorWindow *ew = new EditorWindow(_client, this);
        this->hide();
        ew->show();
    } else if(result == "OPENFILE_SUCCESS") {
        QMessageBox messageBox;
        messageBox.critical(nullptr, "OPENFILE SUCCESS", "Openfile successfully completed.");
        messageBox.setFixedSize(500,200);
        EditorWindow *ew = new EditorWindow(_client, this);
        this->hide();
        ew->show();
    } else if(result == "OPENWITHURI_SUCCESS") {
        QMessageBox messageBox;
        messageBox.critical(nullptr, "OPENWITHURI SUCCESS", "Openwithuri successfully completed.");
        messageBox.setFixedSize(500,200);
        EditorWindow *ew = new EditorWindow(_client, this);
        this->hide();
        ew->show();
    } else if(result == "LISTFILE_SUCCESS") {
        QMessageBox messageBox;
        messageBox.critical(nullptr, "LISTFILE SUCCESS", "Listfile successfully completed.");
        messageBox.setFixedSize(500,200);
        ui->stackedWidget->setCurrentIndex(1);
    }
}

void MenuWindow::showPopupFailure(QString result) {
    if(result == "LOGOUT_FAILURE") {
        QMessageBox messageBox;
        messageBox.critical(nullptr, "LOGOUT FAILURE", "Error: Logout NOT completed!");
        messageBox.setFixedSize(500,200);
        //Stay in the same window
    } else if(result == "NEWFILE_FAILURE") {
        QMessageBox messageBox;
        messageBox.critical(nullptr, "NEWFILE FAILURE", "Error: Newfile NOT completed!");
        messageBox.setFixedSize(500,200);
        //Stay in the same window
    } else if(result == "OPENFILE_FAILURE") {
        QMessageBox messageBox;
        messageBox.critical(nullptr, "OPENFILE FAILURE", "Error: Openfile NOT completed!");
        messageBox.setFixedSize(500,200);
        //Stay in the same window (MenuWindow(1))
    } else if(result == "OPENWITHURI_FAILURE") {
        QMessageBox messageBox;
        messageBox.critical(nullptr, "OPENWITHURI FAILURE", "Error: Openwithuri NOT completed!");
        messageBox.setFixedSize(500,200);
        //Stay in the same window
    } else if(result == "LISTFILE_FAILURE") {
        QMessageBox messageBox;
        messageBox.critical(nullptr, "LISTFILE FAILURE", "Error: Listfile NOT completed!");
        messageBox.setFixedSize(500,200);
        //Stay in the same window (MenuWindow(1))
    } else if(result == "LISTFILE_FAILURE_LISTNOTEXIST") {
        QMessageBox messageBox;
        messageBox.critical(nullptr, "LISTFILE FAILURE", "Error: Listfile NOT exist!");
        messageBox.setFixedSize(500,200);
        //Stay in the same window (MenuWindow(1))
    } else if(result == "RESPONSE_FAILURE") {
        QMessageBox messageBox;
        messageBox.critical(nullptr, "RESPONSE FAILURE", "Error: Response NOT handled!");
        messageBox.setFixedSize(500,200);
        //Stay in the same window
    } else {
        QMessageBox messageBox;
        messageBox.information(nullptr, "GENERIC FAILURE", "Error: Something went wrong!");
        messageBox.setFixedSize(500,200);
    }
}

void MenuWindow::showListFile(std::vector<File> files) {

    qDebug() << "Sono in showListFile";

    QString filename,owner,timestamp;
    QList<QListWidgetItem*> fileItem;

    foreach (File f, files) {
        filename = QString::fromUtf8(f.getfilename().c_str());
        owner = QString::fromUtf8(f.getowner().c_str());
        timestamp = QString::fromUtf8(f.gettimestamp().c_str());
        fileItem.append(new QListWidgetItem(filename+"\t"+owner+"\t"+timestamp, ui->listWidget));
    }
}

void MenuWindow::SetImage() {
    QRect rect(0,0,58,58);
    QRegion region(rect, QRegion::Ellipse);
    qDebug() << region.boundingRect().size();
    ui->logoutButton->setMask(region);
    ui->backButton->setMask(region);
}

void MenuWindow::sendRequestMsg(std::string req) {
    message msg;
    msg.body_length(req.size());
    std::memcpy(msg.body(), req.data(), msg.body_length());
    msg.body()[msg.body_length()] = '\0'; //TODO: do we have to leave it??
    msg.encode_header();
    _client->write(msg);
}

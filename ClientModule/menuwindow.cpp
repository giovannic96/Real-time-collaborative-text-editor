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
    connect(_client, &myClient::backToMenuWindow,this, &MenuWindow::resumeWindow);
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

    QMessageBox::StandardButton reply;
      reply = QMessageBox::question(this, "Uscita", "Vuoi disconnetterti?",
                                    QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::Yes) {

        //Serialize data
        json j;
        jsonUtility::to_jsonUser(j, "DISCONNECT_REQUEST", c_user);
        const std::string req = j.dump();

        //Send data (header and body)
        sendRequestMsg(req);
      }
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
    //showListFile(_client->getVectorFile());
    on_listFiles_clicked();
    on_backButton_clicked();
    QString filename, owner, timestamp;
    QList<QListWidgetItem*> fileItem;
    int Contafile=0;
    int ContaFileOwner=0;

    if(!_client->getVectorFile().empty()){
        std::vector<File> files = _client->getVectorFile();
        foreach (File f, files) {
            filename  = QString::fromUtf8(f.getfilename().c_str());
            owner     = QString::fromUtf8(f.getowner().c_str());
            timestamp = QString::fromUtf8(f.gettimestamp().c_str());
            Contafile++;
            if(owner==_client->getUsername()){
                ContaFileOwner++;
            }
        }
    }else{
        Contafile=0;
        ContaFileOwner=0;
    }

    qDebug()<<"Ho un totale di "<< Contafile << "file";
    qDebug()<<"Ho creato "<< ContaFileOwner << "file";

    UserProfile *up = new UserProfile(_client->getUsername(), _client->getMail()); //with parameters
    up->show();
}

//EXIT BUTTON
void MenuWindow::on_exitButton_clicked() {

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Uscita", "Sei sicuro di voler uscire?",
                                    QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {

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
    if (ok && !text.isEmpty() && text.size()<=25){

        //Get data from the form
        QString user = _client->getUsername();
        QByteArray ba_user = user.toLocal8Bit();
        const char *c_user = ba_user.data();
        QString filename = QLatin1String(text.toUtf8()); //è diventa A con dieresi e un altro simbolo. Facendo toLatin1 alla ricezione lo riconverto in è.
        //QString filename = QLatin1String(text.toLatin1()); //crash
        //QString filename = QString::fromUtf8(text.toLatin1()); //è diventa <?> però diventa ? nel filename
        //QString filename = QLatin1String(text.toLocal8Bit()); //crash
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
    else if (ok && !text.isEmpty() && text.size()>25){
        QMessageBox::critical(this,"Errore", "Inserire un nome minore di 25 caratteri!");
        on_newDoc_clicked();
    }
    else if (ok && text.isEmpty()){
        QMessageBox::critical(this,"Errore", "Inserire il nome del documento!");
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
    if (ok && !text.isEmpty() && text.size()<=25){ //TODO: better controls
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
    else if (ok && !text.isEmpty() && text.size()>25) {
        QMessageBox::critical(this,"Errore", "Inserire un nome minore di 25 caratteri!!");
        on_uriDoc_clicked();
    }
    else if (ok && text.isEmpty()){
        QMessageBox::critical(this,"Errore", "Inserire il nome del documento!");
        on_uriDoc_clicked();
    }
}

//OPEN ONE DOCUMENT FROM A LIST OF USER'S DOC
void MenuWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    //Get data from the form
    QString user = _client->getUsername();
    QByteArray ba_user = user.toLocal8Bit();
    const char *c_user = ba_user.data();
    std::vector<QString> uriAndFilename = item->data(Qt::UserRole).value<std::vector<QString>>();
    QString uri = uriAndFilename.at(0);
    QString filename = uriAndFilename.at(1);
    qDebug() << "Opening file: "<<filename<< " - with URI: " << uri;
    filename = QLatin1String(filename.toUtf8());
    QByteArray ba_uri = uri.toLocal8Bit();
    const char *c_uri = ba_uri.data();

    //Serialize data
    json j;
    jsonUtility::to_jsonUri(j, "OPENFILE_REQUEST", c_user, c_uri);
    const std::string req = j.dump();

    //update client data
    _client->setUsername(user);
    _client->setFileURI(uri);
    _client->setFilename(filename);

    //Send data (header and body)
    sendRequestMsg(req);
}

void MenuWindow::showPopupSuccess(QString result) {
    if(result == "DISCONNECT_SUCCESS") {
        StartWindow *s = new StartWindow();
        this->close();
        s->show();
    } else if(result == "LOGOUT_SUCCESS") {
        QApplication::exit();
    } else if(result == "NEWFILE_SUCCESS") {
        EditorWindow *ew = new EditorWindow(_client, this);
        this->hide();
        ew->show();
    } else if(result == "OPENFILE_SUCCESS") {
        _ew = new EditorWindow(_client);
        this->hide();
        _ew->showMaximized(); //later change to showMaximized
    } else if(result == "OPENWITHURI_SUCCESS") {
        EditorWindow *ew = new EditorWindow(_client, this);
        this->hide();
        ew->show();
    } else if(result == "LISTFILE_SUCCESS") {
        ui->stackedWidget->setCurrentIndex(1);
    }
}

void MenuWindow::showPopupFailure(QString result) {
    if(result == "LOGOUT_FAILURE") {
        QMessageBox::critical(this,"Errore", "Logout non completato!");           //Stay in the same window
    } else if(result == "DISCONNECT_FAILURE") {
        QMessageBox::critical(this,"Errore", "Disconnect non completato!");       //Stay in the same window
    } else if(result == "NEWFILE_FAILURE") {
        QMessageBox::critical(this,"Errore", "Newfile non completata!");          //Stay in the same window
    } else if(result == "OPENFILE_FAILURE") {
        QMessageBox::critical(this,"Errore", "Openfile non completata!");         //Stay in the same window (MenuWindow(1))
    } else if(result == "OPENWITHURI_FAILURE") {
        QMessageBox::critical(this,"Errore", "Openwithuri non completata!");      //Stay in the same window
    } else if(result == "LISTFILE_FAILURE") {
        QMessageBox::critical(this,"Errore", "Listfile non completata!");         //Stay in the same window (MenuWindow(1))
    } else if(result == "LISTFILE_FAILURE_LISTNOTEXIST") {
        QMessageBox::warning(this,"Attenzione", "Non hai ancora creato un documento!");  //Stay in the same window (MenuWindow(1))
    } else if(result == "RESPONSE_FAILURE") {
        QMessageBox::critical(this,"Errore", "Risposta non gestita!\nErrore di tipo RESPONSE_FAILURE");
    } else {
        QMessageBox::information(nullptr, "Attenzione", "Qualcosa è andato storto! Riprova!");
    }
}

void MenuWindow::showListFile(std::vector<File> files) {

    qDebug() << "Sono in showListFile";

    QString filename, owner, timestamp;
    QString itemString;
    QList<QListWidgetItem*> fileItem;

    ui->listWidget->clear();
    foreach (File f, files) {
        filename  = QString::fromUtf8(f.getfilename().c_str());
        owner     = QString::fromUtf8(f.getowner().c_str());
        timestamp = QString::fromUtf8(f.gettimestamp().c_str());
        QListWidgetItem* item;
        if(filename.length()>=15){
            filename.resize(14);
            filename=filename+"...";
            itemString = filename+"\t"+owner+"\t"+timestamp;
        }else{
            itemString = filename+"\t\t"+owner+"\t"+timestamp;
        }
        item = new QListWidgetItem(itemString, ui->listWidget);
        std::vector<QString> uriAndFilename;
        uriAndFilename.push_back(QString::fromStdString(f.getidfile()));
        uriAndFilename.push_back(filename);
        QVariant var;
        var.setValue(uriAndFilename);
        item->setData(Qt::UserRole, var);
        _client->setVectorFile(files);
        fileItem.append(item);
    }
}

void MenuWindow::resumeWindow() {
    this->show();
}

void MenuWindow::SetImage() {
    QRect rect(0,0,60,60);
    QRegion region(rect, QRegion::Ellipse);
    qDebug() << region.boundingRect().size();
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

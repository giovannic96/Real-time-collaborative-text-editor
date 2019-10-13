#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "versioninfo.h"
#include "loggeduserinfo.h"
#include <QtGui>            //Per QPoint
#include <QDebug>            //Per QPoint
#include <QMessageBox>      //Per Messaggi di alert

//CONSTRUCTOR --> The FramelessWindowsHint and WindowSystemMenuHint options is needed for make bordless the window
LoginWindow::LoginWindow(QWidget *parent):
    QMainWindow(parent, Qt::FramelessWindowHint | Qt::WindowSystemMenuHint), ui(new Ui::LoginWindow){
    ui->setupUi(this);
    ui->version->setText(qstr);//Associate the QLabel "version" at the string "qstr". In this way I can show the version of this software
}

//DESTRUCTION
LoginWindow::~LoginWindow(){
    delete ui;
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
}

//REGISTRATI BUTTON --> handle the switch beetween this window and the "registration window"
void LoginWindow::on_RegistratiButton_clicked(){
    RegWindow *l = new RegWindow();
    l->show();
    this->hide();
}

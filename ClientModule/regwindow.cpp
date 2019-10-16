#include "regwindow.h"
#include "ui_regwindow.h"
#include "versioninfo.h"
#include <QtGui>            //QPoint

//CONSTRUCTOR
RegWindow::RegWindow(QWidget *parent) :
    QMainWindow(parent, Qt::FramelessWindowHint | Qt::WindowSystemMenuHint), ui(new Ui::RegWindow){
    ui->setupUi(this);
    ui->version->setText(qstr); //Associate the QLabel "version" at the string "qstr". In this way I can show the version of this software
}

//DESTRUCTOR
RegWindow::~RegWindow() {
    delete ui;
    db.close();
}

//FUNCTION FOR MAKE DRAGGABLE THE WINDOW
void RegWindow::mousePressEvent(QMouseEvent *evt){
     oldPos = evt->globalPos();
}

//FUNCTION FOR MAKE DRAGGABLE THE WINDOW
void RegWindow::mouseMoveEvent(QMouseEvent *evt){
    const QPoint delta = evt->globalPos() - oldPos;
    move(x()+delta.x(), y()+delta.y());
    oldPos = evt->globalPos();
}

//EXIT BUTTON
void RegWindow::on_exitButton_clicked(){
    QApplication::exit();   //I've used exit() instead quit() or close() for this reason --> https://ux.stackexchange.com/questions/50893/do-we-exit-quit-or-close-an-application
}

//ACCEDI BUTTON --> handle the switch beetween this window and the "login window"
void RegWindow::on_AccediButton_clicked(){
    LoginWindow *l = new LoginWindow();
    l->show();
    this->hide();
}

void RegWindow::on_SignUpButton_clicked()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("INSERIRE PERCORSO DB LOCALE"); //IMPORTANTE SENNO' NON PARTE

    if(db.open()) {

        //Retrieve data from input fields
        QString username = ui->LineEditUsernameForm->text();
        QString password = ui->LineEditPasswordForm->text();
        QString email = ui->LineEditMailForm->text();

        //Run our query
        QSqlQuery query;
        query.prepare("INSERT INTO users (username, password, email) VALUES (:username, :password, :email)");
        query.bindValue(":username", username);
        query.bindValue(":password", password);
        query.bindValue(":email", email);

        if(query.exec()) {
            QMessageBox::information(this, "Inserted", "Data inserted successfully");
            db.close();
        } else {
            QMessageBox::information(this, "Not inserted", "Error: Data not inserted!");
            db.close();
        }
    } else {
        QSqlError error = db.lastError();
        QMessageBox::information(this, "Error during connection", error.databaseText());
    }
}


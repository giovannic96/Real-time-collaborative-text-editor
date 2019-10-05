#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_username->setPlaceholderText("Enter username");
    ui->lineEdit_password->setPlaceholderText("Enter password");
    ui->lineEdit_email->setPlaceholderText("Enter email");
}

MainWindow::~MainWindow()
{
    delete ui;
    db.close();
}

void MainWindow::on_registerButton_clicked()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    //db.setHostName("localhost");
    //db.setUserName("root");
    //db.setPassword("");
    db.setDatabaseName("C:/Users/giova/QTProjects/ClientModule/Db/texteditor_users.sqlite");

    if(db.open()) {

        //Retrieve data from input fields
        QString username = ui->lineEdit_username->text();
        QString password = ui->lineEdit_password->text();
        QString email = ui->lineEdit_email->text();

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

void MainWindow::on_loginButton_clicked()
{
    QSqlDatabase db2;
    db2 = QSqlDatabase::addDatabase("QSQLITE", "MyConnect");
    db2.setDatabaseName("C:/Users/giova/QTProjects/ClientModule/Db/texteditor_users.sqlite");
    if(db2.open()) {

        //Retrieve data from input fields
        QString username = ui->lineEdit_username_login->text();
        QString password = ui->lineEdit_password_login->text();

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
                    QMessageBox::information(this, "Success", "Login success");
                    loginDialog myDialog; //new window
                    myDialog.setModal(true);
                    myDialog.exec();
                } else {
                    QMessageBox::information(this, "Failure", "Login failed");
                }
            }
            db2.close();
        } else {
            QMessageBox::information(this, "Failed", "Error: Query failed to execute!");
            db2.close();
        }
    } else {
        QSqlError error = db2.lastError();
        QMessageBox::information(this, "Error during connection", error.databaseText());
    }
}













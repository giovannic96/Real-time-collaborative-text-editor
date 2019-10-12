#include <iostream>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QtCore/QVariant>

void signup() {
    QSqlDatabase db;

    //queste variabili arriveranno dal client
    QString username = "pincopallino";
    QString password = "asdasdasdas";
    QString email = "allo@gmail.com";

    //controllo regex sulla mail
    QRegExp mailREX("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");
    mailREX.setCaseSensitivity(Qt::CaseInsensitive);
    mailREX.setPatternSyntax(QRegExp::RegExp);
    if (!mailREX.exactMatch(email)) {
        std::cout << "E-mail non valida" << std::endl;
    } //else bisogna avvisare il client (json che contiene il corretto codice di errore per la mail) e non fare nessun inserimento nel db

    db = QSqlDatabase::addDatabase("QSQLITE", "MyConnect");
    db.setDatabaseName("texteditor_users.sqlite");

    if (db.open()) {
        QSqlQuery query(QSqlDatabase::database("MyConnect"));
        query.prepare(QString("SELECT * FROM users WHERE username = :username"));
        query.bindValue(":username", username);

        if (query.exec()) {
            if (query.next()) {
                QString usernameFromDb = query.value(0).toString();
                QString passwordFromDb = query.value(1).toString();
                if (usernameFromDb == username) {
                    std::cout << "Utente già esistente" << std::endl;
                }
            } else {
                std::cout << "L'utente può essere creato" << std::endl;

                QSqlQuery query2(QSqlDatabase::database("MyConnect"));
                query2.prepare("INSERT INTO users (username, password, email) VALUES (:username, :password, :email)");
                query2.bindValue(":username", username);
                query2.bindValue(":password", password);
                query2.bindValue(":email", email);

                if (query2.exec()) {
                    std::cout << "Inserted Data inserted successfully";
                } else {
                    std::cout << "Not inserted Error: Data not inserted!";
                }
            }
            db.close();
        } else {
            std::cout << "Query SELECT fallita" << std::endl;
            db.close();
        }

    } else {
        QSqlError error = db.lastError();
        std::cout << "Error during connection";
    }
    QSqlDatabase::removeDatabase("QSQLITE");
}
void login(){
    QSqlDatabase db;

    //queste variabili arriveranno dal client
    QString username = "pincopallino";
    QString password = "asdasdasdas";
    QString email = "allo@gmail.com";

    //controllo regex sulla mail
    QRegExp mailREX("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");
    mailREX.setCaseSensitivity(Qt::CaseInsensitive);
    mailREX.setPatternSyntax(QRegExp::RegExp);
    if (!mailREX.exactMatch(email)) {
        std::cout << "E-mail non valida" << std::endl;
    } //else bisogna avvisare il client (json che contiene il corretto codice di errore per la mail) e non fare nessun inserimento nel db

    db = QSqlDatabase::addDatabase("QSQLITE", "MyConnect2");
    db.setDatabaseName("texteditor_users.sqlite");

    if(db.open()) {

        QSqlQuery query(QSqlDatabase::database("MyConnect2"));
        query.prepare(QString("SELECT * FROM users WHERE username = :username AND password = :password"));
        query.bindValue(":username", username);
        query.bindValue(":password", password);

        if(query.exec()) {
            if(query.next()) {
                QString usernameFromDb = query.value(0).toString();
                QString passwordFromDb = query.value(1).toString();

                if(usernameFromDb == username && passwordFromDb == password) {
                    std::cout << "Login success" << std::endl;
                }
            } else {
                std::cout << "Login fail" << std::endl;
            }
            db.close();
        } else {
            std::cout << "Errore nella Select" << std::endl;
            db.close();
        }
    } else {
        QSqlError error = db.lastError();
        std::cout << "Errore connessione db" << std::endl;
    }
    QSqlDatabase::removeDatabase("QSQLITE");
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    signup();
    login();
    return 0;
}
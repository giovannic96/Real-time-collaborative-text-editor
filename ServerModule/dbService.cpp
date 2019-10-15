//
// Created by giova on 05/10/2019.
//

#include <string>
#include "header_files/dbService.h"
#include <iostream>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QtCore/QVariant>

dbService::DB_RESPONSE dbService::tryLogin(const std::string& user, const std::string& pass) {
    QSqlDatabase db;

    QString username = QString::fromUtf8(user.data(), user.size());
    QString password = QString::fromUtf8(pass.data(), pass.size());

    db = QSqlDatabase::addDatabase("QSQLITE", "MyConnect2");
    db.setDatabaseName("C:/Users/giova/CLionProjects/Real time text editor/ServerModule/Db/texteditor_users.sqlite");

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
                    return LOGIN_OK;
                }
            } else {
                std::cout << "Login failed" << std::endl;
                return LOGIN_FAILED;
            }
            db.close();
        } else {
            std::cout << "Error on select" << std::endl;
            db.close();
            return QUERY_ERROR;
        }
    } else {
        QSqlError error = db.lastError();
        std::cout << "Error on db connection. " << error.text().data() << std::endl;
        return DB_ERROR;
    }
    QSqlDatabase::removeDatabase("QSQLITE");
}

dbService::DB_RESPONSE dbService::trySignup(const std::string& user, const std::string& pass, const std::string& email) {

    std::string query = "INSERT INTO users (username, password, email) VALUES (?,?,?)";
    sqlite3_stmt * st;

    if(sqlite3_open("Db/texteditor_users.sqlite", &_db) == SQLITE_OK) {
        sqlite3_prepare(_db, query.c_str(), -1, &st, nullptr);
        sqlite3_bind_text(st, 1, user.c_str(), user.length(), SQLITE_TRANSIENT);
        sqlite3_bind_text(st, 2, pass.c_str(), pass.length(), SQLITE_TRANSIENT);
        sqlite3_bind_text(st, 3, email.c_str(), email.length(), SQLITE_TRANSIENT);
        sqlite3_step(st);
        return SIGNUP_OK;
    } else {
        return SIGNUP_FAILED;
    }
}

inline const char* dbService::enumToStr(dbService::DB_RESPONSE db_resp) {
    switch (db_resp) {
        case dbService::LOGIN_OK:       return "LOGIN_OK";
        case dbService::LOGIN_FAILED:   return "LOGIN_FAILED";
        case dbService::SIGNUP_OK:      return "SIGNUP_OK";
        case dbService::SIGNUP_FAILED:  return "SIGNUP_FAILED";
        case dbService::DB_ERROR:       return "DB_ERROR";
        case dbService::QUERY_ERROR:    return "QUERY_ERROR";
        default:                        return "[Unknown db response]";
    }
}
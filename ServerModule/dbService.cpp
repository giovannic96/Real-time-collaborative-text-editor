//
// Created by giova on 05/10/2019.
//

#include <string>
#include "header_files/dbService.h"

dbService::DB_RESPONSE dbService::tryLogin(std::string user, std::string pass) {

    //write function
    return LOGIN_OK;
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

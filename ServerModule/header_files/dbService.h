//
// Created by giova on 05/10/2019.
//

#ifndef SERVERMODULE_DBSERVICE_H
#define SERVERMODULE_DBSERVICE_H

#include "sqlite3.h"

class dbService {

private:
    sqlite3* _db;

public:
    enum DB_RESPONSE {LOGIN_OK, LOGIN_FAILED, SIGNUP_OK, SIGNUP_FAILED, DB_ERROR, QUERY_ERROR};
    static inline const char* enumToStr(dbService::DB_RESPONSE db_resp);
    static DB_RESPONSE tryLogin(const std::string& user, const std::string& pass);
    DB_RESPONSE trySignup(const std::string &user, const std::string &pass, const std::string &email);
};


#endif //SERVERMODULE_DBSERVICE_H

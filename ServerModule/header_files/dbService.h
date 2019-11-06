//
// Created by giova on 05/10/2019.
//

#ifndef SERVERMODULE_DBSERVICE_H
#define SERVERMODULE_DBSERVICE_H

#include <QtCore/QString>
#include "sqlite3.h"
#include <vector>
#include "File.h"

class dbService {

private:
    sqlite3* _db;

public:
    enum DB_RESPONSE {LOGIN_OK, LOGIN_FAILED, SIGNUP_OK, SIGNUP_FAILED, NEWFILE_OK, NEWFILE_FAILED, OPENFILE_OK, OPENFILE_FAILED,
                        DB_ERROR, QUERY_ERROR, EMAIL_ERROR, FILENAME_ERROR, ALREADY_LOGGED, LIST_EXIST, LIST_DOESNT_EXIST
    };
    static inline const char* enumToStr(dbService::DB_RESPONSE db_resp);
    static QString generateURI(int len);
    static QString getTimestamp();
    static DB_RESPONSE tryLogin(const std::string& user, const std::string& pass);
    static DB_RESPONSE trySignup(const std::string& user, const std::string& pass, const std::string& email);
    static DB_RESPONSE tryNewFile(const std::string& user, const std::string& file_name);
    static DB_RESPONSE tryListFile(const std::string& user, std::vector<File>& vectorFile);
    static DB_RESPONSE tryOpenFile(const std::string& user, const std::string& file_name);
};


#endif //SERVERMODULE_DBSERVICE_H

//
// Created by giova on 05/10/2019.
//

#ifndef SERVERMODULE_DBSERVICE_H
#define SERVERMODULE_DBSERVICE_H

#include <QtCore/QString>
#include "sqlite3.h"
#include <vector>
#include <map>
#include "File.h"

class dbService {

private:
    sqlite3* _db;

public:
    enum DB_RESPONSE {LOGIN_OK, LOGIN_FAILED, SIGNUP_OK, SIGNUP_FAILED, NEWFILE_OK, NEWFILE_FAILED, OPENFILE_OK, OPENFILE_FAILED,
                        DB_ERROR, QUERY_ERROR, EMAIL_ERROR, ALREADY_LOGGED, LIST_EXIST, LIST_DOESNT_EXIST, OPENWITHURI_OK,
                        OPENWITHURI_FAILED, LOGOUT_OK, LOGOUT_FAILED, RENAME_OK, RENAME_FAILED, ALREADY_PARTECIPANT, INVITE_URI_SUCCESS,
                        INVITE_URI_FAILED, INVITED_NOT_EXIST, GET_EMAIL_OK, GET_COLLAB_COLORS_MAP_OK

    };
    static inline const char* enumToStr(dbService::DB_RESPONSE db_resp);
    static QString generateURI(int len);
    static QString generateColor();
    static QString getTimestamp();
    static DB_RESPONSE tryLogin(const std::string& user, const std::string& pass, QString& color);
    static DB_RESPONSE tryLogout(const std::string& user, const std::string& urifile);
    static DB_RESPONSE tryLogout(const std::string& user);
    static DB_RESPONSE trySignup(const std::string& user, const std::string& pass, const std::string& email);
    static DB_RESPONSE tryNewFile(const std::string& user, const std::string& file_name, const QString& uri);
    static DB_RESPONSE tryListFile(const std::string& user, std::vector<File>& vectorFile);
    static DB_RESPONSE tryOpenFile(const std::string& user, const std::string& urifile);
    static DB_RESPONSE tryOpenWithURIFile(const std::string& user, const std::string& urifile, std::string& filename);
    static DB_RESPONSE tryRenameFile(const std::string& newNameFile, const std::string& urifile, const std::string& user);
    static DB_RESPONSE tryGetEmail(const std::string& invited, std::string& email_invited);
    static DB_RESPONSE tryAddFriend(const std::string& invited, const std::string& urifile);
    static DB_RESPONSE tryGetCollabColors(const std::string& uri, std::map<std::string, std::string>& collabColorsMap);

    };


#endif //SERVERMODULE_DBSERVICE_H

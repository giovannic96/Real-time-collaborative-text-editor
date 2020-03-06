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
#include <QtCore/QDateTime>

dbService::DB_RESPONSE dbService::tryLogout(const std::string& user) {
    QSqlDatabase db;
    QString username = QString::fromUtf8(user.data(), user.size());

    db = QSqlDatabase::addDatabase("QSQLITE", "MyConnect2");
    db.setDatabaseName("../Db/texteditor_users.sqlite");
    if(db.open()) {
        QSqlQuery query(QSqlDatabase::database("MyConnect2"));
        query.prepare(QString("UPDATE users SET isLogged=0 WHERE username= :username"));
        query.bindValue(":username", username);

        if(query.exec()) {
            std::cout << "LOGOUT without URI success" << std::endl;
            db.close();
            return LOGOUT_OK;
        } else {
            std::cout << "Error on SELECT" << std::endl;
            db.close();
            return QUERY_ERROR;
        }
    } else {
        QSqlError error = db.lastError();
        std::cout << "Error on db connection. " << error.text().data() << std::endl;
        return DB_ERROR;
    }
}

dbService::DB_RESPONSE dbService::tryLogout(const std::string& user, const std::string& urifile) {
    QSqlDatabase db;
    QString username = QString::fromUtf8(user.data(), user.size());
    QString uri = QString::fromUtf8(urifile.data(), urifile.size());

    db = QSqlDatabase::addDatabase("QSQLITE", "MyConnect2");
    db.setDatabaseName("../Db/texteditor_users.sqlite");

    if(db.open()) {
        QSqlQuery query(QSqlDatabase::database("MyConnect2"));
        query.prepare(QString("UPDATE permissions SET isOpen=0 WHERE iduser= :username and idfile = :uri"));
        query.bindValue(":username", username);
        query.bindValue(":uri", uri);

        if(query.exec()) {
            std::cout << "LOGOUT with URI success" << std::endl;
            db.close();
            return LOGOUT_OK;
        } else {
            std::cout << "Error on UPDATE isOpen" << std::endl;
            db.close();
            return QUERY_ERROR;
        }
    } else {
        QSqlError error = db.lastError();
        std::cout << "Error on db connection. " << error.text().data() << std::endl;
        return DB_ERROR;
    }
}

dbService::DB_RESPONSE dbService::tryLogin(const std::string& user, const std::string& pass, QString& color) {
    QSqlDatabase db;
    QString username = QString::fromUtf8(user.data(), user.size());
    QString password = QString::fromUtf8(pass.data(), pass.size());

    db = QSqlDatabase::addDatabase("QSQLITE", "MyConnect2");
    db.setDatabaseName("../Db/texteditor_users.sqlite");

    if(db.open()) {
        QSqlQuery query(QSqlDatabase::database("MyConnect2"));
        query.prepare(QString("SELECT * FROM users WHERE username = :username AND password = :password"));
        query.bindValue(":username", username);
        query.bindValue(":password", password);

        if(query.exec()) {
            if(query.next()) {
                QString usernameFromDb = query.value(0).toString();
                QString passwordFromDb = query.value(1).toString();
                bool isLoggedFromDb = query.value(3).toBool();
                QString colorFromDb = query.value(4).toString();

                if(usernameFromDb == username && passwordFromDb == password) {
                    if(!isLoggedFromDb) {
                        QSqlQuery query2(QSqlDatabase::database("MyConnect2"));
                        query2.prepare(QString("UPDATE users SET isLogged=1 WHERE username= :username and password= :password"));
                        query2.bindValue(":username", usernameFromDb);
                        query2.bindValue(":password", passwordFromDb);

                        if(query2.exec()) {
                            std::cout << "Login success" << std::endl;
                            color = colorFromDb;
                            return LOGIN_OK;
                        } else {
                            std::cout << "Error on UPDATE" << std::endl;
                            return QUERY_ERROR;
                        }
                    }
                    else {
                        std::cout << "Already logged user" << std::endl;
                        return ALREADY_LOGGED;
                    }
                }
            } else {
                std::cout << "Login failed" << std::endl;
                return LOGIN_FAILED;
            }
            db.close();
        } else {
            std::cout << "Error on SELECT" << std::endl;
            db.close();
            return QUERY_ERROR;
        }
    } else {
        QSqlError error = db.lastError();
        std::cout << "Error on db connection. " << error.text().data() << std::endl;
        return DB_ERROR;
    }
}

dbService::DB_RESPONSE dbService::trySignup(const std::string& user, const std::string& pass, const std::string& email) {
    QSqlDatabase db;

    QString username = QString::fromUtf8(user.data(), user.size());
    QString password = QString::fromUtf8(pass.data(), pass.size());
    QString mail = QString::fromUtf8(email.data(), email.size());

    //control email with regex
    QRegExp mailREX(R"(\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\.[A-Z]{2,4}\b)");
    mailREX.setCaseSensitivity(Qt::CaseInsensitive);
    mailREX.setPatternSyntax(QRegExp::RegExp);
    if (!mailREX.exactMatch(mail)) {
        return EMAIL_ERROR;
    }

    db = QSqlDatabase::addDatabase("QSQLITE", "MyConnect");
    db.setDatabaseName("../Db/texteditor_users.sqlite");

    if (db.open()) {
        QSqlQuery query(QSqlDatabase::database("MyConnect"));
        query.prepare(QString("SELECT * FROM users WHERE username = :username"));
        query.bindValue(":username", username);

        if (query.exec()) {
            if (query.next()) {
                QString usernameFromDb = query.value(0).toString();
                QString passwordFromDb = query.value(1).toString();
                if (usernameFromDb == username)
                    return SIGNUP_FAILED;
            } else { //user can be created
                QSqlQuery query2(QSqlDatabase::database("MyConnect"));
                query2.prepare("INSERT INTO users (username, password, email, color) VALUES (:username, :password, :email, :color)");
                query2.bindValue(":username", username);
                query2.bindValue(":password", password);
                query2.bindValue(":email", mail);
                query2.bindValue(":color", generateColor());

                if (query2.exec())
                    return SIGNUP_OK;
                else
                    return QUERY_ERROR;
            }
            db.close();
        } else {
            db.close();
            return QUERY_ERROR;
        }
    } else {
        QSqlError error = db.lastError();
        return DB_ERROR;
    }
}

dbService::DB_RESPONSE dbService::tryNewFile(const std::string& user, const std::string& file_name, const QString& uri) {
    QSqlDatabase db;

    QString username = QString::fromUtf8(user.data(), user.size());
    QString filename = QString::fromUtf8(file_name.data(), file_name.size());

    db = QSqlDatabase::addDatabase("QSQLITE", "MyConnect3");
    db.setDatabaseName("../Db/texteditor_users.sqlite");
    if (db.open()) {
        QSqlQuery query(QSqlDatabase::database("MyConnect3"));
        query.prepare(QString("SELECT * FROM files WHERE filename = :filename and  owner = :username "));
        query.bindValue(":username", username);
        query.bindValue(":filename", filename);

        if (query.exec()) {
            if (query.next()) //username already exists
                return NEWFILE_FAILED;

            QString timestamp = getTimestamp();
            QSqlQuery query2(QSqlDatabase::database("MyConnect3"));

            query2.prepare("INSERT INTO files (uri, filename, owner, timestamp) VALUES (:uri, :filename, :owner, :timestamp)");
            query2.bindValue(":uri", uri);
            query2.bindValue(":filename", filename);
            query2.bindValue(":owner", username);
            query2.bindValue(":timestamp", timestamp);

            if (query2.exec()) {
                QSqlQuery query3(QSqlDatabase::database("MyConnect3"));

                query3.prepare("INSERT INTO permissions (idfile, iduser, isOwner, isOpen, isConfirmed) VALUES (:idfile, :iduser, :isOwner, :isOpen, :isConfirmed)");
                query3.bindValue(":idfile", uri);
                query3.bindValue(":iduser", username);
                query3.bindValue(":isOwner", true);
                query3.bindValue(":isOpen", true);
                query3.bindValue(":isConfirmed", true);

                if (query3.exec()) {
                    /* TODO: remove this query4 later */
                    QSqlQuery query4(QSqlDatabase::database("MyConnect3"));
                    query4.prepare("INSERT INTO permissions (idfile, iduser, isOwner, isOpen, isConfirmed) VALUES (:idfile, :iduser, :isOwner, :isOpen, :isConfirmed)");
                    query4.bindValue(":idfile", uri);
                    query4.bindValue(":iduser", "a5");
                    query4.bindValue(":isOwner", false);
                    query4.bindValue(":isOpen", false);
                    query4.bindValue(":isConfirmed", true);
                    query4.exec();
                    return NEWFILE_OK;
                }
                else
                    return NEWFILE_FAILED;
            } else {
                db.close();
                return QUERY_ERROR;
            }
        } else {
            db.close();
            return QUERY_ERROR;
        }
    } else {
        QSqlError error = db.lastError();
        return DB_ERROR;
    }
}
dbService::DB_RESPONSE dbService::tryListFile(const std::string& user, std::vector<File>& vectorFile) {
    QSqlDatabase db;
    QString username = QString::fromUtf8(user.data(), user.size());

    db = QSqlDatabase::addDatabase("QSQLITE", "MyConnect2");
    db.setDatabaseName("../Db/texteditor_users.sqlite");

    if(db.open()) {
        QSqlQuery query(QSqlDatabase::database("MyConnect2"));
        query.prepare(QString("SELECT uri, filename, owner, timestamp FROM files F, permissions P  WHERE F.uri=P.idfile AND iduser = :username AND isConfirmed=1"));
        query.bindValue(":username", username);
        if (query.exec()) {
            bool check = false;
            while (query.next()) {
                std::string uriDb = query.value(0).toString().toStdString();
                std::string filenameDb = query.value(1).toString().toStdString();
                std::string ownerDb = query.value(2).toString().toStdString();
                std::string timestampDb = query.value(3).toString().toStdString();

                File file = File{uriDb, filenameDb, ownerDb, timestampDb};
                vectorFile.push_back(file);
                check = true;
            }
            db.close();
            if(check)
                return LIST_EXIST;
            else
                return LIST_DOESNT_EXIST;
        } else {
            std::cout << "Error on SELECT" << std::endl;
            db.close();
            return QUERY_ERROR;
        }
    } else {
        QSqlError error = db.lastError();
        std::cout << "Error on db connection. " << error.text().data() << std::endl;
        return DB_ERROR;
    }
}

dbService::DB_RESPONSE dbService::tryOpenFile(const std::string& user, const std::string& urifile) {
    QSqlDatabase db;
    QString username = QString::fromUtf8(user.data(), user.size());
    QString uri = QString::fromUtf8(urifile.data(), urifile.size());

    db = QSqlDatabase::addDatabase("QSQLITE", "MyConnect2");
    db.setDatabaseName("../Db/texteditor_users.sqlite");

    if(db.open()) {
        QSqlQuery query(QSqlDatabase::database("MyConnect2"));
        query.prepare(QString("SELECT idfile, iduser FROM  permissions  WHERE idfile= :uri and iduser = :username and isConfirmed=true"));
        query.bindValue(":username", username);
        query.bindValue(":uri", uri);
        if (query.exec()) {
            if (query.next()) {
                QSqlQuery query2(QSqlDatabase::database("MyConnect2"));
                query2.prepare(QString("UPDATE permissions SET isOpen=1 WHERE idfile= :uri and iduser= :username"));
                query2.bindValue(":username", username);
                query2.bindValue(":uri", uri);

                if(query2.exec()) {
                    db.close();
                    return OPENFILE_OK;
                } else {
                    std::cout << "Error on UPDATE" << std::endl;
                    db.close();
                    return QUERY_ERROR;
                }
            } else {
                std::cout << "User doesn't have permission to open the file" << std::endl;
                db.close();
                return OPENFILE_FAILED;
            }
        } else {
            std::cout << "Error on SELECT" << std::endl;
            db.close();
            return QUERY_ERROR;
        }
    } else {
        QSqlError error = db.lastError();
        std::cout << "Error on db connection. " << error.text().data() << std::endl;
        return DB_ERROR;
    }
}

dbService::DB_RESPONSE dbService::tryOpenWithURIFile(const std::string& user, const std::string& urifile, std::string& filename) {
    QSqlDatabase db;
    QString username = QString::fromUtf8(user.data(), user.size());
    QString uri = QString::fromUtf8(urifile.data(), urifile.size());

    db = QSqlDatabase::addDatabase("QSQLITE", "MyConnect2");
    db.setDatabaseName("../Db/texteditor_users.sqlite");

    if(db.open()) {
        QSqlQuery query(QSqlDatabase::database("MyConnect2"));
        query.prepare(QString("SELECT uri, filename, iduser FROM files F, permissions P  WHERE F.uri = P.idfile and P.idfile = :uri and P.iduser = :username"));
        query.bindValue(":username", username);
        query.bindValue(":uri", uri);
        if (query.exec()) {
            if (query.next()) {
                filename = query.value(1).toString().toStdString();
                QSqlQuery query2(QSqlDatabase::database("MyConnect2"));
                query2.prepare(QString("UPDATE permissions SET isOpen=1, isConfirmed=1 WHERE idfile= :uri and iduser= :username"));
                query2.bindValue(":username", username);
                query2.bindValue(":uri", uri);

                if(query2.exec()) {
                    db.close();
                    return OPENWITHURI_OK;
                } else {
                    std::cout << "Error on UPDATE" << std::endl;
                    db.close();
                    return QUERY_ERROR;
                }
            } else {
                std::cout << "User doesn't have permission to open the file" << std::endl;
                db.close();
                return OPENWITHURI_FAILED;
            }
        } else {
            std::cout << "Error on SELECT" << std::endl;
            db.close();
            return QUERY_ERROR;
        }
    } else {
        QSqlError error = db.lastError();
        std::cout << "Error on db connection. " << error.text().data() << std::endl;
        return DB_ERROR;
    }
}

dbService::DB_RESPONSE dbService::tryGetEmail(const std::string &invited, std::string &email_invited) {
    QSqlDatabase db;
    QString username = QString::fromUtf8(invited.data(), invited.size());

    db = QSqlDatabase::addDatabase("QSQLITE", "MyConnect2");
    db.setDatabaseName("../Db/texteditor_users.sqlite");
    if(db.open()) {
        QSqlQuery query(QSqlDatabase::database("MyConnect2"));
        query.prepare(QString("SELECT email FROM users WHERE username= :username LIMIT 1"));
        query.bindValue(":username", username);
        if (query.exec()) {
            if (query.next()) { //user exists
                email_invited = query.value(0).toString().toStdString();
                db.close();
                return GET_EMAIL_OK;
            } else {
                db.close();
                return INVITED_NOT_EXIST;
            }
        } else {
            std::cout << "Error on SELECT" << std::endl;
            db.close();
            return QUERY_ERROR;
        }
    } else {
        QSqlError error = db.lastError();
        std::cout << "Error on db connection. " << error.text().data() << std::endl;
        return DB_ERROR;
    }
}

dbService::DB_RESPONSE dbService::tryAddFriend(const std::string &invited, const std::string &urifile) {
    QSqlDatabase db;
    QString username = QString::fromUtf8(invited.data(), invited.size());
    QString uri = QString::fromUtf8(urifile.data(), urifile.size());

    db = QSqlDatabase::addDatabase("QSQLITE", "MyConnect2");
    db.setDatabaseName("../Db/texteditor_users.sqlite");

    if(db.open()) {
        QSqlQuery query(QSqlDatabase::database("MyConnect2"));
        query.prepare(QString("SELECT COUNT(*) FROM users WHERE username= :username LIMIT 1"));
        query.bindValue(":username", username);
        if (query.exec()) {
            query.first();
            int num_rows = query.value(0).toInt();
            if(num_rows == 0) {
                db.close();
                std::cout << "Applicant doesn't exist" << std::endl;
                return INVITED_NOT_EXIST;
            }
        } else {
            std::cout << "Error on SELECT COUNT" << std::endl;
            db.close();
            return QUERY_ERROR;
        }

        QSqlQuery query3(QSqlDatabase::database("MyConnect2"));
        query3.prepare(QString("SELECT idfile, iduser FROM permissions WHERE idfile= :uri and iduser= :username"));
        query3.bindValue(":username", username);
        query3.bindValue(":uri", uri);
        if (query3.exec()) {
            if (query3.next()) { //user is already partecipant of the file
                std::cout << "User already partecipant of the file" << std::endl;
                db.close();
                return ALREADY_PARTECIPANT;

            } else {

                QSqlQuery query2(QSqlDatabase::database("MyConnect2"));
                query2.prepare(QString("INSERT INTO permissions (idfile, iduser, isOwner, isOpen, isConfirmed) VALUES (:uri, :username, 0, 0, 0);"));
                query2.bindValue(":username", username);
                query2.bindValue(":uri", uri);

                if(query2.exec()) {
                    db.close();
                    return INVITE_URI_SUCCESS;
                } else {
                    std::cout << "Error Insert" << std::endl;
                    db.close();
                    return INVITE_URI_FAILED;
                }
            }
        } else {
            std::cout << "Error on SELECT" << std::endl;
            db.close();
            return QUERY_ERROR;
        }
    } else {
        QSqlError error = db.lastError();
        std::cout << "Error on db connection. " << error.text().data() << std::endl;
        return DB_ERROR;
    }
}

inline const char* dbService::enumToStr(dbService::DB_RESPONSE db_resp) {
    switch (db_resp) {
        case dbService::LOGIN_OK:       return "LOGIN_OK";
        case dbService::LOGIN_FAILED:   return "LOGIN_FAILED";
        case dbService::LOGOUT_OK:      return "LOGOUT_OK";
        case dbService::LOGOUT_FAILED:  return "LOGOUT_FAILED";
        case dbService::SIGNUP_OK:      return "SIGNUP_OK";
        case dbService::SIGNUP_FAILED:  return "SIGNUP_FAILED";
        case dbService::DB_ERROR:       return "DB_ERROR";
        case dbService::QUERY_ERROR:    return "QUERY_ERROR";
        case dbService::ALREADY_LOGGED: return "ALREADY_LOGGED";
        default:                        return "[Unknown db response]";
    }
}

QString dbService::generateURI(int len) {
    std::string str = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int n = str.length();
    std::string URI;
    for (int i=1; i<=len; i++)
        URI.push_back(str[rand() % n]);
    return(QString::fromUtf8(URI.data(), URI.size()));
}

QString dbService::generateColor() {
    std::string hex = "abcdef0123456789";
    int n = hex.length();
    std::string color;
    color.push_back('#');
    for (int i=1; i<=8; i++)
        color.push_back(hex[rand() % n]);
    return(QString::fromUtf8(color.data(), color.size()));
}

QString dbService::getTimestamp() {
    qint64 utcTime = QDateTime::currentMSecsSinceEpoch();
    QDateTime dt;
    dt.setTime_t(utcTime/1000);
    return dt.toString("yyyy-MM-dd hh:mm:ss");
}

dbService::DB_RESPONSE dbService::tryRenameFile(const std::string &newNameFile, const std::string &urifile, const std::string &user) {
    QSqlDatabase db;
    QString username = QString::fromUtf8(user.data(), user.size());
    QString uri = QString::fromUtf8(urifile.data(), urifile.size());
    QString namefile = QString::fromUtf8(newNameFile.data(), newNameFile.size());
    QString owner;

    db = QSqlDatabase::addDatabase("QSQLITE", "MyConnect3");
    db.setDatabaseName("../Db/texteditor_users.sqlite");

    if (db.open()) {

        //get the name of the owner of the uri requested from the db
        QSqlQuery query3(QSqlDatabase::database("MyConnect3"));
        query3.prepare(QString("SELECT * FROM files WHERE uri = :uri"));
        query3.bindValue(":uri", uri);

        if (query3.exec()) {
            if (query3.next()) {
                owner = query3.value(2).toString();
                //std::cout << "Questo è il proprietario: " << owner.toStdString() << std::endl;//debug
            } else {
                db.close();
                return QUERY_ERROR;
            }
        } else {
            db.close();
            return QUERY_ERROR;
        }

        QSqlQuery query(QSqlDatabase::database("MyConnect3"));
        query.prepare(QString("SELECT * FROM files WHERE filename = :filename and  owner = :username "));
        query.bindValue(":username", owner);
        query.bindValue(":filename", namefile);

        if (query.exec()) {
            if (query.next()) {//filename already exists
                db.close();
                return RENAME_FAILED;
            } else {
                QSqlQuery query2(QSqlDatabase::database("MyConnect3"));
                query2.prepare("UPDATE files SET filename = :filename WHERE uri = :uri and owner = :username ");
                query2.bindValue(":uri", uri);
                query2.bindValue(":filename", namefile);
                query2.bindValue(":username", owner);

                if (query2.exec()) {
                    db.close();
                    return RENAME_OK;
                } else {
                    db.close();
                    return QUERY_ERROR;
                }
            }
        } else {
            db.close();
            return QUERY_ERROR;
        }
    }else {
        QSqlError error = db.lastError();
        return DB_ERROR;
    }
}



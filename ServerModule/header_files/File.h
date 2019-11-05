//
// Created by franc on 10/29/2019.
#include <QtCore/QString>
#ifndef SERVERMODULE_FILE_H
#define SERVERMODULE_FILE_H


class File {
private:
    QString idfile;
    QString filename;
    QString iduser;
    QString timestamp;
    bool isOwner;
public:
    File (const QString idfile, const QString filename, const QString iduser, const bool isOwner, const QString timestamp);
};


#endif //SERVERMODULE_FILE_H

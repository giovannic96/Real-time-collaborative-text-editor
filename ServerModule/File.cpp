//
// Created by franc on 10/29/2019.
//

#include "header_files/File.h"

File::File(const QString idfile, const QString filename, const QString iduser, const bool isOwner, const QString timestamp) {
    this->idfile = idfile;
    this->filename = filename;
    this->iduser = iduser;
    this->isOwner = isOwner;
    this->timestamp = timestamp;
}

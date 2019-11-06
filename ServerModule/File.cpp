//
// Created by franc on 10/29/2019.
//

#include "header_files/File.h"

File::File (const std::string& idfile, const std::string& filename, const std::string& owner, const std::string& timestamp){
    this->idfile = idfile;
    this->filename = filename;
    this->owner = owner;
    this->timestamp = timestamp;
}

std::string File::ToString() const {
    return idfile + filename + owner + timestamp;
}

std::string File::getidfile() const {
    return idfile;
}

std::string File::getfilename() const {
    return filename;
}

std::string File::getowner() const {
    return owner;
}

std::string File::gettimestamp() const {
    return timestamp;
}

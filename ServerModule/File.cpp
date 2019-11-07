//
// Created by franc on 10/29/2019.
//

#include "header_files/File.h"

#include <utility>

File::File(std::string idfile, std::string filename, std::string owner, std::string timestamp)
        : _idfile(std::move(idfile)), _filename(std::move(filename)), _owner(std::move(owner)), _timestamp(std::move(timestamp)) {}

std::string File::ToString() const {
    return getidfile() + getfilename() + getowner() + gettimestamp();
}

std::string File::getidfile() const {
    return _idfile;
}

std::string File::getfilename() const {
    return _filename;
}

std::string File::getowner() const {
    return _owner;
}

std::string File::gettimestamp() const {
    return _timestamp;
}

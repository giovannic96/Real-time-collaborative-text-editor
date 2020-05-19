//
// Created by franc on 10/29/2019.
#include <string>
#ifndef SERVERMODULE_FILE_H
#define SERVERMODULE_FILE_H

class File {
private:
    std::string _idfile;
    std::string _filename;
    std::string _owner;
    std::string _timestamp;

public:
    File(std::string idfile, std::string filename, std::string owner, std::string timestamp);
    std::string getidfile() const;
    std::string getfilename() const;
    std::string getowner() const;
    std::string gettimestamp() const;
};


#endif //SERVERMODULE_FILE_H

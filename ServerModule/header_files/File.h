//
// Created by franc on 10/29/2019.
#include <string>
#ifndef SERVERMODULE_FILE_H
#define SERVERMODULE_FILE_H


class File {
private:
    std::string idfile;
    std::string filename;
    std::string owner;
    std::string timestamp;
public:
    File (const std::string& idfile, const std::string& filename, const std::string& owner, const std::string& timestamp);

    std::string ToString() const;

    std::string getidfile() const;

    std::string getfilename() const;

    std::string getowner() const;

    std::string gettimestamp() const;
};


#endif //SERVERMODULE_FILE_H

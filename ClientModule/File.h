#ifndef FILE_H
#define FILE_H

#include <string>

class File {
private:
    std::string _idfile;
    std::string _filename;
    std::string _owner;
    std::string _timestamp;
public:
    File (std::string idfile, std::string filename, std::string owner, std::string timestamp);
    std::string ToString() const;
    std::string getidfile() const;
    std::string getfilename() const;
    std::string getowner() const;
    std::string gettimestamp() const;
};


#endif //FILE_H

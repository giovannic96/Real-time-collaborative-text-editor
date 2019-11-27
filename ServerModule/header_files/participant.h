//
// Created by giova on 10/10/2019.
//

#ifndef SERVERMODULE_PARTICIPANT_H
#define SERVERMODULE_PARTICIPANT_H

#include <vector>
#include "message.h"
#include "symbol.h"
#include "msgInfo.h"

class participant {

private:
    int _siteId;
    std::string currentFile;
    std::vector<symbol> _symbols;
    int _counter = 0;
    std::vector<int> generatePos(int index, char value);
    std::vector<int> generatePosBetween(std::vector<int> pos1, std::vector<int> pos2, std::vector<int> newPos = {});
    int comparePos(std::vector<int> curSymPos, std::vector<int> newSymPos, int posIndex);

public:
    virtual ~participant() {}
    virtual void deliver(const message& msg) = 0;
    int getId() const;
    msgInfo localInsert(int index, char value);
    msgInfo localErase(int index);
    msgInfo localErase(int startIndex, int endIndex);
    void process(const msgInfo& m);
    std::string to_string();
    std::vector<symbol> getSymbols(); //maybe we can use pointer (symbol*)
    void setSymbols(std::vector<symbol> symbols);
    void setCurrentFile(std::string uri);
    void setSiteId(int edId);
    std::string getCurrentFile();
};


#endif //SERVERMODULE_PARTICIPANT_H

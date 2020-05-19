//
// Created by giova on 10/10/2019.
//

#ifndef SERVERMODULE_PARTICIPANT_H
#define SERVERMODULE_PARTICIPANT_H

#include <vector>
#include "message.h"
#include "symbol.h"

typedef std::pair<int,int> sId;

class participant {

private:
    int _siteId;
    std::string currentFile;
    std::string username;
    std::string color;
    std::vector<symbol> _symbols;
    int comparePosdx(std::vector<int> curSymPos, std::pair<int,int> curSymId, std::vector<int> newSymPos, std::pair<int,int> newSymId, int posIndex);
    int comparePos(std::vector<int> curSymPos, std::pair<int,int> curSymId, std::vector<int> newSymPos, std::pair<int,int> newSymId, int posIndex);

public:
    enum formatType {MAKE_BOLD=0, MAKE_ITALIC=1, MAKE_UNDERLINE=2, UNMAKE_BOLD=3, UNMAKE_ITALIC=4, UNMAKE_UNDERLINE=5, FORMAT_UNKNOWN=6};
    virtual ~participant() = default;
    virtual void deliver(const message& msg) = 0;
    int getId() const;
    int process(int type, int indexEditor, const std::vector<symbol>& roomSymbols, const symbol& newSymbol);
    int process(int type, int indexEditor, const std::vector<symbol>& roomSymbols, const std::vector<symbol>& newSymbols);
    int getIndexById(const std::vector<symbol>& roomSymbols, sId id);
    std::string to_string();
    std::vector<symbol> getSymbols();
    void setSymbols(std::vector<symbol> symbols);
    void setCurrentFile(std::string uri);
    void setUsername(std::string userName);
    void setColor(std::string color);
    void setSiteId(int edId);
    std::string getCurrentFile();
    std::string getUsername();
    std::string getColor();
};


#endif //SERVERMODULE_PARTICIPANT_H

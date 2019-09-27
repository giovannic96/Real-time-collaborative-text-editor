//
// Created by giova on 06/05/2019.
//

#include "SharedEditor.h"
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <stdexcept>

SharedEditor::SharedEditor(NetworkServer& server) : _server(server), _siteId(0) {
    _siteId = server.connect(this);
}
SharedEditor::~SharedEditor() {
    _server.disconnect(this);
}

int SharedEditor::getId() {
    return _siteId;
}

void SharedEditor::localInsert(int index, char value) noexcept(false) {
    std::vector<int> pos;

    if(index < 0 || index > _symbols.size())
        throw InsertedIndexNotValid();

    if(_symbols.empty()) {
        pos = {0};
        index = 0;
    } else if(index > _symbols.size()-1) {
        pos = {_symbols.back().getPos().at(0) + 1}; //last element will not have fraction -> pos will be [x] not [x,y]
        index = _symbols.size();
    } else if(index == 0) {
        pos = {_symbols.front().getPos().at(0) - 1}; //put negative pos
    } else
        pos = generatePos(index, value);

    Symbol s(value, std::make_tuple(_siteId, ++_counter), pos);
    _symbols.insert(_symbols.begin() + index, s);

    Message m(0, getId(), s);
    _server.send(m);
}

std::vector<int> SharedEditor::generatePos(int index, char value) {
    const std::vector<int> posBefore = _symbols[index-1].getPos();
    const std::vector<int> posAfter = _symbols[index].getPos();
    return generatePosBetween(posBefore, posAfter);
}

std::vector<int> SharedEditor::generatePosBetween(std::vector<int> pos1, std::vector<int> pos2, std::vector<int> newPos) {
    int id1 = pos1.at(0);
    int id2 = pos2.at(0);
    //newPos.push_back(id1);  //PRIMA ERA MESSO QUA, ADESSO L'HO MESSO DENTRO GLI IF, TRANNE NEL SECONDO IF

    if(id2 - id1 == 0) {
        newPos.push_back(id1);
        pos1.erase(pos1.begin());
        pos2.erase(pos2.begin());
        if(pos1.empty()) {
            newPos.push_back(pos2.front()-1);
            return newPos;
        } else
            return generatePosBetween(pos1, pos2, newPos);
    }
    else if(id2 - id1 > 1) {
        newPos.push_back(pos1.front()+1); //PRIMA ERA newpos.pushback(0);
        return newPos;
    }
    else if(id2 - id1 == 1) {
        newPos.push_back(id1);
        pos1.erase(pos1.begin());
        if(pos1.empty()) {
            newPos.push_back(0);
            return newPos;
        } else {
            newPos.push_back(pos1.front()+1);
            return newPos;
        }
    }
}

void SharedEditor::localErase(int index) noexcept(false) {
    Symbol s = _symbols.at(index);
    _symbols.erase(_symbols.begin() + index);
    Message m(1, getId(), s);
    _server.send(m);
}

int SharedEditor::comparePos(std::vector<int> curSymPos, std::vector<int> newSymPos, int posIndex) {
    if(curSymPos.at(posIndex) > newSymPos.at(posIndex))
        return 1; //correct position found
    else if (curSymPos.at(posIndex) == newSymPos.at(posIndex))
        if (newSymPos.size() > posIndex+1 && curSymPos.size() <= posIndex+1) //newSymPos[posIndex+1] != null && curSymPos[posIndex] == null
            return -1; //newSymPos > curSymPos -> make another cycle taking the next symbol from _symbols
        else if (newSymPos.size() <= posIndex+1 && curSymPos.size() > posIndex+1) //newSymPos[posIndex+1] == null && curSymPos[posIndex] != null
            return 1; //correct position found
        else if (newSymPos.size() > posIndex+1 && curSymPos.size() > posIndex+1) //newSymPos[posIndex+1] != null && curSymPos[posIndex] != null
            return comparePos(curSymPos, newSymPos, posIndex+1); //call recursively this function using next index for posIndex
}

void SharedEditor::process(const Message& m) {
    /* Insertion */
    if (m.getType() == 0) {
        int symbols_index = 0, pos_index = 0;
        int my_index = _symbols.size();

        for (auto s: _symbols) {
            symbols_index++;
            int retValue = comparePos(s.getPos(), m.getSymbol().getPos(), pos_index);
            if (retValue == -1)
                continue;
            else if (retValue == 1) {
                my_index = symbols_index - 1;
                break;
            }
        }
        _symbols.insert(_symbols.begin() + my_index, m.getSymbol());
    }
    else { /* Removal */
        std::vector<int> fractionalPos = m.getSymbol().getPos();
        auto it = std::find_if(_symbols.begin(), _symbols.end(), [fractionalPos](Symbol i) {return i.getPos() == fractionalPos;});
        if (it == _symbols.end())
            throw NotFoundException();
        int index = it - _symbols.begin();

        if(_symbols.at(index).getId() == m.getSymbol().getId())
            _symbols.erase(_symbols.begin() + index);
    }
}

std::vector<Symbol> SharedEditor::getSymbols() {
    return _symbols;
}

std::string SharedEditor::to_string() {
    std::string my_string;
    for(auto s: _symbols)
        my_string.push_back(s.getValue());
    return my_string;
}

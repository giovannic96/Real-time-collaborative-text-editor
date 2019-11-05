//
// Created by giova on 10/10/2019.
//

#include <algorithm>
#include <iostream>
#include "header_files/participant.h"

int participant::getId() {
    return _siteId;
}

msgInfo participant::localInsert(int index, char value) /*noexcept(false)*/ {
    std::vector<int> pos;

    if(index < 0 || index > _symbols.size()) {
        std::cout << "Inserted index not valid."; //TODO: throw InsertedIndexNotValid();
        //TODO: return null msgInfo or sthg similar
    }

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

    symbol s(value, std::make_pair(_siteId, ++_counter), pos);
    _symbols.insert(_symbols.begin() + index, s);

    msgInfo m(0, getId(), s);
    return m;
}

std::vector<int> participant::generatePos(int index, char value) {
    const std::vector<int> posBefore = _symbols[index-1].getPos();
    const std::vector<int> posAfter = _symbols[index].getPos();
    return generatePosBetween(posBefore, posAfter);
}

std::vector<int> participant::generatePosBetween(std::vector<int> pos1, std::vector<int> pos2, std::vector<int> newPos) {
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

msgInfo participant::localErase(int index) noexcept(false) {
    symbol s = _symbols.at(index);
    _symbols.erase(_symbols.begin() + index);
    msgInfo m(1, getId(), s);
    return m;
}

int participant::comparePos(std::vector<int> curSymPos, std::vector<int> newSymPos, int posIndex) {
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

void participant::process(const msgInfo& m) {
    /* Insertion */
    if (m.getType() == 0) { //TODO: switch case for different msgtypes, better enum not int
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
        auto it = std::find_if(_symbols.begin(), _symbols.end(), [fractionalPos](symbol i) {return i.getPos() == fractionalPos;});
        if (it == _symbols.end()) {
            std::cout << "Symbol not found."; //TODO: throw NotFoundException();
            return;
        }
        int index = it - _symbols.begin();

        if(_symbols.at(index).getId() == m.getSymbol().getId())
            _symbols.erase(_symbols.begin() + index);
    }
}

std::vector<symbol> participant::getSymbols() {
    return _symbols;
}

std::string participant::to_string() {
    std::string my_string;
    for(auto s: _symbols)
        my_string.push_back(s.getLetter());
    return my_string;
}
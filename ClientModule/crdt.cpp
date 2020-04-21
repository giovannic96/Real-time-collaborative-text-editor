#include "crdt.h"
#include <algorithm>
#include <iostream>
#include <utility>

std::vector<int> crdt::generatePos(int index) {
    const std::vector<int> posBefore = _symbols[index-1].getPos();
    const std::vector<int> posAfter = _symbols[index].getPos();
    return generatePosBetween(posBefore, posAfter);
}

std::vector<int> crdt::generatePosBetween(std::vector<int> pos1, std::vector<int> pos2, std::vector<int> newPos) {
    int id1 = pos1.at(0);
    int id2 = pos2.at(0);

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
        newPos.push_back(pos1.front()+1);
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
    //else if(id2 - id1 < 0)//TODO this must not happen otherwise the server crashes
}

int crdt::comparePosdx(std::vector<int> curSymPos, std::pair<int,int> curSymId, std::vector<int> newSymPos, std::pair<int,int> newSymId, int posIndex) {
    int newSymPosSize = static_cast<int>(newSymPos.size());
    int curSymPosSize = static_cast<int>(curSymPos.size());
    int curSymPosCurIndex = static_cast<int>(curSymPos.at(posIndex));
    int newSymPosCurIndex = static_cast<int>(newSymPos.at(posIndex));

    if (curSymPosCurIndex < newSymPosCurIndex)
        return 1;
    else if (curSymPosCurIndex == newSymPosCurIndex) {
        if (newSymPosSize > posIndex + 1 &&
            curSymPosSize <= posIndex + 1) //newSymPos[posIndex+1] != null && curSymPos[posIndex+1] == null
            return 1; // correct position found
        else if (newSymPosSize <= posIndex + 1 &&
                 curSymPosSize > posIndex + 1) //newSymPos[posIndex+1] == null && curSymPos[posIndex+1] != null
            return -1; //curSymPos > newSymPos  -> make another cycle taking the next symbol from _symbols
        else if (newSymPosSize > posIndex + 1 &&
                 curSymPosSize > posIndex + 1) //newSymPos[posIndex+1] != null && curSymPos[posIndex+1] != null
            return comparePosdx(curSymPos, curSymId, newSymPos,
                               newSymId, posIndex + 1); //call recursively this function using next index for posIndex
        else //newSymPos[posIndex+1] == null && curSymPos[posIndex+1] == null
            return newSymId > curSymId ? 1 : -1;
    } else
        return -1; //make another cycle taking the next symbol from _symbols
}

int crdt::comparePos(std::vector<int> curSymPos, std::pair<int,int> curSymId, std::vector<int> newSymPos, std::pair<int,int> newSymId, int posIndex) {
    int newSymPosSize = static_cast<int>(newSymPos.size());
    int curSymPosSize = static_cast<int>(curSymPos.size());
    int curSymPosCurIndex = static_cast<int>(curSymPos.at(posIndex));
    int newSymPosCurIndex = static_cast<int>(newSymPos.at(posIndex));

    if(curSymPosCurIndex > newSymPosCurIndex)
        return 1; //correct position found
    else if (curSymPosCurIndex == newSymPosCurIndex) {
        if (newSymPosSize > posIndex + 1 &&
            curSymPosSize <= posIndex + 1) //newSymPos[posIndex+1] != null && curSymPos[posIndex+1] == null
            return -1; //newSymPos > curSymPos -> make another cycle taking the next symbol from _symbols
        else if (newSymPosSize <= posIndex + 1 &&
                 curSymPosSize > posIndex + 1) //newSymPos[posIndex+1] == null && curSymPos[posIndex+1] != null
            return 1; //correct position found
        else if (newSymPosSize > posIndex + 1 &&
                 curSymPosSize > posIndex + 1) //newSymPos[posIndex+1] != null && curSymPos[posIndex+1] != null
            return comparePos(curSymPos, curSymId, newSymPos,
                              newSymId, posIndex + 1); //call recursively this function using next index for posIndex
        else //newSymPos[posIndex+1] == null && curSymPos[posIndex] == null
            return newSymId.first < curSymId.first ? 1 : -1;
    } else
        return -1; //make another cycle taking the next symbol from _symbols
}

symbol crdt::localInsert(int index, wchar_t value, symbolStyle style) noexcept(false) {
    std::vector<int> pos;

    if(_symbols.empty()) {
        pos = {0};
        index = 0;
    } else if(index > static_cast<int>(_symbols.size())-1) {
        pos = {_symbols.back().getPos().at(0) + 1}; //last element will not have fraction -> pos will be [x] not [x,y]
        index = static_cast<int>(_symbols.size());
    } else if(index == 0) {
        pos = {_symbols.front().getPos().at(0) - 1}; //put negative pos
    } else
        pos = generatePos(index);

    symbol s(value, std::make_pair(_siteId, ++_counter), pos, std::move(style));
    _symbols.insert(_symbols.begin() + index, s);

    return s;
}

std::vector<symbol> crdt::localInsert(int startIndex, std::vector<symbol> symbols) noexcept(false) {
    std::vector<int> pos;

    //generate initial pos and initial index
    if(_symbols.empty()) {
        pos = {0};
        startIndex = 0;
    } else if(startIndex > static_cast<int>(_symbols.size())-1) {
        pos = {_symbols.back().getPos().at(0) + 1}; //last element will not have fraction -> pos will be [x] not [x,y]
        startIndex = static_cast<int>(_symbols.size());
    } else if(startIndex == 0) {
        pos = {_symbols.front().getPos().at(0) - 1}; //put negative pos
    } else
        pos = generatePos(startIndex);

    std::vector<symbol> symbolVector;
    bool firstTime = true;
    bool secondTime = true;
    int counter = 0;

    std::for_each(symbols.begin(), symbols.end(), [&firstTime, &secondTime, &counter, &pos, &symbolVector, this](const symbol& s) {
        //get values
        wchar_t value = s.getLetter();
        symbolStyle style = s.getStyle();

        //generate next pos
        if(firstTime)
            firstTime = false;
        else {
            if(secondTime) {
                pos.push_back(counter++);
                secondTime = false;
            }
            else
                pos.back() = counter++;
        }

        //insert symbol
        symbol sym(value, std::make_pair(_siteId, ++_counter), pos, std::move(style));
        symbolVector.push_back(sym);
    });
    _symbols.insert(_symbols.begin() + startIndex, symbolVector.begin(), symbolVector.end());

    return std::move(symbolVector);
}

int crdt::process(int type, int indexEditor, symbol newSym) {
    /* Insertion */
    if (type == 0) {
        int symbols_index = 0, pos_index = 0;
        int startIndex = static_cast<int>(_symbols.size());

        //get first index
        if (indexEditor > static_cast<int>(_symbols.size()/2)) { //LOOP FROM RIGHT TO LEFT
            for (auto s = _symbols.crbegin(); s != _symbols.crend(); s++) {
                startIndex--;
                int retValue = comparePosdx(s->getPos(), s->getId(), newSym.getPos(), newSym.getId(), pos_index);

                if (retValue == -1)
                    continue;
                else if (retValue == 1) {
                    startIndex ++;
                    break;
                }
            }
        }
        else { //LOOP FROM LEFT TO RIGHT
            for (const auto &s: _symbols) {
                symbols_index++;
                int retValue = comparePos(s.getPos(), s.getId(), newSym.getPos(), newSym.getId(), pos_index);

                if (retValue == -1)
                    continue;
                else if (retValue == 1) {
                    startIndex = symbols_index - 1;
                    break;
                }
            }
        }
        std::cout << std::endl << "STAAAAAART INDEX: " << startIndex << std::endl << std::endl;
        _symbols.insert(_symbols.begin() + startIndex, newSym);
        return startIndex;
    }
}

int crdt::process(int type, int indexEditor, std::vector<symbol> newSymbols) {
    /* Insertion range */
    if(type == 6) {
        int symbols_index = 0, pos_index = 0;
        int startIndex = static_cast<int>(_symbols.size());

        //get first index
        if(indexEditor > static_cast<int>(_symbols.size()/2)) {  //LOOP FROM RIGHT TO LEFT
            for (auto s = _symbols.crbegin(); s != _symbols.crend(); s++) {
                startIndex--;
                int retValue = comparePosdx(s->getPos(), s->getId(), newSymbols.at(0).getPos(),
                                            newSymbols.at(0).getId(), pos_index);
                if (retValue == -1)
                    continue;
                else if (retValue == 1) {
                    startIndex ++;
                    break;
                }
            }
        }
        else { //LOOP FROM LEFT TO RIGHT
            for (const auto &s: _symbols) {
                symbols_index++;
                int retValue = comparePos(s.getPos(), s.getId(), newSymbols.at(0).getPos(),
                                          newSymbols.at(0).getId(), pos_index);
                if (retValue == -1)
                    continue;
                else if (retValue == 1) {
                    startIndex = symbols_index - 1;
                    break;
                }
            }
        }
        _symbols.insert(_symbols.begin() + startIndex, newSymbols.begin(), newSymbols.end());
        return startIndex;
    }
}

int crdt::getSiteId() {
    return this->_siteId;
}

int crdt::getCounter() {
    return this->_counter;
}

std::vector<symbol> crdt::getSymbols() {
    return _symbols;
}

void crdt::setSiteId(int id) {
    this->_siteId = id;
}

void crdt::setCounter(int counter) {
    this->_counter = counter;
}

void crdt::setSymbols(std::vector<symbol> symbols) {
    this->_symbols = std::move(symbols);
}

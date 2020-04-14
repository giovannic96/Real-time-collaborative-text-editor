//
// Created by giova on 10/10/2019.
//

#include <algorithm>
#include <iostream>
#include <utility>
#include <chrono>
#include "header_files/participant.h"

int participant::getId() const {
    return _siteId;
}

msgInfo participant::localInsert(int index, wchar_t value, symbolStyle style) noexcept(false) {
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
        pos = generatePos(index);

    symbol s(value, std::make_pair(_siteId, ++_counter), pos, std::move(style));
    _symbols.insert(_symbols.begin() + index, s);

    msgInfo m(0, getId(), s, index);
    return m;
}

msgInfo participant::localInsert(std::vector<symbolInfo> symbols) noexcept(false) {
    auto t_start = std::chrono::high_resolution_clock::now();
    std::vector<int> pos;

    int startIndex = symbols.front().getIndex();

    //generate initial pos and initial index
    if(_symbols.empty()) {
        pos = {0};
        startIndex = 0;
    } else if(startIndex > _symbols.size()-1) {
        pos = {_symbols.back().getPos().at(0) + 1}; //last element will not have fraction -> pos will be [x] not [x,y]
        startIndex = _symbols.size();
    } else if(startIndex == 0) {
        pos = {_symbols.front().getPos().at(0) - 1}; //put negative pos
    } else
        pos = generatePos(startIndex);

    std::vector<symbol> symbolVector;
    bool firstTime = true;
    bool secondTime = true;
    int counter = 0;

    std::for_each(symbols.begin(), symbols.end(), [&firstTime, &secondTime, &counter, &pos, &symbolVector, this](const symbolInfo& s) {
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

    auto t_end = std::chrono::high_resolution_clock::now();
    double elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end-t_start).count();
    std::cout << "FOR EACH LOCAL INSERT - ELAPSED (ms): " << elapsed_time_ms << std::endl;

    msgInfo m(6, getId(), std::move(symbolVector), startIndex);
    return m;
}

std::vector<int> participant::generatePos(int index) {
    const std::vector<int> posBefore = _symbols[index-1].getPos();
    const std::vector<int> posAfter = _symbols[index].getPos();
    return generatePosBetween(posBefore, posAfter);
}

std::vector<int> participant::generatePosBetween(std::vector<int> pos1, std::vector<int> pos2, std::vector<int> newPos) {
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
    //else if(id2 - id1 < 0)//TODO THIS must not happen otherwise the server crashes
}

int participant::comparePosdx(std::vector<int> curSymPos, std::vector<int> newSymPos, int posIndex) {
    if (curSymPos.at(posIndex) < newSymPos.at(posIndex))
        return 1;
    else if (curSymPos.at(posIndex) == newSymPos.at(posIndex)) {
        if (newSymPos.size() > posIndex + 1 &&
            curSymPos.size() <= posIndex + 1) //newSymPos[posIndex+1] != null && curSymPos[posIndex+1] == null
            return 1; // correct position found
        else if (newSymPos.size() <= posIndex + 1 &&
                 curSymPos.size() > posIndex + 1) //newSymPos[posIndex+1] == null && curSymPos[posIndex+1] != null
            return -1; //curSymPos > newSymPos  -> make another cycle taking the next symbol from _symbols
        else if (newSymPos.size() > posIndex + 1 &&
                 curSymPos.size() > posIndex + 1) //newSymPos[posIndex+1] != null && curSymPos[posIndex+1] != null
            return comparePosdx(curSymPos, newSymPos,
                              posIndex + 1); //call recursively this function using next index for posIndex
    } else
        return -1; //make another cycle taking the next symbol from _symbols
}

int participant::comparePos(std::vector<int> curSymPos, std::vector<int> newSymPos, int posIndex) {
    if(curSymPos.at(posIndex) > newSymPos.at(posIndex))
        return 1; //correct position found
    else if (curSymPos.at(posIndex) == newSymPos.at(posIndex)) {
        if (newSymPos.size() > posIndex + 1 &&
            curSymPos.size() <= posIndex + 1) //newSymPos[posIndex+1] != null && curSymPos[posIndex] == null
            return -1; //newSymPos > curSymPos -> make another cycle taking the next symbol from _symbols
        else if (newSymPos.size() <= posIndex + 1 &&
                 curSymPos.size() > posIndex + 1) //newSymPos[posIndex+1] == null && curSymPos[posIndex] != null
            return 1; //correct position found
        else if (newSymPos.size() > posIndex + 1 &&
                 curSymPos.size() > posIndex + 1) //newSymPos[posIndex+1] != null && curSymPos[posIndex] != null
            return comparePos(curSymPos, newSymPos,
                              posIndex + 1); //call recursively this function using next index for posIndex
    } else
        return -1; //make another cycle taking the next symbol from _symbols
}

msgInfo participant::localErase(int startIndex, int endIndex) noexcept(false) {
    if(startIndex >= endIndex || startIndex < 0 || endIndex > _symbols.size()) {
        std::cout << "Inserted index not valid."; //TODO: throw InsertedIndexNotValid();
        //TODO: return null msgInfo or sthg similar
    }
    symbol s = _symbols.at(startIndex);
    _symbols.erase(_symbols.begin() + startIndex, _symbols.begin() + endIndex);
    msgInfo m(1, getId(), s, endIndex-startIndex);
    return m;
}

msgInfo participant::localFormat(int startIndex, int endIndex, int format) noexcept(false) {
    if(startIndex >= endIndex || startIndex < 0 || startIndex > _symbols.size()) {
        std::cout << "Inserted index not valid."; //TODO: throw InsertedIndexNotValid();
        //TODO: return null msgInfo or sthg similar
    }

    symbol s = _symbols.at(startIndex);
    std::for_each(_symbols.begin() + startIndex, _symbols.begin() + endIndex, [format](symbol& s) {
        symbolStyle newStyle;
        if(format == MAKE_BOLD)
            newStyle = {true, s.getStyle().isItalic(), s.getStyle().isUnderlined(), s.getStyle().getFontFamily(), s.getStyle().getFontSize(), s.getStyle().getAlignment(), s.getStyle().getColor()};
        else if(format == MAKE_ITALIC)
            newStyle = {s.getStyle().isBold(), true, s.getStyle().isUnderlined(), s.getStyle().getFontFamily(), s.getStyle().getFontSize(), s.getStyle().getAlignment(), s.getStyle().getColor() };
        else if(format == MAKE_UNDERLINE)
            newStyle = {s.getStyle().isBold(), s.getStyle().isItalic(), true, s.getStyle().getFontFamily(), s.getStyle().getFontSize(), s.getStyle().getAlignment(), s.getStyle().getColor() };
        else if(format == UNMAKE_BOLD)
            newStyle = {false, s.getStyle().isItalic(), s.getStyle().isUnderlined(), s.getStyle().getFontFamily(), s.getStyle().getFontSize(), s.getStyle().getAlignment(), s.getStyle().getColor() };
        else if(format == UNMAKE_ITALIC)
            newStyle = {s.getStyle().isBold(), false, s.getStyle().isUnderlined(), s.getStyle().getFontFamily(), s.getStyle().getFontSize(), s.getStyle().getAlignment(), s.getStyle().getColor() };
        else if(format == UNMAKE_UNDERLINE)
            newStyle = {s.getStyle().isBold(), s.getStyle().isItalic(), false, s.getStyle().getFontFamily(), s.getStyle().getFontSize(), s.getStyle().getAlignment(), s.getStyle().getColor() };
        else
            newStyle = s.getStyle();
        s.setStyle(newStyle);
    });
    msgInfo m(2, getId(), s, endIndex-startIndex, format); //in this case 'format' (4th param) represents the format type, not the newIndex -> 0: Bold, 1: Italic, 2: Underline
    return m;
}

msgInfo participant::localFontSizeChange(int startIndex, int endIndex, int fontSize) noexcept(false) {
    if(startIndex >= endIndex || startIndex < 0 || startIndex > _symbols.size()) {
        std::cout << "Inserted index not valid."; //TODO: throw InsertedIndexNotValid();
        //TODO: return null msgInfo or sthg similar
    }
    symbol s = _symbols.at(startIndex);
    std::for_each(_symbols.begin() + startIndex, _symbols.begin() + endIndex, [fontSize](symbol& s) {
        symbolStyle newStyle;
        newStyle = {s.getStyle().isBold(), s.getStyle().isItalic(), s.getStyle().isUnderlined(), s.getStyle().getFontFamily(), fontSize, s.getStyle().getAlignment(), s.getStyle().getColor() };
        s.setStyle(newStyle);
    });
    msgInfo m(3, getId(), s, endIndex-startIndex, fontSize); //in this case 'fontSize' (4th param) represents the fontSize, not the newIndex
    return m;
}

msgInfo participant::localFontFamilyChange(int startIndex, int endIndex, const std::string& fontFamily) noexcept(false) {
    if(startIndex >= endIndex || startIndex < 0 || startIndex > _symbols.size()) {
        std::cout << "Inserted index not valid."; //TODO: throw InsertedIndexNotValid();
        //TODO: return null msgInfo or sthg similar
    }
    symbol s = _symbols.at(startIndex);
    std::for_each(_symbols.begin() + startIndex, _symbols.begin() + endIndex, [fontFamily](symbol& s) {
        symbolStyle newStyle;
        newStyle = {s.getStyle().isBold(), s.getStyle().isItalic(), s.getStyle().isUnderlined(), fontFamily, s.getStyle().getFontSize(), s.getStyle().getAlignment(), s.getStyle().getColor() };
        s.setStyle(newStyle);
    });
    msgInfo m(4, getId(), s, endIndex-startIndex, fontFamily);
    return m;
}

msgInfo participant::localAlignmentChange(int startIndex, int endIndex, int alignment) noexcept(false) {
    if(startIndex > endIndex || startIndex < 0 || startIndex > _symbols.size()) {
        std::cout << "Inserted index not valid."; //TODO: throw InsertedIndexNotValid();
        //TODO: return null msgInfo or sthg similar
    }
    if(startIndex == endIndex) {
        msgInfo m(5, getId(), endIndex-startIndex, alignment); //in this case 'alignment' (4th param) represents the alignment, not the newIndex
        return m;
    } else {
        symbol s = _symbols.at(startIndex);
        std::for_each(_symbols.begin() + startIndex, _symbols.begin() + endIndex, [alignment](symbol& s) {
            symbolStyle newStyle;
            newStyle = {s.getStyle().isBold(), s.getStyle().isItalic(), s.getStyle().isUnderlined(), s.getStyle().getFontFamily(), s.getStyle().getFontSize(), alignment, s.getStyle().getColor()};
            s.setStyle(newStyle);
        });
        msgInfo m(5, getId(), s, endIndex-startIndex, alignment); //in this case 'alignment' (4th param) represents the alignment, not the newIndex
        return m;
    }
}

void participant::process(const msgInfo& m) {
    /* Insertion */
    if (m.getType() == 0) { //TODO: switch case for different msgtypes, better enum not int

        int symbols_index = 0, pos_index = 0;
        int startIndex = _symbols.size();

        //get first index
        if (m.getNewIndex() > _symbols.size()/2) { //LOOP FROM RIGHT TO LEFT
            std::cout << std::endl << "RIGHT TO LEFT: " << startIndex << std::endl << std::endl;
            for (auto s = _symbols.crbegin(); s != _symbols.crend(); s++) {
                startIndex--;
                int retValue = comparePosdx(s->getPos(), m.getSymbol().getPos(), pos_index);

                if (retValue == -1)
                    continue;
                else if (retValue == 1) {
                    startIndex ++;
                    break;
                }
            }
        }
        else { //LOOP FROM LEFT TO RIGHT
            std::cout << std::endl << "LEFT TO RIGHT: " << startIndex << std::endl << std::endl;
            for (const auto &s: _symbols) {
                symbols_index++;
                int retValue = comparePos(s.getPos(), m.getSymbol().getPos(), pos_index);

                if (retValue == -1)
                    continue;
                else if (retValue == 1) {
                    startIndex = symbols_index - 1;
                    break;
                }
            }
        }
        std::cout << std::endl << "STAAAAAART INDEX: " << startIndex << std::endl << std::endl;
        _symbols.insert(_symbols.begin() + startIndex, m.getSymbol());
    }
    /* Removal */
    else if (m.getType() == 1) {
        std::vector<int> fractionalPos = m.getSymbol().getPos();
        auto it = std::find_if(_symbols.begin(), _symbols.end(), [fractionalPos](const symbol& i) {return i.getPos() == fractionalPos;});
        if (it == _symbols.end()) {
            std::cout << "Symbol not found."; //TODO: throw NotFoundException();
            return;
        }
        int index = it - _symbols.begin();

        if(_symbols.at(index).getId() == m.getSymbol().getId())
            _symbols.erase(_symbols.begin() + index, _symbols.begin() + index + m.getNewIndex());
    }
    /* Format */
    else if(m.getType() == 2) {
        std::vector<int> fractionalPos = m.getSymbol().getPos();
        auto it = std::find_if(_symbols.begin(), _symbols.end(), [fractionalPos](const symbol& i) {return i.getPos() == fractionalPos;});
        if (it == _symbols.end()) {
            std::cout << "Symbol not found."; //TODO: throw NotFoundException();
            return;
        }
        int index = it - _symbols.begin();

        if(_symbols.at(index).getId() == m.getSymbol().getId()) {
            std::for_each(_symbols.begin() + index, _symbols.begin() + index + m.getRange(), [&m](symbol& s) {
                symbolStyle newStyle;
                //in this case 'newIndex' of msgInfo represents the format type -> 0: Bold, 1: Italic, 2: Underline, 3: Unbold
                if(m.getNewIndex() == MAKE_BOLD)
                    newStyle = {true, s.getStyle().isItalic(), s.getStyle().isUnderlined(), s.getStyle().getFontFamily(), s.getStyle().getFontSize(), s.getStyle().getAlignment(), s.getStyle().getColor() };
                else if(m.getNewIndex() == MAKE_ITALIC)
                    newStyle = {s.getStyle().isBold(), true, s.getStyle().isUnderlined(), s.getStyle().getFontFamily(), s.getStyle().getFontSize(), s.getStyle().getAlignment(), s.getStyle().getColor() };
                else if(m.getNewIndex() == MAKE_UNDERLINE)
                    newStyle = {s.getStyle().isBold(), s.getStyle().isItalic(), true, s.getStyle().getFontFamily(), s.getStyle().getFontSize(), s.getStyle().getAlignment(), s.getStyle().getColor() };
                else if(m.getNewIndex() == UNMAKE_BOLD)
                    newStyle = {false, s.getStyle().isItalic(), s.getStyle().isUnderlined(), s.getStyle().getFontFamily(), s.getStyle().getFontSize(), s.getStyle().getAlignment(), s.getStyle().getColor() };
                else if(m.getNewIndex() == UNMAKE_ITALIC)
                    newStyle = {s.getStyle().isBold(), false, s.getStyle().isUnderlined(), s.getStyle().getFontFamily(), s.getStyle().getFontSize(), s.getStyle().getAlignment(), s.getStyle().getColor() };
                else if(m.getNewIndex() == UNMAKE_UNDERLINE)
                    newStyle = {s.getStyle().isBold(), s.getStyle().isItalic(), false, s.getStyle().getFontFamily(), s.getStyle().getFontSize(), s.getStyle().getAlignment(), s.getStyle().getColor() };
                else
                    newStyle = s.getStyle();
                s.setStyle(newStyle);
            });
        }
    }
    /* Font size change */
    else if(m.getType() == 3) {
        std::vector<int> fractionalPos = m.getSymbol().getPos();
        auto it = std::find_if(_symbols.begin(), _symbols.end(), [fractionalPos](const symbol& i) {return i.getPos() == fractionalPos;});
        if (it == _symbols.end()) {
            std::cout << "Symbol not found."; //TODO: throw NotFoundException();
            return;
        }
        int index = it - _symbols.begin();

        if(_symbols.at(index).getId() == m.getSymbol().getId()) {
            std::for_each(_symbols.begin() + index, _symbols.begin() + index + m.getRange(), [&m](symbol& s) {
                symbolStyle newStyle;
                //in this case 'newIndex' of msgInfo represents the fontSize
                newStyle = {s.getStyle().isBold(), s.getStyle().isItalic(), s.getStyle().isUnderlined(), s.getStyle().getFontFamily(), m.getNewIndex(), s.getStyle().getAlignment(), s.getStyle().getColor() };
                s.setStyle(newStyle);
            });
        }
    }
    /* Font family change */
    else if(m.getType() == 4) {
        std::vector<int> fractionalPos = m.getSymbol().getPos();
        auto it = std::find_if(_symbols.begin(), _symbols.end(), [fractionalPos](const symbol& i) {return i.getPos() == fractionalPos;});
        if (it == _symbols.end()) {
            std::cout << "Symbol not found."; //TODO: throw NotFoundException();
            return;
        }
        int index = it - _symbols.begin();

        if(_symbols.at(index).getId() == m.getSymbol().getId()) {
            std::for_each(_symbols.begin() + index, _symbols.begin() + index + m.getRange(), [&m](symbol& s) {
                symbolStyle newStyle;
                newStyle = {s.getStyle().isBold(), s.getStyle().isItalic(), s.getStyle().isUnderlined(), m.getFontFamily(), s.getStyle().getFontSize(), s.getStyle().getAlignment(), s.getStyle().getColor() };
                s.setStyle(newStyle);
            });
        }
    }
    /* Alignment change */
    else if(m.getType() == 5) {
        if(m.getRange() > 0) {
            std::vector<int> fractionalPos = m.getSymbol().getPos();
            auto it = std::find_if(_symbols.begin(), _symbols.end(), [fractionalPos](const symbol& i) {return i.getPos() == fractionalPos;});
            if (it == _symbols.end()) {
                std::cout << "Symbol not found."; //TODO: throw NotFoundException();
                return;
            }
            int index = it - _symbols.begin();

            if(_symbols.at(index).getId() == m.getSymbol().getId()) {
                std::for_each(_symbols.begin() + index, _symbols.begin() + index + m.getRange(), [&m](symbol& s) {
                    symbolStyle newStyle;
                    //in this case 'newIndex' of msgInfo represents the alignment
                    newStyle = {s.getStyle().isBold(), s.getStyle().isItalic(), s.getStyle().isUnderlined(), s.getStyle().getFontFamily(), s.getStyle().getFontSize(), m.getNewIndex(), s.getStyle().getColor()};
                    s.setStyle(newStyle);
                });
            }
        }
    }
    /* Insertion range */
    else if(m.getType() == 6) {
        int symbols_index = 0, pos_index = 0;
        int my_index = _symbols.size();

        auto t_start = std::chrono::high_resolution_clock::now();
        //get first index
        if(m.getNewIndex() > _symbols.size()/2) {  //LOOP FROM RIGHT TO LEFT
            for (auto s = _symbols.crbegin(); s != _symbols.crend(); s++) {
                my_index--;
                int retValue = comparePosdx(s->getPos(), m.getSymbol().getPos(), pos_index);
                if (retValue == -1)
                    continue;
                else if (retValue == 1) {
                    my_index ++;
                    break;
                }
            }
        }
        else { //LOOP FROM LEFT TO RIGHT*/
            for (const auto &s: _symbols) {
                symbols_index++;
                int retValue = comparePos(s.getPos(), m.getSymbol().getPos(), pos_index);
                if (retValue == -1)
                    continue;
                else if (retValue == 1) {
                    my_index = symbols_index - 1;
                    break;
                }
            }
        }
        auto t_end = std::chrono::high_resolution_clock::now();
        double elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end-t_start).count();
        std::cout << "FOR EACH SYMBOLS - ELAPSED (ms): " << elapsed_time_ms << std::endl;

        auto t_start1 = std::chrono::high_resolution_clock::now();
        std::vector<symbol> v = m.getSymbolVector();
        _symbols.insert(_symbols.begin() + my_index, v.begin(), v.end());
        auto t_end1 = std::chrono::high_resolution_clock::now();
        double elapsed_time_ms1 = std::chrono::duration<double, std::milli>(t_end1-t_start1).count();
        std::cout << "FOR EACH m.getSymbolVector() - ELAPSED (ms): " << elapsed_time_ms1 << std::endl;
    }
}

std::vector<symbol> participant::getSymbols() {
    return _symbols;
}

std::string participant::getCurrentFile() {
    return this->currentFile;
}

std::string participant::getUsername() {
    return this->username;
}

std::string participant::getColor() {
    return this->color;
}

std::string participant::to_string() {
    std::string my_string;
    for(const auto& s: _symbols)
        my_string.push_back(s.getLetter());
    return my_string;
}

void participant::setSiteId(int edId) {
    this->_siteId = edId;
}

void participant::setSymbols(std::vector<symbol> symbols) {
    this->_symbols = std::move(symbols);
}

void participant::setCurrentFile(std::string uri) {
    this->currentFile = std::move(uri);
}

void participant::setUsername(std::string userName) {
    this->username = std::move(userName);
}

void participant::setColor(std::string color) {
    this->color = std::move(color);
}
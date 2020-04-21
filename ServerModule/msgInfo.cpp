//
// Created by giova on 31/10/2019.
//

#include <iostream>
#include <utility>
#include "header_files/msgInfo.h"

msgInfo::msgInfo(int type, int editorId, symbol s): type(type), editorId(editorId), s(std::move(s)) {
}

msgInfo::msgInfo(int type, int editorId, symbol s, int newIndex)
        : type(type), editorId(editorId), s(std::move(s)), newIndex(newIndex) {
}

msgInfo::msgInfo(int type, int editorId, symbol s, int range, int format)
        : type(type), editorId(editorId), s(std::move(s)), range(range), newIndex(format) {
}

msgInfo::msgInfo(int type, int editorId, symbol s, int range, std::string family)
        : type(type), editorId(editorId), s(std::move(s)), range(range), fontFamily(std::move(family)) {
}

msgInfo::msgInfo(int type, int editorId, std::vector<symbol> symbols, int startIndex)
        : type(type), editorId(editorId), s(symbols.front()), newIndex(startIndex) {
    this->symbols = symbols;
}

msgInfo::msgInfo(int type, int editorId, symbol s, std::string family)
        : type(type), editorId(editorId), s(std::move(s)), fontFamily(std::move(family)) {
}

msgInfo::msgInfo(int type, int editorId, int range, int alignment)
        : type(type), editorId(editorId), range(range), newIndex(alignment), s('a', std::make_pair(0,0), std::vector<int>()) {
}

int msgInfo::getType() const {
    return type;
}

symbol msgInfo::getSymbol() const {
    return s;
}

int msgInfo::getEditorId() const {
    return editorId;
}

int msgInfo::getNewIndex() const {
    return newIndex;
}

int msgInfo::getRange() const {
    return range;
}

std::string msgInfo::getFontFamily() const {
    return fontFamily;
}

std::vector<symbol> msgInfo::getSymbolVector() const {
    return symbols;
}

std::string msgInfo::toString() {
    //convert symbol pos to string
    std::string posToStr;
    for (const auto& p: this->s.getPos())
        posToStr += std::to_string(p);

    //construct final string for msgInfo
    std::string str("Type:" + std::to_string(this->type) + " EditorID:" + std::to_string(this->editorId) +
                    " Symbol - Letter: " + std::to_string(this->s.getLetter()) + " Symbol - Pos: " + posToStr + " Symbol - Id: " +
                    std::to_string(this->s.getId().first) + std::to_string(this->s.getId().second) + " New index: " +
                    std::to_string(this->newIndex));
    return str;
}

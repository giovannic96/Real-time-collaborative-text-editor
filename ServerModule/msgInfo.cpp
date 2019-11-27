//
// Created by giova on 31/10/2019.
//

#include <iostream>
#include "header_files/msgInfo.h"

msgInfo::msgInfo(int type, int editorId, symbol s): type(type), editorId(editorId), s(std::move(s)) {
}

msgInfo::msgInfo(int type, int editorId, symbol s, int newIndex)
            : type(type), editorId(editorId), s(std::move(s)), newIndex(newIndex) {
}

int msgInfo::getType() const {
    return type;
}

symbol msgInfo::getSymbol() const {
    return s;
}

int msgInfo::getEditorId() {
    return editorId;
}

int msgInfo::getNewIndex() const {
    return newIndex;
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

//
// Created by giova on 31/10/2019.
//

#include "header_files/msgInfo.h"

msgInfo::msgInfo(int type, int editorId, symbol s): type(type), editorId(editorId), s(std::move(s)) {
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
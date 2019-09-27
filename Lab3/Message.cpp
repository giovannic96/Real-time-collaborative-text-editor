#include <utility>

//
// Created by giova on 06/05/2019.
//

#include "Message.h"

Message::Message(int type, int editorId, Symbol s): type(type), editorId(editorId), s(std::move(s)) {
}

int Message::getType() const {
    return type;
}

Symbol Message::getSymbol() const {
    return s;
}

int Message::getEditorId() {
    return editorId;
}

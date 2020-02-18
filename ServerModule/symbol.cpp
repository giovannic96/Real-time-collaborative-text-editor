//
// Created by giova on 31/10/2019.
//

#include "header_files/symbol.h"
#include <utility>

symbol::symbol(wchar_t character, std::pair<int, int> id, std::vector<int> pos)
    : _letter(character), _id(std::move(id)), _pos(std::move(pos)), _style() {}

symbol::symbol(wchar_t character, std::pair<int, int> id, std::vector<int> pos, symbolStyle style)
    : _letter(character), _id(std::move(id)), _pos(std::move(pos)), _style(std::move(style)) {}

std::vector<int> symbol::getPos() const {
    return _pos;
}

wchar_t symbol::getLetter() const {
    return _letter;
}

std::pair<int, int> symbol::getId() const {
    return _id;
}

symbolStyle symbol::getStyle() const {
    return _style;
}

void symbol::setLetter(wchar_t letter) {
    this->_letter = letter;
}

void symbol::setId(std::pair<int, int> id) {
    this->_id = id;
}

void symbol::setPos(std::vector<int> pos) {
    this->_pos = std::move(pos);
}

void symbol::setStyle(symbolStyle style) {
    this->_style = std::move(style);
}



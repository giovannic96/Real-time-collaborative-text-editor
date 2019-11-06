//
// Created by giova on 31/10/2019.
//

#include "symbol.h"

#include <utility>

symbol::symbol(char character, std::pair<int, int> id, std::vector<int> pos)
                        : _letter(character), _id(std::move(id)), _pos(std::move(pos)), _isBold(false), _isItalic(false) {}

std::vector<int> symbol::getPos() const {
    return _pos;
}

char symbol::getLetter() const {
    return _letter;
}

std::pair<int, int> symbol::getId() const {
    return _id;
}

bool symbol::isBold() const {
    return _isBold;
}

bool symbol::isItalic() const {
    return _isItalic;
}

void symbol::setBold(bool val) {
    this->_isBold = val;
}

void symbol::setItalic(bool val) {
    this->_isItalic = val;
}

void symbol::setLetter(char letter) {
    this->_letter = letter;
}

void symbol::setId(std::pair<int, int> id) {
    this->_id = id;
}

void symbol::setPos(std::vector<int> pos) {
    this->_pos = std::move(pos);
}

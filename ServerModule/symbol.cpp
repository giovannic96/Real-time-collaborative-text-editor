//
// Created by giova on 31/10/2019.
//

#include "header_files/symbol.h"

#include <utility>

symbol::symbol(wchar_t character, std::pair<int, int> id, std::vector<int> pos)
                        : _letter(character), _id(std::move(id)), _pos(std::move(pos)), _isBold(false), _isItalic(false) {}

symbol::symbol(wchar_t character, std::pair<int, int> id, std::vector<int> pos, bool isBold, bool isItalic)
    : _letter(character), _id(std::move(id)), _pos(std::move(pos)), _isBold(isBold), _isItalic(isItalic) {}

std::vector<int> symbol::getPos() const {
    return _pos;
}

wchar_t symbol::getLetter() const {
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

void symbol::setLetter(wchar_t letter) {
    this->_letter = letter;
}

void symbol::setId(std::pair<int, int> id) {
    this->_id = id;
}

void symbol::setPos(std::vector<int> pos) {
    this->_pos = std::move(pos);
}

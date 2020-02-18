//
// Created by giova on 07/12/2019.
//

#include "symbolInfo.h"
#include <utility>

symbolInfo::symbolInfo(int index, wchar_t letter, symbolStyle style)
        : _index(index), _letter(letter), _style(std::move(style)) {}

int symbolInfo::getIndex() const {
    return _index;
}

wchar_t symbolInfo::getLetter() const {
    return _letter;
}

symbolStyle symbolInfo::getStyle() const {
    return _style;
}

void symbolInfo::setIndex(int index) {
    this->_index = index;
}

void symbolInfo::setLetter(wchar_t letter) {
    this->_letter = letter;
}

void symbolInfo::setStyle(symbolStyle style) {
    this->_style = std::move(style);
}

//
// Created by giova on 07/12/2019.
//

#include "header_files/symbol_formatting.h"
#include <utility>

symbol_formatting::symbol_formatting(int index, wchar_t letter, std::array<bool,2> formattingTypes)
        : _index(index), _letter(letter), _formattingTypes(formattingTypes) {}

int symbol_formatting::getIndex() const {
    return _index;
}

wchar_t symbol_formatting::getLetter() const {
    return _letter;
}

std::array<bool,2> symbol_formatting::getFormattingTypes() const {
    return _formattingTypes;
}
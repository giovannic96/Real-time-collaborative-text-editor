#include <utility>

//
// Created by giova on 06/05/2019.
//

#include "Symbol.h"

Symbol::Symbol(char character, std::tuple<int, int> id, std::vector<int> pos) : _value(character), _id(std::move(id)), _pos(std::move(pos)) {

}

std::vector<int> Symbol::getPos() {
    return _pos;
}

char Symbol::getValue() {
    return _value;
}

std::tuple<int, int> Symbol::getId() {
    return _id;
}

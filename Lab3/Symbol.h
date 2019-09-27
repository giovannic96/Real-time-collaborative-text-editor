//
// Created by giova on 06/05/2019.
//

#ifndef LAB3_SYMBOL_H
#define LAB3_SYMBOL_H

#include <vector>
#include <tuple>

class Symbol {

    private:
        char _value;
        std::tuple<int, int> _id;
        std::vector<int> _pos;

    public:
        Symbol(char character, std::tuple<int, int> id, std::vector<int> pos);
        std::vector<int> getPos();
        char getValue();
        std::tuple<int, int> getId();
};


#endif //LAB3_SYMBOL_H

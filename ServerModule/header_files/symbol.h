//
// Created by giova on 31/10/2019.
//

#ifndef SERVERMODULE_SYMBOL_H
#define SERVERMODULE_SYMBOL_H

#include <vector>
#include <string>
#include <array>
#include "symbolStyle.h"

class symbol {

private:
    wchar_t _letter;
    std::pair<int, int> _id;
    std::vector<int> _pos;
    symbolStyle _style;

public:
    /* Constructors */
    symbol(wchar_t character, std::pair<int, int> id, std::vector<int> pos);
    symbol(wchar_t character, std::pair<int, int> id, std::vector<int> pos, symbolStyle style);

    /* Getters */
    std::vector<int> getPos() const;
    wchar_t getLetter() const;
    std::pair<int, int> getId() const;
    symbolStyle getStyle() const;

    /* Setters */
    void setLetter(wchar_t letter);
    void setId(std::pair<int,int> id);
    void setPos(std::vector<int> pos);
    void setStyle(symbolStyle style);
};


#endif //SERVERMODULE_SYMBOL_H

//
// Created by giova on 07/12/2019.
//

#ifndef SERVERMODULE_SYMBOLINFO_H
#define SERVERMODULE_SYMBOLINFO_H

#include <vector>
#include <array>
#include "symbolStyle.h"

/* This class is like a "fake" symbol, that is created by the client and sent to the server, that creates a real symbol from it,
 * sending it to the client. */
class symbolInfo {

private:
    int _index;
    wchar_t _letter;
    symbolStyle _style;

public:
    /* Constructors */
    symbolInfo(int index, wchar_t letter, symbolStyle style);

    /* Getters */
    int getIndex() const;
    wchar_t getLetter() const;
    symbolStyle getStyle() const;

    /* Setters */
    void setIndex(int index);
    void setLetter(wchar_t letter);
    void setStyle(symbolStyle style);
};


#endif //SERVERMODULE_SYMBOLINFO_H

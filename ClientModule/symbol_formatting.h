//
// Created by giova on 07/12/2019.
//

#ifndef SERVERMODULE_SYMBOL_FORMATTING_H
#define SERVERMODULE_SYMBOL_FORMATTING_H

#include <vector>
#include <array>

/* This class is like a "fake" symbol, that is created by the client and sent to the server, that creates a real symbol from it,
 * sending it to the client. */
class symbol_formatting {

private:
    int _index;
    wchar_t _letter;
    std::array<bool, 2> _formattingTypes; //ex. bold, italic, ecc.
    std::string _fontFamily;

public:
    symbol_formatting(int index, wchar_t letter, std::array<bool, 2> formattingTypes, std::string fontFamily);
    int getIndex() const;
    wchar_t getLetter() const;
    std::array<bool, 2> getFormattingTypes() const;
    std::string getFontFamily() const;
};


#endif //SERVERMODULE_SYMBOL_FORMATTING_H

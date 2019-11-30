//
// Created by giova on 31/10/2019.
//

#ifndef SERVERMODULE_SYMBOL_H
#define SERVERMODULE_SYMBOL_H

#include <vector>

class symbol {

private:
    wchar_t _letter;
    std::pair<int, int> _id;
    std::vector<int> _pos;
    bool _isBold;
    bool _isItalic;

public:
    symbol(wchar_t character, std::pair<int, int> id, std::vector<int> pos);
    symbol(wchar_t character, std::pair<int, int> id, std::vector<int> pos, bool isBold, bool isItalic);
    std::vector<int> getPos() const;
    wchar_t getLetter() const;
    std::pair<int, int> getId() const;
    bool isBold() const;
    bool isItalic() const;
    void setBold(bool val);
    void setItalic(bool val);
    void setLetter(wchar_t letter);
    void setId(std::pair<int,int> id);
    void setPos(std::vector<int> pos);
};


#endif //SERVERMODULE_SYMBOL_H

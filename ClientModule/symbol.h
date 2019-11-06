//
// Created by giova on 31/10/2019.
//

#ifndef SERVERMODULE_SYMBOL_H
#define SERVERMODULE_SYMBOL_H

#include <vector>

class symbol {

private:
    char _letter;
    std::pair<int, int> _id;
    std::vector<int> _pos;
    bool _isBold;
    bool _isItalic;

public:
    symbol(char character, std::pair<int, int> id, std::vector<int> pos);
    std::vector<int> getPos() const;
    char getLetter() const;
    std::pair<int, int> getId() const;
    bool isBold() const;
    bool isItalic() const;
    void setBold(bool val);
    void setItalic(bool val);
    void setLetter(char letter);
    void setId(std::pair<int,int> id);
    void setPos(std::vector<int> pos);
};


#endif //SERVERMODULE_SYMBOL_H

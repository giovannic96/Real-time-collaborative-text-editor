//
// Created by giova on 06/05/2019.
//

#ifndef LAB3_MESSAGE_H
#define LAB3_MESSAGE_H


#include "Symbol.h"

class Message {

    private:
        int type; //0 = 'insertion'; 1 = 'removal'
        int editorId;
        Symbol s;

    public:
        Message(int type, int editorId, Symbol s);
        int getType() const;
        int getEditorId();
        Symbol getSymbol() const;
};


#endif //LAB3_MESSAGE_H

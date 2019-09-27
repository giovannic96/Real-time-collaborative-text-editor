//
// Created by giova on 06/05/2019.
//

#ifndef LAB3_SHAREDEDITOR_H
#define LAB3_SHAREDEDITOR_H

#include "NetworkServer.h"
#include "Symbol.h"

struct NotFoundException : public std::exception {
    const char * what () const noexcept override {
        return "Not Found Exception";
    }
};

struct InsertedIndexNotValid : public std::exception {
    const char * what () const noexcept override {
        return "Inserted Index Not Valid Exception";
    }
};

class SharedEditor {

    private:
        NetworkServer& _server;
        int _siteId;
        std::vector<Symbol> _symbols;
        int _counter = 0;
        std::vector<int> generatePos(int index, char value);
        std::vector<int> generatePosBetween(std::vector<int> pos1, std::vector<int> pos2, std::vector<int> newPos = {});
        int comparePos(std::vector<int> curSymPos, std::vector<int> newSymPos, int posIndex);

    public:
        explicit SharedEditor(NetworkServer& server);
        ~SharedEditor();
        int getId();
        void localInsert(int index, char value);
        void localErase(int index);
        void process(const Message& m);
        std::string to_string();
        std::vector<Symbol> getSymbols(); //la dovrò eliminare forse, utile solo per debug
};


#endif //LAB3_SHAREDEDITOR_H

#ifndef CRDT_H
#define CRDT_H

#include <vector>
#include <symbolStyle.h>
#include <symbolInfo.h>
#include <symbol.h>

class crdt {

public:
    crdt() = default;
    virtual ~crdt() = default;
    symbol localInsert(int index, wchar_t value, symbolStyle style);
    std::vector<symbol> localInsert(std::vector<symbolInfo> symbols);
    void localErase(int startIndex, int endIndex);
    void localFormat(int startIndex, int endIndex, int format);
    void localFontSizeChange(int startIndex, int endIndex, int fontSize);
    void localFontFamilyChange(int startIndex, int endIndex, const std::string& fontFamily);
    void localAlignmentChange(int startIndex, int endIndex, int alignment);
    int process(int type, int indexEditor, symbol newSym);
    void setVector(std::vector<symbol> symbols);
    void setSiteId(int id);
    void setCounter(int counter);
    void setSymbols(std::vector<symbol> symbols);
    int getCounter();
    int getSiteId();
    std::vector<symbol> getSymbols();

private:
    std::vector<symbol> _symbols;
    int _counter = 0;
    int _siteId;
    std::vector<int> generatePos(int index);
    std::vector<int> generatePosBetween(std::vector<int> pos1, std::vector<int> pos2, std::vector<int> newPos = {});
    int comparePosdx(std::vector<int> curSymPos, std::pair<int,int> curSymId, std::vector<int> newSymPos, std::pair<int,int> newSymId, int posIndex);
    int comparePos(std::vector<int> curSymPos, std::pair<int,int> curSymId, std::vector<int> newSymPos, std::pair<int,int> newSymId, int posIndex);
    enum formatType {MAKE_BOLD=0, MAKE_ITALIC=1, MAKE_UNDERLINE=2, UNMAKE_BOLD=3, UNMAKE_ITALIC=4, UNMAKE_UNDERLINE=5, FORMAT_UNKNOWN=6};

};

#endif // CRDT_H

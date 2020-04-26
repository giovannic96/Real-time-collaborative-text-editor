#ifndef CRDT_H
#define CRDT_H

#include <vector>
#include <symbolStyle.h>
#include <symbol.h>
#include <QDebug>

typedef std::pair<int,int> sId;

class crdt {

public:
    crdt() = default;
    virtual ~crdt() = default;
    symbol localInsert(int index, wchar_t value, symbolStyle style);
    std::vector<symbol> localInsert(int startIndex, std::vector<symbol> symbols);
    std::vector<sId> localErase(int startIndex, int endIndex);
    std::vector<sId> localFormat(int startIndex, int endIndex, int format);
    std::vector<sId> localFontSizeChange(int startIndex, int endIndex, int fontSize);
    std::vector<sId> localFontFamilyChange(int startIndex, int endIndex, const std::string& fontFamily);
    std::vector<sId> localAlignmentChange(int startIndex, int endIndex, int alignment);
    int process(int type, int indexEditor, symbol newSym);
    int process(int type, int indexEditor, std::vector<symbol> newSymbols);
    int processErase(sId id);
    int processFormat(sId id, int format);
    int processFontSize(sId id, int fontSize);
    int processFontFamily(sId id, const std::string& fontFamily);
    int processAlignment(sId id, int alignment);
    void setVector(std::vector<symbol> symbols);
    void setSiteId(int id);
    void setCounter(int counter);
    void setSymbols(std::vector<symbol> symbols);
    void updateAlignmentSymbols(int index, int alignment);
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

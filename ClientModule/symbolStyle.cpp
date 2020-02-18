//
// Created by giova on 31/10/2019.
//

#include "symbolStyle.h"
#include <utility>

symbolStyle::symbolStyle()
        : _isBold(false), _isItalic(false), _isUnderlined(false), _fontFamily(DEFAULT_FONT_FAMILY), _fontSize(DEFAULT_FONT_SIZE) {}

symbolStyle::symbolStyle(bool isBold, bool isItalic, bool isUnderlined, std::string fontFamily, int fontSize)
    : _isBold(isBold), _isItalic(isItalic), _isUnderlined(isUnderlined), _fontFamily(std::move(fontFamily)), _fontSize(fontSize) {}

std::string symbolStyle::getFontFamily() const {
    return _fontFamily;
}

int symbolStyle::getFontSize() const {
    return _fontSize;
}

bool symbolStyle::isBold() const {
    return _isBold;
}

bool symbolStyle::isItalic() const {
    return _isItalic;
}

bool symbolStyle::isUnderlined() const {
    return _isUnderlined;
}

void symbolStyle::setBold(bool val) {
    this->_isBold = val;
}

void symbolStyle::setItalic(bool val) {
    this->_isItalic = val;
}

void symbolStyle::setUnderlined(bool val) {
    this->_isUnderlined = val;
}

void symbolStyle::setFontFamily(std::string fontFamily) {
    this->_fontFamily = std::move(fontFamily);
}

void symbolStyle::setFontSize(int value) {
    this->_fontSize = value;
}

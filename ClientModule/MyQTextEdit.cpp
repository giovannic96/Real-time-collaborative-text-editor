#include "MyQTextEdit.h"
#include <QMimeData>
#include <qdebug.h>
#include <QContextMenuEvent>
#include <QMenu>
#include <QDebug>
#include <QAction>
#include <QApplication>
#include <QClipboard>
#include <QRegularExpression>
#include <QPainter>

void MyQTextEdit::insertFromMimeData(const QMimeData* source) {
    if (source->hasText() && !source->hasImage() && !source->hasUrls() && !source->html().contains("<a href")) {
        QString text = source->text();
        QTextCursor cursor = textCursor();
        int startIndex;

        cursor.hasSelection() ? startIndex = cursor.selectionStart() : startIndex = cursor.position();

        /* Get background color */
        QString html = replaceColorWithEditorColor(source->html());

        /* Get alignments vector */
        QVector<std::pair<int,int>> alignments = getAlignmentsVector();

        /* Insert text (formatted) */
        cursor.insertHtml(html);

        /* Update each block with correct alignment */
        int numChars = source->text().size();
        Qt::AlignmentFlag align = Qt::AlignLeft;

        for(int i=0; i<numChars; i++) {
            QTextBlockFormat textBlockFormat;
            align = static_cast<Qt::AlignmentFlag>(getAlignmentValues(alignments));
            textBlockFormat.setAlignment(align);
            cursor.setPosition(startIndex++);
            cursor.mergeBlockFormat(textBlockFormat);
        }
        this->setAlignment(align);
        emit updateAlignmentButton();
    }
}

void MyQTextEdit::paintEvent(QPaintEvent *event) {
    QTextEdit::paintEvent(event);
    QPainter painter(viewport());
    painter.setRenderHint(QPainter::Antialiasing, true);

    QHash<QString, std::pair<QString,int>>::iterator i;
    for (i = remoteCursors.begin(); i != remoteCursors.end(); ++i) {
        /* Get current info */
        QTextCursor cursor = this->textCursor();
        cursor.setPosition(i.value().second);
        int curFontSize = static_cast<int>(cursor.charFormat().fontPointSize());
        if(cursor.position()==0) {
            if(this->toPlainText().size()>0) {
                cursor.movePosition(QTextCursor::Right);
                curFontSize = static_cast<int>(cursor.charFormat().fontPointSize());
                cursor.movePosition(QTextCursor::Left);
            } else
                curFontSize = static_cast<int>(this->font().pointSize());
        }
        int rectHeight = (curFontSize*30)/14;
        QString username = i.key();
        QColor color = i.value().first;
        QPen pen;
        pen.setColor(color);
        pen.setWidth(2);
        painter.setPen(pen);
        QFontMetrics metrics(cursor.charFormat().font());

        /* Rect for remote line cursor */
        QRect rect = cursorRect(cursor);
        QPoint center = rect.center();
        int offsetHeight = calculateOffsetHeight(curFontSize);
        int offsetY = calculateOffsetY(curFontSize);
        int y = rect.bottom()-(rect.height()/4)-metrics.ascent()+(metrics.descent()/2)*(cursor.charFormat().font().pointSize()/50);
        qDebug() << center.x() << y-offsetY << rectHeight << offsetHeight;
        painter.drawRect(center.x(), y-offsetY, 1, (rectHeight-offsetHeight));

        /* Horizontal rect for username */
        if(showHorizontalRect) {
            QPainterPath path;
            int widthViewport = viewport()->rect().width();
            int finalX = center.x()-2;
            int widthRect = calculateWidthForUsername(username);

            if((center.x()-2) >= (widthViewport-widthRect))
                finalX = center.x()-2 - (widthRect-5);
            QRectF rectUsername(finalX, y-offsetY-1, widthRect, -19);
            path.addRoundedRect(rectUsername, 2, 2);
            painter.fillPath(path, color);
            painter.drawPath(path);

            /* text for username inside rect */
            QFont font("Helvetica", 10, QFont::Bold, false);
            painter.setPen(QColor(255,255,255));
            painter.setFont(font);
            painter.drawText(finalX+1, y-offsetY-6, username);
        } else {
            /* Small Rect above cursor */
            QRectF smallRect(center.x()-4, y-offsetY-7, 9, 7);
            painter.fillRect(smallRect, color);
        }
    }
}

int MyQTextEdit::calculateWidthForUsername(QString& username) {
    int startWidth = username.contains('w', Qt::CaseInsensitive) ? 95 : 80;
    int length = username.length();
    int finalVal = (length*startWidth)/8;
    if(finalVal < 22)
        finalVal+=10;
    else if(finalVal > 150) {
        finalVal = 150;
        username = username.mid(0, (finalVal*8)/startWidth);
        username.insert(username.length(), "...");
    }
    return finalVal;
}

int MyQTextEdit::calculateOffsetY(int curFontSize) {
    int retVal = 0;
    if(curFontSize > 0 && curFontSize <= 96)
        retVal = 0;
    else if(curFontSize > 96 && curFontSize <= 140)
        retVal = 10;
    else if(curFontSize > 140 && curFontSize <= 160)
        retVal = 40;
    else if(curFontSize > 160 && curFontSize <= 180)
        retVal = 45;
    else if(curFontSize > 180 && curFontSize <= 190)
        retVal = 48;
    else if(curFontSize > 190 && curFontSize <= 199)
        retVal = 51;
    else if(curFontSize == 200)
        retVal = 80;
    return retVal;
}

int MyQTextEdit::calculateOffsetHeight(int curFontSize) {
    int retVal;
    int base = (curFontSize*3)/14;
    if(curFontSize > 0 && curFontSize <= 30)
        retVal = base-2;
    else if(curFontSize > 30 && curFontSize <= 48)
        retVal = base;
    else if(curFontSize > 48 && curFontSize <= 60)
        retVal = base+10;
    else if(curFontSize > 60 && curFontSize <= 78)
        retVal = base+17;
    else if(curFontSize > 78 && curFontSize <= 96)
        retVal = base+22;
    else if(curFontSize > 96 && curFontSize <= 99)
        retVal = base+9;
    else if(curFontSize > 99 && curFontSize <= 116)
        retVal = base+25;
    else if(curFontSize > 116 && curFontSize <= 136)
        retVal = base+35;
    else if(curFontSize > 136 && curFontSize <= 140)
        retVal = base+45;
    else if(curFontSize > 140 && curFontSize <= 149)
        retVal = base+19;
    else if(curFontSize > 149 && curFontSize <= 170)
        retVal = base+40;
    else if(curFontSize > 170 && curFontSize <= 190)
        retVal = base+48;
    else if(curFontSize > 190 && curFontSize <= 199)
        retVal = base+54;
    else if(curFontSize == 200)
        retVal = base+62;
    else
        retVal = 0;
    return retVal;
}

int MyQTextEdit::getAlignmentValues(QVector<std::pair<int,int>>& alignments) {
    int alignment = alignments.at(0).second;
    if(alignments.at(0).first > 1)
        alignments[0].first -= 1; //decrease the number of chars having same style
    else
        alignments.pop_front(); //remove the style from the vector -> i.e. all chars with that style has been handled
    return alignment;
}

QString MyQTextEdit::hexToHtmlRGB(QString hexARGB) {
    //at the end we have to obtain something like this: rgba(235,166,63,0.533333)
    QColor color(hexARGB);
    color.toRgb();
    qDebug() << "ALPHA:"<<color.alpha();
    QString alpha = QString::number(static_cast<double>(color.alpha())/255);
    QString red = QString::number(color.red());
    QString green = QString::number(color.green());
    QString blue = QString::number(color.blue());
    QString htmlColor = "rgba(" + red + "," + green + "," + blue + "," + alpha + ")";
    return htmlColor;
}

void MyQTextEdit::setBtnColorChecked(bool val) {
    this->isColorBtnChecked = val;
}

void MyQTextEdit::setAlignmentsVector(QVector<std::pair<int,int>> alignmentVector) {
    this->alignments = alignmentVector;
}

void MyQTextEdit::setEditorColor(QString color) {
    this->editorColor = color;
}

void MyQTextEdit::addRemoteCursor(QString username, std::pair<QString, int> colorAndPos) {
    this->remoteCursors.insert(username, std::make_pair(colorAndPos.first, colorAndPos.second));
}

QString MyQTextEdit::getEditorColor() {
    if(isBtnColorChecked())
        return this->editorColor;
    else {
        QString edColor = this->editorColor;
        edColor[1] = '0';
        edColor[2] = '1';
        return edColor;
    }
}

QHash<QString, std::pair<QString,int>> MyQTextEdit::getRemoteCursors() {
    return this->remoteCursors;
}

bool MyQTextEdit::isBtnColorChecked() {
    return this->isColorBtnChecked;
}

QVector<std::pair<int,int>> MyQTextEdit::getAlignmentsVector() {
    return this->alignments;
}

QString MyQTextEdit::replaceColorWithEditorColor(QString text) {
    QString html = text;
    QRegularExpression rx("background-color:([^;]+);");
    QStringList list = getRegexListFromHTML(text, rx);
    QString edColor = hexToHtmlRGB(this->getEditorColor());
    foreach (QString s, list) {
        html.replace(s, edColor);
    }
    return html;
}

QStringList MyQTextEdit::getRegexListFromHTML(QString text, QRegularExpression rx) {
    QStringList list;
    QRegularExpressionMatchIterator i = rx.globalMatch(text);
    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        QString word = match.captured(1);
        list << word;
    }
    return list;
}

void MyQTextEdit::removeRemoteCursor(std::string username) {
    remoteCursors.remove(QString::fromStdString(username));
    this->viewport()->update();
}

void MyQTextEdit::changeRemoteCursor(std::string username, std::string color, int pos) {
    QString col = QString::fromStdString(color);
    col[1] = 'f';
    col[2] = 'f';
    addRemoteCursor(QString::fromStdString(username), std::make_pair(col, pos));
    showHorizontalRect = true;
    timer.setSingleShot(true);
    timer.start(3000);
    this->viewport()->update();
}

void MyQTextEdit::hideHorizontalRect() {
    showHorizontalRect = false;
    this->viewport()->update();
}



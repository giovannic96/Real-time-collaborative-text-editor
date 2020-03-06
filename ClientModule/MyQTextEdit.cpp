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

int MyQTextEdit::getAlignmentValues(QVector<std::pair<int,int>>& alignments) {
    int alignment = alignments.at(0).second;
    if(alignments.at(0).first > 1)
        alignments[0].first -= 1; //decrease the number of chars having same style
    else
        alignments.pop_front(); //remove the style from the vector -> i.e. all chars with that style has been handled
    return alignment;
}

QString MyQTextEdit::hexToHtmlRGB(QString hexARGB) {
    //at the end we have to obtain something like this: rgba(235,166,63,0.6)
    QColor color(hexARGB);
    color.toRgb();
    QString alpha = QString::number(static_cast<double>(color.alpha())/255);
    QString red = QString::number(color.red());
    QString green = QString::number(color.green());
    QString blue = QString::number(color.blue());
    QString htmlColor = "rgba(" + red + "," + green + "," + blue + "," + alpha + ")";
    return htmlColor;
}

void MyQTextEdit::setAlignmentsVector(QVector<std::pair<int,int>> alignmentVector) {
    this->alignments = alignmentVector;
}

void MyQTextEdit::setEditorColor(QString color) {
    this->editorColor = color;
}

QString MyQTextEdit::getEditorColor() {
    return this->editorColor;
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

void MyQTextEdit::contextMenuEvent(QContextMenuEvent *event){
    QMenu *menu = createStandardContextMenu();
    menu->addSeparator();
    menu->addAction(tr("HidroSaphire Was Here"));
    menu->addSeparator();
   // menu->removeAction(); //How get default redo/undo action??? Can't find a solution - Help
    menu->exec(event->globalPos());
    delete menu;
}


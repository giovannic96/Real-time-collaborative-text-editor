#include "MyQTextEdit.h"
#include <QMimeData>
#include <qdebug.h>
#include <QContextMenuEvent>
#include <QMenu>
#include <QDebug>
#include <QAction>
#include <QApplication>
#include <QClipboard>

void MyQTextEdit::insertFromMimeData(const QMimeData* source) {
    if (source->hasText() && !source->hasImage() && !source->hasUrls() && !source->html().contains("<a href")) {
        QString text = source->text();
        QTextCursor cursor = textCursor();
        int startIndex;
        QString html = source->html();
        cursor.hasSelection() ? startIndex = cursor.selectionStart() : startIndex = cursor.position();

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

void MyQTextEdit::setAlignmentsVector(QVector<std::pair<int,int>> alignmentVector) {
    this->alignments = alignmentVector;
}

QVector<std::pair<int,int>> MyQTextEdit::getAlignmentsVector() {
    return this->alignments;
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


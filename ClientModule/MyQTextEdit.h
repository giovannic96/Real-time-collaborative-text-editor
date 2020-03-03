#ifndef MYQTEXTEDIT_H
#define MYQTEXTEDIT_H
#include <QTextEdit>

class MyQTextEdit : public QTextEdit
{
    Q_OBJECT

public:
    MyQTextEdit(QWidget* parent) : QTextEdit(parent) {}
    void insertFromMimeData(const QMimeData * source) override;
    void setAlignmentsVector(QVector<std::pair<int,int>> alignmentVector);
    QVector<std::pair<int,int>> getAlignmentsVector();

private:
    QVector<std::pair<int,int>> alignments;
    int getAlignmentValues(QVector<std::pair<int,int>>& alignments);
    void contextMenuEvent(QContextMenuEvent *event) override;

signals:
    void updateAlignmentButton();

};

#endif //MYQTEXTEDIT_H

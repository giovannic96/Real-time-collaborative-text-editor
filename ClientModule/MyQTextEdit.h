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
    void setEditorColor(QString color);
    QVector<std::pair<int,int>> getAlignmentsVector();
    QString getEditorColor();

private:
    QVector<std::pair<int,int>> alignments;
    QString editorColor;
    int getAlignmentValues(QVector<std::pair<int,int>>& alignments);
    void contextMenuEvent(QContextMenuEvent *event) override;
    QString hexToHtmlRGB(QString hexARGB);
    QString replaceColorWithEditorColor(QString text);
    QStringList getRegexListFromHTML(QString text, QRegularExpression rx);

signals:
    void updateAlignmentButton();

};

#endif //MYQTEXTEDIT_H

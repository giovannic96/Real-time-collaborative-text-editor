#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H

#include <QMainWindow>

namespace Ui {class EditorWindow;}

class EditorWindow : public QMainWindow{
    Q_OBJECT

public:
    EditorWindow(QString text, QWidget *parent = nullptr);
    ~EditorWindow();

private slots:
    void on_pushButton_3_clicked();

private:
    Ui::EditorWindow *ui;
    //For "DocName" QString
    QString textname;

};

#endif // EDITORWINDOW_H

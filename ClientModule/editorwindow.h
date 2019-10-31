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
    void on_buttonGrassetto_clicked();
    void on_buttonCorsivo_clicked();
    void on_buttonAlignDX_clicked();
    void on_buttonSottolineato_clicked();
    void on_buttonAlignCX_clicked();
    void on_buttonAlignSX_clicked();
    void on_buttonUndo_clicked();
    void on_buttonRedo_clicked();
    void on_buttonTaglia_clicked();
    void on_buttonIncolla_clicked();
    void on_buttonCopia_clicked();
    void on_buttonColor_clicked();
    void on_actionSave_triggered();
    void on_buttonExit_clicked();
    void on_actionChiudi_triggered();
    void on_renameButton_clicked();
    void on_buttonEvidenziato_clicked();
    void on_buttonFontUp_clicked();
    void on_buttonFontDown_clicked();

    void on_buttonToIcon_clicked();
    void on_buttonReduce_clicked();
    void on_actionFullscreen_triggered();

private:
    Ui::EditorWindow *ui;
    //For "DocName" QString
    QString textname;
    //For "Resizing the window"
    //QSize currentSize;
    //QPoint currentPos;

};

#endif // EDITORWINDOW_H

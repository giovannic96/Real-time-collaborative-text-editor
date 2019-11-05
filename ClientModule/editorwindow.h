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
    //void on_pushButton_3_clicked(); --> Old Rename Function Deprecated
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

    void on_buttonToIcon_clicked();
    void on_buttonReduce_clicked();
    void on_actionFullscreen_triggered();
    void on_actionAbout_triggered();

    void on_fontDimensionBox_activated(int index);
    void on_fontSelectorBox_currentFontChanged(const QFont &f);

    void on_RealTextEdit_cursorPositionChanged();

    /************************************
     *           DEBUG FUNCTION         *
     ************************************/
    void on_buttonDebug_clicked();
    void on_DebugIns1_clicked();
    void on_DebugInsInit_clicked();
    void on_DebugDel1_clicked();
    void on_DebugCursLeft_clicked();
    void on_DebugCursRight_clicked();
    void on_DebugCursLeftAnchor_clicked();
    void on_DebugWordLeft_clicked();
    void on_DebugWordRight_clicked();
    void on_DebugIns6Word_clicked();

private:
    Ui::EditorWindow *ui;
    //For "DocName" QString
    QString textname;

};

#endif // EDITORWINDOW_H

#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H

#include <QMainWindow>
#include "jsonUtility.h"
#include "message.h"
#include "myClient.h"

namespace Ui {class EditorWindow;}

class EditorWindow : public QMainWindow{
    Q_OBJECT

public:
    EditorWindow(myClient* client, QWidget *parent = nullptr);
    ~EditorWindow();

private slots:
    //void on_pushButton_3_clicked(); --> Old Rename Function Deprecated

    //Button for change style of the text
    void on_buttonGrassetto_clicked();
    void on_buttonCorsivo_clicked();
    void on_buttonSottolineato_clicked();
    void on_buttonColor_clicked();
    void on_buttonBackgroundColor_clicked();

    //Button for align the text
    void on_buttonAlignDX_clicked();
    void on_buttonAlignCX_clicked();
    void on_buttonAlignSX_clicked();
    void on_buttonAlignJFX_clicked();

    //Button for modify the text
    void on_buttonUndo_clicked();
    void on_buttonRedo_clicked();
    void on_buttonTaglia_clicked();
    void on_buttonIncolla_clicked();
    void on_buttonCopia_clicked();

    //Button for modify font and size of text
    void on_fontDimensionBox_activated(int index);
    void on_fontSelectorBox_currentFontChanged(const QFont &f);

    //RealTextEdit Function
    void on_RealTextEdit_cursorPositionChanged();

    //TopLeftBar Button
    void on_buttonExit_clicked();
    void on_buttonToIcon_clicked();
    void on_buttonReduce_clicked();

    //TopRightBar Button
    void on_fileButton_clicked();
    void on_pdfButton_clicked();
    //void on_uriButton_clicked(); MAYBE WE HAVE TO DELETE THIS

    //FileFrame Button
    //void on_newDocButton_clicked(); MAYBE WE HAVE TO DELETE THIS
    //void on_URIButton_clicked(); MAYBE WE HAVE TO DELETE THIS
    void on_buttonRename_clicked();
    void on_aboutButton_clicked();
    void on_CloseButton_clicked();

    /************************************
     *              ACTION              *
     ************************************/
    void on_actionFullscreen_triggered();
    void on_actionSave_triggered();
    void on_actionNew_triggered();
    void on_actionAbout_triggered();

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

public slots:
    void showPopupSuccess(QString result);
    void showPopupFailure(QString result);

private:
    Ui::EditorWindow *ui;
    QPoint oldPos;                  //This "oldPos" object is used to save the old position of the windows for the translation of windows
    void sendRequestMsg(std::string req);
    myClient *_client;

protected:
    //Function for mouse related event
    void mousePressEvent(QMouseEvent *evt);
    void mouseMoveEvent(QMouseEvent *evt);

};

#endif // EDITORWINDOW_H

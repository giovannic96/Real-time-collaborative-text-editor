#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include "editorwindow.h"
#include "myClient.h"

namespace Ui{class MenuWindow;}

class MenuWindow: public QMainWindow{
    Q_OBJECT

public:
    MenuWindow(myClient* client, QWidget *parent = nullptr);
    ~MenuWindow();

private slots:
    void on_LogoutButton_clicked();
    void on_Username_clicked();
    void on_newDoc_clicked();
    void on_uriDoc_clicked();
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);
    void on_listFiles_clicked();
    void on_exitButton_clicked();
    void on_backButton_clicked();
    void closeEvent(QCloseEvent * event);
    void RapidUserLogout();

public slots:
    void showPopupSuccess(QString result);
    void showPopupFailure(QString result);
    void showListFile(std::vector<File> files);
    void resumeWindow();

private:
    Ui::MenuWindow *ui;            //"ui" (user interface)
    QPoint oldPos;                  //This "oldPos" object is used to save the old position of the windows for the translation of windows
    myClient *_client;
    EditorWindow *_ew;
    void sendRequestMsg(const std::string req);
    void SetImage();
    bool Logout = false;

protected:
    //Function for mouse related event
    void mousePressEvent(QMouseEvent *evt);
    void mouseMoveEvent(QMouseEvent *evt);

};

#endif // MENUWINDOW_H


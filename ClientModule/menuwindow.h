#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QMainWindow>
#include "myClient.h"

namespace Ui{class MenuWindow;}

class MenuWindow: public QMainWindow{
    Q_OBJECT

public:
    MenuWindow(QWidget *parent = nullptr); //Constructor
    ~MenuWindow();                         //Destructor

private slots:
    void on_exitButton_clicked();
    void on_LogoutButton_clicked();
    void on_Username_clicked();
    void on_newDoc_clicked();
    void on_openDoc_clicked();
    void on_uriDoc_clicked();

private:
    Ui::MenuWindow *ui;            //"ui" (user interface)
    //For mouse related event
    QPoint oldPos;                  //This "oldPos" object is used to save the old position of the windows for the translation of windows
    //For client
    myClient *client;
    void sendRequestMsg(const char* req);

protected:
    //Function for mouse related event
    void mousePressEvent(QMouseEvent *evt);
    void mouseMoveEvent(QMouseEvent *evt);

};

#endif // MENUWINDOW_H


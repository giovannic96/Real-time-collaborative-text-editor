//  CLASS RegWindow - v0.1.3a
#ifndef REGWINDOW_H
#define REGWINDOW_H

#include <QMainWindow>
#include <QtGui>            //For QPoint
#include <QtSql>            //For SQL
#include <QSqlDatabase>     //For SQL
#include "versioninfo.h"    //Needed to show the current version of the software
#include "loginwindow.h"    //For switching to the login window

namespace Ui {class RegWindow;}

//Class RegWindow --> This class show a bordless window used to allow the user to sign up
class RegWindow : public QMainWindow{
    Q_OBJECT

public:
    explicit RegWindow(QWidget *parent = nullptr);
    ~RegWindow();

private slots:
    void on_exitButton_clicked();
    void on_AccediButton_clicked();
    void on_SignUpButton_clicked();

private:
    Ui::RegWindow *ui;                      //"ui" (user interface)
    //For mouse related event
    QPoint oldPos;                          //This "oldPos" object is used to save the old position of the windows for the translation of windows
    //For "version" QString
    VersionInfo v1;
    QString qstr = v1.getVersion();
    //For Database
    QSqlDatabase db;
    //...

protected:
    //Function for mouse related event
    void mousePressEvent(QMouseEvent *evt);
    void mouseMoveEvent(QMouseEvent *evt);
};


#endif // REGWINDOW_H

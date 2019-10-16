//  CLASS StartMenu - v0.1.3a
#ifndef STARTMENU_H
#define STARTMENU_H
#include <QMainWindow>
#include <QtGui>            //QPoint
#include "versioninfo.h"    //Needed to show the current version of the software
#include "loginwindow.h"    //For switching to the login window
#include "userprofile.h"    //For switching to the userprofile window

namespace Ui {class StartMenu;}

//Class StartMenu --> This class show a welcome page for the logged user in a bordless window
class StartMenu : public QMainWindow{
    Q_OBJECT

public:
    explicit StartMenu(QString nome, QWidget *parent = nullptr);
    ~StartMenu();
    //void setNomeUtente(QString nome){nomeutente=nome;}    //No more necessary //Dont delete me for a moment

private slots:
    void on_exitButton_clicked();
    void on_LogoutButton_clicked();
    void on_Username_clicked();

    void on_openEditor_clicked();

private:
    Ui::StartMenu *ui;                      //"ui" (user interface)
    //For "version" QString
    VersionInfo v1;
    QString qstr = v1.getVersion();
    //For "Username" QString
    QString nomeutente;
    //For mouse related event
    QPoint oldPos;                          //This "oldPos" object is used to save the old position of the windows for the translation of windows

protected:
    //Function for mouse related event
    void mousePressEvent(QMouseEvent *evt);
    void mouseMoveEvent(QMouseEvent *evt);

};

#endif // STARTMENU_H

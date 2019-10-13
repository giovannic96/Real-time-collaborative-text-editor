//  CLASS StartMenu - v 0.1.2a
#ifndef STARTMENU_H
#define STARTMENU_H

#include <QMainWindow>
#include <QtGui>            //QPoint
#include "versioninfo.h"    //Needed to show the current version of the software

namespace Ui {class StartMenu;}

//Class StartMenu --> This class show a welcome page for the logged user in a bordless window
class StartMenu : public QMainWindow{
    Q_OBJECT

public:
    explicit StartMenu(QString nome, QWidget *parent = nullptr);
    ~StartMenu();
    //void setNomeUtente(QString nome){nomeutente=nome;}    //No more necessary

private slots:
    void on_exitButton_clicked();

private:
    Ui::StartMenu *ui;
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

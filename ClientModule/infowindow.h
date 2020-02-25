#ifndef INFOWINDOW_H
#define INFOWINDOW_H

#include <QWidget>
#include <QtGui>            //QPoint
#include "versioninfo.h"

namespace Ui {class infoWindow;}

class infoWindow : public QWidget{
    Q_OBJECT

public:
    explicit infoWindow(QWidget *parent = nullptr);
    ~infoWindow();

private slots:
    void on_exitButton_clicked();
    void on_exitButton_2_clicked();
    //Github Profile
    void on_giovanni_clicked();
    void on_francesco_clicked();
    void on_rinaldo_clicked();
    void on_enrico_clicked();

private:
    Ui::infoWindow *ui;
    //For "version" QString
    VersionInfo version;
    QString qstr = version.getVersion();
    //For mouse related event
    QPoint oldPos;                  //This "oldPos" object is used to save the old position of the windows for the translation of windows

protected:
    //Function for mouse related event
    void mousePressEvent(QMouseEvent *evt);
    void mouseMoveEvent(QMouseEvent *evt);
};

#endif // INFOWINDOW_H

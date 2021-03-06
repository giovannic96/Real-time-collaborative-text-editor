//  CLASS UserProfile - v0.1.3a
#ifndef USERPROFILE_H
#define USERPROFILE_H

#include <QWidget>
#include <QtGui>            //QPoint
#include "myClient.h"


namespace Ui {class UserProfile;}

//Class UserProfile --> This class show the information about the logged user in a bordless window
class UserProfile : public QWidget{
    Q_OBJECT

public:
    explicit UserProfile(myClient* client, QString nome, QString mail, int files, int myFiles, QWidget *parent = nullptr);
    ~UserProfile();
    void SetRadiusBorder();
    void SetImage();

private slots:
    void on_exitButton_clicked();

signals:
    void closeUserProfile();

private:
    Ui::UserProfile *ui;                //"ui" (user interface)
    myClient *_client;
    //For mouse related event
    QPoint oldPos;                  //This "oldPos" object is used to save the old position of the windows for the translation of windows
    QChar SimplifySingleCharForSorting(QChar c, bool changeToLowerCase);

protected:
    //Function for mouse related event
    void mousePressEvent(QMouseEvent *evt);
    void mouseMoveEvent(QMouseEvent *evt);
};

#endif // USERPROFILE_H

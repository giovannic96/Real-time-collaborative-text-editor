//  CLASS UserProfile - v0.1.3a
#ifndef USERPROFILE_H
#define USERPROFILE_H

#include <QWidget>

namespace Ui {class UserProfile;}

//Class UserProfile --> This class show the information about the logged user in a bordless window
class UserProfile : public QWidget{
    Q_OBJECT

public:
    explicit UserProfile(QString nome, QWidget *parent = nullptr);
    ~UserProfile();
    void SetRadiusBorder();

private slots:
    void on_exitButton_clicked();
    void on_UserImageButton_clicked();

private:
    Ui::UserProfile *ui;                //"ui" (user interface)
    //For "Username" QString
    QString nomeutente;
};

#endif // USERPROFILE_H

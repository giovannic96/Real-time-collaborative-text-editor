//  CLASS UserProfile - v0.1.3a
#ifndef USERPROFILE_H
#define USERPROFILE_H

#include <QWidget>

namespace Ui {class UserProfile;}

//Class StartMenu --> This class show a welcome page for the logged user in a bordless window
class UserProfile : public QWidget{
    Q_OBJECT

public:
    explicit UserProfile(QWidget *parent = nullptr);
    ~UserProfile();
    void SetRadiusBorder();

private slots:
    void on_exitButton_clicked();
    void on_UserImageButton_clicked();

private:
    Ui::UserProfile *ui;                //"ui" (user interface)
};

#endif // USERPROFILE_H

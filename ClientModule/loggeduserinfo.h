#pragma once
#include <QString>

class LoggedUserInfo{
private:
    QString Username;
public:
    LoggedUserInfo(QString nome): Username(nome){} //Costruttore
    QString getUsername(){return Username;}
};

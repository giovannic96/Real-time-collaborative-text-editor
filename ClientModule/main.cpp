#include <boost/asio.hpp>
#include "startwindow.h"
#include <QApplication>

int main(int argc, char *argv[]){

    QApplication a(argc, argv);

    //Building first window (login).       //TODO --> Add a splashscreen
    StartWindow w;
    w.show();

    return a.exec();    //Starting point of the event loop of "thread GUI" (or primary thread)
}

#include <boost/asio.hpp>
#include "startwindow.h"
#include "debugroom.h"
#include <QApplication>

int main(int argc, char *argv[]){

    QApplication a(argc, argv);

    //Building first window (login).       //TODO --> Add a splashscreen

    /*DELETE ME FOR FINAL VERSION
    StartWindow w;
    w.show();
    */
    DebugRoom TheLobby;
    TheLobby.show();

    return a.exec();    //Starting point of the event loop of "thread GUI" (or primary thread)
}

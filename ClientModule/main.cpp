#include <boost/asio.hpp>
#include "startwindow.h"
#include <QApplication>
#include <QSplashScreen>
#include <QTimer>
#include <unistd.h>         //For sleep();

int main(int argc, char *argv[]){

    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    qRegisterMetaType<std::pair<int,char>>("std::pair<int,char>");
    qRegisterMetaType<std::string>("std::string");

    QApplication a(argc, argv);
    QSplashScreen *loadingScreen = new QSplashScreen;
    loadingScreen->setPixmap(QPixmap(":/image/SplashScreen.png"));
    loadingScreen->show();
    a.processEvents();  //Process the application (is the loading)

    sleep(1);
    StartWindow w;
    QTimer::singleShot(200,loadingScreen,SLOT(close()));
    QTimer::singleShot(200,&w,SLOT(show()));
    w.show();

    return a.exec();    //Starting point of the event loop of "thread GUI" (or primary thread)
}

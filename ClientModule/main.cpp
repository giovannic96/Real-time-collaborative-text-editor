#include <boost/asio.hpp>
#include "startwindow.h"
#include <QApplication>

int main(int argc, char *argv[]){

    qRegisterMetaType<std::pair<int,wchar_t>>("std::pair<int,wchar_t>");
    qRegisterMetaType<std::string>("std::string");

    /*
     * FOLLOWING COMMENTED LINE IS FOR DPI SCALING -> IT DOESN'T WORK FOR ME. Check yourself with your monitor
     * I tryed to copy this line in the constructor of EditorWindow, it doesn't work too!
     * This is big smoking shit! Can't find a solution.
     * @rinaldoclemente suggest to use image instead of text, but I (HidroSaphire) don't like it as solution
     *
     * Futhermore, I discover that is a Well Known Bug of Qt
     * See this and https://bugreports.qt.io/browse/QTBUG-53022
     *
    QApplication::setAttribute(Qt::AA_Use96Dpi);
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    qputenv("QT_DEVICE_PIXEL_RATIO", QByteArray("1")); //Deprecated in Qt 5.6
    qputenv("QT_SCALE_FACTORS", "2");
    qputenv("QT_AUTO_SCREEN_SCALE_FACTORS", "2");
    */

    QApplication a(argc, argv);

    //Building first window (login).       //TODO --> Add a splashscreen

    StartWindow w;
    w.show();

    return a.exec();    //Starting point of the event loop of "thread GUI" (or primary thread)
}

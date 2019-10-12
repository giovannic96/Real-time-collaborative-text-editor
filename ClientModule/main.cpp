#include <boost/asio.hpp>
#include "loginwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Costruzione dell'oggetto finestra principale di login.
    LoginWindow w;
    w.show();

    //punto di inizio dell'event loop del thread GUI (o thread principale)
    return a.exec();
}

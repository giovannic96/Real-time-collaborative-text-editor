#include "regwindow.h"
#include "loginwindow.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Costruzione dell'oggetto finestra principale di login.
    RegWindow w;
    LoginWindow s;
    w.show();
    s.hide();

    //punto di inizio dell'event loop del thread GUI (o thread principale)
    return a.exec();
}

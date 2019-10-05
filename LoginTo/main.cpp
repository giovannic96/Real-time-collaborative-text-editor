#include "loginwindow.h"
#include <QApplication>
#include "singupwindow.h"   //DEBUG --> rimuovi
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Costruzione dell'oggetto finestra principale di login.
    SingupWindow w;
    w.show();

    //punto di inizio dell'event loop del thread GUI (o thread principale)
    return a.exec();
}

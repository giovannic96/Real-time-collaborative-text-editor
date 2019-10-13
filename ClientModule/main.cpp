#include "loginwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Costruzione dell'oggetto finestra principale di login.
    LoginWindow w;
    w.show();


    return a.exec(); //Starting point of the event loop of "thread GUI" (or primary thread)
}

//  CLASSE LoginWindow - v 0.1.1a
//  LastEdit = 2019/10/05 @ 18:50

#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H
#include <QMainWindow>
#include <QtGui>            //Per QPoint
#include <QtSql>            //Per SQL
#include <QSqlDatabase>     //Per SQL
#include "versioninfo.h"    //Per visualizzare la versione corrente del software
#include "regwindow.h"      //Per lo switch delle window

QT_BEGIN_NAMESPACE
namespace Ui { class LoginWindow; }
QT_END_NAMESPACE

/*HS************Classe LoginWindow che estende QMainWindow*******************
* Questa classe mostra una Window "bordless" di dimensioni prefissate (384x667)
* che permette all'utente di inserire le credenziali per potersi loggare
*****************************************************************************/
class LoginWindow : public QMainWindow{
    Q_OBJECT

public:
    LoginWindow(QWidget *parent = nullptr); //Costruttore
    ~LoginWindow();                         //Distruttore

private slots:
    void on_exitButton_clicked();           //gestione del click sul pulsante di uscita (la X in alto a destra)
    void on_ForgotPasswordButton_clicked();
    void on_LoginButton_clicked();
    void on_RegistratiButton_clicked();

private:
    Ui::LoginWindow *ui;                    //Creo "ui" (user interface)
    //Per lo sfondo
    QWidget *frame = new QWidget(this);     //Creo un QWidget chiamato "frame" tramite allocazione dinamica. Viene distrutto nel distruttore
    //Per il database
    QSqlDatabase db2;
    //Per il trascinamento del mouse
    QPoint oldPos;                          //Un oggetto "oldPos" ti tipo QPoint mi serve per salvare la vecchia posizione della finestra durante le azioni di trascinamento (mousePressEvent e mouseMove)
    //Per la stringa della versione
    VersionInfo v1;                         //Creo un oggetto v1 di tipo VersionInfo che mi permette di conoscere la versione del software
    QString qstr = v1.getVersion();         //Creo un oggetto qstr di tipo QString a cui assegno la QString ritornata dalla funzione getVersion() dell'oggetto v1;
    //...

protected:
    //Funzioni per la gestione del trascinamento della finestra
    void mousePressEvent(QMouseEvent *evt);
    void mouseMoveEvent(QMouseEvent *evt);

};
#endif // LOGINWINDOW_H

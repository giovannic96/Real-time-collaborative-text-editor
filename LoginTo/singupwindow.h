//  CLASSE LoginWindow - v 0.1.1a
//  LastEdit = 2019/10/05 @ 17:00

#ifndef SINGUPWINDOW_H
#define SINGUPWINDOW_H
#include <QMainWindow>
#include <QtGui>            //Per QPoint
#include "versioninfo.h"    //Per visualizzare la versione corrente del software
#include <QtSql>            //Per SQL
#include <QSqlDatabase>     //Per SQL

namespace Ui { class SingupWindow; }

/*HS************Classe SingupWindow che estende QMainWindow*******************
* Questa classe mostra una Window "bordless" di dimensioni prefissate (384x667)
* che permette all'utente di inserire le credenziali per potersi registrare
*****************************************************************************/
class SingupWindow : public QMainWindow{
    Q_OBJECT

public:
    SingupWindow(QWidget *parent = nullptr);   //Costruttore //TODO --> Perchè era explicit?
    ~SingupWindow();            //Distruttore

private:
    Ui::SingupWindow *ui;
    //Per lo sfondo
    QWidget *frame = new QWidget(this);     //Creo un QWidget chiamato "frame" tramite allocazione dinamica. Viene distrutto nel distruttore
    //Per il database
//  QSqlDatabase db2;
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

private slots:
    void on_exitButton_clicked();
};

#endif // SINGUPWINDOW_H

//  CLASSE RegWindow - v 0.1.1a
//  LastEdit = 2019/10/05 @ 18:50
#ifndef REGWINDOW_H
#define REGWINDOW_H

#include <QMainWindow>
#include <QtGui>            //Per QPoint
#include "versioninfo.h"    //Per visualizzare la versione corrente del software
#include <QtSql>            //Per SQL
#include <QSqlDatabase>     //Per SQL
#include "loginwindow.h"

namespace Ui {class RegWindow;}

/*HS************Classe RegWindow che estende QMainWindow*********************
* Questa classe mostra una Window "bordless" di dimensioni prefissate (384x667)
* che permette all'utente di inserire le credenziali per potersi registrare
*****************************************************************************/
class RegWindow : public QMainWindow{
    Q_OBJECT

public:
    explicit RegWindow(QWidget *parent = nullptr);
    ~RegWindow();

private slots:
    void on_exitButton_clicked();
    void on_SingUpButton_clicked();

private:
    Ui::RegWindow *ui;
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
};


#endif // REGWINDOW_H

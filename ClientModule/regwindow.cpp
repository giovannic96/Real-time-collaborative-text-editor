#include "regwindow.h"
#include "ui_regwindow.h"
#include "versioninfo.h"
#include <QtGui>            //Per QPoint
#include <QMessageBox>      //Per Messaggi di alert

/*HS************Costruttore della RegWindow********************************
* Il costruttore costruisce la MainWindows con i parametri FramelessWindowsHint e WindowSystemMenuHint
* che permettono di rendere "bordless" la finestra. Avrei potuto abilitare la proprietà della QMainWindow
*****************************************************************************/
RegWindow::RegWindow(QWidget *parent) :
    QMainWindow(parent, Qt::FramelessWindowHint | Qt::WindowSystemMenuHint), ui(new Ui::RegWindow){
    ui->setupUi(this);
    //Associo alla QLabel "version" la stringa "qstr". In questo modo vedo sulla schermata la versione del software in uso
    ui->version->setText(qstr);
    //Associo l'immagine di sfondo al frame (parte dal punto 0x0, dimensioni 390x670)
    frame->setGeometry(0,0, 390,670);
    frame->setStyleSheet("background-image: url(:/image/Registration.png)");
}

/*HS************Distruttore della RegWindow*********************************
 * Distruggo il frame e l'user interface
 ***************************************************************************/
RegWindow::~RegWindow(){
    delete frame;
    delete ui;
}

/*HS*************************************************************************
* Questa funzione acquisisce la posizione x-y del mouse quando viene pressato il bottone sinistro
* sulla finestra LoginWindow e salva tale posizione nella variabile "oldPos" di tipo QPoint.
*
* La funzione va in coppia con la seguente LoginWindow::mouseMoveEvent che permette il trascinamento
* della finestra
*****************************************************************************/
void RegWindow::mousePressEvent(QMouseEvent *evt){
     oldPos = evt->globalPos();
}

/*HS*************************************************************************
* Questa funzione permette di trascinare la finestra LoginWindow quando si preme il pulsante sinistro
* del mouse sulla finestra LoginWindow, ricalcolandone la posizione x-y.
* Il ricalcolo della finestra tramite l'ausilio di un altro punto QPoint chiamato "delta" a cui viene
* sottratta la vecchia posizione aquisita del mouse tramite la funzione precedente, ossia la funzione
* LoginWindow::mousePressEvent (vedi descrizione approfondita alla fine di questo commento).
*
* Il riposizionamento della finestra avviene con la funzione "move". A questa funzione vengono passati:
* 1) la vecchia coordinata x a cui viene sommato il delta-x dello spostamento lungo l'asse x
* 2) la vecchia coordinata y a cui viene sommato il delta-y dello spostamento lungo l'asse y
*
* Infine, la funzione riacquisisce la posizione x-y del mouse, in modo che al frame video successivo si
* possa continuare a spostare la finestra, dando all'utente una percezione di continuità nel trascinamento
*
* La funzione va in coppia con la precedente LoginWindow::mousePressEvent che registra la posizione
* originale del mouse, memorizzando le coordinate x-y al momento della prima pressione del tasto sinistro
* sulla finestra
*****************************************************************************/
void RegWindow::mouseMoveEvent(QMouseEvent *evt){
    const QPoint delta = evt->globalPos() - oldPos;
    move(x()+delta.x(), y()+delta.y());
    oldPos = evt->globalPos();
}

/*HS*************************************************************************
* Questa funzione viene richiamata quando clicchiamo il pulsante "X" per uscire dal programma
*
* La QApplication mette a disposizione tre funzioni membro: exit(), close() e quit(). Nonostante la semantica sia uguale,
* le funzioni vanno scelte a seconda del S.O. di destinazione e dal contesto (per la coerenza) con il nome visualizzato.
* C'è ancora molta confusione su quale delle tre funzioni membro usare, come si evince nel seguente thread:
* https://ux.stackexchange.com/questions/50893/do-we-exit-quit-or-close-an-application
*
* Dato che stiamo sviluppando questa applicazione per S.O. Windows, abbiamo deciso di usare la exit() come suggerito dal
* Windows Dev Center, nella sezione "Standard Menu Bars", al seguente link:
* https://ux.stackexchange.com/questions/50893/do-we-exit-quit-or-close-an-application
*
* Se fossimo stati in un contesto MacOS, avremmo utilizzato la quit(), come suggerito nella  Human Interface Guidelines
* della Apple, che trovate al seguente link:
* https://developer.apple.com/design/human-interface-guidelines/macos/overview/themes/#//apple_ref/doc/uid/TP30000356-TP6
*
* Tuttavia, dato che la semantica è uguale per tutte le funzioni, e la "X" è il simbolo universale della chiusura del
* programma,è indifferente quale funzione scegliere.
*****************************************************************************/
void RegWindow::on_exitButton_clicked(){
    QApplication::exit();
}

/*HR**************************************************************************
* Funzione che permette di switchare da questa Window (RegWindow) alla
* finestra di login (LoginWindow). Questa funzione ha fatto sudare Enrico e Rinaldo
******************************************************************************/
/*
void LoginWindow::on_RegistratiButton_clicked(){
    RegWindow *l = new RegWindow();
    l->show();
    this->hide();
}
*/
void RegWindow::on_AccediButton_clicked(){
    LoginWindow *l = new LoginWindow();
    l->show();
    this->hide();
}

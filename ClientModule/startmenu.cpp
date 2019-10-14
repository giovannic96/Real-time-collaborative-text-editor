#include "startmenu.h"
#include "ui_startmenu.h"
#include <QMessageBox>

//CONSTRUCTOR WITH PARAMETERS
StartMenu::StartMenu(QString nome, QWidget *parent) :
    QMainWindow(parent, Qt::FramelessWindowHint | Qt::WindowSystemMenuHint), ui(new Ui::StartMenu){
    ui->setupUi(this);
    ui->version->setText(qstr); //Associate the QLabel "version" at the string "qstr". In this way I can show the version of this software
    ui->Username->setText(nome); //Associate the QLabel "Username" at the string "nome" passed by argument. In this way I can show the username of the user
}

//DESTRUCTOR
StartMenu::~StartMenu(){
    delete ui;
}

//EXIT BUTTON
void StartMenu::on_exitButton_clicked(){
     QApplication::exit();
}

//FUNCTION FOR MAKE DRAGGABLE THE WINDOW
void StartMenu::mousePressEvent(QMouseEvent *evt){
     oldPos = evt->globalPos();
}

//FUNCTION FOR MAKE DRAGGABLE THE WINDOW
void StartMenu::mouseMoveEvent(QMouseEvent *evt){
    const QPoint delta = evt->globalPos() - oldPos;
    move(x()+delta.x(), y()+delta.y());
    oldPos = evt->globalPos();
}

//LOGOUT BUTTON --> handle the switch beetween this window and the "login window"
void StartMenu::on_LogoutButton_clicked(){
       //TODO --> MAKE THE USER REALLY DISCONNECT
    LoginWindow *l = new LoginWindow();
    l->show();
    this->hide();
}

//USERNAME BUTTON
void StartMenu::on_Username_clicked(){
    QMessageBox msgBox;
    msgBox.setText("Cliccando qui apparirà la schermata di impostazioni dell'utente.\nLa schermata sarà richiamabile anche all'interno dell'editor");
    msgBox.exec();
}

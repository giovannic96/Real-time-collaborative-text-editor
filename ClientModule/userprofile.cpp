#include "userprofile.h"
#include "ui_userprofile.h"
#include <QMessageBox>

//CONSTRUCTOR
UserProfile::UserProfile(QWidget *parent): QWidget(parent, Qt::FramelessWindowHint | Qt::WindowSystemMenuHint), ui(new Ui::UserProfile){
    ui->setupUi(this);
}

//DESTRUCTOR
UserProfile::~UserProfile(){
    delete ui;
}

//EXIT BUTTON
void UserProfile::on_exitButton_clicked(){
    QWidget::close();
}

//USER'S IMAGE BUTTON
//TODO --> Quando l'utente passa il mouse sul bottone, dovrà apparire sovrapposta un'altra immagine semitrasparente con un icona di uan fotocamera al centro
void UserProfile::on_UserImageButton_clicked(){
    QMessageBox msgBox;
    msgBox.setText("Cliccando qui apparirà la schermata per far cambiare l'immagine dell'utente.\nNon so ancora se questa feature verrà implementata!");
    msgBox.exec();
}

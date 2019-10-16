#include "userprofile.h"
#include "ui_userprofile.h"
#include <QMessageBox>

//CONSTRUCTOR
UserProfile::UserProfile(QWidget *parent): QWidget(parent, Qt::FramelessWindowHint | Qt::WindowSystemMenuHint), ui(new Ui::UserProfile){
    ui->setupUi(this);
    SetRadiusBorder();
    this->show();
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
    msgBox.setText("Cliccando qui apparirà la schermata per far cambiare l'immagine dell'utente.\n"
                   "Non so ancora se questa feature verrà implementata!\n\n"
                   "UPDATE 2019/10/16 @ 22:16 \n"
                   "Mi serve un grafico (Rinaldo sei tu?) che mi faccia un immagine rotonda con sfondo\n grigio chiaro"
                   "e con opacità tra il 20 e 40%, dove sopra compaia un icona (nera/bianca) di una macchina fotografica"
                   "Ho fatto infatti diverse prove per farla su Qt, purtroppo non viene accettata la proprietà \"opacity\""
                   "dello StyleSheet, e neanche la transazione, quindi dovremmo sperimentare un modo per farla apparire"
                   "Dato che ancora non so se questa feature sarà implementata ne discuteremo successivamente.");
    msgBox.exec();
}

//SET RADIUS BORDER --> Called in constructor to make the window with round edges
void UserProfile::SetRadiusBorder(){
    const int radius = 40;

    QPainterPath path;
    path.addRoundedRect(this->rect(), radius, radius);
    QRegion mask = QRegion (path.toFillPolygon().toPolygon());
    this->setMask(mask);
}

#include "userprofile.h"
#include "ui_userprofile.h"
#include <QMessageBox>
#include <QDebug>

//CONSTRUCTOR WITH PARAMETERS
UserProfile::UserProfile(QString nome, QWidget *parent): QWidget(parent, Qt::FramelessWindowHint | Qt::WindowSystemMenuHint), ui(new Ui::UserProfile){
    ui->setupUi(this);
    ui->Username->setText(nome); //Associate the QLabel "Username" at the string "nome" passed by argument. In this way I can show the username of the user
    SetRadiusBorder();
    SetImage();
    this->show();
}

//DESTRUCTOR
UserProfile::~UserProfile(){
    delete ui;
    qDebug() << "Destructor of UserProfile Widget in action";
}

//EXIT BUTTON
void UserProfile::on_exitButton_clicked(){
    QWidget::close();
    delete this;   //Very important, is needed for calling the destructor
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
    const int radius = 21;

    QPainterPath path;
    path.addRoundedRect(this->rect(), radius, radius);
    QRegion mask = QRegion (path.toFillPolygon().toPolygon());
    this->setMask(mask);
}

void UserProfile::SetImage(){
    QRect rect(0,0,128,128);
    QRegion region(rect, QRegion::Ellipse);
    qDebug() << region.boundingRect().size();
    ui->UserImageButton->setMask(region);
}

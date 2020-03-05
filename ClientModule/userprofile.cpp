#include "userprofile.h"
#include "ui_userprofile.h"
#include <QMessageBox>
#include <QDebug>

UserProfile::UserProfile(QString nome, QString mail,int files, int myFiles, QWidget *parent): QWidget(parent, Qt::FramelessWindowHint | Qt::WindowSystemMenuHint), ui(new Ui::UserProfile){
    ui->setupUi(this);
    ui->Username->setText(nome); //Associate the QLabel "Username" at the string "nome" passed by argument. In this way I can show the username of the user
    ui->Mail->setText(mail);     //Same way

    QString sFiles = QString::number(files);
    QString sMyFiles = QString::number(myFiles);
    QString sTotFiles = QString::number(files+myFiles);

    ui->myFile->setText(sMyFiles);
    ui->totFile->setText(sTotFiles);
    ui->otherFile->setText(sFiles);
    SetImage();
    this->show();
}

UserProfile::~UserProfile() {
    delete ui;
    qDebug() << "Destructor of UserProfile Widget in action";
}

//EXIT BUTTON
void UserProfile::on_exitButton_clicked() {
    QWidget::close();
    delete this;   //Very important, is needed for calling the destructor
}

//To make draggable the window
void UserProfile::mousePressEvent(QMouseEvent *evt) {
     oldPos = evt->globalPos();
}

//To make draggable the window
void UserProfile::mouseMoveEvent(QMouseEvent *evt) {
    const QPoint delta = evt->globalPos() - oldPos;
    move(x()+delta.x(), y()+delta.y());
    oldPos = evt->globalPos();
}

//USER'S IMAGE BUTTON
//TODO --> Quando l'utente passa il mouse sul bottone, dovrà apparire sovrapposta un'altra immagine semitrasparente con un icona di uan fotocamera al centro
void UserProfile::on_UserImageButton_clicked() {
    QMessageBox msgBox;
    msgBox.setText("Cliccando qui apparirà la schermata per far cambiare l'immagine dell'utente.\n");
    msgBox.exec();
}

void UserProfile::SetImage() {
    QRect rect(0,0,128,128);
    QRegion region(rect, QRegion::Ellipse);
    qDebug() << region.boundingRect().size();
    ui->UserImageButton->setMask(region);
}

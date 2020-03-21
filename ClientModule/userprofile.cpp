#include "userprofile.h"
#include "ui_userprofile.h"
#include <QMessageBox>
#include <QDebug>

UserProfile::UserProfile(QString nome, QString mail,int files, int myFiles, QWidget *parent): QWidget(parent, Qt::FramelessWindowHint | Qt::WindowSystemMenuHint), ui(new Ui::UserProfile){
    ui->setupUi(this);
    ui->Username->setText(nome); //Associate the QLabel "Username" at the string "nome" passed by argument. In this way I can show the username of the user
    ui->Mail->setText(mail);     //Same way

    QString TotalFiles = QString::number(files);
    QString MyFiles = QString::number(myFiles);
    QString PartecipingFiles = QString::number(files-myFiles);

    ui->myFile->setText(MyFiles);
    ui->totFile->setText(TotalFiles);
    ui->otherFile->setText(PartecipingFiles);

    QChar firstLetter;

    for (int i=0;i<nome.length();i++){
        firstLetter = nome.at(i);
        if(firstLetter.isLetter()){
            break;
        }
    }

    SimplifySingleCharForSorting(firstLetter,1);
    ui->UserImageButton->setText(firstLetter.toUpper());

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

QChar UserProfile::SimplifySingleCharForSorting(QChar c, bool changeToLowerCase){

    if ( ( c >= 0xC0 && c <= 0xC5 ) || ( c >= 0xE1 && c <= 0xE5 ) || c == 0xAA )
        return ( ( c >= 0xC0 && c <= 0xC5 ) && !changeToLowerCase ) ? 'A' : 'a';
    if ( ( c >= 0xC8 && c <= 0xCB ) || ( c >= 0xE8 && c <= 0xEB ) )
        return ( c > 0xCB || changeToLowerCase ) ? 'e' : 'E';
    if ( ( c >= 0xCC && c <= 0xCF ) || ( c >= 0xEC && c <= 0xEF ) )
        return ( c > 0xCF || changeToLowerCase ) ? 'i' : 'I';
    if ( ( c >= 0xD2 && c <= 0xD6 ) || ( c >= 0xF2 && c <= 0xF6 ) || c == 0xBA )
        return ( ( c >= 0xD2 && c <= 0xD6 ) && !changeToLowerCase ) ? 'O' : 'o';
    if ( ( c >= 0xD9 && c <= 0xDC ) || ( c >= 0xF9 && c <= 0xFC ) )
        return ( c > 0xDC || changeToLowerCase ) ? 'u' : 'U';
    if ( c == 0xA9 || c == 0xC7 || c == 0xE7 )
        return ( c == 0xC7 && !changeToLowerCase ) ? 'C' : 'c';
    if ( c == 0xD1 || c == 0xF1 )
        return ( c == 0xD1 && !changeToLowerCase ) ? 'N' : 'n';
    if ( c == 0xAE )
        return 'r';
    if ( c == 0xDF )
        return 's';
    if ( c == 0x8E || c == 0x9E )
        return ( c == 0x8E && !changeToLowerCase ) ? 'Z' : 'z';
    if ( c == 0x9F || c == 0xDD || c == 0xFD || c == 0xFF )
        return ( ( c == 0x9F || c == 0xDD ) && !changeToLowerCase ) ? 'Y' : 'y';
    return c;
}

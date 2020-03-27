#include "infowindow.h"
#include "ui_infowindow.h"

//CONSTRUCTOR
infoWindow::infoWindow(QWidget *parent): QWidget(parent, Qt::FramelessWindowHint | Qt::WindowSystemMenuHint), ui(new Ui::infoWindow){
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose, true); //Call the constructor when Windows close this.
    ui->version->setText(qstr);
    ui->giovanni->setStyleSheet("background: transparent;");
    ui->francesco->setStyleSheet("background: transparent;");
    ui->rinaldo->setStyleSheet("background: transparent;");
    ui->enrico->setStyleSheet("background: transparent;");
    this->show();
}

//DESTRUCTOR
infoWindow::~infoWindow(){
    delete ui;
}

//EXIT BUTTON
void infoWindow::on_exitButton_clicked(){
    QWidget::close();
    delete this;   //Very important, is needed for calling the destructor
}

void infoWindow::on_exitButton_2_clicked(){
    QWidget::close();
    delete this;   //Very important, is needed for calling the destructor
}


//FUNCTION FOR MAKE DRAGGABLE THE WINDOW
void infoWindow::mousePressEvent(QMouseEvent *evt){
     oldPos = evt->globalPos();
}

//FUNCTION FOR MAKE DRAGGABLE THE WINDOW
void infoWindow::mouseMoveEvent(QMouseEvent *evt){
    const QPoint delta = evt->globalPos() - oldPos;
    move(x()+delta.x(), y()+delta.y());
    oldPos = evt->globalPos();
}


/***********************************************************************************
*                          BUTTON ON NAME - GITHUB LINKS                           *
************************************************************************************/
void infoWindow::on_giovanni_clicked(){
    QString link = "https://github.com/giovannic96/";
    QDesktopServices::openUrl(QUrl(link));
}

void infoWindow::on_francesco_clicked(){
    QString link = "https://github.com/fr2sinc/";
    QDesktopServices::openUrl(QUrl(link));
}

void infoWindow::on_rinaldo_clicked(){
    QString link = "https://github.com/rinaldoclemente/";
    QDesktopServices::openUrl(QUrl(link));
}

void infoWindow::on_enrico_clicked(){
    QString link = "https://github.com/HidroSaphire/";
    QDesktopServices::openUrl(QUrl(link));
}

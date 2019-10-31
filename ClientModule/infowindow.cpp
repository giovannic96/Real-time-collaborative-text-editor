#include "infowindow.h"
#include "ui_infowindow.h"

//CONSTRUCTOR
infoWindow::infoWindow(QWidget *parent): QWidget(parent, Qt::FramelessWindowHint | Qt::WindowSystemMenuHint), ui(new Ui::infoWindow){
    ui->setupUi(this);
    ui->version->setText(qstr);
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

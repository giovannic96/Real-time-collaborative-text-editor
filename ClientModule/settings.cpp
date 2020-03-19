#include "settings.h"
#include "ui_settings.h"
#include "editorwindow.h"
#include <QSettings>

Settings::Settings(EditorState &estate, QWidget *parent): QWidget(parent), ui(new Ui::Settings), estate(estate){
    ui->setupUi(this);
}

Settings::~Settings(){
    delete ui;
}

void Settings::on_pushButton_clicked(){
    estate.SetDarkMode(true);
}

void Settings::on_day_clicked()
{
    estate.SetDarkMode(false);
}

void Settings::on_pushButton_3_clicked()
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "MySoft", "Star Runner");
    settings.setValue("darkmode", estate.GetDarkMode());
    settings.endGroup();
}

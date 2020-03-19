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

//DEBUG
void Settings::on_pushButton_clicked(){
    estate.SetDarkMode(true);
}

//DEBUG
void Settings::on_day_clicked(){
    estate.SetDarkMode(false);
}

void Settings::on_Save_clicked(){
    /*****************************/
    //          All'avvio        //
    /*****************************/
    if(ui->dayRadio->isChecked()){
         estate.SetDarkMode(false);
    }
    if(ui->darkRadio->isChecked()){
        estate.SetDarkMode(true);
    }

    if(ui->toolShowRadio->isChecked()){
        estate.SetToolbar(true);
    }
    if(ui->toolHideRadio->isChecked()){
        estate.SetToolbar(false);
    }

    if(ui->collabShowRadio->isChecked()){
        estate.SetCollaboratorBar(true);
    }
    if(ui->collabHideRadio->isChecked()){
        estate.SetCollaboratorBar(false);
    }

    /*****************************/
    //      Barra del titolo     //
    /*****************************/
    if(ui->titleRadio1->isChecked()){
        estate.SetTitlebar(1);
    }
    if(ui->titleRadio2->isChecked()){
        estate.SetTitlebar(2);
    }
    if(ui->titleRadio3->isChecked()){
        estate.SetTitlebar(3);
    }
    if(ui->titleRadio4->isChecked()){
        estate.SetTitlebar(4);
    }


    /*****************************/
    //            Temi           //
    /*****************************/
    if(ui->dayTheme1->isChecked()){
        estate.SetThemeDay(1);
    }
    if(ui->dayTheme2->isChecked()){
        estate.SetThemeDay(2);
    }
    if(ui->dayTheme3->isChecked()){
        estate.SetThemeDay(3);
    }
    if(ui->darkTheme1->isChecked()){
        estate.SetThemeDark(1);
    }
    if(ui->darkTheme2->isChecked()){
        estate.SetThemeDark(2);
    }
    if(ui->darkTheme3->isChecked()){
        estate.SetThemeDark(3);
    }
    WriteSettingOnFile();
}

void Settings::WriteSettingOnFile(){
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "C.A.R.T.E. Studio", "C.A.R.T.E.");
    settings.beginGroup("Start");
    settings.setValue("darkmode", estate.GetDarkMode());
    settings.setValue("collaboratorbar", estate.GetCollaboratorBar());
    settings.setValue("toolbar", estate.GetToolbar());
    settings.endGroup();

    settings.beginGroup("Titlebar");
    settings.setValue("titlebar", estate.GetTitlebar());
    settings.endGroup();

    settings.beginGroup("Theme");
    settings.setValue("dayTheme", estate.GetThemeDay());
    settings.setValue("darkTheme", estate.GetThemeDark());
    settings.endGroup();
}


void Settings::on_Default_clicked(){
     estate.SetDarkMode(false);
     estate.SetToolbar(true);
     estate.SetCollaboratorBar(true);
     estate.SetTitlebar(2);
     estate.SetThemeDay(1);
     estate.SetThemeDark(1);

     WriteSettingOnFile();
}

#include "settings.h"
#include "ui_settings.h"
#include "editorwindow.h"
#include <QSettings>

Settings::Settings(EditorState &estate, QWidget *parent): QWidget(parent), ui(new Ui::Settings), estate(estate){
    ui->setupUi(this);

    LoadAndSetDefaultRadioButton();

}

Settings::~Settings(){
    delete ui;
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
    if(ui->titleRadio5->isChecked()){
        estate.SetTitlebar(5);
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

    QWidget::close();
    delete this;   //Very important, is needed for calling the destructor
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
     estate.SetDarkMode(false);             ui->dayRadio->setChecked(true);
     estate.SetToolbar(true);               ui->toolShowRadio->setChecked(true);
     estate.SetCollaboratorBar(true);       ui->collabShowRadio->setChecked(true);
     estate.SetTitlebar(1);                 ui->titleRadio1->setChecked(true);
     estate.SetThemeDay(1);                 ui->dayTheme1->setChecked(true);
     estate.SetThemeDark(1);                ui->darkTheme1->setChecked(true);

     WriteSettingOnFile();
}

void Settings::on_Abort_clicked(){
    QWidget::close();
    delete this;   //Very important, is needed for calling the destructor
}

void Settings::LoadAndSetDefaultRadioButton(){
    bool darkmodeD = estate.GetDarkMode();
    if(darkmodeD==true){
        ui->darkRadio->setChecked(true);
    }else{
        ui->dayRadio->setChecked(true);
    }

    bool toolbarD = estate.GetToolbar();
    if(toolbarD==false){
        ui->toolHideRadio->setChecked(true);
    }else{
        ui->toolShowRadio->setChecked(true);
    }

    bool collabD = estate.GetCollaboratorBar();
    if(collabD==false){
        ui->collabHideRadio->setChecked(true);
    }else{
        ui->collabShowRadio->setChecked(true);
    }

    int titleD = estate.GetTitlebar();
    if(titleD==1){
        ui->titleRadio1->setChecked(true);
    }else if(titleD==2){
        ui->titleRadio2->setChecked(true);
    }else if(titleD==3){
        ui->titleRadio3->setChecked(true);
    }else if(titleD==4){
        ui->titleRadio4->setChecked(true);
    }else if(titleD==5){
        ui->titleRadio5->setChecked(true);
    }

    int themedayD = estate.GetThemeDay();
    if(themedayD==1){
        ui->dayTheme1->setChecked(true);
    }else if(themedayD==2){
        ui->dayTheme2->setChecked(true);
    }else if(themedayD==3){
        ui->dayTheme3->setChecked(true);
    }

    int themedarkD = estate.GetThemeDark();
    if(themedarkD==1){
        ui->darkTheme1->setChecked(true);
    }else if(themedayD==2){
        ui->darkTheme2->setChecked(true);
    }else if(themedayD==3){
        ui->darkTheme3->setChecked(true);
    }
}

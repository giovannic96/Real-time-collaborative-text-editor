#include "settings.h"
#include "ui_settings.h"
#include "editorwindow.h"
#include <QSettings>
#include <QMovie>

Settings::Settings(EditorState &estate, QWidget *parent): QWidget(parent), ui(new Ui::Settings), estate(estate){
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose, true); //Call the constructor when Windows close this.

    LoadAndSetDefaultRadioButton();

    Settings::on_ComboDark_currentIndexChanged(ui->ComboDark->currentIndex());
    Settings::on_ComboDay_currentIndexChanged(ui->ComboDay->currentIndex());

    QMovie *movie = new QMovie(":/image/Settings/alternatoCarteDoc.gif");
    ui->PreviewBar_4->setMovie(movie);
    QMovie *movie2 = new QMovie(":/image/Settings/animatoCarte.gif");
    ui->PreviewBar_5->setMovie(movie2);
    movie->start();
    movie2->start();

}

Settings::~Settings(){
    emit closeSettings();
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
    int dayThemeIndex = ui->ComboDay->currentIndex();
    int darkThemeIndex = ui->ComboDark->currentIndex();

    if(dayThemeIndex==0){
        estate.SetThemeDay(1);
    }
    if(dayThemeIndex==1){
        estate.SetThemeDay(2);
    }
    if(dayThemeIndex==2){
        estate.SetThemeDay(3);
    }
    if(dayThemeIndex==3){
        estate.SetThemeDay(4);
    }
    if(dayThemeIndex==4){
        estate.SetThemeDay(5);
    }
    if(dayThemeIndex==5){
        estate.SetThemeDay(6);
    }
    if(dayThemeIndex==6){
        estate.SetThemeDay(7);
    }
    if(dayThemeIndex==7){
        estate.SetThemeDay(8);
    }
    if(dayThemeIndex==8){
        estate.SetThemeDay(9);
    }
    if(dayThemeIndex==9){
        estate.SetThemeDay(10);
    }
    if(dayThemeIndex==10){
        estate.SetThemeDay(11);
    }

    if(darkThemeIndex==0){
        estate.SetThemeDark(1);
    }
    if(darkThemeIndex==1){
        estate.SetThemeDark(2);
    }
    if(darkThemeIndex==2){
        estate.SetThemeDark(3);
    }
    if(darkThemeIndex==3){
        estate.SetThemeDark(4);
    }
    if(darkThemeIndex==4){
        estate.SetThemeDark(5);
    }
    if(darkThemeIndex==5){
        estate.SetThemeDark(6);
    }
    if(darkThemeIndex==6){
        estate.SetThemeDark(7);
    }
    if(darkThemeIndex==7){
        estate.SetThemeDark(8);
    }
    if(darkThemeIndex==8){
        estate.SetThemeDark(9);
    }
    if(darkThemeIndex==9){
        estate.SetThemeDark(10);
    }
    if(darkThemeIndex==10){
        estate.SetThemeDark(11);
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
     estate.SetThemeDay(1);                 ui->ComboDay->setCurrentIndex(0);
     estate.SetThemeDark(1);                ui->ComboDark->setCurrentIndex(0);

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
        ui->ComboDay->setCurrentIndex(0);
    }else if(themedayD==2){
        ui->ComboDay->setCurrentIndex(1);
    }else if(themedayD==3){
        ui->ComboDay->setCurrentIndex(2);
    }else if(themedayD==4){
        ui->ComboDay->setCurrentIndex(3);
    }else if(themedayD==5){
        ui->ComboDay->setCurrentIndex(4);
    }else if(themedayD==6){
        ui->ComboDay->setCurrentIndex(5);
    }else if(themedayD==7){
        ui->ComboDay->setCurrentIndex(6);
    }else if(themedayD==8){
        ui->ComboDay->setCurrentIndex(7);
    }else if(themedayD==9){
        ui->ComboDay->setCurrentIndex(8);
    }else if(themedayD==10){
        ui->ComboDay->setCurrentIndex(9);
    }else if(themedayD==11){
        ui->ComboDay->setCurrentIndex(10);
    }


    int themedarkD = estate.GetThemeDark();
    if(themedarkD==1){
        ui->ComboDark->setCurrentIndex(0);
    }else if(themedarkD==2){
        ui->ComboDark->setCurrentIndex(1);
    }else if(themedarkD==3){
        ui->ComboDark->setCurrentIndex(2);
    }else if(themedarkD==4){
        ui->ComboDark->setCurrentIndex(3);
    }else if(themedarkD==5){
        ui->ComboDark->setCurrentIndex(4);
    }else if(themedarkD==6){
        ui->ComboDark->setCurrentIndex(5);
    }else if(themedarkD==7){
        ui->ComboDark->setCurrentIndex(6);
    }else if(themedarkD==8){
        ui->ComboDark->setCurrentIndex(7);
    }else if(themedarkD==9){
        ui->ComboDark->setCurrentIndex(8);
    }else if(themedarkD==10){
        ui->ComboDark->setCurrentIndex(9);
    }else if(themedarkD==11){
        ui->ComboDark->setCurrentIndex(10);
    }
}

void Settings::on_ComboDay_currentIndexChanged(int index)
{
    int dayThemeIndex = ui->ComboDay->currentIndex();

    if(dayThemeIndex==0){
        ui->PreviewThemeDay->setStyleSheet("#PreviewThemeDay{\n	background:url(:/image/Settings/dayClassicBlue.png);\n}");
    }
    if(dayThemeIndex==1){
        ui->PreviewThemeDay->setStyleSheet("#PreviewThemeDay{\n	background:url(:/image/Settings/dayPlainBlue.png);\n}");
    }
    if(dayThemeIndex==2){
        ui->PreviewThemeDay->setStyleSheet("#PreviewThemeDay{\n	background:url(:/image/Settings/dayElectricBlue.png);\n}");
    }
    if(dayThemeIndex==3){
        ui->PreviewThemeDay->setStyleSheet("#PreviewThemeDay{\n	background:url(:/image/Settings/dayClassicPurple.png);\n}");
    }
    if(dayThemeIndex==4){
        ui->PreviewThemeDay->setStyleSheet("#PreviewThemeDay{\n	background:url(:/image/Settings/dayClassicOrange.png);\n}");
    }
    if(dayThemeIndex==5){
        ui->PreviewThemeDay->setStyleSheet("#PreviewThemeDay{\n	background:url(:/image/Settings/dayClassicGreen.png);\n}");
    }
    if(dayThemeIndex==6){
        ui->PreviewThemeDay->setStyleSheet("#PreviewThemeDay{\n	background:url(:/image/Settings/dayClassicRed.png);\n}");
    }
    if(dayThemeIndex==7){
        ui->PreviewThemeDay->setStyleSheet("#PreviewThemeDay{\n	background:url(:/image/Settings/dayFantasy.png);\n}");
    }
    if(dayThemeIndex==8){
        ui->PreviewThemeDay->setStyleSheet("#PreviewThemeDay{\n	background:url(:/image/Settings/dayRainbow.png);\n}");
    }
    if(dayThemeIndex==9){
        ui->PreviewThemeDay->setStyleSheet("#PreviewThemeDay{\n	background:url(:/image/Settings/dayPolito.png);\n}");
    }
    if(dayThemeIndex==10){
        ui->PreviewThemeDay->setStyleSheet("#PreviewThemeDay{\n	background:url(:/image/Settings/daySpecial.png);\n}");
    }
}

void Settings::on_ComboDark_currentIndexChanged(int index)
{
    int darkThemeIndex = ui->ComboDark->currentIndex();

    if(darkThemeIndex==0){
        ui->PreviewThemeDark->setStyleSheet("#PreviewThemeDark{\n	background:url(:/image/Settings/darkClassicOrange.png);\n}");
    }
    if(darkThemeIndex==1){
        ui->PreviewThemeDark->setStyleSheet("#PreviewThemeDark{\n	background:url(:/image/Settings/darkPlainOrange.png);\n}");
    }
    if(darkThemeIndex==2){
        ui->PreviewThemeDark->setStyleSheet("#PreviewThemeDark{\n	background:url(:/image/Settings/darkElectricOrange.png);\n}");
    }
    if(darkThemeIndex==3){
        ui->PreviewThemeDark->setStyleSheet("#PreviewThemeDark{\n	background:url(:/image/Settings/darkClassicPurple.png);\n}");
    }
    if(darkThemeIndex==4){
        ui->PreviewThemeDark->setStyleSheet("#PreviewThemeDark{\n	background:url(:/image/Settings/darkClassicBlue.png);\n}");
    }
    if(darkThemeIndex==5){
        ui->PreviewThemeDark->setStyleSheet("#PreviewThemeDark{\n	background:url(:/image/Settings/darkClassicGreen.png);\n}");
    }
    if(darkThemeIndex==6){
        ui->PreviewThemeDark->setStyleSheet("#PreviewThemeDark{\n	background:url(:/image/Settings/darkClassicRed.png);\n}");
    }
    if(darkThemeIndex==7){
        ui->PreviewThemeDark->setStyleSheet("#PreviewThemeDark{\n	background:url(:/image/Settings/darkFantasy.png);\n}");
    }
    if(darkThemeIndex==8){
        ui->PreviewThemeDark->setStyleSheet("#PreviewThemeDark{\n	background:url(:/image/Settings/darkRainbow.png);\n}");
    }
    if(darkThemeIndex==9){
        ui->PreviewThemeDark->setStyleSheet("#PreviewThemeDark{\n	background:url(:/image/Settings/darkPolito.png);\n}");
    }
    if(darkThemeIndex==10){
        ui->PreviewThemeDark->setStyleSheet("#PreviewThemeDark{\n	background:url(:/image/Settings/darkSpecial.png);\n}");

    }
}

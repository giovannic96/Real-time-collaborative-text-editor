#include "debugroom.h"
#include "ui_debugroom.h"
#include "startwindow.h"
#include "menuwindow.h"
#include "userprofile.h"
#include "editorwindow.h"

DebugRoom::DebugRoom(QWidget *parent): QMainWindow(parent), ui(new Ui::DebugRoom){
    ui->setupUi(this);
}

DebugRoom::~DebugRoom(){
    delete ui;
}

void DebugRoom::on_StartButton_clicked(){
    StartWindow *w=new StartWindow();
    w->show();
}

void DebugRoom::on_UserProfileButton_clicked(){
    UserProfile *up = new UserProfile("Superior Administrator"); //with parameters //TODO --> The parameter will become the "username" of who are logged into the system.
    up->show();
}

void DebugRoom::on_EditorButton_clicked(){
    EditorWindow *ew = new EditorWindow("NoTextForDebug");
    ew->show();
}

void DebugRoom::on_MenuWindowButton_clicked(){
    MenuWindow *mw=new MenuWindow();
    mw->show();
}

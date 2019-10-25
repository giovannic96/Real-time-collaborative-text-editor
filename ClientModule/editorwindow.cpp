#include "editorwindow.h"
#include "ui_editorwindow.h"
#include <QInputDialog>
#include <QLineEdit>
#include <QMessageBox>

EditorWindow::EditorWindow(QString text, QWidget *parent): QMainWindow(parent),  ui(new Ui::EditorWindow), textname(text){
    ui->setupUi(this);
    ui->DocName->setText(text);
    Grassetto = false;
}

EditorWindow::~EditorWindow(){
    delete ui;
}

//FUNZIONE WORK-IN-PROGRESS DA GESTIRE MEGLIO, TODO PERCHé é UN CASINO!
void EditorWindow::on_pushButton_3_clicked(){
    bool ok;
        QString newText = QInputDialog::getText(this, tr("Titolo documento"),
                                             tr("Inserisci un nome per il documento:"), QLineEdit::Normal,
                                             textname, &ok);
        if (ok && !newText.isEmpty() && newText.size()<=15){
            //TODO controllo file database (nome e utente)
            //TODO Inserire il file nel database
            //TODO aprire il file nell'editor

            EditorWindow *ew = new EditorWindow(newText);
            ew->show();
            delete this;
        }
        else if (ok && !newText.isEmpty() && newText.size()>15){
            QMessageBox messageBox;
            messageBox.critical(nullptr,"Errore","Inserire un nome minore di 15 caratteri!");
            messageBox.setFixedSize(600,400);
            on_pushButton_3_clicked();
        }
        else if (ok && newText.isEmpty()){
            QMessageBox messageBox;
            messageBox.critical(nullptr,"Errore","Inserire un nome!");
            messageBox.setFixedSize(600,400);
            on_pushButton_3_clicked();
        }
        //AT THE END

}

//FUNCTION GRASSETTO --> Make Bold inside text area
void EditorWindow::on_Grassetto_clicked(){
    QTextCharFormat formato{};
    if(Grassetto==false){
        formato.setFontWeight(QFont::Bold);
        Grassetto=true;
    }else{
         formato.setFontWeight(QFont::Thin);
         Grassetto=false;
    }
    ui->RealTextEdit->setCurrentCharFormat(formato);
}

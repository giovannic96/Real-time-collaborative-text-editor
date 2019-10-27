#include "editorwindow.h"
#include "ui_editorwindow.h"
#include <QInputDialog>
#include <QLineEdit>
#include <QColorDialog>
#include <QMessageBox>

EditorWindow::EditorWindow(QString text, QWidget *parent): QMainWindow(parent), ui(new Ui::EditorWindow), textname(text){
    ui->setupUi(this);
    ui->DocName->setText(text);
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
void EditorWindow::on_buttonGrassetto_clicked(){
    QTextCharFormat formato{};
    if(ui->buttonGrassetto->isChecked()){
        formato.setFontWeight(QFont::Bold);
        ui->buttonGrassetto->setCheckable(false);
    }else{
         formato.setFontWeight(QFont::Thin);
          ui->buttonGrassetto->setCheckable(true);
    }
    ui->RealTextEdit->setCurrentCharFormat(formato);
}

void EditorWindow::on_buttonCorsivo_clicked(){
    QTextCharFormat formato{};
    if(ui->buttonCorsivo->isChecked()){
        formato.setFontItalic(QFont::StyleItalic);
        ui->buttonCorsivo->setCheckable(false);
    }else{
         formato.setFontItalic(QFont::StyleNormal);
          ui->buttonCorsivo->setCheckable(true);
    }
    ui->RealTextEdit->setCurrentCharFormat(formato);
}

void EditorWindow::on_buttonSottolineato_clicked(){

}

void EditorWindow::on_buttonAlignDX_clicked(){
    ui->RealTextEdit->setAlignment(Qt::AlignRight);
}

void EditorWindow::on_buttonAlignCX_clicked(){
    ui->RealTextEdit->setAlignment(Qt::AlignCenter);
}

void EditorWindow::on_buttonAlignSX_clicked(){
    ui->RealTextEdit->setAlignment(Qt::AlignLeft);
}

void EditorWindow::on_buttonUndo_clicked(){
    ui->RealTextEdit->undo();
}

void EditorWindow::on_buttonRedo_clicked(){
    ui->RealTextEdit->redo();
}

void EditorWindow::on_buttonTaglia_clicked(){
    ui->RealTextEdit->cut();
}

void EditorWindow::on_buttonIncolla_clicked(){
    ui->RealTextEdit->paste();
}

void EditorWindow::on_buttonCopia_clicked(){
    ui->RealTextEdit->copy();
}

void EditorWindow::on_buttonColor_clicked(){
    QColor txtColour = QColorDialog::getColor();
    ui->RealTextEdit->setTextColor(txtColour);
}

#include "editorwindow.h"
#include "ui_editorwindow.h"
#include <QInputDialog>
#include <QLineEdit>
#include <QColorDialog>     //FOR OPEN COLOR PALETTE
#include <QFileDialog>      //FOR OPEN SAVE WITH NAME LOCALLY
#include <QTextStream>      //FOR SAVE THE FILE LOCALLY AND PDF CONVERSION
#include <QMessageBox>
#include <QPrinter>

//CONSTRUCTOR
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

void EditorWindow::on_actionSave_triggered()
{
    QString pathname;

    //GIOVANNI SO CHE HAI VOGLIA DI MODIFICARLA, SE VUOI OK, MA VORREI FARLO IO ;)

    QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Esporta come PDF", QString(), "*.pdf");
    if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }
    //QString fileName = QFileDialog::getSaveFileName(this,"Salva il file in locale");
       QFile File (fileName);
       pathname = fileName;
       if(!File.open(QFile::WriteOnly | QFile::Text)){
          //Return if the user cancels or does something unexpected!
          //I Don't like it, I suggest to change it with a try-catch statement
           return;
        }
        else{
          //Read the file
          QTextStream writeData(&File);
          QString fileText = ui->RealTextEdit->toHtml(); //HTML NO PLAINTEXT (DEVO PROVARE IO CON PLAINTEXT MA NON TOCCATE!!!!!!!)

          QTextDocument doc;
          doc.setHtml(fileText);
          QPrinter file;
          file.setOutputFormat(QPrinter::PdfFormat);
          file.setOutputFileName("myfile.pdf"); // better to use full path //GIOVANNI MODIFICO IO
          doc.print(&file); //REFERENCE DO NOT TOUCH IT FUNZIONA!

          writeData << &file; //like CIN, but in a stream of text
          File.flush();
          File.close();
        }
}

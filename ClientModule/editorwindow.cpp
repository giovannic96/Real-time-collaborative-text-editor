#include "editorwindow.h"
#include "ui_editorwindow.h"
#include <QInputDialog>
#include <QLineEdit>
#include <QColorDialog>     //FOR OPEN COLOR PALETTE
#include <QFileDialog>      //FOR OPEN SAVE WITH NAME LOCALLY
#include <QTextStream>      //FOR SAVE THE FILE LOCALLY AND PDF CONVERSION
#include <QMessageBox>
#include <QPrinter>         //FOR PRINTING THE PDF
#include "infowindow.h"

//CONSTRUCTOR
EditorWindow::EditorWindow(QString text, QWidget *parent): QMainWindow(parent, Qt::FramelessWindowHint | Qt::WindowSystemMenuHint), ui(new Ui::EditorWindow), textname(text){
    ui->setupUi(this);
    ui->DocName->setText(text);
}

//DESTRUCTOR
EditorWindow::~EditorWindow(){
    delete ui;
}

//BUTTON FOR CHANGE TYPE OF TEXT
void EditorWindow::on_buttonGrassetto_clicked(){
    if(ui->buttonGrassetto->isChecked()){
        ui->RealTextEdit->setFontWeight(QFont::Bold);
    }else{
         ui->RealTextEdit->setFontWeight(QFont::Light);
         ui->buttonGrassetto->setCheckable(true);
    }
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}

void EditorWindow::on_buttonCorsivo_clicked(){
    if(ui->buttonCorsivo->isChecked()){
        ui->RealTextEdit->setFontItalic(true);
    }else{
         ui->RealTextEdit->setFontItalic(false);
         ui->buttonCorsivo->setCheckable(true);
    }
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}

void EditorWindow::on_buttonSottolineato_clicked(){
    if(ui->buttonSottolineato->isChecked()){
        ui->RealTextEdit->setFontUnderline(true);
    }else{
         ui->RealTextEdit->setFontUnderline(false);
         ui->buttonSottolineato->setCheckable(true);
    }
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}

//BUTTON FOR CHANGE COLOUR OF TEXT
void EditorWindow::on_buttonEvidenziato_clicked(){
    QColor backColour = QColorDialog::getColor();
    ui->RealTextEdit->setTextBackgroundColor(backColour);
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}

void EditorWindow::on_buttonColor_clicked(){
    QColor txtColour = QColorDialog::getColor();
    ui->RealTextEdit->setTextColor(txtColour);
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}


//BUTTON FOR ALIGN THE TEXT
void EditorWindow::on_buttonAlignDX_clicked(){
    ui->RealTextEdit->setAlignment(Qt::AlignRight);
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}

void EditorWindow::on_buttonAlignCX_clicked(){
    ui->RealTextEdit->setAlignment(Qt::AlignCenter);
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}

void EditorWindow::on_buttonAlignSX_clicked(){
    ui->RealTextEdit->setAlignment(Qt::AlignLeft);
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}

//TODO JUSTIFY


//BUTTON FOR UNDO AND REDO
void EditorWindow::on_buttonUndo_clicked(){
    ui->RealTextEdit->undo();
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}

void EditorWindow::on_buttonRedo_clicked(){
    ui->RealTextEdit->redo();
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}


//BUTTON FOR CUT-COPY-PASTE
void EditorWindow::on_buttonTaglia_clicked(){
    ui->RealTextEdit->cut();
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}

void EditorWindow::on_buttonIncolla_clicked(){
    ui->RealTextEdit->paste();
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}

void EditorWindow::on_buttonCopia_clicked(){
    ui->RealTextEdit->copy();
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}


//FUNCTION FOR EXPORT TEXT INTO PDF
void EditorWindow::on_actionSave_triggered(){
    QString pathname;
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
          file.setOutputFileName(textname+".pdf"); // better to use full path //GIOVANNI MODIFICO IO
          doc.print(&file); //REFERENCE DO NOT TOUCH IT FUNZIONA!

          writeData << &file; //like CIN, but in a stream of text
          File.flush();
          File.close();
        }
}

//EXIT BUTTON
void EditorWindow::on_buttonExit_clicked(){
    QApplication::exit();   //I've used exit() instead quit() or close() for this reason --> https://ux.stackexchange.com/questions/50893/do-we-exit-quit-or-close-an-application
}

//ACTION TO QUIT THE PROGRAM BY MENù
void EditorWindow::on_actionChiudi_triggered(){
    QApplication::quit();   //I've used quit() instead exit() or close() for this reason --> https://ux.stackexchange.com/questions/50893/do-we-exit-quit-or-close-an-application

}

/*RENAME BUTTON v1 - "DEPRECATED FUNCTION --> SEE RENAME BUTTON v2"
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
*/

//RENAME BUTTON v2 - TODO APPLY CONTROL LIKE RENAME BUTTON v1
void EditorWindow::on_renameButton_clicked(){
    QString newText = QInputDialog::getText(this, tr("Titolo documento"),
                                         tr("Inserisci un nome per il documento:"), QLineEdit::Normal,
                                         textname);
    ui->DocName->setText(newText);
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}

//BUTTON TO ICON
void EditorWindow::on_buttonToIcon_clicked(){
    this->setWindowState(Qt::WindowMinimized); //See Note 2 at the end
}

//BUTTON REDUCE
void EditorWindow::on_buttonReduce_clicked(){
    if(ui->buttonReduce->isChecked()){
        this->setWindowState(Qt::WindowMaximized);
    }else{
        this->setWindowState(Qt::WindowNoState); //See Note 1 at the end
        ui->buttonReduce->setCheckable(true);
    }
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}

//FULLSCREEN ACTION
void EditorWindow::on_actionFullscreen_triggered(){
    if(ui->actionFullscreen->isChecked()){
        this->setWindowState(Qt::WindowFullScreen);
    }else{
        this->setWindowState(Qt::WindowNoState); //See Note 1 at the end
        ui->actionFullscreen->setCheckable(true);
    }
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}


/*
Note 1:
WindowNoState save automatically old position and size of the window.
There's no need to use function like size(), resize(), pos() and move() because they needed more code, more global variable, ecc...
It drive me crazy for implement that thing, and in the end is really easy...

Note 2:
this->parentWidget()->setWindowState(Qt::WindowMinimized); <-- This isn't working
this->setWindowState(Qt::WindowMinimized);                 <-- That work!
We can't follow the pointer in parentWidget(). I have to understand why.
*/

void EditorWindow::on_actionAbout_triggered(){
    infoWindow *iw = new infoWindow();
    iw->show();
}


void EditorWindow::on_fontDimensionBox_activated(int index){
    switch(index){
    case 0:
        ui->RealTextEdit->setFontPointSize(2);
        break;
    case 1:
        ui->RealTextEdit->setFontPointSize(4);
        break;
    case 2:
        ui->RealTextEdit->setFontPointSize(6);
        break;
    case 3:
        ui->RealTextEdit->setFontPointSize(8);
        break;
    case 4:
        ui->RealTextEdit->setFontPointSize(10);
        break;
    case 5:
        ui->RealTextEdit->setFontPointSize(12);
        break;
    case 6:
        ui->RealTextEdit->setFontPointSize(14);
        break;
    case 7:
        ui->RealTextEdit->setFontPointSize(16);
        break;
    case 8:
        ui->RealTextEdit->setFontPointSize(18);
        break;
    case 9:
        ui->RealTextEdit->setFontPointSize(20);
        break;
    case 10:
        ui->RealTextEdit->setFontPointSize(22);
        break;
    case 11:
        ui->RealTextEdit->setFontPointSize(24);
        break;
    case 12:
        ui->RealTextEdit->setFontPointSize(28);
        break;
    case 13:
        ui->RealTextEdit->setFontPointSize(32);
        break;
    case 14:
        ui->RealTextEdit->setFontPointSize(48);
        break;
    case 15:
        ui->RealTextEdit->setFontPointSize(32);
        break;
    default:
        QMessageBox msgBox;
        msgBox.setText("Come sei riuscito a leggere questo errore?\nContattami perchè dovrò implementare un try-catch!");
        msgBox.exec();
        break;
    }
    ui->RealTextEdit->setFocus();
}

//TODO: Find a way to restore Bold, Italic, Sub, Color and Background of text
//TODO 2: Watch the situation of have a text made of different dimension, what's happend??
void EditorWindow::on_fontSelectorBox_currentFontChanged(const QFont &f){
    QTextCursor c = ui->RealTextEdit->textCursor();
    double a = ui->RealTextEdit->fontPointSize(); //save the previous dimension of the font
    if(c.hasSelection()){
        QTextCharFormat format;
        format.setFont(f);
        c.setCharFormat(format);
        ui->RealTextEdit->setFontPointSize(a);     //restore the previous dimension of the font
    }
    ui->RealTextEdit->setFocus();
}

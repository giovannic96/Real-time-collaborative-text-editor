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
#include "menuwindow.h"

using json = nlohmann::json;

//CONSTRUCTOR
EditorWindow::EditorWindow(myClient* client, QWidget *parent): QMainWindow(parent, Qt::CustomizeWindowHint), ui(new Ui::EditorWindow), _client(client) {
    ui->setupUi(this);
    connect(_client, &myClient::editorResultSuccess, this, &EditorWindow::showPopupSuccess);
    connect(_client, &myClient::editorResultFailure, this, &EditorWindow::showPopupFailure);
    ui->DocName->setText(_client->getFilename());
    ui->RealTextEdit->setFontPointSize(14);         //Force the TextEdit to have a value for the FontPointSize. Is necessary for get the default parameter of Point Size.
    QColor a = QColor(255,255,255,255);             //R, G, B, Alpha
    ui->RealTextEdit->setTextBackgroundColor(a);    //Force the TextEdit to have this color of background.
    ui->DebugFrame->setVisible(false);      //DELETE ME IN THE END
    ui->FileFrame->setVisible(false);       //DELETE ME IN THE END
}

//DESTRUCTOR
EditorWindow::~EditorWindow() {
    delete ui;
    //TODO: do I have to delete also client????
}


/***********************************************************************************
*                       BUTTON FOR CHANGE STYLE OF THE TEXT                        *
************************************************************************************/
void EditorWindow::on_buttonGrassetto_clicked(){
    if(ui->buttonGrassetto->isChecked()){
        ui->RealTextEdit->setFontWeight(QFont::Light);
    }else{
         ui->RealTextEdit->setFontWeight(QFont::Bold);
         ui->buttonGrassetto->setCheckable(true);
    }
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}

void EditorWindow::on_buttonCorsivo_clicked(){
    if(ui->buttonCorsivo->isChecked()){
        ui->RealTextEdit->setFontItalic(false);
    }else{
         ui->RealTextEdit->setFontItalic(true);
         ui->buttonCorsivo->setCheckable(true);
    }
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}

void EditorWindow::on_buttonSottolineato_clicked(){
    if(ui->buttonSottolineato->isChecked()){
        ui->RealTextEdit->setFontUnderline(false);
    }else{
         ui->RealTextEdit->setFontUnderline(true);
         ui->buttonSottolineato->setCheckable(true);
    }
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}

void EditorWindow::on_buttonBackgroundColor_clicked(){
    QColor backColour = QColorDialog::getColor();
    ui->RealTextEdit->setTextBackgroundColor(backColour);
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}

void EditorWindow::on_buttonColor_clicked(){
    QColor txtColour = QColorDialog::getColor();
    ui->RealTextEdit->setTextColor(txtColour);
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}


/***********************************************************************************
*                            BUTTON FOR ALIGN THE TEXT                             *
************************************************************************************/
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

void EditorWindow::on_buttonAlignJFX_clicked(){
    ui->RealTextEdit->setAlignment(Qt::AlignJustify);
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}

/***********************************************************************************
*                           BUTTON FOR MODIFY THE TEXT                             *
************************************************************************************/
void EditorWindow::on_buttonUndo_clicked(){
    ui->RealTextEdit->undo();
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}

void EditorWindow::on_buttonRedo_clicked(){
    ui->RealTextEdit->redo();
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}

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


/***********************************************************************************
*                  BUTTON FOR MODIFY FONT AND SIZE OF THE TEXT                     *
************************************************************************************/
void EditorWindow::on_fontDimensionBox_activated(int index){

    auto lambda1 = [] (int index) {return (index*2)+2;}; //Lambda Function
    //index 0 = 2, index 1 = 4, index 2 = 6, index 3 = 8...

    if (index<=11){
        ui->RealTextEdit->setFontPointSize(lambda1(index));
    }else{
        //After index 11, the formula applied in the lambda function is not respected anymore
        switch(index){
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
                ui->RealTextEdit->setFontPointSize(72);
                break;
            default:
                QMessageBox msgBox;
                msgBox.setText("Come sei riuscito a leggere questo errore?\nContattami perchè dovrò implementare un try-catch!");
                msgBox.exec();
                break;
        }
    }
    ui->RealTextEdit->setFocus();   //Return focus to textedit
}

//TODO 3: Watch the situation of have a text made of different dimension, what's happend??
void EditorWindow::on_fontSelectorBox_currentFontChanged(const QFont &f){

    double fontPointSize;
    bool bold = false;
    bool italic = false;
    bool underl = false;
    QColor textcolor;
    QColor backcolor;

    //CATCH CURSOR
    QTextCursor c = ui->RealTextEdit->textCursor();

    //SAVE PREVIOUS PROPRIETY OF TEXT
    fontPointSize = ui->RealTextEdit->fontPointSize();
    textcolor = ui->RealTextEdit->textColor();
    backcolor = ui->RealTextEdit->textBackgroundColor();
    if(ui->RealTextEdit->fontWeight()>50){
        bold=true;
    }
    if(ui->RealTextEdit->fontItalic()){
        italic = true;
    }
    if(ui->RealTextEdit->fontUnderline()){
        underl = true;
    }

    //CHANGE FONT
    if(c.hasSelection()){
        QTextCharFormat format;
        format.setFont(f);
        c.setCharFormat(format);
    }else{
        //I had to change the next text font
        //TODO --> EDIT THIS PART OF THIS FUNCTION BECAUSE IT'S BUGGED
               QTextCursor c = ui->RealTextEdit->textCursor();
               c.insertText(" ");
               c.movePosition(QTextCursor::PreviousCharacter,QTextCursor::KeepAnchor,1);
               QTextCharFormat format;
               format.setFont(f);
               c.setCharFormat(format);
               c.movePosition(QTextCursor::PreviousCharacter,QTextCursor::MoveAnchor,1);
               //c.deleteChar();
    }

    //RESTORE PREVIOUS PROPRIETY OF TEXT
    ui->RealTextEdit->setFontPointSize(fontPointSize);
    ui->RealTextEdit->setTextColor(textcolor);
    ui->RealTextEdit->setTextBackgroundColor(backcolor);
    if(bold==true){
        ui->RealTextEdit->setFontWeight(QFont::Bold);
    }
    if(italic==true){
        ui->RealTextEdit->setFontItalic(true);
    }
    if(underl==true){
        ui->RealTextEdit->setFontUnderline(true);
    }

    //AT THE END
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}

/***********************************************************************************
*                              RealTextEdit FUNCTION                               *
************************************************************************************/
//TEMP FUNCTION --> Is a Working in Progress function that change the text into Combobox, depending on the cursor position
void EditorWindow::on_RealTextEdit_cursorPositionChanged(){
    //QTextCursor c = ui->RealTextEdit->textCursor();
    double fontPointSize = ui->RealTextEdit->fontPointSize();
    qDebug() << "La dimensione del font è "<<fontPointSize;
    QString textFontPointSize = QString::number(fontPointSize);
    ui->fontDimensionBox->setItemText(6, textFontPointSize);
}


/***********************************************************************************
*                                TopLeftBar FUNCTION                               *
************************************************************************************/
void EditorWindow::on_buttonExit_clicked() {
    LogoutRequest();  //Return to MenuWindow (close only the current document)
}


void EditorWindow::on_buttonToIcon_clicked() {
    this->setWindowState(Qt::WindowMinimized); //See Note 2 at the end
}

void EditorWindow::on_buttonReduce_clicked(){
    if(ui->buttonReduce->isChecked()){
        this->setWindowState(Qt::WindowMaximized);
    }else{
        this->setWindowState(Qt::WindowNoState); //See Note 1 at the end
        ui->buttonReduce->setCheckable(true);
    }
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}

/***********************************************************************************
*                                TopRightBar FUNCTION                              *
************************************************************************************/
void EditorWindow::on_fileButton_clicked(){
    if(ui->fileButton->isChecked()){
        ui->FileFrame->setVisible(false);
    }else{
         ui->FileFrame->setVisible(true);
         ui->fileButton->setCheckable(true);
    }
}

//FUNCTION FOR EXPORT TEXT INTO PDF
void EditorWindow::on_pdfButton_clicked(){

    /* VERSION 1 - DEPRECATED
    QString pathname;
    //Dont change the follow line even if there is a warning (UNTIL I STUDY SMARTPOINTER)
    QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Esporta come PDF", QString(), "*.pdf");
    if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }
    //QString fileName = QFileDialog::getSaveFileName(this,"Salva il file in locale");
    QFile File (fileName);
    pathname = fileName;
    if(!File.open(QFile::WriteOnly | QFile::Text)){
    //Return if the user cancels or does something unexpected!
    //I Don't like it, I suggest to change it with a try-catch statement?
        return;
    }else{
          //Read the file
          QTextStream writeData(&File);
          QString fileText = ui->RealTextEdit->toHtml(); //HTML NO PLAINTEXT
          QTextDocument doc;
          doc.setHtml(fileText);
          QPrinter file;
          file.setOutputFormat(QPrinter::PdfFormat);
          file.setOutputFileName(_fileName+".pdf"); // better to use full path
          doc.print(&file); //REFERENCE DO NOT TOUCH IT!
          writeData << &file; //like CIN, but in a stream of text
          File.flush();
          File.close();
    }
    */

    //VERSION 2
    QString filename;
    filename = _client->getFilename();
    filename.append(".pdf");

    QFile File (filename);
    if(!File.open(QFile::WriteOnly | QFile::Text)){
    //Return if the user cancels or does something unexpected!
    //I Don't like it, I suggest to change it with a try-catch statement?
        return;
    }else{
        //Read the file
        QTextStream writeData(&File);
        QString fileText = ui->RealTextEdit->toHtml(); //HTML NO PLAINTEXT

        QTextDocument doc;
        doc.setHtml(fileText);
        QPrinter file;
        file.setOutputFormat(QPrinter::PdfFormat);
        file.setOutputFileName(filename); // better to use full path
        doc.print(&file); //REFERENCE DO NOT TOUCH IT!

        writeData << &file; //like CIN, but in a stream of text
        File.flush();
        File.close();

        QMessageBox messageBox;
        messageBox.information(nullptr, filename+" salvato", "Il file "+filename+" è stato salvato!");
        messageBox.setFixedSize(600,400);
        messageBox.show();
    }
}

/* MAYBE WE HAVE TO DELETE THIS
void EditorWindow::on_uriButton_clicked(){
    on_URIButton_clicked(); //See Function Below
}
*/

/***********************************************************************************
*                                 FileFrame FUNCTION                               *
************************************************************************************/
/* MAYBE WE HAVE TO DELETE THIS
void EditorWindow::on_newDocButton_clicked(){
    ui->FileFrame->setVisible(false);
    bool ok;
        QString text = QInputDialog::getText(this, tr("Titolo documento"),
                                             tr("Inserisci un nome per il nuovo documento:"), QLineEdit::Normal,
                                             "", &ok);
        if (ok && !text.isEmpty() && text.size()<=15){
            //TODO controllo file database (nome e utente)

            //Get data from the form
            //QString user = ui->Username->text();
            //QByteArray ba_user = user.toLocal8Bit();
            //const char *c_user = ba_user.data();
            //QString filename = text;
            //QByteArray ba_filename = filename.toLocal8Bit();
            //const char *c_filename = ba_filename.data();
            //Serialize data
            //json j;
            //jsonUtility::to_jsonFilename(j, "NEWFILE_REQUEST", c_user, c_filename);
            //const char* req = j.dump().c_str();
            //Send data (header and body)
            //sendRequestMsg(req);

            //TODO: don't open file right now! First check the NEWFILE_RESPONSE from the server.
            EditorWindow *ew = new EditorWindow(text);
            ew->show();
            delete this;
        }
        else if (ok && !text.isEmpty() && text.size()>15){
            QMessageBox messageBox;
            messageBox.critical(nullptr,"Errore","Inserire un nome minore di 15 caratteri!");
            messageBox.setFixedSize(600,400);
            on_newDocButton_clicked();
        }
        else if (ok && text.isEmpty()){
            QMessageBox messageBox;
            messageBox.critical(nullptr,"Errore","Inserire un nome!");
            messageBox.setFixedSize(600,400);
            on_newDocButton_clicked();
        }

}
*/

/* MAYBE WE HAVE TO DELETE THIS
void EditorWindow::on_URIButton_clicked(){
    ui->FileFrame->setVisible(false);
    bool ok;
        QString text = QInputDialog::getText(this, tr("Sei stato invitato?"),
                                             tr("Inserisci una URI:"), QLineEdit::Normal,
                                             "", &ok);
        if (ok && !text.isEmpty()){

            QMessageBox messageBox;
            messageBox.information(nullptr, "ATTENZIONE", "Ora si chiede troppo (da implementare)");
            messageBox.setFixedSize(600,400);
            messageBox.show();
        }
}
*/

/*RENAME BUTTON v1 - "DEPRECATED FUNCTION --> SEE RENAME BUTTON v2"
void EditorWindow::on_pushButton_3_clicked(){
    bool ok;
        QString newText = QInputDialog::getText(this, tr("Titolo documento"),
                                             tr("Inserisci un nome per il documento:"), QLineEdit::Normal,
                                             _fileName, &ok);
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
void EditorWindow::on_buttonRename_clicked(){
    ui->FileFrame->setVisible(false);
    QString newText = QInputDialog::getText(this, tr("Titolo documento"),
                                         tr("Inserisci un nome per il documento:"), QLineEdit::Normal,
                                         _client->getFilename());
    ui->DocName->setText(newText);  //Assign newText to the label
    _client->setFilename(newText);  //Assign newText to the variable
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}

void EditorWindow::on_aboutButton_clicked(){
    ui->FileFrame->setVisible(false);
    infoWindow *iw = new infoWindow();
    iw->show();
}

void EditorWindow::on_CloseButton_clicked(){
    LogoutRequest();          //Return to MenuWindow (close only the current document)
}


/***********************************************************************************
*                                       ACTION                                     *
*                                                                                  *
*     Action can be recallable with shortcut, but for now it doesn't work          *
************************************************************************************/

void EditorWindow::on_actionSave_triggered(){
    on_pdfButton_clicked();
}

//FULLSCREEN ACTION     -->     CTRL+F11
void EditorWindow::on_actionFullscreen_triggered(){
    if(ui->actionFullscreen->isChecked()){
        this->setWindowState(Qt::WindowFullScreen);
    }else{
        this->setWindowState(Qt::WindowNoState); //WindowNoState save the old position and the old size of the window
        ui->actionFullscreen->setCheckable(true);
    }
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}

//NEW DOCUMENT ACTION   -->     CTRL+N
void EditorWindow::on_actionNew_triggered(){
    //on_newDocButton_clicked();
}

//NEW ABOUT ACTION      -->     CTRL+I
void EditorWindow::on_actionAbout_triggered(){
    on_aboutButton_clicked();
}



/***********************************************************************************
*                                                                                  *
*                              STANDALONE FUNCTION                                 *
*                                                                                  *
************************************************************************************/
void EditorWindow::LogoutRequest(){
    //Get data from the form
    QString user = this->_client->getUsername();
    QByteArray ba_user = user.toLocal8Bit();
    const char *c_user = ba_user.data();
    QString uri = this->_client->getFileURI();
    QByteArray ba_uri = uri.toLocal8Bit();
    const char *c_uri = ba_uri.data();

    //Serialize data
    json j;
    jsonUtility::to_jsonUri(j, "LOGOUTURI_REQUEST", c_user, c_uri);
    const std::string req = j.dump();

    //Send data (header and body)
    sendRequestMsg(req);
}

/***********************************************************************************
*
*   ALL THE FOLLOWING FUNCTION ARE ONLY FOR TEST AND DEBUG
*   ALL THESE FUNCTION MUST BE DELETED BEFORE WE REACH A BETA VERISION
*
*   THIS FUNCTION ARE PLAYNING WITH A CURSOR THAT ISN'T SHARED, BUT WE NEED TO
*   BUILD A CURSOR (An original one, but I would prefer it to be a class that
*   extends the original) SHARED BY ALL THE FUNCTION
*
*   THIS FUNCTION EMULATE THE MESSAGE THAT ARRIVED FROM THE SERVER.
*   THE CURSON ISN'T SHOWN IN THE EDITOR AND WE HAD TO FIND A WAY TO DO IT!
*
*                                                                        HidroSaphire
*
***********************************************************************************/
void EditorWindow::on_buttonDebug_clicked(){
    if(ui->buttonDebug->isChecked()){
        ui->DebugFrame->setVisible(false);
    }else{
         ui->DebugFrame->setVisible(true);
         ui->buttonDebug->setCheckable(true);
    }
}

void EditorWindow::on_DebugIns1_clicked(){
    QTextCursor c = ui->RealTextEdit->textCursor();
    c.setPosition(1);
    c.insertText("Z");
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}

void EditorWindow::on_DebugInsInit_clicked(){
    QTextCursor c = ui->RealTextEdit->textCursor();
    c.setPosition(0);
    c.insertText("A");
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}


void EditorWindow::on_DebugDel1_clicked(){
    QTextCursor c = ui->RealTextEdit->textCursor();
    c.setPosition(1);
    c.deleteChar();
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}

void EditorWindow::on_DebugCursLeft_clicked(){
    QTextCursor c = ui->RealTextEdit->textCursor();
    c.movePosition(QTextCursor::PreviousCharacter,QTextCursor::MoveAnchor,1);
    ui->RealTextEdit->setTextCursor(c);
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}

void EditorWindow::on_DebugCursRight_clicked(){
    QTextCursor c = ui->RealTextEdit->textCursor();
    c.movePosition(QTextCursor::NextCharacter,QTextCursor::MoveAnchor,1);
    ui->RealTextEdit->setTextCursor(c);
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}

void EditorWindow::on_DebugCursLeftAnchor_clicked(){
    QTextCursor c = ui->RealTextEdit->textCursor();
    c.movePosition(QTextCursor::NextCharacter,QTextCursor::KeepAnchor,1);
    ui->RealTextEdit->setTextCursor(c);
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}

void EditorWindow::on_DebugWordLeft_clicked(){
    QTextCursor c = ui->RealTextEdit->textCursor();
    c.movePosition(QTextCursor::WordLeft,QTextCursor::MoveAnchor,1);
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}

void EditorWindow::on_DebugWordRight_clicked(){
    QTextCursor c = ui->RealTextEdit->textCursor();
    c.movePosition(QTextCursor::WordRight,QTextCursor::MoveAnchor,1);
    ui->RealTextEdit->setTextCursor(c);
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}

void EditorWindow::on_DebugIns6Word_clicked(){
    QTextCursor c = ui->RealTextEdit->textCursor();
    c.setPosition(6);
    c.insertText("HidroDebug");
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}

//I WANT TO JOIN THIS FOLLOWING FUNCTION ONLY WITH THE UPPER FRAME OF THE WINDOW
//FUNCTION FOR MAKE DRAGGABLE THE WINDOW
void EditorWindow::mousePressEvent(QMouseEvent *evt){
        oldPos = evt->globalPos();
}

//FUNCTION FOR MAKE DRAGGABLE THE WINDOW
void EditorWindow::mouseMoveEvent(QMouseEvent *evt){
       const QPoint delta = evt->globalPos() - oldPos;
       move(x()+delta.x(), y()+delta.y());
       oldPos = evt->globalPos();
}

void EditorWindow::showPopupSuccess(QString result) {
    if(result == "LOGOUTURI_SUCCESS") {
        QMessageBox messageBox;
        messageBox.information(nullptr, "LOGOUTURI SUCCESS", "Logouturi successfully completed.");
        messageBox.setFixedSize(500,200);
        this->close();
        parentWidget()->show();
        delete this;
    }
}

void EditorWindow::showPopupFailure(QString result) {
    if(result == "LOGOUTURI_FAILURE") {
        QMessageBox messageBox;
        messageBox.critical(nullptr, "LOGOUTURI FAILURE", "Error: Logouturi NOT completed!");
        messageBox.setFixedSize(500,200);
        //Stay in the same window
    } else {
        QMessageBox messageBox;
        messageBox.information(nullptr, "GENERIC FAILURE", "Error: Something went wrong!");
        messageBox.setFixedSize(500,200);
    }
}

void EditorWindow::sendRequestMsg(std::string req) {
    message msg;
    msg.body_length(req.size());
    std::memcpy(msg.body(), req.data(), msg.body_length());
    msg.body()[msg.body_length()] = '\0'; //TODO: do we have to leave it??
    msg.encode_header();
    _client->write(msg);
}

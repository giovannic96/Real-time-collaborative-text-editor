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
#include <QEvent>

using json = nlohmann::json;

//CONSTRUCTOR
EditorWindow::EditorWindow(myClient* client, QWidget *parent):
                        QMainWindow(parent, Qt::CustomizeWindowHint), ui(new Ui::EditorWindow), _client(client) {
    ui->setupUi(this);
    connect(_client, &myClient::editorResultSuccess, this, &EditorWindow::showPopupSuccess);
    connect(_client, &myClient::editorResultFailure, this, &EditorWindow::showPopupFailure);
    connect(_client, &myClient::insertSymbol, this, &EditorWindow::showSymbol);
    connect(_client, &myClient::eraseSymbol, this, &EditorWindow::eraseSymbol);
    connect(_client, &myClient::eraseSymbols, this, &EditorWindow::eraseSymbols);
    ui->DocName->setText(_client->getFilename().toLatin1()); //toLatin1 accept accented char
    ui->RealTextEdit->setFontPointSize(14);
    ui->RealTextEdit->setFontFamily("Times New Roman");
    //ui->RealTextEdit->document()->setDefaultFont(QFont("Times New Roman", 14));
    qRegisterMetaType<std::vector<symbol>>("std::vector<symbol>");
    showSymbols(_client->getVector());
    ui->DebugFrame->setVisible(false);      //DELETE ME IN THE END
    ui->FileFrame->setVisible(false);
    ui->RealTextEdit->installEventFilter(this);
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
        ui->buttonGrassetto->setChecked(true);
        ui->RealTextEdit->setFontWeight(QFont::Bold);
    }else{
        ui->buttonGrassetto->setChecked(false);
        ui->RealTextEdit->setFontWeight(QFont::Light);
    }
    SmokinSexyShowtimeStyleHandler();
    ui->FileFrame->setVisible(false);
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}

void EditorWindow::on_buttonCorsivo_clicked(){
    if(ui->buttonCorsivo->isChecked()){
        ui->buttonCorsivo->setChecked(true);
        ui->RealTextEdit->setFontItalic(true);
    }else{
        ui->buttonCorsivo->setChecked(false);
        ui->RealTextEdit->setFontItalic(false);
    }
    SmokinSexyShowtimeStyleHandler();
    ui->FileFrame->setVisible(false);
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}

void EditorWindow::on_buttonSottolineato_clicked(){
    if(ui->buttonSottolineato->isChecked()){
        ui->buttonSottolineato->setChecked(true);
        ui->RealTextEdit->setFontUnderline(true);
    }else{
        ui->buttonSottolineato->setChecked(false);
        ui->RealTextEdit->setFontUnderline(false);
    }
    SmokinSexyShowtimeStyleHandler();
    ui->FileFrame->setVisible(false);
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}

void EditorWindow::on_buttonBackgroundColor_clicked(){
    //VERSION 1 --> Working only if EditorWindow is build without passing the parent (2° argument)
        /*
        QColor backColour = QColorDialog::getColor();
        ui->RealTextEdit->setTextBackgroundColor(backColour);
        */
    //VERSION 2 --> Working if EditorWindow is build passing menuWindow as a parent (2° argument)
        QColorDialog *dialog = new QColorDialog(this); //passing this is important for returning
        dialog->show();
        QObject::connect(dialog,&QDialog::accepted,[=](){
            QColor txtColour = dialog->currentColor();
            ui->RealTextEdit->setTextBackgroundColor(txtColour);
        });
    //SAME FOR v1 AND v2
    ui->FileFrame->setVisible(false);
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}


void EditorWindow::on_buttonColor_clicked(){
    //VERSION 1 --> Working only if EditorWindow is build without passing the parent (2° argument)
    /*
        QColor txtColour = QColorDialog::getColor();
        ui->RealTextEdit->setTextColor(txtColour);
    */
    //VERSION 2 --> Working if EditorWindow is build passing menuWindow as a parent (2° argument)
        QColorDialog *dialog = new QColorDialog(this); //passing this is important for returning
        dialog->show();
        QObject::connect(dialog,&QDialog::accepted,[=](){
            QColor txtColour = dialog->currentColor();
            ui->RealTextEdit->setTextColor(txtColour);
        });
    //SAME FOR v1 AND v2
    ui->FileFrame->setVisible(false);
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}


/***********************************************************************************
*                            BUTTON FOR ALIGN THE TEXT                             *
************************************************************************************/
void EditorWindow::on_buttonAlignDX_clicked(){
    ui->RealTextEdit->setAlignment(Qt::AlignRight);
    AlignDXButtonHandler();
    AlignButtonStyleHandler();
    ui->FileFrame->setVisible(false);
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}

void EditorWindow::on_buttonAlignCX_clicked(){
    ui->RealTextEdit->setAlignment(Qt::AlignCenter);
    AlignCXButtonHandler();
    AlignButtonStyleHandler();
    ui->FileFrame->setVisible(false);
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}

void EditorWindow::on_buttonAlignSX_clicked(){
    ui->RealTextEdit->setAlignment(Qt::AlignLeft);
    AlignSXButtonHandler();
    AlignButtonStyleHandler();
    ui->FileFrame->setVisible(false);
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}

void EditorWindow::on_buttonAlignJFX_clicked(){
    ui->RealTextEdit->setAlignment(Qt::AlignJustify);   
    AlignJFXButtonHandler();
    AlignButtonStyleHandler();
    ui->FileFrame->setVisible(false);
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}


/***********************************************************************************
*                           BUTTON FOR MODIFY THE TEXT                             *
************************************************************************************/
void EditorWindow::on_buttonUndo_clicked(){
    ui->RealTextEdit->undo();
    ui->FileFrame->setVisible(false);
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}

void EditorWindow::on_buttonRedo_clicked(){
    ui->RealTextEdit->redo();
    ui->FileFrame->setVisible(false);
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}

void EditorWindow::on_buttonTaglia_clicked(){
    ui->RealTextEdit->cut();
    ui->FileFrame->setVisible(false);
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}

void EditorWindow::on_buttonIncolla_clicked(){
    ui->RealTextEdit->paste();
    ui->FileFrame->setVisible(false);
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}

void EditorWindow::on_buttonCopia_clicked(){
    ui->RealTextEdit->copy();
    ui->FileFrame->setVisible(false);
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}


/***********************************************************************************
*                         BUTTON FOR HIGHLIGHT THE TEXT                            *
************************************************************************************/
void EditorWindow::on_buttonSearch_clicked(){
    QString findtext = QInputDialog::getText(this,"Ricerca","Inserisci testo da cercare:");
    ui->RealTextEdit->moveCursor(QTextCursor::Start);
    if(!ui->RealTextEdit->find(findtext,QTextDocument::FindWholeWords)){
        QMessageBox::information(this,"Attenzione", "La ricerca non ha trovato alcun risultato!");
    }
    ui->FileFrame->setVisible(false);
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
                QMessageBox::critical(this,"Errore", "Si è verificato un problema durante il cambio di dimensione del testo!");
                break;
        }
    }
    ui->FileFrame->setVisible(false);
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
    qDebug() << "Il colore del testo selezionato era " << backcolor;
    if(ui->RealTextEdit->fontWeight()>50){
        bold=true;
    }
    if(ui->RealTextEdit->fontItalic()){
        italic = true;
    }
    if(ui->RealTextEdit->fontUnderline()){
        underl = true;
    }


    //SET THE NEW FAMILY OF THE FONT (Spent a lot of time for this...)
    QTextCharFormat format;
    format.setFont(f);
    QFontInfo infof(f);
    QString family = infof.family();
    ui->RealTextEdit->setFontFamily(family);


    //RESTORE PREVIOUS PROPRIETY OF TEXT
    ui->RealTextEdit->setFontPointSize(fontPointSize);
    ui->RealTextEdit->setTextColor(textcolor);
    if(bold==true){
        ui->RealTextEdit->setFontWeight(QFont::Bold);
    }
    if(italic==true){
        ui->RealTextEdit->setFontItalic(true);
    }
    if(underl==true){
        ui->RealTextEdit->setFontUnderline(true);
    }

    //CHECK IF BACKGROUND COLOR IS THE DEFAULT ONE OR NOT <-- THIS IS MUCH IMPORTANT, I SPENT MORE THAN A WEEK FOR THAT!!!!
    if(backcolor!=(QColor(0,0,0,255))){ //The QColor is default trasparent (r=0,g=0,b=0,a=255) that in Qt ARGB is (1,0,0,0).
        //If backcolor is == (0,0,0,255) and i set another background color, then the background will be black.
        qDebug() << "Ho settato il colore di sfondo del testo";
        ui->RealTextEdit->setTextBackgroundColor(backcolor);
    }

    //AT THE END
    ui->FileFrame->setVisible(false);
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}

/***********************************************************************************
*                              RealTextEdit FUNCTION                               *
************************************************************************************/
void EditorWindow::on_RealTextEdit_cursorPositionChanged(){

    //CATCH CURSOR
    QTextCursor c = ui->RealTextEdit->textCursor();

    /****************************************************************
     * STEP 0 - Hidro's Personal Solution to handle the QTBUG-29393 --> https://bugreports.qt.io/browse/QTBUG-29393
     * https://github.com/giovannic96/Real-time-collaborative-text-editor/issues/29
     ****************************************************************/
    if(ui->RealTextEdit->fontPointSize()<=0){
        /*
        If I'm in the first position and press CANC or BACKSPACE, the font index and the size of font became 0 (QT Known bug 29393)
        This is my personal solution: if fontPointSize became less or equal than 0, then I restore the previous selected font and dimension
        KNOWN BUG
        1) If the user press "CTRL+A and after CANC", the first char is in default font/dimension (Time New Romans - 14)
        2) If the user press "Arrow Up" and the RealTextEdit is fully empty, the first char is in default font/dimension (Time New Romans - 14)
        */
        int dimensionFromOtherSide = (ui->fontDimensionBox->currentText()).toInt();
        QString fontFromOtherSide = ui->fontSelectorBox->currentText();
        ui->RealTextEdit->setFontPointSize(dimensionFromOtherSide);
        ui->RealTextEdit->setFontFamily(fontFromOtherSide);
        qDebug()<<"Il Cursore è sicuramente in posizione iniziale";
    }


    /****************************************************************
     * STEP 1 - Send information of location of the cursor to the server
     ****************************************************************/
    //TODO --> c.position();


    /****************************************************************
     * STEP 2 - Get font size and update fontDimensionBox
     ****************************************************************/
    double fontPointSize = ui->RealTextEdit->fontPointSize();
    int intFontPointSize = static_cast<int>(fontPointSize);

    //QString textFontPointSize = QString::number(fontPointSize);
    auto antilambda1 = [] (int intFontPointSize){return (intFontPointSize/2)-1;}; //Inversed Lambda1 Function

    if (intFontPointSize<=26){
        ui->fontDimensionBox->setCurrentIndex(antilambda1(intFontPointSize));
    }else{
        //After FontDimensionSize 24, the formula applied in the antilambda1 function is not respected anymore
        switch(intFontPointSize){
            case 28:
                ui->fontDimensionBox->setCurrentIndex(12);
                break;
            case 32:
                ui->fontDimensionBox->setCurrentIndex(13);
                break;
            case 48:
                ui->fontDimensionBox->setCurrentIndex(14);
                break;
            case 72:
                ui->fontDimensionBox->setCurrentIndex(15);
                break;
            default:
                QMessageBox::critical(this,"Errore", "Si è verificato un problema durante l'aggiornamento della dimensione del testo!");
                break;
        }
    }


    /****************************************************************
     * STEP 3 - Get font family and update fontSelectorBox
     ****************************************************************/
    //Get the Font and estract the Family from it
    QFont f = ui->RealTextEdit->fontFamily();
    QFontInfo infof(f);
    QString family = infof.family();

    if(!c.hasSelection()){
        /*
         * Is important that the cursor hasn't selection. If i have "AAAAABBB" text on the document,
         * where A is a char written with font1 and B is char written with font 2, and I start a selection
         * from the second A up and reach the B, then the text becomes "ABBBBBBBB".
         * Another example is the following: if I start a selection from the last B and reach the fourth,
         * then the text becomes "AAAAAAAA".
         *
         * Change fontSelector trigger the fontSelectorBox_currentFontChanged() function, that change the
         * font of the selected text (or the following text) according to the fontSelectorBox!
         * Hey, did you imagine to fall in this complexed situation? Me neither! This s**t goes crazy!
        */
        ui->fontSelectorBox->setCurrentFont(family);
    }


    /****************************************************************
     * STEP 4 - If Bold/Italic/Underline, set button to clicked
     ****************************************************************/
    if(ui->RealTextEdit->fontWeight()>50){
        ui->buttonGrassetto->setChecked(true);
    }else{
        ui->buttonGrassetto->setChecked(false);
    }
    if(ui->RealTextEdit->fontItalic()){
        ui->buttonCorsivo->setChecked(true);
    }else{
        ui->buttonCorsivo->setChecked(false);
    }
    if(ui->RealTextEdit->fontUnderline()){
        ui->buttonSottolineato->setChecked(true);
    }else{
        ui->buttonSottolineato->setChecked(false);
    }
    SmokinSexyShowtimeStyleHandler();


    /****************************************************************
     * STEP 5 - If text is aligned, set alignment button to clicked
     ****************************************************************/
    if(ui->RealTextEdit->alignment()==Qt::AlignLeft){
        AlignSXButtonHandler();
    }else if(ui->RealTextEdit->alignment()==Qt::AlignCenter){
        AlignCXButtonHandler();
    }else if(ui->RealTextEdit->alignment()==Qt::AlignRight){
        AlignDXButtonHandler();
    }else if(ui->RealTextEdit->alignment()==Qt::AlignJustify){
        AlignJFXButtonHandler();
    }
    AlignButtonStyleHandler();


    //int debugAntiLambda1 = static_cast<int>(antilambda1(fontPointSize)); --> THIS MAKE SERVER CRASH SO LOUDLY THAT MY NEIGHBORS CALLED THE COPS!
    qDebug() << "Font = "<< infof.family() << " - Size = "<< fontPointSize;  //<< "il cui indice è " << antilambda1(intFontPointSize);
}

void EditorWindow::on_RealTextEdit_textChanged() {
    /*
    //Get data
    std::pair<int, wchar_t> tuple;
    QTextCursor cursor = ui->RealTextEdit->textCursor();
    int pos = cursor.position();
    wchar_t c = ui->RealTextEdit->toPlainText().mid(pos-1, 1).toStdString().c_str()[0];
    tuple = std::make_pair(pos-1, c);

    //Serialize data
    json j;
    jsonUtility::to_json_insertion(j, "INSERTION_REQUEST", tuple);
    const std::string req = j.dump();

    //Send data (header and body)
    sendRequestMsg(req);
    */
}


/***********************************************************************************
*                                TopLeftBar FUNCTION                               *
************************************************************************************/
void EditorWindow::on_buttonExit_clicked() {
    QMessageBox::StandardButton reply;
      reply = QMessageBox::question(this, "Uscita", "Uscire dal documento?",
                                    QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::Yes) {
        qDebug() << "Yes was clicked";
        LogoutRequest();//Return to MenuWindow (close only the current document)
      } else {
        qDebug() << "Yes was not clicked";
      }
}


void EditorWindow::on_buttonToIcon_clicked() {
    ui->FileFrame->setVisible(false);
    this->setWindowState(Qt::WindowMinimized); //See Note 2 at the end
}

void EditorWindow::on_buttonReduce_clicked(){
    if(ui->buttonReduce->isChecked()){
        this->setWindowState(Qt::WindowMaximized);
    }else{
        this->setWindowState(Qt::WindowNoState); //See Note 1 at the end
        ui->buttonReduce->setCheckable(true);
    }
    ui->FileFrame->setVisible(false);
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

    //VERSION 1
    QString pathname;
    //Dont change the follow line even if there is a warning (UNTIL I STUDY SMARTPOINTER)
    QString fileName = QFileDialog::getSaveFileName(this,"Esporta come PDF", ui->DocName->text(), "PDF File (*.pdf)");

    if (fileName==nullptr){
        return;
    }

    if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }
    QFile File (fileName);
    pathname = fileName;

    QTextStream writeData(&File);
    QString fileText = ui->RealTextEdit->toHtml(); //HTML NO PLAINTEXT
    QTextDocument doc;
    doc.setHtml(fileText);
    QPrinter file(QPrinter::ScreenResolution);
    file.setOutputFormat(QPrinter::PdfFormat);
    file.setOutputFileName(fileName+".pdf"); // better to use full path
    doc.print(&file); //REFERENCE DO NOT TOUCH IT!
    writeData << &file; //like CIN, but in a stream of text
    File.flush();
    File.close();

    ui->FileFrame->setVisible(false);
    ui->RealTextEdit->setFocus();

}


/* MAYBE WE HAVE TO DELETE THIS <---------------------(HEY!!! I AGREE WITH YOU BROTHER! HidroSaphire)
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
    bool ok;
    QString newText = QInputDialog::getText(this, tr("Titolo documento"),
                                         tr("Inserisci un nome per il documento:"), QLineEdit::Normal,
                                         _client->getFilename(), &ok);

    if (ok && !newText.isEmpty() && newText.size()<=15) {

        //Serialize data
        json j;
        jsonUtility::to_jsonRenamefile(j, "RENAMEFILE_REQUEST", newText.toStdString(), _client->getFileURI().toStdString(), _client->getUsername().toStdString());
        const std::string req = j.dump();

        //Send data (header and body)
        sendRequestMsg(req);
    }
    else if (ok && !newText.isEmpty() && newText.size()>25){
        QMessageBox::critical(this,"Errore", "Inserire un nome minore di 25 caratteri!!");
        on_buttonRename_clicked();
    }
    else if (ok && newText.isEmpty()){
        QMessageBox::critical(this,"Errore", "Inserire il nome del documento!");
        on_buttonRename_clicked();
    }
}

void EditorWindow::on_aboutButton_clicked(){
    ui->FileFrame->setVisible(false);
    infoWindow *iw = new infoWindow(this);
    iw->show();
    ui->FileFrame->setVisible(false);
}

void EditorWindow::on_CloseButton_clicked(){
    LogoutRequest();          //Return to MenuWindow (close only the current document)
}



/***********************************************************************************
*                                   EVENT HANDLER                                  *
*                                                                                  *
*     KeyPressEvent is my personal way for recall the Action function              *
************************************************************************************/
bool EditorWindow::eventFilter(QObject *obj, QEvent *ev){
    if (obj == ui->RealTextEdit && ev->type() == QEvent::KeyPress) {

        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(ev);
        qDebug() << "You Pressed Key " + keyEvent->text();
        int key = keyEvent->key();

        if(!keyEvent->text().isEmpty()) {

        //if((key >= Qt::Key_Space && key <= Qt::Key_AsciiTilde) || key == Qt::Key_Return || key == Qt::Key_Egrave) { //only ASCII characters and also "enter"
        if(!(key == Qt::Key_Backspace) && !(key == Qt::Key_Delete)) {
            //Get data
            std::pair<int, wchar_t> tuple;
            QTextCursor cursor = ui->RealTextEdit->textCursor();
            int pos = cursor.position();
            wchar_t c = keyEvent->text().toStdWString().c_str()[0];
            qDebug() << "char: " << c;
            tuple = std::make_pair(pos, c);

            //Serialize data
            json j;
            jsonUtility::to_json_insertion(j, "INSERTION_REQUEST", tuple);
            const std::string req = j.dump();

            //Send data (header and body)
            sendRequestMsg(req);
            return QObject::eventFilter(obj, ev);
        }
        else if(key == Qt::Key_Backspace) { //only Backspace

            //Get data
            QTextCursor cursor = ui->RealTextEdit->textCursor();
            int pos = cursor.position();

            if(cursor.hasSelection()) { //Remove range of characters selected
                int startIndex = cursor.selectionStart();
                int endIndex = cursor.selectionEnd();

                //Serialize data
                json j;
                jsonUtility::to_json_removal_range(j, "REMOVALRANGE_REQUEST", startIndex, endIndex);
                const std::string req = j.dump();

                //Send data (header and body)
                sendRequestMsg(req);
                return QObject::eventFilter(obj, ev);
            }
            else if(pos > 0) { //Remove only one character

                //Serialize data
                json j;
                jsonUtility::to_json_removal(j, "REMOVAL_REQUEST", pos-1);
                const std::string req = j.dump();

                //Send data (header and body)
                sendRequestMsg(req);
                return QObject::eventFilter(obj, ev);
            } else
                return QObject::eventFilter(obj, ev);
        }
        else if(key == Qt::Key_Delete) { //only "canc" button

            //Get data
            QTextCursor cursor = ui->RealTextEdit->textCursor();
            int pos = cursor.position();

            if(cursor.hasSelection()) { //Remove range of characters selected
                int startIndex = cursor.selectionStart();
                int endIndex = cursor.selectionEnd();

                //Serialize data
                json j;
                jsonUtility::to_json_removal_range(j, "REMOVALRANGE_REQUEST", startIndex, endIndex);
                const std::string req = j.dump();

                //Send data (header and body)
                sendRequestMsg(req);
                return QObject::eventFilter(obj, ev);
            }
            else if(pos >= 0 && pos < ui->RealTextEdit->toPlainText().size()) { //Remove only one character

                //Serialize data
                json j;
                jsonUtility::to_json_removal(j, "REMOVAL_REQUEST", pos);
                const std::string req = j.dump();

                //Send data (header and body)
                sendRequestMsg(req);
                return QObject::eventFilter(obj, ev);
            } else
                return QObject::eventFilter(obj, ev);
        }
        } else
            return QObject::eventFilter(obj, ev);
        return false; //or return QObject::eventFilter(obj, ev);
    }
    return false; //or return QObject::eventFilter(obj, ev);
}


void EditorWindow::keyPressEvent(QKeyEvent *e){
    //WORKING ON IT
    if ((e->key() == Qt::Key_I) && QApplication::keyboardModifiers() && Qt::ControlModifier){
        qDebug()<<" CTRL + I";
        on_actionAbout_triggered();
    }else if((e->key() == Qt::Key_S) && QApplication::keyboardModifiers() && Qt::ControlModifier){
        qDebug()<<" CTRL + S";
        on_actionSave_triggered();
    }else if((e->key() == Qt::Key_F11) && Qt::ControlModifier){
        qDebug()<<" CTRL + F11";
        on_actionFullscreen_triggered();
    }else if((e->key() == Qt::Key_E) && QApplication::keyboardModifiers() && Qt::ControlModifier){
        qDebug()<<" CTRL + E";
        on_actionExit_triggered();
    }else if((e->key() == Qt::Key_N) && QApplication::keyboardModifiers() && Qt::ControlModifier){
        qDebug()<<" CTRL + N - But the action is temporanely disabled";
        on_actionNew_triggered();
    }
}

/***********************************************************************************
*                                       ACTION                                     *
*                                                                                  *
*     Action can be recallable with shortcut, but for now it doesn't work          *
************************************************************************************/

//SAVE AS PDF ACTION     -->     CTRL+S
void EditorWindow::on_actionSave_triggered(){
    on_pdfButton_clicked();
}

//FULLSCREEN ACTION      -->     CTRL+F11
void EditorWindow::on_actionFullscreen_triggered(){
    if(ui->actionFullscreen->isChecked()){
        this->setWindowState(Qt::WindowFullScreen);
    }else{
        this->setWindowState(Qt::WindowNoState); //WindowNoState save the old position and the old size of the window
        ui->actionFullscreen->setCheckable(true);
    }
    ui->FileFrame->setVisible(false);
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}

//NEW DOCUMENT ACTION    -->     CTRL+N
void EditorWindow::on_actionNew_triggered(){
    //on_newDocButton_clicked();
}

//ABOUT ACTION           -->     CTRL+I
void EditorWindow::on_actionAbout_triggered(){
    on_aboutButton_clicked();
    ui->FileFrame->setVisible(false);

}//EXIT DOCUMENT ACTION  -->     CTRL+E
void EditorWindow::on_actionExit_triggered(){
     on_CloseButton_clicked();
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

void EditorWindow::PaintItBlack(){
    if(ui->buttonDarkMode->isChecked()){
        //I see a red door and I want to Paint it Black No colors anymore I want them to turn black I see the girls walk by dressed in their summer clothes I have to turn my head until my darkness goes
        ui->buttonDarkMode->setChecked(true);

        ui->frame->setStyleSheet("#frame{background-color: #cc6600;}");
        ui->FileFrame->setStyleSheet("#FileFrame{background-color: #cc6600;}");
        ui->DebugFrame->setStyleSheet("#DebugFrame{background-color: #1a0d00}");
        ui->frame_3->setStyleSheet("#frame_3{background-color: #1a1a1a;}");
        ui->frame_2->setStyleSheet("#frame_2{background-color: #262626;}");
        ui->RealTextEdit->setStyleSheet("#RealTextEdit{background: #4d4d4d; border-left: 2px solid #e6e6e6;}");
        ui->DocName->setStyleSheet("#DocName{color: #ff8000;}");

        QIcon icoAC, icoAD, icoAS, icoJS, icoCPY, icoCUT, icoPAS, icoDEBUG, icoREDO, icoUNDO, icoMAGN, icoCOL, icoBCOL, icoSUN, icoICONA, v2B, v2I, v2U;
        icoAC.addPixmap(QPixmap(":/image/DarkEditor/center-align.png"),QIcon::Normal,QIcon::On);
        icoAS.addPixmap(QPixmap(":/image/DarkEditor/left-align.png"),QIcon::Normal,QIcon::On);
        icoAD.addPixmap(QPixmap(":/image/DarkEditor/right-align.png"),QIcon::Normal,QIcon::On);
        icoJS.addPixmap(QPixmap(":/image/DarkEditor/justify.png"),QIcon::Normal,QIcon::On);
        icoCPY.addPixmap(QPixmap(":/image/DarkEditor/copy.png"),QIcon::Normal,QIcon::On);
        icoCUT.addPixmap(QPixmap(":/image/DarkEditor/cut.png"),QIcon::Normal,QIcon::On);
        icoPAS.addPixmap(QPixmap(":/image/DarkEditor/paste.png"),QIcon::Normal,QIcon::On);
        icoDEBUG.addPixmap(QPixmap(":/image/DarkEditor/debugger-icon-16.jpg.png"),QIcon::Normal,QIcon::On);
        icoREDO.addPixmap(QPixmap(":/image/DarkEditor/redo.png"),QIcon::Normal,QIcon::On);
        icoUNDO.addPixmap(QPixmap(":/image/DarkEditor/undo.png"),QIcon::Normal,QIcon::On);
        icoMAGN.addPixmap(QPixmap(":/image/DarkEditor/Magnifier.png"),QIcon::Normal,QIcon::On);
        icoCOL.addPixmap(QPixmap(":/image/DarkEditor/paintbrush.png"),QIcon::Normal,QIcon::On);
        icoBCOL.addPixmap(QPixmap(":/image/DarkEditor/highlighter.png"),QIcon::Normal,QIcon::On);
        icoSUN.addPixmap(QPixmap(":/image/DarkEditor/DarkSun.png"),QIcon::Normal,QIcon::On);
        icoICONA.addPixmap(QPixmap(":/image/DarkEditor/iconcina.png"),QIcon::Normal,QIcon::On);
        v2B.addPixmap(QPixmap(":/image/DarkEditor/v2bold.png"),QIcon::Normal,QIcon::On);
        v2I.addPixmap(QPixmap(":/image/DarkEditor/v2italic.png"),QIcon::Normal,QIcon::On);
        v2U.addPixmap(QPixmap(":/image/DarkEditor/v2underline.png"),QIcon::Normal,QIcon::On);
        ui->buttonAlignCX->setIcon(icoAC);
        ui->buttonAlignSX->setIcon(icoAS);
        ui->buttonAlignDX->setIcon(icoAD);
        ui->buttonAlignJFX->setIcon(icoJS);
        ui->buttonCopia->setIcon(icoCPY);
        ui->buttonTaglia->setIcon(icoCUT);
        ui->buttonIncolla->setIcon(icoPAS);
        ui->buttonDebug->setIcon(icoDEBUG);
        ui->buttonRedo->setIcon(icoREDO);
        ui->buttonUndo->setIcon(icoUNDO);
        ui->buttonSearch->setIcon(icoMAGN);
        ui->buttonColor->setIcon(icoCOL);
        ui->buttonBackgroundColor->setIcon(icoBCOL);
        ui->buttonDarkMode->setIcon(icoSUN);
        ui->buttonIcona->setIcon(icoICONA);
        ui->buttonGrassetto->setIcon(v2B);
        ui->buttonCorsivo->setIcon(v2I);
        ui->buttonSottolineato->setIcon(v2U);
        //SetCSS
        ui->buttonCopia->setStyleSheet("    #buttonCopia{border:none;}              #buttonCopia:hover{border:1px solid #b2b2b2;              border-radius: 3px;}");
        ui->buttonTaglia->setStyleSheet("   #buttonTaglia{border:none;}             #buttonTaglia:hover{border:1px solid #b2b2b2;             border-radius: 3px;}");
        ui->buttonIncolla->setStyleSheet("  #buttonIncolla{border:none;}            #buttonIncolla:hover{border:1px solid #b2b2b2;            border-radius: 3px;}");
        ui->buttonDebug->setStyleSheet("    #buttonDebug{border:none;}              #buttonDebug:hover{border:1px solid #F00000;              border-radius: 3px;}");
        ui->buttonRedo->setStyleSheet("     #buttonRedo{border:none;}               #buttonRedo:hover{border:1px solid #b2b2b2;               border-radius: 3px;}");
        ui->buttonUndo->setStyleSheet("     #buttonUndo{border:none;}               #buttonUndo:hover{border:1px solid #b2b2b2;               border-radius: 3px;}");
        ui->buttonSearch->setStyleSheet("   #buttonSearch{border:none;}             #buttonSearch:hover{border:1px solid #b2b2b2;             border-radius: 3px;}");
        ui->buttonColor->setStyleSheet("    #buttonColor{border:none;}              #buttonColor:hover{border:1px solid #b2b2b2;              border-radius: 3px;}");
        ui->buttonBackgroundColor->setStyleSheet("#buttonBackgroundColor{border:none;}#buttonBackgroundColor:hover{border:1px solid #b2b2b2;  border-radius: 3px;}");
        ui->buttonDarkMode->setStyleSheet(" #buttonDarkMode{border:none;}           #buttonDarkMode:hover{border:1px solid #b2b2b2;           border-radius: 3px;}");
        //frame CSS
        ui->fileButton->setStyleSheet("     #fileButton{border:none; color:white; border-left: 2px solid #EFEFEF;}      #fileButton:hover{background-color: #ff9900;}");
        ui->pdfButton->setStyleSheet("      #pdfButton{border:none; color:white; border-left: 2px solid #EFEFEF;}       #pdfButton:hover{background-color: #ff9900;}");
        ui->uriButton->setStyleSheet("      #uriButton{border:none; color:white; border-left: 2px solid #EFEFEF;}       #uriButton:hover{background-color: #ff9900;}");
        ui->buttonToIcon->setStyleSheet("   #buttonToIcon{color:white; border: transparent; background-color: transparent;}   #buttonToIcon:hover{background-color: #ff9900;}");
        ui->buttonReduce->setStyleSheet("   #buttonReduce{color:white; border: transparent; background-color: transparent;}   #buttonReduce:hover{background-color: #ff9900;}");
        //FileFrame CSS
        ui->CloseButton->setStyleSheet("    #CloseButton{border:none; color:white;}     #CloseButton:hover{background-color: #ff9900;}");
        ui->URIButton->setStyleSheet("      #URIButton{border:none; color:white;}       #URIButton:hover{background-color: #ff9900;}");
        ui->aboutButton->setStyleSheet("    #aboutButton{border:none; color:white; border-top: 2px solid #EFEFEF;}      #aboutButton:hover{background-color: #ff9900;}");
        ui->buttonRename->setStyleSheet("   #buttonRename{border:none; color:white;}    #buttonRename:hover{background-color: #ff9900;}");
        ui->newDocButton->setStyleSheet("   #newDocButton{border:none; color:white;}    #newDocButton:hover{background-color: #ff9900;}");

    }else{
        //How come no-one told me all throughout history the loneliest people were the ones who always spoke the truth
        ui->buttonDarkMode->setChecked(false);

        ui->frame->setStyleSheet("#frame{background-color: rgb(19, 29, 80)}");
        ui->FileFrame->setStyleSheet("#FileFrame{background-color: rgb(19, 29, 80);}");
        ui->DebugFrame->setStyleSheet("#DebugFrame{background-color:rgb(100, 23, 23);}");
        ui->frame_3->setStyleSheet("#frame_3{background-color: #FFFFFF;}");
        ui->frame_2->setStyleSheet("#frame_2{background-color: #EFEFEF;}");
        ui->RealTextEdit->setStyleSheet("#RealTextEdit{background: #FFFFFF; border-left: 2px solid #404040;}");
        ui->DocName->setStyleSheet("#DocName{color: #505050;}");

        QIcon icoAC, icoAD, icoAS, icoJS, icoCPY, icoCUT, icoPAS, icoDEBUG, icoREDO, icoUNDO, icoMAGN, icoCOL, icoBCOL, icoSUN, icoICONA, v2B, v2I, v2U;
        icoAC.addPixmap(QPixmap(":/image/Editor/center-align.png"),QIcon::Normal,QIcon::On);
        icoAS.addPixmap(QPixmap(":/image/Editor/left-align.png"),QIcon::Normal,QIcon::On);
        icoAD.addPixmap(QPixmap(":/image/Editor/right-align.png"),QIcon::Normal,QIcon::On);
        icoJS.addPixmap(QPixmap(":/image/Editor/justify.png"),QIcon::Normal,QIcon::On);
        icoCPY.addPixmap(QPixmap(":/image/Editor/copy.png"),QIcon::Normal,QIcon::On);
        icoCUT.addPixmap(QPixmap(":/image/Editor/cut.png"),QIcon::Normal,QIcon::On);
        icoPAS.addPixmap(QPixmap(":/image/Editor/paste.png"),QIcon::Normal,QIcon::On);
        icoDEBUG.addPixmap(QPixmap(":/image/debugger-icon-16.jpg.png"),QIcon::Normal,QIcon::On);
        icoREDO.addPixmap(QPixmap(":/image/Editor/redo.png"),QIcon::Normal,QIcon::On);
        icoUNDO.addPixmap(QPixmap(":/image/Editor/undo.png"),QIcon::Normal,QIcon::On);
        icoMAGN.addPixmap(QPixmap(":/image/Editor/Magnifier.png"),QIcon::Normal,QIcon::On);
        icoCOL.addPixmap(QPixmap(":/image/Editor/paintbrush.png"),QIcon::Normal,QIcon::On);
        icoBCOL.addPixmap(QPixmap(":/image/Editor/highlighter.png"),QIcon::Normal,QIcon::On);
        icoSUN.addPixmap(QPixmap(":/image/Editor/DarkMoon.png"),QIcon::Normal,QIcon::On);
        icoICONA.addPixmap(QPixmap(":/image/Editor/iconcina.png"),QIcon::Normal,QIcon::On);
        v2B.addPixmap(QPixmap(":/image/Editor/v2bold.png"),QIcon::Normal,QIcon::On);
        v2I.addPixmap(QPixmap(":/image/Editor/v2italic.png"),QIcon::Normal,QIcon::On);
        v2U.addPixmap(QPixmap(":/image/Editor/v2underline.png"),QIcon::Normal,QIcon::On);
        ui->buttonAlignCX->setIcon(icoAC);
        ui->buttonAlignSX->setIcon(icoAS);
        ui->buttonAlignDX->setIcon(icoAD);
        ui->buttonAlignJFX->setIcon(icoJS);
        ui->buttonCopia->setIcon(icoCPY);
        ui->buttonTaglia->setIcon(icoCUT);
        ui->buttonIncolla->setIcon(icoPAS);
        ui->buttonDebug->setIcon(icoDEBUG);
        ui->buttonRedo->setIcon(icoREDO);
        ui->buttonUndo->setIcon(icoUNDO);
        ui->buttonSearch->setIcon(icoMAGN);
        ui->buttonColor->setIcon(icoCOL);
        ui->buttonBackgroundColor->setIcon(icoBCOL);
        ui->buttonDarkMode->setIcon(icoSUN);
        ui->buttonIcona->setIcon(icoICONA);
        ui->buttonGrassetto->setIcon(v2B);
        ui->buttonCorsivo->setIcon(v2I);
        ui->buttonSottolineato->setIcon(v2U);
        //SetCSS
        ui->buttonCopia->setStyleSheet("    #buttonCopia{border:none;}              #buttonCopia:hover{border:1px solid #b2b2b2;              border-radius: 3px;}");
        ui->buttonTaglia->setStyleSheet("   #buttonTaglia{border:none;}             #buttonTaglia:hover{border:1px solid #b2b2b2;             border-radius: 3px;}");
        ui->buttonIncolla->setStyleSheet("  #buttonIncolla{border:none;}            #buttonIncolla:hover{border:1px solid #b2b2b2;            border-radius: 3px;}");
        ui->buttonDebug->setStyleSheet("    #buttonDebug{border:none;}              #buttonDebug:hover{border:1px solid #F00000;              border-radius: 3px;}");
        ui->buttonRedo->setStyleSheet("     #buttonRedo{border:none;}               #buttonRedo:hover{border:1px solid #b2b2b2;               border-radius: 3px;}");
        ui->buttonUndo->setStyleSheet("     #buttonUndo{border:none;}               #buttonUndo:hover{border:1px solid #b2b2b2;               border-radius: 3px;}");
        ui->buttonSearch->setStyleSheet("   #buttonSearch{border:none;}             #buttonSearch:hover{border:1px solid #b2b2b2;             border-radius: 3px;}");
        ui->buttonColor->setStyleSheet("    #buttonColor{border:none;}              #buttonColor:hover{border:1px solid #b2b2b2;              border-radius: 3px;}");
        ui->buttonBackgroundColor->setStyleSheet("#buttonBackgroundColor{border:none;}#buttonBackgroundColor:hover{border:1px solid #b2b2b2;  border-radius: 3px;}");
        ui->buttonDarkMode->setStyleSheet(" #buttonDarkMode{border:none;}           #buttonDarkMode:hover{border:1px solid #b2b2b2;           border-radius: 3px;}");
        //frame CSS
        ui->fileButton->setStyleSheet("     #fileButton{border:none; color:white; border-left: 2px solid #EFEFEF;}            #fileButton:hover{background-color: #003cb3;}");
        ui->pdfButton->setStyleSheet("      #pdfButton{border:none; color:white; border-left: 2px solid #EFEFEF;}             #pdfButton:hover{background-color: #003cb3;}");
        ui->uriButton->setStyleSheet("      #uriButton{border:none; color:white; border-left: 2px solid #EFEFEF;}             #uriButton:hover{background-color: #003cb3;}");
        ui->buttonToIcon->setStyleSheet("   #buttonToIcon{color:white; border: transparent; background-color: transparent;}   #buttonToIcon:hover{background-color: #003cb3;}");
        ui->buttonReduce->setStyleSheet("   #buttonReduce{color:white; border: transparent; background-color: transparent;}   #buttonReduce:hover{background-color: #003cb3;}");
        //FileFrame CSS
        ui->CloseButton->setStyleSheet("    #CloseButton{border:none; color:white;}     #CloseButton:hover{background-color: #003cb3;}");
        ui->URIButton->setStyleSheet("      #URIButton{border:none; color:white;}       #URIButton:hover{background-color: #003cb3;}");
        ui->aboutButton->setStyleSheet("    #aboutButton{border:none; color:white; border-top: 2px solid #EFEFEF;}      #aboutButton:hover{background-color: #003cb3;}");
        ui->buttonRename->setStyleSheet("   #buttonRename{border:none; color:white;}    #buttonRename:hover{background-color: #003cb3;}");
        ui->newDocButton->setStyleSheet("   #newDocButton{border:none; color:white;}    #newDocButton:hover{background-color: #003cb3;}");

    }
    //Set Other CSS
    AlignButtonStyleHandler();
    SmokinSexyShowtimeStyleHandler();
    //IN THE END
    ui->FileFrame->setVisible(false);
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}

void EditorWindow::AlignDXButtonHandler(){
ui->buttonAlignDX->setChecked(true);
ui->buttonAlignCX->setChecked(false);
ui->buttonAlignSX->setChecked(false);
ui->buttonAlignJFX->setChecked(false);
}

void EditorWindow::AlignCXButtonHandler(){
ui->buttonAlignDX->setChecked(false);
ui->buttonAlignCX->setChecked(true);
ui->buttonAlignSX->setChecked(false);
ui->buttonAlignJFX->setChecked(false);

}
void EditorWindow::AlignSXButtonHandler(){
ui->buttonAlignDX->setChecked(false);
ui->buttonAlignCX->setChecked(false);
ui->buttonAlignSX->setChecked(true);
ui->buttonAlignJFX->setChecked(false);
}

void EditorWindow::AlignJFXButtonHandler(){
ui->buttonAlignDX->setChecked(false);
ui->buttonAlignCX->setChecked(false);
ui->buttonAlignSX->setChecked(false);
ui->buttonAlignJFX->setChecked(true);
}

void EditorWindow::AlignButtonStyleHandler(){
    if(ui->buttonDarkMode->isChecked()){
        //Alone in the Dark (change the value of background color)
        if(ui->buttonAlignCX->isChecked()){
            ui->buttonAlignCX->setStyleSheet("  #buttonAlignCX{border:none; background-color:#AEAEAE}   #buttonAlignCX:hover{border:1px solid #b2b2b2;   border-radius: 3px;}");
            ui->buttonAlignSX->setStyleSheet("  #buttonAlignSX{border:none;}                            #buttonAlignSX:hover{border:1px solid #b2b2b2;   border-radius: 3px;}");
            ui->buttonAlignDX->setStyleSheet("  #buttonAlignDX{border:none;}                            #buttonAlignDX:hover{border:1px solid #b2b2b2;   border-radius: 3px;}");
            ui->buttonAlignJFX->setStyleSheet(" #buttonAlignJFX{border:none;}                           #buttonAlignJFX:hover{border:1px solid #b2b2b2;  border-radius: 3px;}");
        }else if(ui->buttonAlignSX->isChecked()){
            ui->buttonAlignCX->setStyleSheet("  #buttonAlignCX{border:none;}                            #buttonAlignCX:hover{border:1px solid #b2b2b2;   border-radius: 3px;}");
            ui->buttonAlignSX->setStyleSheet("  #buttonAlignSX{border:none; background-color:#AEAEAE}   #buttonAlignSX:hover{border:1px solid #b2b2b2;   border-radius: 3px;}");
            ui->buttonAlignDX->setStyleSheet("  #buttonAlignDX{border:none;}                            #buttonAlignDX:hover{border:1px solid #b2b2b2;   border-radius: 3px;}");
            ui->buttonAlignJFX->setStyleSheet(" #buttonAlignJFX{border:none;}                           #buttonAlignJFX:hover{border:1px solid #b2b2b2;  border-radius: 3px;}");
        }else if(ui->buttonAlignDX->isChecked()){
            ui->buttonAlignCX->setStyleSheet("  #buttonAlignCX{border:none;}                            #buttonAlignCX:hover{border:1px solid #b2b2b2;   border-radius: 3px;}");
            ui->buttonAlignSX->setStyleSheet("  #buttonAlignSX{border:none;}                            #buttonAlignSX:hover{border:1px solid #b2b2b2;   border-radius: 3px;}");
            ui->buttonAlignDX->setStyleSheet("  #buttonAlignDX{border:none; background-color:#AEAEAE}   #buttonAlignDX:hover{border:1px solid #b2b2b2;   border-radius: 3px;}");
            ui->buttonAlignJFX->setStyleSheet(" #buttonAlignJFX{border:none;}                           #buttonAlignJFX:hover{border:1px solid #b2b2b2;  border-radius: 3px;}");
        }else if(ui->buttonAlignJFX->isChecked()){
            ui->buttonAlignCX->setStyleSheet("  #buttonAlignCX{border:none;}                            #buttonAlignCX:hover{border:1px solid #b2b2b2;   border-radius: 3px;}");
            ui->buttonAlignSX->setStyleSheet("  #buttonAlignSX{border:none;}                            #buttonAlignSX:hover{border:1px solid #b2b2b2;   border-radius: 3px;}");
            ui->buttonAlignDX->setStyleSheet("  #buttonAlignDX{border:none;}                            #buttonAlignDX:hover{border:1px solid #b2b2b2;   border-radius: 3px;}");
            ui->buttonAlignJFX->setStyleSheet(" #buttonAlignJFX{border:none; background-color:#AEAEAE}  #buttonAlignJFX:hover{border:1px solid #b2b2b2;  border-radius: 3px;}");
        }
    }else{
        //There is a house in New Orleans They call the Rising Sun And it's been the ruin of many a poor boy And God I know I'm one
        if(ui->buttonAlignCX->isChecked()){
            ui->buttonAlignCX->setStyleSheet("  #buttonAlignCX{border:none; background-color:#AEAEAE}   #buttonAlignCX:hover{border:1px solid #b2b2b2;   border-radius: 3px;}");
            ui->buttonAlignSX->setStyleSheet("  #buttonAlignSX{border:none;}                            #buttonAlignSX:hover{border:1px solid #b2b2b2;   border-radius: 3px;}");
            ui->buttonAlignDX->setStyleSheet("  #buttonAlignDX{border:none;}                            #buttonAlignDX:hover{border:1px solid #b2b2b2;   border-radius: 3px;}");
            ui->buttonAlignJFX->setStyleSheet(" #buttonAlignJFX{border:none;}                           #buttonAlignJFX:hover{border:1px solid #b2b2b2;  border-radius: 3px;}");
        }else if(ui->buttonAlignSX->isChecked()){
            ui->buttonAlignCX->setStyleSheet("  #buttonAlignCX{border:none;}                            #buttonAlignCX:hover{border:1px solid #b2b2b2;   border-radius: 3px;}");
            ui->buttonAlignSX->setStyleSheet("  #buttonAlignSX{border:none; background-color:#AEAEAE}   #buttonAlignSX:hover{border:1px solid #b2b2b2;   border-radius: 3px;}");
            ui->buttonAlignDX->setStyleSheet("  #buttonAlignDX{border:none;}                            #buttonAlignDX:hover{border:1px solid #b2b2b2;   border-radius: 3px;}");
            ui->buttonAlignJFX->setStyleSheet(" #buttonAlignJFX{border:none;}                           #buttonAlignJFX:hover{border:1px solid #b2b2b2;  border-radius: 3px;}");
        }else if(ui->buttonAlignDX->isChecked()){
            ui->buttonAlignCX->setStyleSheet("  #buttonAlignCX{border:none;}                            #buttonAlignCX:hover{border:1px solid #b2b2b2;   border-radius: 3px;}");
            ui->buttonAlignSX->setStyleSheet("  #buttonAlignSX{border:none;}                            #buttonAlignSX:hover{border:1px solid #b2b2b2;   border-radius: 3px;}");
            ui->buttonAlignDX->setStyleSheet("  #buttonAlignDX{border:none; background-color:#AEAEAE}   #buttonAlignDX:hover{border:1px solid #b2b2b2;   border-radius: 3px;}");
            ui->buttonAlignJFX->setStyleSheet(" #buttonAlignJFX{border:none;}                           #buttonAlignJFX:hover{border:1px solid #b2b2b2;  border-radius: 3px;}");
        }else if(ui->buttonAlignJFX->isChecked()){
            ui->buttonAlignCX->setStyleSheet("  #buttonAlignCX{border:none;}                            #buttonAlignCX:hover{border:1px solid #b2b2b2;   border-radius: 3px;}");
            ui->buttonAlignSX->setStyleSheet("  #buttonAlignSX{border:none;}                            #buttonAlignSX:hover{border:1px solid #b2b2b2;   border-radius: 3px;}");
            ui->buttonAlignDX->setStyleSheet("  #buttonAlignDX{border:none;}                            #buttonAlignDX:hover{border:1px solid #b2b2b2;   border-radius: 3px;}");
            ui->buttonAlignJFX->setStyleSheet(" #buttonAlignJFX{border:none; background-color:#AEAEAE}  #buttonAlignJFX:hover{border:1px solid #b2b2b2;  border-radius: 3px;}");
        }
    }
}

void EditorWindow::SmokinSexyShowtimeStyleHandler(){
    if(ui->buttonDarkMode->isChecked()){
        //All the leaves are brown and the sky is gray I've been for a walk on a winter's day I'd be safe and warm if I was in L.A California dreamin' on such a winter's day
        if(ui->buttonGrassetto->isChecked()){
            ui->buttonGrassetto->setStyleSheet("#buttonGrassetto{border:none; background-color:#AEAEAE}    #buttonGrassetto:hover{border:1px solid #b2b2b2; border-radius: 3px;}");
        }else{
             ui->buttonGrassetto->setStyleSheet("#buttonGrassetto{border:none;}    #buttonGrassetto:hover{border:1px solid #b2b2b2; border-radius: 3px;}");
        }
        if(ui->buttonCorsivo->isChecked()){
            ui->buttonCorsivo->setStyleSheet("#buttonCorsivo{border:none; background-color:#AEAEAE}    #buttonCorsivo:hover{border:1px solid #b2b2b2; border-radius: 3px;}");
        }else{
             ui->buttonCorsivo->setStyleSheet("#buttonCorsivo{border:none;}    #buttonCorsivo:hover{border:1px solid #b2b2b2; border-radius: 3px;}");
        }
        if(ui->buttonSottolineato->isChecked()){
            ui->buttonSottolineato->setStyleSheet("#buttonSottolineato{border:none; background-color:#AEAEAE}    #buttonSottolineato:hover{border:1px solid #b2b2b2; border-radius: 3px;}");
        }else{
             ui->buttonSottolineato->setStyleSheet("#buttonSottolineato{border:none;}    #buttonSottolineato:hover{border:1px solid #b2b2b2; border-radius: 3px;}");
        }
    }else{
        //She came to me one morning, one lonely Sunday morning Her long hair flowing in the mid-winter wind I know not how she found me For in darkness I was walking
        if(ui->buttonGrassetto->isChecked()){
            ui->buttonGrassetto->setStyleSheet("#buttonGrassetto{border:none; background-color:#AEAEAE}    #buttonGrassetto:hover{border:1px solid #b2b2b2; border-radius: 3px;}");
        }else{
             ui->buttonGrassetto->setStyleSheet("#buttonGrassetto{border:none;}    #buttonGrassetto:hover{border:1px solid #b2b2b2; border-radius: 3px;}");
        }
        if(ui->buttonCorsivo->isChecked()){
            ui->buttonCorsivo->setStyleSheet("#buttonCorsivo{border:none; background-color:#AEAEAE}    #buttonCorsivo:hover{border:1px solid #b2b2b2; border-radius: 3px;}");
        }else{
             ui->buttonCorsivo->setStyleSheet("#buttonCorsivo{border:none;}    #buttonCorsivo:hover{border:1px solid #b2b2b2; border-radius: 3px;}");
        }
        if(ui->buttonSottolineato->isChecked()){
            ui->buttonSottolineato->setStyleSheet("#buttonSottolineato{border:none; background-color:#AEAEAE}    #buttonSottolineato:hover{border:1px solid #b2b2b2; border-radius: 3px;}");
        }else{
             ui->buttonSottolineato->setStyleSheet("#buttonSottolineato{border:none;}    #buttonSottolineato:hover{border:1px solid #b2b2b2; border-radius: 3px;}");
        }
    }
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
    ui->FileFrame->setVisible(false);
    ui->RealTextEdit->setFocus();
}

void EditorWindow::on_DebugIns1_clicked(){
    QTextCursor c = ui->RealTextEdit->textCursor();
    c.setPosition(1);
    c.insertText("Z");
    ui->FileFrame->setVisible(false);
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}

void EditorWindow::on_DebugInsInit_clicked(){
    QTextCursor c = ui->RealTextEdit->textCursor();
    c.setPosition(0);
    c.insertText("A");
    ui->FileFrame->setVisible(false);
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}


void EditorWindow::on_DebugDel1_clicked(){
    QTextCursor c = ui->RealTextEdit->textCursor();
    c.setPosition(1);
    c.deleteChar();
    ui->FileFrame->setVisible(false);
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}

void EditorWindow::on_DebugCursLeft_clicked(){
    QTextCursor c = ui->RealTextEdit->textCursor();
    c.movePosition(QTextCursor::PreviousCharacter,QTextCursor::MoveAnchor,1);
    ui->RealTextEdit->setTextCursor(c);
    ui->FileFrame->setVisible(false);
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}

void EditorWindow::on_DebugCursRight_clicked(){
    QTextCursor c = ui->RealTextEdit->textCursor();
    c.movePosition(QTextCursor::NextCharacter,QTextCursor::MoveAnchor,1);
    ui->RealTextEdit->setTextCursor(c);
    ui->FileFrame->setVisible(false);
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}

void EditorWindow::on_DebugCursLeftAnchor_clicked(){
    QTextCursor c = ui->RealTextEdit->textCursor();
    c.movePosition(QTextCursor::NextCharacter,QTextCursor::KeepAnchor,1);
    ui->RealTextEdit->setTextCursor(c);
    ui->FileFrame->setVisible(false);
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}

void EditorWindow::on_DebugWordLeft_clicked(){
    QTextCursor c = ui->RealTextEdit->textCursor();
    c.movePosition(QTextCursor::WordLeft,QTextCursor::MoveAnchor,1);
    ui->FileFrame->setVisible(false);
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}

void EditorWindow::on_DebugWordRight_clicked(){
    QTextCursor c = ui->RealTextEdit->textCursor();
    c.movePosition(QTextCursor::WordRight,QTextCursor::MoveAnchor,1);
    ui->RealTextEdit->setTextCursor(c);
    ui->FileFrame->setVisible(false);
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}

void EditorWindow::on_DebugIns6Word_clicked(){
    QTextCursor c = ui->RealTextEdit->textCursor();
    c.setPosition(6);
    c.insertText("HidroSaphire è il migliore");
    ui->FileFrame->setVisible(false);
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}


void EditorWindow::on_buttonDarkMode_clicked(){
    PaintItBlack();
}

//----------------------OTHER KIND OF FUNCTION OVER THERE-----------------------------//

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

void EditorWindow::showPopupSuccess(QString result, std::string filename) {
    if(result == "LOGOUTURI_SUCCESS") {
        this->close();
        parentWidget()->show();
        delete this;
    } else if (result == "RENAME_SUCCESS"){
        ui->DocName->setText(QString::fromStdString(filename));
        _client->setFilename(QString::fromStdString(filename));      //Assign newText to the variable
        ui->FileFrame->setVisible(false);
        ui->RealTextEdit->setFocus(); //Return focus to textedit
    }
}

void EditorWindow::showPopupFailure(QString result) {
    if(result == "LOGOUTURI_FAILURE") {
        QMessageBox::critical(this,"Errore", "LogoutURI non completata!");                                 //Stay in the same window
    } else if(result == "RENAME_FAILURE") {
        QMessageBox::warning(this,"Impossibile rinominare", "Esiste già un file con questo nome!");        //Stay in the same window
    } else {
        QMessageBox::information(nullptr, "Attenzione", "Qualcosa è andato storto! Riprova!");
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

void EditorWindow::showSymbols(std::vector<symbol> symbols) {
    wchar_t letter;
    QTextCursor c = ui->RealTextEdit->textCursor();
    foreach (symbol s, symbols) {
        letter = s.getLetter();
        QTextCharFormat oldFormat = c.charFormat();
        QTextCharFormat newFormat = oldFormat;
        if (s.isBold()){
            newFormat.setFontWeight(QFont::Bold);
        }
        if (s.isItalic()){
            newFormat.setFontItalic(true);
        }

        int pos = s.getPos().at(0);
        c.setPosition(pos);
        c.setCharFormat(newFormat);
        c.insertText(static_cast<QString>(letter));
        ui->RealTextEdit->setTextCursor(c);
        c.setCharFormat(oldFormat);
    }
}

void EditorWindow::showSymbol(std::pair<int, wchar_t> tuple) {
    int pos = tuple.first;
    wchar_t c = tuple.second;
    QTextCursor cursor = ui->RealTextEdit->textCursor();
    cursor.setPosition(pos);
    cursor.insertText(static_cast<QString>(c));
    qDebug() << "Written in pos: " << pos << endl;
    ui->FileFrame->setVisible(false);
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}

void EditorWindow::eraseSymbol(int index) {
    QTextCursor cursor = ui->RealTextEdit->textCursor();
    int oldPos = cursor.position();
    cursor.setPosition(index);
    //cursor.insertText(static_cast<QString>(c));
    cursor.deleteChar();
    cursor.setPosition(oldPos);
    qDebug() << "Deleted char in pos: " << index << endl;
    ui->FileFrame->setVisible(false);
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}

void EditorWindow::eraseSymbols(int startIndex, int endIndex) {
    QString plaintext = ui->RealTextEdit->toPlainText();
    plaintext = plaintext.remove(startIndex, endIndex-startIndex);
    ui->RealTextEdit->setPlainText(plaintext);

    qDebug() << "Deleted char range from pos: " << startIndex << " to pos: " << endIndex << endl;
    ui->FileFrame->setVisible(false);
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}

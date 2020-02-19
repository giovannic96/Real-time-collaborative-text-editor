#include "editorwindow.h"
#include "ui_editorwindow.h"
#include <QInputDialog>
#include <QLineEdit>
#include <QColorDialog>     //FOR OPEN COLOR PALETTE
#include <QFileDialog>      //FOR OPEN SAVE WITH NAME LOCALLY
#include <QTextStream>      //FOR SAVE THE FILE LOCALLY AND PDF CONVERSION
#include <QMessageBox>
#include <QGraphicsOpacityEffect>   //<-- REMOVE IT
#include <QPrinter>         //FOR PRINTING THE PDF
#include "infowindow.h"
#include "menuwindow.h"
#include <QEvent>

using json = nlohmann::json;

//CONSTRUCTOR
EditorWindow::EditorWindow(myClient* client, QWidget *parent): QMainWindow(parent), ui(new Ui::EditorWindow), _client(client) {
    ui->setupUi(this);
    connect(_client, &myClient::editorResultSuccess, this, &EditorWindow::showPopupSuccess);
    connect(_client, &myClient::editorResultFailure, this, &EditorWindow::showPopupFailure);
    connect(_client, &myClient::insertSymbol, this, &EditorWindow::showSymbol);
    connect(_client, &myClient::eraseSymbol, this, &EditorWindow::eraseSymbol);
    connect(_client, &myClient::eraseSymbols, this, &EditorWindow::eraseSymbols);
    connect(_client, &myClient::insertSymbols, this, &EditorWindow::showSymbolsAt);    

    //PROVA LIST WIDGET UTENTI //TODO CREARE FUNZIONE DINAMICA
    ui->listWidget->setStyleSheet(
      "QListWidget::item {"
         "border-color:#e0e0e0;"
      "}");

    QString itemString;
    QList<QListWidgetItem*> fileItem;
    QListWidgetItem* item;
    QListWidgetItem* item2;

    item = new QListWidgetItem(itemString, ui->listWidget);
    item2 = new QListWidgetItem(itemString, ui->listWidget);

    item->setText("Genitore Uno");
    fileItem.append(item);
    item2->setText("Genitore Due");
    fileItem.append(item2);
    //FINE PROVA

    ui->DocName->setText(docName);
    ui->RealTextEdit->setFontPointSize(14);
    ui->RealTextEdit->setFontFamily("Times New Roman");
    //ui->RealTextEdit->document()->setDefaultFont(QFont("Times New Roman", 14));
    qRegisterMetaType<std::vector<symbol>>("std::vector<symbol>");
    showSymbolsAt(0, _client->getVector());
    ui->RealTextEdit->installEventFilter(this);
    textOnTitleBar = "C.A.R.T.E. - " + docName;
    this->setWindowTitle(textOnTitleBar);
}

//DESTRUCTOR
EditorWindow::~EditorWindow() {
    delete ui;
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
        ui->RealTextEdit->setFontWeight(QFont::Normal);
    }
    SmokinSexyShowtimeStyleHandler();
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}

void EditorWindow::on_buttonCorsivo_clicked() {
    if(ui->buttonCorsivo->isChecked()){
        ui->buttonCorsivo->setChecked(true);
        ui->RealTextEdit->setFontItalic(true);
    }else{
        ui->buttonCorsivo->setChecked(false);
        ui->RealTextEdit->setFontItalic(false);
    }
    SmokinSexyShowtimeStyleHandler();
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
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}


/***********************************************************************************
*                            BUTTON FOR ALIGN THE TEXT                             *
************************************************************************************/
void EditorWindow::on_buttonAlignDX_clicked(){
    ui->RealTextEdit->setAlignment(Qt::AlignRight);
    AlignDXButtonHandler();
    AlignButtonStyleHandler();
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}

void EditorWindow::on_buttonAlignCX_clicked(){
    ui->RealTextEdit->setAlignment(Qt::AlignCenter);
    AlignCXButtonHandler();
    AlignButtonStyleHandler();
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}

void EditorWindow::on_buttonAlignSX_clicked(){
    ui->RealTextEdit->setAlignment(Qt::AlignLeft);
    AlignSXButtonHandler();
    AlignButtonStyleHandler();
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}

void EditorWindow::on_buttonAlignJFX_clicked(){
    ui->RealTextEdit->setAlignment(Qt::AlignJustify);
    AlignJFXButtonHandler();
    AlignButtonStyleHandler();
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
*                         BUTTON FOR HIGHLIGHT THE TEXT                            *
************************************************************************************/
void EditorWindow::on_buttonSearch_clicked(){
    QString findtext = QInputDialog::getText(this,"Ricerca","Inserisci testo da cercare:");
    ui->RealTextEdit->moveCursor(QTextCursor::Start);
    if(!ui->RealTextEdit->find(findtext,QTextDocument::FindWholeWords)){
        QMessageBox::information(this,"Attenzione", "La ricerca non ha trovato alcun risultato!");
    }
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

    //SET THE NEW FAMILY OF THE FONT
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
*                            OLD TopLeftBar FUNCTION                               *
************************************************************************************
void EditorWindow::on_buttonExit_clicked() {
    QMessageBox::StandardButton reply;
      reply = QMessageBox::question(this, "Uscita", "Uscire dal documento?",
                                    QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::Yes) {
        LogoutRequest(); //Return to MenuWindow (close only the current document)
      }
}


void EditorWindow::on_buttonToIcon_clicked() {
    this->setWindowState(Qt::WindowMinimized);
}

void EditorWindow::on_buttonReduce_clicked(){
    if(ui->buttonReduce->isChecked()){
        this->setWindowState(Qt::WindowMaximized);
    }else{
        this->setWindowState(Qt::WindowNoState);
        ui->buttonReduce->setCheckable(true);
    }
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}
*/


/***********************************************************************************
*                                 FileFrame FUNCTION                               *
************************************************************************************/
/* MAYBE WE HAVE TO DELETE THIS
void EditorWindow::on_newDocButton_clicked(){

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
        Qt::KeyboardModifiers modifiers = keyEvent->modifiers();
        QList<Qt::Key> modifiersList;

        if(!keyEvent->text().isEmpty()) { //to ignore chars like "CAPS_LOCK", "SHIFT", "CTRL", etc...

        if (keyEvent->matches(QKeySequence::Cut)) { //CTRL-X
            //Get data
            QTextCursor cursor = ui->RealTextEdit->textCursor();

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
            else
                return QObject::eventFilter(obj, ev);
        }
        else if (keyEvent->matches(QKeySequence::Paste)) { //CTRL-V
            //Get data
            const QClipboard *clipboard = QApplication::clipboard();
            const QMimeData *mimeData = clipboard->mimeData();
            QTextCursor cursor = ui->RealTextEdit->textCursor();
            int pos;

            if(cursor.hasSelection()) { //Remove range of characters selected
                pos = cursor.selectionStart();
                int startIndex = cursor.selectionStart();
                int endIndex = cursor.selectionEnd();

                //Serialize data
                json j;
                jsonUtility::to_json_removal_range(j, "REMOVALRANGE_REQUEST", startIndex, endIndex);
                const std::string req = j.dump();

                //Send data (header and body)
                sendRequestMsg(req);
            } else {
                pos = cursor.position();
            }

            if(mimeData->hasText()) { //TODO: and if mimeData has Images or html??? -> handle this case
                //Get data
                int numChars = mimeData->text().size(); //number of chars = number of iterations
                std::wstring str_to_paste = mimeData->text().toStdWString();
                QVector<QVector<QString>> styles = getStylesFromHTML(mimeData->html());
                std::vector<symbolInfo> infoSymbols;
                int index;
                wchar_t c;
                symbolStyle charStyle;

                for(int i=0; i<numChars; i++) {
                    c = str_to_paste.c_str()[0]; //get wchar
                    qDebug() << "char: " << c;
                    str_to_paste.erase(0,1); //remove first wchar
                    index = pos++; //get index
                    if(c <= 32 || c > 126) //special characters has no style (LF, CR, ESC, SP, ecc.)
                        charStyle = symbolStyle(false, false, false, "Times New Roman", 14);
                    else
                        charStyle = getStyleFromHTMLStyles(styles); //get the style
                    symbolInfo s(index, c, charStyle);
                    infoSymbols.push_back(s);
                }

                //Serialize data
                json j;
                std::vector<json> symFormattingVectorJSON = jsonUtility::fromFormattingSymToJson(infoSymbols);
                jsonUtility::to_json_insertion_range(j, "INSERTIONRANGE_REQUEST", symFormattingVectorJSON);
                const std::string req = j.dump();

                //Send data (header and body)
                sendRequestMsg(req);
                return QObject::eventFilter(obj, ev);
            } else {
                qDebug() << "Cannot paste this." << endl;
                return QObject::eventFilter(obj, ev);
            }
        }
        else if(modifiers & Qt::ControlModifier) { //ignore other CTRL combinations
            return QObject::eventFilter(obj, ev);
        }
        else if(!(key == Qt::Key_Backspace) && !(key == Qt::Key_Delete)) {
            //Get data
            std::pair<int, wchar_t> tuple;
            QTextCursor cursor = ui->RealTextEdit->textCursor();
            int pos = cursor.position();
            wchar_t c = keyEvent->text().toStdWString().c_str()[0];
            qDebug() << "char: " << c;
            tuple = std::make_pair(pos, c);

            //Serialize data
            json j;
            jsonUtility::to_json_insertion(j, "INSERTION_REQUEST", tuple, getCurCharStyle());
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
        on_actionEsporta_come_PDF_triggered();
    }else if((e->key() == Qt::Key_F11) && Qt::ControlModifier){
        qDebug()<<" CTRL + F11";
        on_actionFullscreen_triggered();
    }else if((e->key() == Qt::Key_E) && QApplication::keyboardModifiers() && Qt::ControlModifier){
        qDebug()<<" CTRL + E";
        on_actionExit_triggered();
    }else if((e->key() == Qt::Key_N) && QApplication::keyboardModifiers() && Qt::ControlModifier){
        qDebug()<<" CTRL + N - But the action is temporanely disabled";
        on_actionNew_triggered();
    }else if((e->key() == Qt::Key_N) && QApplication::keyboardModifiers() && Qt::ControlModifier){
        qDebug()<<" CTRL + R";
        on_actionRinomina_triggered();
    }else if((e->key() == Qt::Key_N) && QApplication::keyboardModifiers() && Qt::ControlModifier){
        qDebug()<<" CTRL + D";
        on_actionDark_Mode_triggered();
    }
}

//CHECK HOW THIS WINDOW IS CLOSED   -   IS AN OVERRIDE OF A ORIGINAL CLOSE EVENT
void EditorWindow::closeEvent(QCloseEvent * event){

    //If is a forced close then, ask the user if he really wants to close the document
    if(BruteClose==true){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Uscita", "Uscire dal documento?",
                                      QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            event->ignore();    //IGNORE FORCED CLOSE EVENT --> Is the "override", i'll handle the close event with a LogoutRequest();
            LogoutRequest();    //By ignoring the closing event, the LogoutRequest() brings me back to the menuWindow.
         }else{
            event->ignore();    //IGNORE FORCED CLOSE EVENT --> Stay in this window (EditorWindow)
        }
    }
}

/***********************************************************************************
*                                       ACTION                                     *
*                                                                                  *
*     Action can be recallable with shortcut, but for now it doesn't work          *
************************************************************************************/

//FULLSCREEN ACTION      -->     CTRL+F11
void EditorWindow::on_actionFullscreen_triggered(){
    //WORKING ON - I KNOW THAT IT DOESN'T WORK AT 100%
    if(ui->actionFullscreen->isChecked()){
        ui->actionFullscreen->setChecked(true);
        this->setWindowState(Qt::WindowFullScreen);
    }else{
        this->setWindowState(Qt::WindowNoState); //WindowNoState save the old position and the old size of the window
        ui->actionFullscreen->setChecked(false);
    }
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}

//NEW DOCUMENT ACTION    -->     CTRL+N
void EditorWindow::on_actionNew_triggered(){
    //on_newDocButton_clicked();
}

//ABOUT ACTION           -->     CTRL+I
void EditorWindow::on_actionAbout_triggered(){
    infoWindow *iw = new infoWindow(this);
    iw->show();
}

//EXIT DOCUMENT ACTION  -->     CTRL+E
void EditorWindow::on_actionExit_triggered(){
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Uscita", "Uscire dal documento?",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
      LogoutRequest(); //Return to MenuWindow (close only the current document)
    }
}

//RENAME ACTION         -->     CTRL+R
void EditorWindow::on_actionRinomina_triggered(){
    bool ok;
    QString newText = QInputDialog::getText(this, tr("Titolo documento"),
                                         tr("Inserisci un nome per il documento:"), QLineEdit::Normal,
                                         _client->getFilename(), &ok);

    if (ok && !newText.isEmpty() && newText.size()<=25) {

        //Serialize data
        json j;
        jsonUtility::to_jsonRenamefile(j, "RENAMEFILE_REQUEST", newText.toStdString(), _client->getFileURI().toStdString(), _client->getUsername().toStdString());
        const std::string req = j.dump();

        //Send data (header and body)
        sendRequestMsg(req);
    }
    else if (ok && !newText.isEmpty() && newText.size()>25){
        QMessageBox::critical(this,"Errore", "Inserire un nome minore di 25 caratteri!!");
        on_actionRinomina_triggered();
    }
    else if (ok && newText.isEmpty()){
        QMessageBox::critical(this,"Errore", "Inserire il nome del documento!");
        on_actionRinomina_triggered();
    }
    textOnTitleBar = "C.A.R.T.E. - " + newText;
    this->setWindowTitle(textOnTitleBar);
}

//EXPORT AS PDF ACTION  --> CTRL + S
void EditorWindow::on_actionEsporta_come_PDF_triggered(){
    QString pathname;
    //Dont change the follow line even if there is a warning (UNTIL I STUDY SMARTPOINTER)
    QString fileName = QFileDialog::getSaveFileName(this,"Esporta come PDF", ui->DocName->text(), "PDF File (*.pdf)");

    if (fileName==nullptr){
        return;
    }

    //if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); } //Isn't necessary anymore
    QFile File (fileName);
    pathname = fileName;

    QTextStream writeData(&File);
    QString fileText = ui->RealTextEdit->toHtml(); //HTML NO PLAINTEXT
    QTextDocument doc;
    doc.setHtml(fileText);
    QPrinter file(QPrinter::ScreenResolution);
    file.setOutputFormat(QPrinter::PdfFormat);
    file.setOutputFileName(fileName); // better to use full path
    doc.print(&file); //REFERENCE DO NOT TOUCH IT!
    writeData << &file;
    File.flush();
    File.close();

    ui->RealTextEdit->setFocus();
}

//INVITE A FRIEND WITH URI ACTION
void EditorWindow::on_actionInvita_tramite_URI_triggered(){
    bool ok;
    QString text = QInputDialog::getText(this, tr("Invito a collaborare"),
                                         tr("Inserisci username del nuovo partecipante:"), QLineEdit::Normal,
                                         "", &ok);
    if (ok && !text.isEmpty() && text.size()<=15) {
        //Get data
        QString invited = text;
        QByteArray ba_invited = invited.toLocal8Bit();
        const char *c_invited = ba_invited.data();
        QString applicant = this->_client->getUsername();
        QByteArray ba_applicant = applicant.toLocal8Bit();
        const char *c_applicant = ba_applicant.data();
        QString uri = this->_client->getFileURI();
        QByteArray ba_uri = uri.toLocal8Bit();
        const char *c_uri = ba_uri.data();

        if(invited == applicant) {
            QMessageBox messageBox;
            messageBox.critical(nullptr,"Errore","Non puoi invitare te stesso!");
            messageBox.setFixedSize(600,400);
            on_actionInvita_tramite_URI_triggered();
        } else {
            //Serialize data
            json j;
            jsonUtility::to_json_inviteURI(j, "INVITE_URI_REQUEST", c_invited, c_applicant, c_uri);
            const std::string req = j.dump();

            //Send data (header and body)
            sendRequestMsg(req);
        }
    }
    else if (ok && !text.isEmpty() && text.size()>15) {
        QMessageBox messageBox;
        messageBox.critical(nullptr,"Errore","Inserire un nome minore di 15 caratteri!");
        messageBox.setFixedSize(600,400);
        on_actionInvita_tramite_URI_triggered();
    }
    else if (ok && text.isEmpty()) {
        QMessageBox messageBox;
        messageBox.critical(nullptr,"Errore","Inserire un nome!");
        messageBox.setFixedSize(600,400);
        on_actionInvita_tramite_URI_triggered();
    }
}

//DARK MODE TRIGGERED       -->     CTRL+D
void EditorWindow::on_actionDark_Mode_triggered(){
    PaintItBlack();
}


/***********************************************************************************
*                                                                                  *
*                              STANDALONE FUNCTION                                 *
*                                                                                  *
************************************************************************************/
void EditorWindow::LogoutRequest() {

    BruteClose=false;

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
    if(ui->actionDark_Mode->isChecked()){
        //I see a red door and I want to Paint it Black No colors anymore I want them to turn black I see the girls walk by dressed in their summer clothes I have to turn my head until my darkness goes
        ui->actionDark_Mode->setChecked(true);

        ui->DocumentFrame->setStyleSheet("#DocumentFrame{background-color: #1a1a1a;}");
        ui->editorFrame->setStyleSheet("#editorFrame{background-color: #262626;}");
        ui->RealTextEdit->setStyleSheet("#RealTextEdit{background: #4d4d4d; border-left: 2px solid #e6e6e6;}");
        ui->DocName->setStyleSheet("#DocName{color: #ff8000;}");

        QIcon icoAC, icoAD, icoAS, icoJS, icoCPY, icoCUT, icoPAS, icoREDO, icoUNDO, icoMAGN, icoCOL, v2B, v2I, v2U;
        icoAC.addPixmap(QPixmap(":/image/DarkEditor/center-align.png"),QIcon::Normal,QIcon::On);
        icoAS.addPixmap(QPixmap(":/image/DarkEditor/left-align.png"),QIcon::Normal,QIcon::On);
        icoAD.addPixmap(QPixmap(":/image/DarkEditor/right-align.png"),QIcon::Normal,QIcon::On);
        icoJS.addPixmap(QPixmap(":/image/DarkEditor/justify.png"),QIcon::Normal,QIcon::On);
        icoCPY.addPixmap(QPixmap(":/image/DarkEditor/copy.png"),QIcon::Normal,QIcon::On);
        icoCUT.addPixmap(QPixmap(":/image/DarkEditor/cut.png"),QIcon::Normal,QIcon::On);
        icoPAS.addPixmap(QPixmap(":/image/DarkEditor/paste.png"),QIcon::Normal,QIcon::On);
        icoREDO.addPixmap(QPixmap(":/image/DarkEditor/redo.png"),QIcon::Normal,QIcon::On);
        icoUNDO.addPixmap(QPixmap(":/image/DarkEditor/undo.png"),QIcon::Normal,QIcon::On);
        icoMAGN.addPixmap(QPixmap(":/image/DarkEditor/Magnifier.png"),QIcon::Normal,QIcon::On);
        icoCOL.addPixmap(QPixmap(":/image/DarkEditor/paintbrush.png"),QIcon::Normal,QIcon::On);
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
        ui->buttonRedo->setIcon(icoREDO);
        ui->buttonUndo->setIcon(icoUNDO);
        ui->buttonSearch->setIcon(icoMAGN);
        ui->buttonColor->setIcon(icoCOL);
        ui->buttonGrassetto->setIcon(v2B);
        ui->buttonCorsivo->setIcon(v2I);
        ui->buttonSottolineato->setIcon(v2U);
        //iconContainer CSS
        ui->buttonCopia->setStyleSheet("    #buttonCopia{background-color:#AEAEAE; border-radius:4px;}");
        ui->buttonTaglia->setStyleSheet("   #buttonTaglia{background-color:#AEAEAE; border-radius:4px;}");
        ui->buttonIncolla->setStyleSheet("  #buttonIncolla{background-color:#AEAEAE; border-radius:4px;}");
        ui->buttonRedo->setStyleSheet("     #buttonRedo{background-color:#AEAEAE; border-radius:4px;}");
        ui->buttonUndo->setStyleSheet("     #buttonUndo{background-color:#AEAEAE; border-radius:4px;}");
        ui->buttonSearch->setStyleSheet("   #buttonSearch{background-color:#AEAEAE; border-radius:4px;}");
        ui->buttonColor->setStyleSheet("    #buttonColor{background-color:#AEAEAE; border-radius:4px;}");

    }else{
        //How come no-one told me all throughout history the loneliest people were the ones who always spoke the truth
        ui->actionDark_Mode->setChecked(false);

        ui->DocumentFrame->setStyleSheet("#DocumentFrame{background-color: #FFFFFF;}");
        ui->editorFrame->setStyleSheet("#editorFrame{background-color: #EFEFEF;}");
        ui->RealTextEdit->setStyleSheet("#RealTextEdit{background: #FFFFFF; border-left: 2px solid #404040;}");
        ui->DocName->setStyleSheet("#DocName{color: #505050;}");

        QIcon icoAC, icoAD, icoAS, icoJS, icoCPY, icoCUT, icoPAS, icoREDO, icoUNDO, icoMAGN, icoCOL, v2B, v2I, v2U;
        icoAC.addPixmap(QPixmap(":/image/Editor/center-align.png"),QIcon::Normal,QIcon::On);
        icoAS.addPixmap(QPixmap(":/image/Editor/left-align.png"),QIcon::Normal,QIcon::On);
        icoAD.addPixmap(QPixmap(":/image/Editor/right-align.png"),QIcon::Normal,QIcon::On);
        icoJS.addPixmap(QPixmap(":/image/Editor/justify.png"),QIcon::Normal,QIcon::On);
        icoCPY.addPixmap(QPixmap(":/image/Editor/copy.png"),QIcon::Normal,QIcon::On);
        icoCUT.addPixmap(QPixmap(":/image/Editor/cut.png"),QIcon::Normal,QIcon::On);
        icoPAS.addPixmap(QPixmap(":/image/Editor/paste.png"),QIcon::Normal,QIcon::On);
        icoREDO.addPixmap(QPixmap(":/image/Editor/redo.png"),QIcon::Normal,QIcon::On);
        icoUNDO.addPixmap(QPixmap(":/image/Editor/undo.png"),QIcon::Normal,QIcon::On);
        icoMAGN.addPixmap(QPixmap(":/image/Editor/Magnifier.png"),QIcon::Normal,QIcon::On);
        icoCOL.addPixmap(QPixmap(":/image/Editor/paintbrush.png"),QIcon::Normal,QIcon::On);
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
        ui->buttonRedo->setIcon(icoREDO);
        ui->buttonUndo->setIcon(icoUNDO);
        ui->buttonSearch->setIcon(icoMAGN);
        ui->buttonColor->setIcon(icoCOL);
        ui->buttonGrassetto->setIcon(v2B);
        ui->buttonCorsivo->setIcon(v2I);
        ui->buttonSottolineato->setIcon(v2U);
        //iconContainer CSS
        ui->buttonCopia->setStyleSheet("    #buttonCopia{border-radius:4px}    #buttonCopia:hover{background-color: lightgrey;}");
        ui->buttonTaglia->setStyleSheet("   #buttonTaglia{border-radius:4px}    #buttonTaglia:hover{background-color: lightgrey;}");
        ui->buttonIncolla->setStyleSheet("  #buttonIncolla{border-radius:4px}    #buttonIncolla:hover{background-color: lightgrey;}");
        ui->buttonRedo->setStyleSheet("     #buttonRedo{border-radius:4px}    #buttonGrassetto:hover{background-color: lightgrey;}");
        ui->buttonUndo->setStyleSheet("     #buttonUndo{border-radius:4px}    #buttonGrassetto:hover{background-color: lightgrey;}");
        ui->buttonSearch->setStyleSheet("   #buttonSearch{border-radius:4px}    #buttonGrassetto:hover{background-color: lightgrey;}");
        ui->buttonColor->setStyleSheet("    #buttonColor{border-radius:4px}    #buttonGrassetto:hover{background-color: lightgrey;}");
    }
    //Set Other CSS
    AlignButtonStyleHandler();
    SmokinSexyShowtimeStyleHandler();
    //IN THE END
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
   if(ui->buttonAlignCX->isChecked()){
        ui->buttonAlignCX->setStyleSheet("  #buttonAlignCX{background-color:#AEAEAE; border-radius:4px;}");
        ui->buttonAlignSX->setStyleSheet("  #buttonAlignSX{border-radius:4px}    #buttonAlignSX:hover{background-color: lightgrey;}");
        ui->buttonAlignDX->setStyleSheet("  #buttonAlignDX{border-radius:4px}    #buttonAlignDX:hover{background-color: lightgrey;}");
        ui->buttonAlignJFX->setStyleSheet(" #buttonAlignJFX{border-radius:4px}    #buttonAlignJFX:hover{background-color: lightgrey;}");
    }else if(ui->buttonAlignSX->isChecked()){
        ui->buttonAlignCX->setStyleSheet("  #buttonAlignCX{border-radius:4px}    #buttonAlignCX:hover{background-color: lightgrey;}");
        ui->buttonAlignSX->setStyleSheet("  #buttonAlignSX{background-color:#AEAEAE; border-radius:4px;}");
        ui->buttonAlignDX->setStyleSheet("  #buttonAlignDX{border-radius:4px}    #buttonAlignDX:hover{background-color: lightgrey;}");
        ui->buttonAlignJFX->setStyleSheet(" #buttonAlignJFX{border-radius:4px}    #buttonAlignJFX:hover{background-color: lightgrey;}");
    }else if(ui->buttonAlignDX->isChecked()){
        ui->buttonAlignCX->setStyleSheet("  #buttonAlignCX{border-radius:4px}    #buttonAlignCX:hover{background-color: lightgrey;}");
        ui->buttonAlignSX->setStyleSheet("  #buttonAlignSX{border-radius:4px}    #buttonAlignSX:hover{background-color: lightgrey;}");
        ui->buttonAlignDX->setStyleSheet("  #buttonAlignDX{background-color:#AEAEAE; border-radius:4px;}");
        ui->buttonAlignJFX->setStyleSheet(" #buttonAlignJFX{border-radius:4px}    #buttonAlignJFX:hover{background-color: lightgrey;}");
    }else if(ui->buttonAlignJFX->isChecked()){
        ui->buttonAlignCX->setStyleSheet("  #buttonAlignCX{border-radius:4px}    #buttonAlignCX:hover{background-color: lightgrey;}");
        ui->buttonAlignSX->setStyleSheet("  #buttonAlignSX{border-radius:4px}    #buttonAlignSX:hover{background-color: lightgrey;}");
        ui->buttonAlignDX->setStyleSheet("  #buttonAlignDX{border-radius:4px}    #buttonAlignDX:hover{background-color: lightgrey;}");
        ui->buttonAlignJFX->setStyleSheet(" #buttonAlignJFX{background-color:#AEAEAE; border-radius:4px;}");
    }
}

void EditorWindow::SmokinSexyShowtimeStyleHandler(){
    if(ui->buttonGrassetto->isChecked()) {
        ui->buttonGrassetto->setStyleSheet("#buttonGrassetto{background-color:#AEAEAE; border-radius:4px;}");
        //ui->RealTextEdit->setFontWeight(QFont::Bold);
    } else {
         ui->buttonGrassetto->setStyleSheet("#buttonGrassetto{border-radius:4px}    #buttonGrassetto:hover{background-color: lightgrey;}");
         //ui->RealTextEdit->setFontWeight(QFont::Normal);
    }
    if(ui->buttonCorsivo->isChecked()) {
        ui->buttonCorsivo->setStyleSheet("#buttonCorsivo{background-color:#AEAEAE; border-radius:4px;}");
        //ui->RealTextEdit->setFontItalic(true);
    } else {
         ui->buttonCorsivo->setStyleSheet("#buttonCorsivo{border-radius:4px}    #buttonCorsivo:hover{background-color: lightgrey;}");
         //ui->RealTextEdit->setFontItalic(false);
    }
    if(ui->buttonSottolineato->isChecked()) {
        ui->buttonSottolineato->setStyleSheet("#buttonSottolineato{background-color:#AEAEAE; border-radius:4px;}");
        //ui->RealTextEdit->setFontUnderline(true);
    } else {
         ui->buttonSottolineato->setStyleSheet("#buttonSottolineato{border-radius:4px}    #buttonSottolineato:hover{background-color: lightgrey;}");
         //ui->RealTextEdit->setFontUnderline(false);
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
/*
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
    c.insertText("HidroSaphire è il migliore");
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}
*/


//----------------------OTHER KIND OF FUNCTION OVER THERE-----------------------------//

void EditorWindow::showPopupSuccess(QString result, std::string filename) {
    if(result == "LOGOUTURI_SUCCESS") {
        this->close();
        delete this;
    } else if (result == "RENAME_SUCCESS") {
        ui->DocName->setText(QString::fromStdString(filename));
        _client->setFilename(QString::fromStdString(filename));      //Assign newText to the variable
        ui->RealTextEdit->setFocus(); //Return focus to textedit
    } else if(result == "INVITE_URI_SUCCESS") {
        QMessageBox::warning(this,"Invito effettuato con successo", "Il tuo invito a collaborare è stato correttamente eseguito.");
    }
}

void EditorWindow::showPopupFailure(QString result) {
    if(result == "LOGOUTURI_FAILURE") {
        QMessageBox::critical(this,"Errore", "LogoutURI non completata!");                                 //Stay in the same window
    } else if(result == "RENAME_FAILURE") {
        QMessageBox::warning(this,"Impossibile rinominare", "Esiste già un file con questo nome!");        //Stay in the same window
    } else if(result == "SEND_EMAIL_FAILED") {
        QMessageBox::warning(this,"Impossibile invitare un amico", "Non è stato possibile inviare l'email. Riprovare più tardi");        //Stay in the same window
    } else if(result == "INVITE_URI_FAILURE") {
        QMessageBox::warning(this,"Impossibile invitare un amico", "Non è stato possibile effettuare l'invito. Riprovare");        //Stay in the same window
    } else if(result == "ALREADY_PARTECIPANT") {
        QMessageBox::warning(this,"Impossibile invitare un amico", "L'utente è già un partecipante di questo file");        //Stay in the same window
    } else if(result == "INVITED_NOT_EXIST") {
        QMessageBox::warning(this,"Impossibile invitare un amico", "L'utente che hai inserito non esiste.");        //Stay in the same window
    } else if(result == "SAME_USER") {
        QMessageBox::warning(this,"Impossibile invitare un amico", "Non puoi invitare te stesso!");        //Stay in the same window
    } else {
        QMessageBox::information(nullptr, "Attenzione", "Qualcosa è andato storto! Riprova!");
    }
}


void EditorWindow::sendRequestMsg(std::string req) {
    message msg;
    msg.body_length(req.size());
    std::memcpy(msg.body(), req.data(), msg.body_length());
    msg.body()[msg.body_length()] = '\0';
    msg.encode_header();
    _client->write(msg);
}

void EditorWindow::showSymbolsAt(int firstIndex, std::vector<symbol> symbols) {
    wchar_t letter;
    int index = firstIndex;
    QTextCursor c = ui->RealTextEdit->textCursor();
    foreach (symbol s, symbols) {
        letter = s.getLetter();
        QTextCharFormat oldFormat = c.charFormat();
        QTextCharFormat newFormat = oldFormat;
        if (s.getStyle().isBold())
            newFormat.setFontWeight(QFont::Bold);
        else
            newFormat.setFontWeight(QFont::Normal);
        if (s.getStyle().isItalic())
            newFormat.setFontItalic(true);
        else
            newFormat.setFontItalic(false);
        if (s.getStyle().isUnderlined())
            newFormat.setFontUnderline(true);
        else
            newFormat.setFontUnderline(false);
        newFormat.setFontFamily(QString::fromStdString(s.getStyle().getFontFamily()));
        newFormat.setFontPointSize(s.getStyle().getFontSize());
        int pos = index++;
        c.setPosition(pos);
        c.setCharFormat(newFormat);
        c.insertText(static_cast<QString>(letter));
        ui->RealTextEdit->setTextCursor(c);
        c.setCharFormat(oldFormat);
    }
}

void EditorWindow::showSymbol(std::pair<int, wchar_t> tuple, symbolStyle style) {
    int pos = tuple.first;
    wchar_t c = tuple.second;
    QTextCharFormat format;
    if(style.isBold())
        format.setFontWeight(QFont::Bold);
    else
        format.setFontWeight(QFont::Normal);
    format.setFontItalic(style.isItalic());
    format.setFontUnderline(style.isUnderlined());
    format.setFontFamily(QString::fromStdString(style.getFontFamily()));
    format.setFontPointSize(style.getFontSize());
    QTextCursor cursor = ui->RealTextEdit->textCursor();
    cursor.setPosition(pos);
    cursor.mergeCharFormat(format); //format the char
    cursor.insertText(static_cast<QString>(c));
    qDebug() << "Written in pos: " << pos << endl;
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}

void EditorWindow::eraseSymbol(int index) {
    QTextCursor cursor = ui->RealTextEdit->textCursor();
    int oldPos = cursor.position();
    cursor.setPosition(index);
    cursor.deleteChar();
    cursor.setPosition(oldPos);
    qDebug() << "Deleted char in pos: " << index << endl;
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}

void EditorWindow::eraseSymbols(int startIndex, int endIndex) {    

    QTextCursor cursor = ui->RealTextEdit->textCursor();
    while(endIndex > startIndex) {
        cursor.setPosition(--endIndex);
        cursor.deleteChar();
    }

    /*
    QString plaintext = ui->RealTextEdit->toPlainText();
    plaintext = plaintext.remove(startIndex, endIndex-startIndex);
    ui->RealTextEdit->setPlainText(plaintext);
    */

    qDebug() << "Deleted char range from pos: " << startIndex << " to pos: " << endIndex << endl;
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}

symbolStyle EditorWindow::getCurCharStyle() {
    bool isBold = ui->RealTextEdit->fontWeight()==QFont::Bold;
    symbolStyle style = {isBold, ui->RealTextEdit->fontItalic(), ui->RealTextEdit->fontUnderline(), ui->RealTextEdit->fontFamily().toStdString(), ui->RealTextEdit->font().pointSize()};
    return style;
}

symbolStyle EditorWindow::getStyleFromHTMLStyles(QVector<QVector<QString>>& styles) {
    //Ex. QVector(QVector("Times New Roman", "14", "", "italic", "underline", "2"), QVector("Times New Roman", "14", "600", "", "", "1"))
    //I consider always the first element (vector) of the 'styles' vector of vector
    bool isBold = styles.at(0).at(2) != "" && styles.at(0).at(2) == "600";
    bool isItalic = styles.at(0).at(3) != "" && styles.at(0).at(3) == "italic";
    bool isUnderlined = styles.at(0).at(4) != "" && styles.at(0).at(4) == "underline";
    std::string fontFamily = styles.at(0).at(0).toStdString();
    int fontSize = styles.at(0).at(1).toInt();

    symbolStyle style = {isBold, isItalic, isUnderlined, fontFamily, fontSize}; //create the style for the current char
    if(styles.at(0).at(5).toInt() > 1)
        styles[0][5] = QString::number(styles.at(0).at(5).toInt() - 1); //decrease the number of chars having same style
    else {
        styles.pop_front(); //remove the style from the vector -> i.e. all chars with that style has been handled
    }
    return style;
}

QVector<QVector<QString>> EditorWindow::getStylesFromHTML(QString htmlText) {
    /* STEP 1 - From HTML To list containing only the essential info -> i.e. normalize HTML text */
    QRegExp rx("<span ([^<]+)</span>");
    QStringList list;
    int pos = 0;

    while((pos = rx.indexIn(htmlText, pos)) != -1) {
        list << rx.cap(1);
        pos += rx.matchedLength();
    }

    /* STEP 2 - From list of essential info To list of list containing only the value of the essential info -> normalize previous list */
    QVector<QVector<QString>> finalVector;
    QRegularExpression fontFamilyRegex("font-family:'(.+?)';");
    QRegularExpression fontSizeRegex("font-size:(.+?)pt;");
    QRegularExpression fontWeightRegex("font-weight:(.+?);");
    QRegularExpression fontStyleRegex("font-style:(.+?);");
    QRegularExpression textDecorationRegex("text-decoration: (.+?);");

    foreach (QString s, list) {
        qDebug() << s;
        int numChars = s.mid(s.indexOf('>')).length()-1;
        QVector<QString> styleVector;
        styleVector.push_back(fontFamilyRegex.match(s).captured(1));
        styleVector.push_back(fontSizeRegex.match(s).captured(1));
        styleVector.push_back(fontWeightRegex.match(s).captured(1));
        styleVector.push_back(fontStyleRegex.match(s).captured(1));
        styleVector.push_back(textDecorationRegex.match(s).captured(1));
        styleVector.push_back(QString::number(numChars));
        finalVector.push_back(styleVector);
    }
    qDebug() << "FINAL VECTOR: " << finalVector << endl;
    return finalVector;
}

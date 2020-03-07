#include "editorwindow.h"
#include "ui_editorwindow.h"
#include "MyQTextEdit.h"
#include "infowindow.h"
#include "menuwindow.h"
#include <QInputDialog>
#include <QLineEdit>
#include <QColorDialog>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QGraphicsOpacityEffect>
#include <QPrinter>
#include <QEvent>
#include <stdexcept>

using json = nlohmann::json;

EditorWindow::EditorWindow(myClient* client, QWidget *parent): QMainWindow(parent), ui(new Ui::EditorWindow), _client(client) {
    ui->setupUi(this);
    connect(_client, &myClient::editorResultSuccess, this, &EditorWindow::showPopupSuccess);
    connect(_client, &myClient::editorResultFailure, this, &EditorWindow::showPopupFailure);
    connect(_client, &myClient::insertSymbol, this, &EditorWindow::showSymbol);
    connect(_client, &myClient::eraseSymbol, this, &EditorWindow::eraseSymbol);
    connect(_client, &myClient::eraseSymbols, this, &EditorWindow::eraseSymbols);
    connect(_client, &myClient::formatSymbols, this, &EditorWindow::formatSymbols);
    connect(_client, &myClient::changeFontSize, this, &EditorWindow::changeFontSize);
    connect(_client, &myClient::changeFontFamily, this, &EditorWindow::changeFontFamily);
    connect(_client, &myClient::changeAlignment, this, &EditorWindow::changeAlignment);
    connect(_client, &myClient::insertSymbols, this, &EditorWindow::showSymbolsAt);    
    connect(ui->fontSizeBox->lineEdit(), &QLineEdit::returnPressed, this, &EditorWindow::hideAndChangeCustomFontSize);
    connect(ui->fontSizeBox->lineEdit(), &QLineEdit::editingFinished, this, &EditorWindow::resetFontSize);
    connect(ui->RealTextEdit, &MyQTextEdit::updateAlignmentButton, this, &EditorWindow::updateAlignmentButton);

    ui->listWidget->setStyleSheet(
      "QListWidget::item {"
         "border-color:#e0e0e0;"
      "}");

    QString itemString;
    QList<QListWidgetItem*> fileItem;
    QListWidgetItem* item;
    QListWidgetItem* item2;
    QRegularExpressionValidator* fontSizeValidator;
    QIcon fontIcon(":/image/font_icon.png");

    item = new QListWidgetItem(itemString, ui->listWidget);
    item2 = new QListWidgetItem(itemString, ui->listWidget);
    fontSizeValidator = new QRegularExpressionValidator(QRegularExpression("^(400|[1-9]|[1-9][0-9]|[1-3][0-9][0-9])")); //from 1 to 400

    item->setText(_client->getUsername());
    item->setForeground(QColor(255,1,1));
    fileItem.append(item);
    item2->setText("Genitore Due");
    fileItem.append(item2);

    ui->fontSizeBox->lineEdit()->setValidator(fontSizeValidator);
    ui->listWidget->hide();
    ui->labelCollab->hide();
    ui->DocNameButton->setText(docName);
    ui->RealTextEdit->setFontPointSize(14);
    ui->RealTextEdit->setFontFamily("Times New Roman");
    ui->RealTextEdit->setAcceptDrops(false);
    ui->fontFamilyBox->setCurrentText(ui->RealTextEdit->currentFont().family());
    for(int i=0; i<ui->fontFamilyBox->count(); i++) {
        ui->fontFamilyBox->setItemIcon(i, fontIcon);
    }
    ui->RealTextEdit->setEditorColor(client->getColor());
    hideLastAddedItem(ui->fontFamilyBox);
    qRegisterMetaType<std::vector<symbol>>("std::vector<symbol>");
    showSymbolsAt(0, _client->getVector());
    ui->RealTextEdit->installEventFilter(this);
    textOnTitleBar = "C.A.R.T.E. - " + docName;
    this->setWindowTitle(textOnTitleBar);
}

EditorWindow::~EditorWindow() {
    delete ui;
}


/***********************************************************************************
*                                 TOP BAR FUNCTION                                 *
************************************************************************************/
void EditorWindow::on_DocNameButton_clicked(){
    on_actionRinomina_triggered();
}

/***********************************************************************************
*                                TEXT FORMAT BUTTONS                               *
************************************************************************************/
void EditorWindow::on_buttonBold_clicked() {
    int format = FORMAT_UNKNOWN;
    if(ui->buttonBold->isChecked()) {
        ui->buttonBold->setChecked(true);
        ui->RealTextEdit->setFontWeight(QFont::Bold);
        format = MAKE_BOLD;
    } else {
        ui->buttonBold->setChecked(false);
        ui->RealTextEdit->setFontWeight(QFont::Normal);
        format = UNMAKE_BOLD;
    }
    refreshFormatButtons();
    sendFormatRequest(format);
    ui->RealTextEdit->setFocus();
}

void EditorWindow::on_buttonItalic_clicked() {
    int format = FORMAT_UNKNOWN;
    if(ui->buttonItalic->isChecked()) {
        ui->buttonItalic->setChecked(true);
        ui->RealTextEdit->setFontItalic(true);
        format = MAKE_ITALIC;
    } else {
        ui->buttonItalic->setChecked(false);
        ui->RealTextEdit->setFontItalic(false);
        format = UNMAKE_ITALIC;
    }
    refreshFormatButtons();
    sendFormatRequest(format);
    ui->RealTextEdit->setFocus();
}

void EditorWindow::on_buttonUnderline_clicked() {
    int format = FORMAT_UNKNOWN;
    if(ui->buttonUnderline->isChecked()) {
        ui->buttonUnderline->setChecked(true);
        ui->RealTextEdit->setFontUnderline(true);
        format = MAKE_UNDERLINE;
    } else {
        ui->buttonUnderline->setChecked(false);
        ui->RealTextEdit->setFontUnderline(false);
        format = UNMAKE_UNDERLINE;
    }
    refreshFormatButtons();
    sendFormatRequest(format);
    ui->RealTextEdit->setFocus();
}

/***********************************************************************************
*                            TEXT COLOR BUTTONS                                    *
************************************************************************************/
void EditorWindow::on_buttonBackgroundColor_clicked() {
    //VERSION 1 --> Working only if EditorWindow is build without passing the parent (2° argument)
        /*
        QColor backColour = QColorDialog::getColor();
        ui->RealTextEdit->setTextBackgroundColor(backColour);
        */
    //VERSION 2 --> Working if EditorWindow is build passing menuWindow as a parent (2° argument)
        QColorDialog *dialog = new QColorDialog(this); //passing this is important for returning
        dialog->show();
        QObject::connect(dialog,&QDialog::accepted,[=]() {
            QColor txtColour = dialog->currentColor();
            ui->RealTextEdit->setTextBackgroundColor(txtColour);
        });
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}


void EditorWindow::on_buttonColor_clicked() {
    //VERSION 1 --> Working only if EditorWindow is build without passing the parent (2° argument)
    /*
        QColor txtColour = QColorDialog::getColor();
        ui->RealTextEdit->setTextColor(txtColour);
    */
    //VERSION 2 --> Working if EditorWindow is build passing menuWindow as a parent (2° argument)
        QColorDialog *dialog = new QColorDialog(this); //passing this is important for returning
        dialog->show();
        QObject::connect(dialog,&QDialog::accepted,[=]() {
            QColor txtColour = dialog->currentColor();
            ui->RealTextEdit->setTextColor(txtColour);
        });
    ui->RealTextEdit->setFocus();
}

/***********************************************************************************
*                            TEXT ALIGNMENT BUTTONS                                *
************************************************************************************/
void EditorWindow::on_buttonAlignDX_clicked() {
    QTextCursor cursor = ui->RealTextEdit->textCursor();

    /* Align Right */
    if(ui->buttonAlignDX->isChecked()) {
        AlignDXButtonHandler();
        AlignButtonStyleHandler();
        if(cursor.hasSelection()) //align multiple (selected) blocks
            alignMultipleBlocks(cursor.selectionStart(), cursor.selectionEnd(), cursor, Qt::AlignRight);
        else
            alignSingleBlock(cursor, Qt::AlignRight); //align single block
    }
    else { /* Align Left by default */
        AlignSXButtonHandler();
        AlignButtonStyleHandler();
        if(cursor.hasSelection()) //align multiple (selected) blocks
            alignMultipleBlocks(cursor.selectionStart(), cursor.selectionEnd(), cursor, Qt::AlignLeft);
        else
            alignSingleBlock(cursor, Qt::AlignLeft); //align single block
    }
    ui->RealTextEdit->setFocus();
}

void EditorWindow::on_buttonAlignCX_clicked() {
    QTextCursor cursor = ui->RealTextEdit->textCursor();

    /* Align Center */
    if(ui->buttonAlignCX->isChecked()) {
        AlignCXButtonHandler();
        AlignButtonStyleHandler();
        if(cursor.hasSelection()) //align multiple (selected) blocks
            alignMultipleBlocks(cursor.selectionStart(), cursor.selectionEnd(), cursor, Qt::AlignCenter);
        else
            alignSingleBlock(cursor, Qt::AlignCenter); //align single block
    }
    else { /* Align Left by default */
        AlignSXButtonHandler();
        AlignButtonStyleHandler();
        if(cursor.hasSelection()) //align multiple (selected) blocks
            alignMultipleBlocks(cursor.selectionStart(), cursor.selectionEnd(), cursor, Qt::AlignLeft);
        else
            alignSingleBlock(cursor, Qt::AlignLeft); //align single block
    }
    ui->RealTextEdit->setFocus();
}

void EditorWindow::on_buttonAlignSX_clicked() {
    QTextCursor cursor = ui->RealTextEdit->textCursor();

    /* Align Left */
    if(ui->buttonAlignSX->isChecked()) {
        AlignSXButtonHandler();
        AlignButtonStyleHandler();
        if(cursor.hasSelection()) //align multiple (selected) blocks
            alignMultipleBlocks(cursor.selectionStart(), cursor.selectionEnd(), cursor, Qt::AlignLeft);
        else
            alignSingleBlock(cursor, Qt::AlignLeft); //align single block
    }
    else { /* Align Justify */
        AlignJFXButtonHandler();
        AlignButtonStyleHandler();
        if(cursor.hasSelection()) //align multiple (selected) blocks
            alignMultipleBlocks(cursor.selectionStart(), cursor.selectionEnd(), cursor, Qt::AlignJustify);
        else
            alignSingleBlock(cursor, Qt::AlignJustify); //align single block
    }
    ui->RealTextEdit->setFocus();
}

void EditorWindow::on_buttonAlignJFX_clicked() {
    QTextCursor cursor = ui->RealTextEdit->textCursor();

    /* Align Justify */
    if(ui->buttonAlignJFX->isChecked()) {
        AlignJFXButtonHandler();
        AlignButtonStyleHandler();
        if(cursor.hasSelection()) //align multiple (selected) blocks
            alignMultipleBlocks(cursor.selectionStart(), cursor.selectionEnd(), cursor, Qt::AlignJustify);
        else
            alignSingleBlock(cursor, Qt::AlignJustify); //align single block
    }
    else { /* Align Left by default */
        AlignSXButtonHandler();
        AlignButtonStyleHandler();
        if(cursor.hasSelection()) //align multiple (selected) blocks
            alignMultipleBlocks(cursor.selectionStart(), cursor.selectionEnd(), cursor, Qt::AlignLeft);
        else
            alignSingleBlock(cursor, Qt::AlignLeft); //align single block
    }
    ui->RealTextEdit->setFocus();
}

/***********************************************************************************
*                           TEXT EDITING BUTTONS                                   *
************************************************************************************/
void EditorWindow::on_buttonCut_clicked() {
    QTextCursor cursor = ui->RealTextEdit->textCursor();
    if(cursor.hasSelection()) {
        changeNextCharsAlignment(cursor, cursor.selectionStart(), cursor.selectionEnd());
        removeCharRangeRequest(cursor);
        ui->RealTextEdit->cut();
    }
    ui->RealTextEdit->setFocus();
}

void EditorWindow::on_buttonPaste_clicked() {
    QTextCursor cursor = ui->RealTextEdit->textCursor();
    int pos;
    bool hasSelection = false;

    cursor.hasSelection() ? pos = cursor.selectionStart() : pos = cursor.position();
    try {
        if(cursor.hasSelection()) {
            hasSelection = true;
            changeNextCharsAlignment(cursor, cursor.selectionStart(), cursor.selectionEnd());
            removeCharRangeRequest(cursor);
        }
        insertCharRangeRequest(pos, hasSelection);
        ui->RealTextEdit->paste();
        ui->RealTextEdit->setFocus();
    } catch(OperationNotSupported& ex) {
        qDebug() << ex.what();
        cursor.removeSelectedText();
    }
}

void EditorWindow::on_buttonCopy_clicked() {
    ui->RealTextEdit->copy();
    ui->RealTextEdit->setFocus();
}

/***********************************************************************************
*                         TEXT SEARCH BUTTON                                       *
************************************************************************************/
void EditorWindow::on_buttonSearch_clicked() {
    QString findtext = QInputDialog::getText(this, "Search", "Insert text to search: ");
    ui->RealTextEdit->moveCursor(QTextCursor::Start);
    if(!ui->RealTextEdit->find(findtext,QTextDocument::FindWholeWords))
        QMessageBox::information(this, "Warning", "No result found!");
    ui->RealTextEdit->setFocus();
}

/***********************************************************************************
*                            FONT SIZE COMBOBOX                                    *
************************************************************************************/
void EditorWindow::on_fontSizeBox_currentIndexChanged(int index) {
    int fontSize = ui->fontSizeBox->currentText().toInt(); //get fontSize from text of item selected
    ui->RealTextEdit->setFontPointSize(fontSize);
    changedCurIndex = true;
    sendFontChangeRequest(fontSize);
    ui->RealTextEdit->setFocus();
}

void EditorWindow::on_fontSizeBox_activated(int index) {
    if(!changedCurIndex)
        setCurPointSize = true;
    changedCurIndex = false;
}

/***********************************************************************************
*                            FONT FAMILY COMBOBOX                                  *
************************************************************************************/
void EditorWindow::on_fontFamilyBox_currentIndexChanged(int index) {
    if(ui->fontFamilyBox->currentText() != "") {
        QTextCursor c = ui->RealTextEdit->textCursor();
        QString fontFamily = ui->fontFamilyBox->currentText(); //get fontfamily from text of item selected
        ui->RealTextEdit->setFontFamily(fontFamily);
        sendFontChangeRequest(fontFamily.toStdString());
        ui->RealTextEdit->setFocus();
    }
}

/***********************************************************************************
*                            BUTTON FOR COLLABORATORS                              *
************************************************************************************/
void EditorWindow::on_buttonCollab_clicked() {
    if(ui->buttonCollab->isChecked()) {
        ui->buttonCollab->setChecked(true);
        ui->actionCollaboratori->setText("Nascondi Collaboratori");
        ui->listWidget->show();
        ui->labelCollab->show();
        //ui->frameCollab->show(); it has to be ever showed
    } else {
        ui->buttonCollab->setChecked(false);
        ui->actionCollaboratori->setText("Mostra Collaboratori");
        ui->listWidget->hide();
        ui->labelCollab->hide();
        //ui->frameCollab->hide(); Never hide the "frameCollab"
    }
    ui->RealTextEdit->setFocus();
}

/***********************************************************************************
*                              RealTextEdit FUNCTIONS                              *
************************************************************************************/
void EditorWindow::on_RealTextEdit_selectionChanged() {
    //Update UI based on current char format (after pressing left/right arrow after selection)
    QTextCursor c = ui->RealTextEdit->textCursor();

    if(!c.hasSelection()) {
        if(ui->RealTextEdit->toPlainText().length() == 0) { //there aren't chars
            setupInitialCondition();
        } else {
            ui->fontSizeBox->setCurrentText(QString::number(c.charFormat().fontPointSize()));
            ui->fontFamilyBox->setCurrentIndex(ui->fontFamilyBox->findText(c.charFormat().fontFamily()));
            c.charFormat().fontWeight()==QFont::Bold ? ui->buttonBold->setChecked(true) : ui->buttonBold->setChecked(false);
            c.charFormat().fontItalic()==true ? ui->buttonItalic->setChecked(true) : ui->buttonItalic->setChecked(false);
            c.charFormat().fontUnderline()==true ? ui->buttonUnderline->setChecked(true) : ui->buttonUnderline->setChecked(false);
            if(c.blockFormat().alignment()==Qt::AlignRight)
                AlignDXButtonHandler();
            else if(c.blockFormat().alignment()==Qt::AlignCenter)
                AlignCXButtonHandler();
            else if(c.blockFormat().alignment()==Qt::AlignJustify)
                AlignJFXButtonHandler();
            else
                AlignSXButtonHandler();
        }
        AlignButtonStyleHandler();
        refreshFormatButtons();
    }
}

void EditorWindow::on_RealTextEdit_cursorPositionChanged() {
    QTextCursor c = ui->RealTextEdit->textCursor();

    /****************************************************************
     * Hidro's Personal Solution to handle the QTBUG-29393 --> https://bugreports.qt.io/browse/QTBUG-29393
     * https://github.com/giovannic96/Real-time-collaborative-text-editor/issues/29
     ****************************************************************/
    if(ui->RealTextEdit->fontPointSize() <= 0) {
        int dimensionFromOtherSide = (ui->fontSizeBox->currentText()).toInt();
        QString fontFamily = ui->fontFamilyBox->currentText();
        ui->RealTextEdit->setFontPointSize(dimensionFromOtherSide);
        ui->RealTextEdit->setFontFamily(fontFamily);
        qDebug()<<"Il Cursore è sicuramente in posizione iniziale";
    }

    /****************************************************************
     *                      TEXT FONT FAMILY                        *
     ****************************************************************/
    if(!c.hasSelection()) {
        QString fontFamily = ui->RealTextEdit->fontFamily();
        ui->fontFamilyBox->setCurrentText(fontFamily);
        ui->fontFamilyBox->setCurrentIndex(ui->fontFamilyBox->findText(ui->fontFamilyBox->currentText()));
    }
    else {
        QString fontFamilyCalculated = calculateFontFamilyComboBox(c);
        if(fontFamilyCalculated == "FONT_UNKNOWN") {
            ui->fontSizeBox->setCurrentText(""); //blank text on item combobox
            ui->fontFamilyBox->setCurrentIndex(ui->fontFamilyBox->findText(""));
        } else {
            ui->fontFamilyBox->setCurrentText(fontFamilyCalculated);
            ui->RealTextEdit->setFontFamily(fontFamilyCalculated); //set fontFamily to common fontFamily of the chars
        }
    }

    /****************************************************************
     *                      TEXT FONT SIZE                          *
     ****************************************************************/
    if(!c.hasSelection()) {
        int fontPointSize = static_cast<int>(ui->RealTextEdit->fontPointSize());
        ui->fontSizeBox->setCurrentText(QString::number(fontPointSize));
        ui->fontSizeBox->setCurrentIndex(ui->fontSizeBox->findText(ui->fontSizeBox->currentText()));
    }
    else {
        int fontSizeCalculated = calculateFontSizeComboBox(c);
        if(fontSizeCalculated == -1) {
            ui->fontSizeBox->setCurrentText(""); //blank text on item combobox
        } else {
            ui->fontSizeBox->setCurrentText(QString::number(fontSizeCalculated));
            ui->RealTextEdit->setFontPointSize(fontSizeCalculated); //set fontSize to common fontSize of the chars
        }
    }

    /****************************************************************
     *                      TEXT ALIGNMENT                          *
     ****************************************************************/
    if(!c.hasSelection()) {
        if(ui->RealTextEdit->alignment() == Qt::AlignCenter)
            AlignCXButtonHandler();
        else if(ui->RealTextEdit->alignment() == Qt::AlignRight)
            AlignDXButtonHandler();
        else if(ui->RealTextEdit->alignment() == Qt::AlignJustify)
            AlignJFXButtonHandler();
        else
            AlignSXButtonHandler();
    } else {
        int alignmentCalculated = calculateAlignmentButtons(c);
        if(alignmentCalculated == -1) {
            AlignNoneButtonHandler(); //uncheck all align buttons
        } else {
            if(alignmentCalculated == Qt::AlignRight)
                AlignDXButtonHandler();
            else if(alignmentCalculated == Qt::AlignCenter)
                AlignCXButtonHandler();
            else if(alignmentCalculated == Qt::AlignJustify)
                AlignJFXButtonHandler();
            else
                AlignSXButtonHandler();
        }
    }
    AlignButtonStyleHandler();

    /****************************************************************
     *                  TEXT FORMAT (Bold/Italic/Underline)         *
     ****************************************************************/
    if(!c.hasSelection()) {
        if(ui->RealTextEdit->fontWeight() == QFont::Bold)
            ui->buttonBold->setChecked(true);
        else
            ui->buttonBold->setChecked(false);
        if(ui->RealTextEdit->fontItalic())
            ui->buttonItalic->setChecked(true);
        else
            ui->buttonItalic->setChecked(false);
        if(ui->RealTextEdit->fontUnderline())
            ui->buttonUnderline->setChecked(true);
        else
            ui->buttonUnderline->setChecked(false);
    } else {
        std::vector<bool> buttonChecks = calculateButtonChecks(c);
        ui->buttonBold->setChecked(buttonChecks.at(0));
        ui->buttonItalic->setChecked(buttonChecks.at(1));
        ui->buttonUnderline->setChecked(buttonChecks.at(2));
    }
    refreshFormatButtons();
}

/***********************************************************************************
*                                   EVENT HANDLER                                  *
************************************************************************************/
bool EditorWindow::eventFilter(QObject *obj, QEvent *ev) {

    if (obj == ui->RealTextEdit && ev->type() == QEvent::KeyPress) {

        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(ev);
        qDebug() << "You Pressed Key " + keyEvent->text();
        int key = keyEvent->key();
        Qt::KeyboardModifiers modifiers = keyEvent->modifiers();
        QList<Qt::Key> modifiersList;

        if(!keyEvent->text().isEmpty()) { //to ignore chars like "CAPS_LOCK", "SHIFT", "CTRL", etc...
        //************************************************* CTRL-X *************************************************
        if (keyEvent->matches(QKeySequence::Cut)) {
            QTextCursor cursor = ui->RealTextEdit->textCursor();
            if(cursor.hasSelection()) {
                changeNextCharsAlignment(cursor, cursor.selectionStart(), cursor.selectionEnd());
                removeCharRangeRequest(cursor);
            }
            return QObject::eventFilter(obj, ev);
        } //*********************************************** CTRL-C *************************************************
        else if (keyEvent->matches(QKeySequence::Copy)) {
            return false; //let the original handler handle this sequence
        } //*********************************************** CTRL-V *************************************************
        else if (keyEvent->matches(QKeySequence::Paste)) {
            QTextCursor cursor = ui->RealTextEdit->textCursor();
            int pos;
            bool hasSelection = false;

            cursor.hasSelection() ? pos = cursor.selectionStart() : pos = cursor.position();
            try {
                if(cursor.hasSelection()) {
                    hasSelection = true;
                    changeNextCharsAlignment(cursor, cursor.selectionStart(), cursor.selectionEnd());
                    removeCharRangeRequest(cursor);
                }
                insertCharRangeRequest(pos, hasSelection);
            } catch(OperationNotSupported& ex) {
                qDebug() << ex.what();
                cursor.removeSelectedText();
                return true; //not paste text
            }
            return QObject::eventFilter(obj, ev);
        } //*********************************************** CTRL-A *************************************************
        else if (keyEvent->matches(QKeySequence::SelectAll)) {
            return false; //let the original handler handle this sequence
        } //******************************************** ALL THE OTHER CTRL COMBINATION ****************************
        else if((modifiers & Qt::ControlModifier) && !(key == Qt::Key_BracketLeft) && !(key == Qt::Key_BracketRight)
                && !(key == Qt::Key_BraceLeft) && !(key == Qt::Key_BraceRight) && !(key == Qt::Key_At) && !(key == Qt::Key_NumberSign) ) {
            qDebug() << "Operation Not Supported";
            return true;
        } //******************************************** ANY DIGIT *************************************************
        else if(!(key == Qt::Key_Backspace) && !(key == Qt::Key_Delete) && !(key == Qt::Key_Escape)) {
            //Get data
            std::pair<int, wchar_t> tuple;
            QTextCursor cursor = ui->RealTextEdit->textCursor();
            QColor color(ui->RealTextEdit->getEditorColor());
            int pos;

            //set default value
            bool firstCharBold = ui->buttonBold->isChecked();
            bool firstCharItalic = ui->buttonItalic->isChecked();
            bool firstCharUnderline = ui->buttonUnderline->isChecked();
            int firstCharAlignment = static_cast<int>(detectAlignment());
            int firstCharFontSize = ui->fontSizeBox->currentText().toInt();
            std::string firstCharFontFamily = ui->fontFamilyBox->currentText().toStdString();

            if(cursor.hasSelection()) { //Remove range of characters selected
                pos = cursor.selectionStart();
                int startIndex = cursor.selectionStart();
                int endIndex = cursor.selectionEnd();
                QTextCursor tempCursor = cursor;

                //change alignment of the chars next to the selection (until the end of that block)
                changeNextCharsAlignment(tempCursor, startIndex, endIndex);

                //get properties of the first char of the selection
                tempCursor.setPosition(startIndex+1, QTextCursor::MoveAnchor);
                firstCharBold = tempCursor.charFormat().font().weight() == QFont::Bold;
                firstCharItalic = tempCursor.charFormat().font().italic();
                firstCharUnderline = tempCursor.charFormat().font().underline();
                firstCharFontSize = tempCursor.charFormat().font().pointSize();
                firstCharFontFamily = tempCursor.charFormat().font().family().toStdString();
                if(tempCursor.positionInBlock() == 0) { //this happens when I select also the newLine (<CR>)
                    tempCursor.movePosition(QTextCursor::Left); //get alignment of previous block
                    firstCharAlignment = static_cast<int>(tempCursor.blockFormat().alignment());
                    tempCursor.movePosition(QTextCursor::Right);
                }
                else
                    firstCharAlignment = static_cast<int>(tempCursor.blockFormat().alignment());

                //change format
                QTextCharFormat f;
                QTextBlockFormat textBlockFormat;
                if(!ui->buttonBold->isChecked())
                    f.setFontWeight(firstCharBold ? QFont::Bold : QFont::Normal);
                else
                    f.setFontWeight(QFont::Bold);
                if(!ui->buttonItalic->isChecked())
                    f.setFontItalic(firstCharItalic);
                else
                    f.setFontItalic(true);
                if(!ui->buttonUnderline->isChecked())
                    f.setFontUnderline(firstCharUnderline);
                else
                    f.setFontUnderline(true);
                if(ui->fontSizeBox->currentText() == "")
                    f.setFontPointSize(firstCharFontSize); //set fontSize of first char of the selection
                else
                    f.setFontPointSize(ui->fontSizeBox->currentText().toInt()); //set fontSize to common fontSize of the chars
                if(ui->fontFamilyBox->currentText() == "")
                    f.setFontFamily(QString::fromStdString(firstCharFontFamily)); //set fontFamily of first char of the selection
                else
                    f.setFontFamily(ui->fontFamilyBox->currentText()); //set fontFamily to common fontFamily of the chars
                f.setBackground(color);
                textBlockFormat.setAlignment(static_cast<Qt::AlignmentFlag>(firstCharAlignment));

                //apply format
                cursor.setPosition(startIndex, QTextCursor::MoveAnchor);
                cursor.setPosition(endIndex, QTextCursor::KeepAnchor);
                cursor.mergeCharFormat(f);
                cursor.mergeBlockFormat(textBlockFormat);
                ui->RealTextEdit->mergeCurrentCharFormat(f);
                ui->RealTextEdit->setAlignment(textBlockFormat.alignment());
                ui->RealTextEdit->setTextCursor(cursor);

                //update data on textedit buttons/combobox
                ui->buttonBold->setChecked(f.fontWeight()==QFont::Bold);
                ui->buttonItalic->setChecked(f.fontItalic());
                ui->buttonUnderline->setChecked(f.fontUnderline());
                setAlignmentButton(static_cast<Qt::AlignmentFlag>(static_cast<int>(textBlockFormat.alignment())));
                refreshFormatButtons();
                AlignButtonStyleHandler();
                ui->fontSizeBox->setCurrentText(QString::number(f.fontPointSize()));
                ui->fontFamilyBox->setCurrentText(f.fontFamily());

                //Serialize data
                json j;
                jsonUtility::to_json_removal_range(j, "REMOVALRANGE_REQUEST", startIndex, endIndex);
                const std::string req = j.dump();

                //Send data (header and body)
                sendRequestMsg(req);
            } else {
                pos = cursor.position();
            }

            //update textedit formats
            wchar_t c = keyEvent->text().toStdWString().c_str()[0];
            ui->RealTextEdit->setFontWeight(ui->buttonBold->isChecked() ? QFont::Bold : QFont::Normal);
            ui->RealTextEdit->setFontItalic(ui->buttonItalic->isChecked());
            ui->RealTextEdit->setFontUnderline(ui->buttonUnderline->isChecked());
            ui->RealTextEdit->setFontPointSize(ui->fontSizeBox->currentText().toInt());
            ui->RealTextEdit->setFontFamily(ui->fontFamilyBox->currentText());
            ui->RealTextEdit->setAlignment(detectAlignment());

            //update char format
            QTextCharFormat form;
            form.setBackground(color);
            form.setFontWeight(ui->buttonBold->isChecked() ? QFont::Bold : QFont::Normal);
            form.setFontItalic(ui->buttonItalic->isChecked());
            form.setFontUnderline(ui->buttonUnderline->isChecked());
            form.setFontPointSize(ui->fontSizeBox->currentText().toInt());
            form.setFontFamily(ui->fontFamilyBox->currentText());
            cursor.setCharFormat(form);
            ui->RealTextEdit->setTextCursor(cursor);

            //if that selected size is not an index of combobox, add it (and hide it)
            if(ui->fontSizeBox->findText(ui->fontSizeBox->currentText()) == -1) {
                ui->fontSizeBox->addItem(ui->fontSizeBox->currentText());
                hideLastAddedItem(ui->fontSizeBox);
            }

            qDebug() << "char: " << c;
            tuple = std::make_pair(pos, c);

            //Serialize data
            json j;
            jsonUtility::to_json_insertion(j, "INSERTION_REQUEST", tuple, getCurCharStyle());
            const std::string req = j.dump();

            //Send data (header and body)
            sendRequestMsg(req);
            return QObject::eventFilter(obj, ev);
        } //******************************************** BACKSPACE *************************************************
        else if(key == Qt::Key_Backspace) {
            QTextCursor cursor = ui->RealTextEdit->textCursor();
            int pos = cursor.position();

            if(cursor.hasSelection()) { //Remove range of characters selected
                changeNextCharsAlignment(cursor, cursor.selectionStart(), cursor.selectionEnd());
                removeCharRangeRequest(cursor);
            }
            else if(pos > 0) { //Remove only one character
                changeNextCharsAlignment(cursor, pos-1, pos);
                removeCharRequest(pos-1);
            }
            return QObject::eventFilter(obj, ev);
        } //******************************************** CANC ******************************************************
        else if(key == Qt::Key_Delete) {
            QTextCursor cursor = ui->RealTextEdit->textCursor();
            int pos = cursor.position();

            if(cursor.hasSelection()) {
                changeNextCharsAlignment(cursor, cursor.selectionStart(), cursor.selectionEnd());
                removeCharRangeRequest(cursor); //Remove range of characters selected
            }
            else if(pos >= 0 && pos < ui->RealTextEdit->toPlainText().size()) {
                changeNextCharsAlignment(cursor, pos, pos+1);
                removeCharRequest(pos); //Remove only one character
            }
            return QObject::eventFilter(obj, ev);
        } //********************************************* ESC ******************************************************
        else if(key == Qt::Key_Escape) {
            return true; //do not handle ESC
        }
        } else
            return QObject::eventFilter(obj, ev);
        return false; //or return QObject::eventFilter(obj, ev);
    }
    return false; //or return QObject::eventFilter(obj, ev);
}

  //******************//
 // Shortcut Handler //
//******************//
void EditorWindow::keyPressEvent(QKeyEvent *e) {
    //WORKING ON IT
    if ((e->key() == Qt::Key_I) && (e->modifiers() == Qt::ControlModifier)  && (e->modifiers() == Qt::ShiftModifier) && QApplication::keyboardModifiers()){
        qDebug()<<" CTRL + Shift + I";
        on_actionAbout_triggered();
    }else if((e->key() == Qt::Key_S) && (e->modifiers() == Qt::ControlModifier) && QApplication::keyboardModifiers()){
        qDebug()<<" CTRL + S";
        on_actionEsporta_come_PDF_triggered();
    }else if((e->key() == Qt::Key_F11) && (e->modifiers() == Qt::ControlModifier)){
        qDebug()<<" CTRL + F11";
        on_actionFullscreen_triggered();
    }else if((e->key() == Qt::Key_Q) && (e->modifiers() == Qt::ControlModifier) && QApplication::keyboardModifiers()){
        qDebug()<<" CTRL + Q";
        on_actionExit_triggered();
    }else if((e->key() == Qt::Key_N) && (e->modifiers() == Qt::ControlModifier) && QApplication::keyboardModifiers()){
        qDebug()<<" CTRL + N - But the action is temporanely disabled";
        on_actionNew_triggered();
    }else if((e->key() == Qt::Key_R) && (e->modifiers() == Qt::ControlModifier) && QApplication::keyboardModifiers()){
        qDebug()<<" CTRL + R";
        on_actionRinomina_triggered();
    }else if((e->key() == Qt::Key_D) && (e->modifiers() == Qt::ControlModifier) && QApplication::keyboardModifiers()){
        qDebug()<<" CTRL + D";
        on_actionDark_Mode_triggered();
    }else if((e->key() == Qt::Key_I) && (e->modifiers() == Qt::ControlModifier) && QApplication::keyboardModifiers()){
        qDebug()<<" CTRL + I";
        ui->buttonItalic->click();
    }else if((e->key() == Qt::Key_B) && (e->modifiers() == Qt::ControlModifier) && QApplication::keyboardModifiers()){
        qDebug()<<" CTRL + B";
        ui->buttonBold->click();
    }else if((e->key() == Qt::Key_S) && (e->modifiers() == Qt::ControlModifier) && QApplication::keyboardModifiers()){
        qDebug()<<" CTRL + S";
        ui->buttonUnderline->click();
    }else if((e->key() == Qt::Key_Q) && (e->modifiers() == Qt::ControlModifier) && (e->modifiers() == Qt::ShiftModifier) && QApplication::keyboardModifiers()){
        qDebug()<<" CTRL + Shift + Q";
        on_actionEsci_triggered();
    }
}

//***********************//
// Close Editor Handler // - Is an override of original closeEvent. Check if Editor is close normally or forced (like ALT+F4)
//*********************//
void EditorWindow::closeEvent(QCloseEvent * event) {
    bool StayInThisWindow = true;
    if(_client->getStatus()==false) {
        StayInThisWindow = handleConnectionLoss();
        if(StayInThisWindow==true) {
            event->ignore();    //IGNORE FORCED CLOSE EVENT --> Stay in this window (EditorWindow)
        }
    } else {
        //If is a forced close then, ask the user if he really wants to close the document
        if(BruteClose==true) {
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Uscita", "Uscire dal documento?", QMessageBox::Yes|QMessageBox::No);
            if (reply == QMessageBox::Yes) {
                event->ignore();    //IGNORE FORCED CLOSE EVENT --> Is the "override", i'll handle the close event with a LogoutRequest();
                LogoutRequest();    //By ignoring the closing event, the LogoutRequest() brings me back to the menuWindow.
             }else{
                event->ignore();    //IGNORE FORCED CLOSE EVENT --> Stay in this window (EditorWindow)
            }
        }
    }
}

/***********************************************************************************
*                                       ACTION                                     *
*                                                                                  *
*     Action can be recallable with shortcut, but for now it doesn't work          *
************************************************************************************/
//FULLSCREEN ACTION      -->     CTRL+F11
void EditorWindow::on_actionFullscreen_triggered() {
   if(SchermoIntero==false) {
        SchermoIntero=true;
        ui->actionFullscreen->setText("Modalità Finestra");
        this->setWindowState(Qt::WindowFullScreen);
    } else if(SchermoIntero==true) {
        SchermoIntero=false;
        this->setWindowState(Qt::WindowNoState); //WindowNoState save the old position and the old size of the window
        ui->actionFullscreen->setText("Schermo Intero");
    }
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}

//NEW DOCUMENT ACTION    -->     CTRL+N
void EditorWindow::on_actionNew_triggered() {
    //on_newDocButton_clicked();
}

//ABOUT ACTION           -->     CTRL+Shift+I
void EditorWindow::on_actionAbout_triggered() {
    infoWindow *iw = new infoWindow(this);
    iw->show();
}

//EXIT DOCUMENT ACTION  -->     CTRL+Q
void EditorWindow::on_actionExit_triggered() {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Uscita", "Uscire dal documento?",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
      LogoutRequest(); //Return to MenuWindow (close only the current document)
    }
}

//RENAME ACTION         -->     CTRL+R
void EditorWindow::on_actionRinomina_triggered() {
    bool ok, StayInThisWindow;
    QString newText = QInputDialog::getText(this, tr("Titolo documento"),
                                         tr("Inserisci un nome per il documento:"), QLineEdit::Normal, docName, &ok);

    if(ok && !newText.isEmpty() && newText.size()<=25) {
        //Serialize data
        json j;
        jsonUtility::to_jsonRenamefile(j, "RENAMEFILE_REQUEST", newText.toStdString(), _client->getFileURI().toStdString(), _client->getUsername().toStdString());
        const std::string req = j.dump();

        //Send data (header and body)
        sendRequestMsg(req);
    }else if(ok && !newText.isEmpty() && newText.size()>25){
        QMessageBox::critical(this,"Errore", "Inserire un nome minore di 25 caratteri!!");
        on_actionRinomina_triggered();
    }else if(ok && newText.isEmpty()){
        QMessageBox::critical(this,"Errore", "Inserire il nome del documento!");
        on_actionRinomina_triggered();
    }

    if(_client->getStatus()==false){
        StayInThisWindow = handleConnectionLoss();
    }

}

//EXPORT AS PDF ACTION  --> CTRL + S
void EditorWindow::on_actionEsporta_come_PDF_triggered() {
    QString pathname;
    //Dont change the follow line even if there is a warning (UNTIL I STUDY SMARTPOINTER)
    QString fileName = QFileDialog::getSaveFileName(this,"Esporta come PDF", ui->DocNameButton->text(), "PDF File (*.pdf)");

    if (fileName==nullptr) {
        return;
    }

    QFile File (fileName);
    pathname = fileName;

    QTextStream writeData(&File);
    QString fileText = ui->RealTextEdit->toHtml();
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

void EditorWindow::on_actionInvita_tramite_URI_triggered() {
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
void EditorWindow::on_actionDark_Mode_triggered() {
    PaintItBlack();
}

//COLLABORATOR TRIGGERED
void EditorWindow::on_actionCollaboratori_triggered() {
    ui->buttonCollab->click();
}

//GRASSETTO TRIGGERED       -->     CTRL + B
void EditorWindow::on_actionGrassetto_triggered() {
    ui->buttonBold->click();
}

//CORSIVO TRIGGERED         -->     CTRL + I
void EditorWindow::on_actionCorsivo_triggered() {
    ui->buttonItalic->click();
}

//SOTTOLINEATO TRIGGERED    -->     CTRL + U
void EditorWindow::on_actionSottolineato_triggered() {
    ui->buttonUnderline->click();
}

//ESCI TRIGGERED            -->     CTRL+Shift+Q
void EditorWindow::on_actionEsci_triggered() {
    //Get data from the form
    QString user = _client->getUsername();
    QByteArray ba_user = user.toLocal8Bit();
    const char *c_user = ba_user.data();

    //Serialize data
    json j;
    jsonUtility::to_jsonUser(j, "DISCONNECT_REQUEST", c_user);
    const std::string req = j.dump();

    //Send data (header and body)
    sendRequestMsg(req);
    QApplication::exit(0);
}

/***********************************************************************************
*                              STANDALONE FUNCTION                                 *
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

void EditorWindow::PaintItBlack() {
    if(DarkMode==false) {
        //I see a red door and I want to Paint it Black No colors anymore I want them to turn black I see the girls walk by dressed in their summer clothes I have to turn my head until my darkness goes
        DarkMode=true;

        ui->DocumentFrame->setStyleSheet("  #DocumentFrame{    background-color: #1a1a1a;}");
        ui->editorFrame->setStyleSheet("    #editorFrame{      background-color: #262626;}");
        ui->IconsBar->setStyleSheet("       #IconsBar{         background-color: ##262626;}");
        ui->RealTextEdit->setStyleSheet("   #RealTextEdit{     background: #4d4d4d; border-left: 2px solid #e6e6e6;}");
        ui->DocNameButton->setStyleSheet("  #DocNameButton{    background-color:transparent; border: transparent; color: #ff8000;}");
        ui->labelCollab->setStyleSheet("    #labelCollab{      background-color:transparent; border: transparent; color: #ff8000;}");

        QIcon icoAC, icoAD, icoAS, icoJS, icoCPY, icoCUT, icoPAS, icoMAGN, icoCOL, v2B, v2I, v2U, menuIcon;
        icoAC.addPixmap(QPixmap(":/image/DarkEditor/center-align.png"),QIcon::Normal,QIcon::On);
        icoAS.addPixmap(QPixmap(":/image/DarkEditor/left-align.png"),QIcon::Normal,QIcon::On);
        icoAD.addPixmap(QPixmap(":/image/DarkEditor/right-align.png"),QIcon::Normal,QIcon::On);
        icoJS.addPixmap(QPixmap(":/image/DarkEditor/justify.png"),QIcon::Normal,QIcon::On);
        icoCPY.addPixmap(QPixmap(":/image/DarkEditor/copy.png"),QIcon::Normal,QIcon::On);
        icoCUT.addPixmap(QPixmap(":/image/DarkEditor/cut.png"),QIcon::Normal,QIcon::On);
        icoPAS.addPixmap(QPixmap(":/image/DarkEditor/paste.png"),QIcon::Normal,QIcon::On);
        icoMAGN.addPixmap(QPixmap(":/image/DarkEditor/Magnifier.png"),QIcon::Normal,QIcon::On);
        icoCOL.addPixmap(QPixmap(":/image/DarkEditor/paintbrush.png"),QIcon::Normal,QIcon::On);
        v2B.addPixmap(QPixmap(":/image/DarkEditor/v2bold.png"),QIcon::Normal,QIcon::On);
        v2I.addPixmap(QPixmap(":/image/DarkEditor/v2italic.png"),QIcon::Normal,QIcon::On);
        v2U.addPixmap(QPixmap(":/image/DarkEditor/v2underline.png"),QIcon::Normal,QIcon::On);
        ui->buttonAlignCX->setIcon(icoAC);
        ui->buttonAlignSX->setIcon(icoAS);
        ui->buttonAlignDX->setIcon(icoAD);
        ui->buttonAlignJFX->setIcon(icoJS);
        ui->buttonCopy->setIcon(icoCPY);
        ui->buttonCut->setIcon(icoCUT);
        ui->buttonPaste->setIcon(icoPAS);
        ui->buttonSearch->setIcon(icoMAGN);
        ui->buttonColor->setIcon(icoCOL);
        ui->buttonBold->setIcon(v2B);
        ui->buttonItalic->setIcon(v2I);
        ui->buttonUnderline->setIcon(v2U);
        //iconContainer CSS
        ui->buttonCopy->setStyleSheet("     #buttonCopy{    background-color:#AEAEAE; border-radius:4px;}");
        ui->buttonCut->setStyleSheet("      #buttonCut{     background-color:#AEAEAE; border-radius:4px;}");
        ui->buttonPaste->setStyleSheet("    #buttonPaste{   background-color:#AEAEAE; border-radius:4px;}");
        ui->buttonSearch->setStyleSheet("   #buttonSearch{  background-color:#AEAEAE; border-radius:4px;}");
        ui->buttonColor->setStyleSheet("    #buttonColor{   background-color:#AEAEAE; border-radius:4px;}");
        //Menu Modify
        menuIcon.addPixmap(QPixmap(":/image/Editor/DarkSun.png"),QIcon::Normal,QIcon::On);
        ui->actionDark_Mode->setText("Modalità Giorno");
        ui->actionDark_Mode->setIcon(menuIcon);

    }else if(DarkMode==true){
        //Shine on you crazy diamond
        DarkMode=false;

        ui->DocumentFrame->setStyleSheet("  #DocumentFrame{ background-color: #FFFFFF;}");
        ui->editorFrame->setStyleSheet("    #editorFrame{   background-color: #EFEFEF;}");
        ui->IconsBar->setStyleSheet("       #IconsBar{      background-color: #EFEFEF;}");
        ui->RealTextEdit->setStyleSheet("   #RealTextEdit{  background: #FFFFFF; border-left: 2px solid #404040;}");
        ui->DocNameButton->setStyleSheet("  #DocNameButton{ background-color:transparent; border: transparent; color: #505050;}");
        ui->labelCollab->setStyleSheet("    #labelCollab{   background-color:transparent; border: transparent; color: #505050;}");

        QIcon icoAC, icoAD, icoAS, icoJS, icoCPY, icoCUT, icoPAS, icoMAGN, icoCOL, v2B, v2I, v2U, menuIcon;
        icoAC.addPixmap(QPixmap(":/image/Editor/center-align.png"),QIcon::Normal,QIcon::On);
        icoAS.addPixmap(QPixmap(":/image/Editor/left-align.png"),QIcon::Normal,QIcon::On);
        icoAD.addPixmap(QPixmap(":/image/Editor/right-align.png"),QIcon::Normal,QIcon::On);
        icoJS.addPixmap(QPixmap(":/image/Editor/justify.png"),QIcon::Normal,QIcon::On);
        icoCPY.addPixmap(QPixmap(":/image/Editor/copy.png"),QIcon::Normal,QIcon::On);
        icoCUT.addPixmap(QPixmap(":/image/Editor/cut.png"),QIcon::Normal,QIcon::On);
        icoPAS.addPixmap(QPixmap(":/image/Editor/paste.png"),QIcon::Normal,QIcon::On);
        icoMAGN.addPixmap(QPixmap(":/image/Editor/Magnifier.png"),QIcon::Normal,QIcon::On);
        icoCOL.addPixmap(QPixmap(":/image/Editor/paintbrush.png"),QIcon::Normal,QIcon::On);
        v2B.addPixmap(QPixmap(":/image/Editor/v2bold.png"),QIcon::Normal,QIcon::On);
        v2I.addPixmap(QPixmap(":/image/Editor/v2italic.png"),QIcon::Normal,QIcon::On);
        v2U.addPixmap(QPixmap(":/image/Editor/v2underline.png"),QIcon::Normal,QIcon::On);
        ui->buttonAlignCX->setIcon(icoAC);
        ui->buttonAlignSX->setIcon(icoAS);
        ui->buttonAlignDX->setIcon(icoAD);
        ui->buttonAlignJFX->setIcon(icoJS);
        ui->buttonCopy->setIcon(icoCPY);
        ui->buttonCut->setIcon(icoCUT);
        ui->buttonPaste->setIcon(icoPAS);
        ui->buttonSearch->setIcon(icoMAGN);
        ui->buttonColor->setIcon(icoCOL);
        ui->buttonBold->setIcon(v2B);
        ui->buttonItalic->setIcon(v2I);
        ui->buttonUnderline->setIcon(v2U);
        //iconContainer CSS
        ui->buttonCopy->setStyleSheet("     #buttonCopy{border-radius:4px}    #buttonCopy:hover{background-color: lightgrey;}");
        ui->buttonCut->setStyleSheet("      #buttonCut{border-radius:4px}     #buttonCut:hover{background-color: lightgrey;}");
        ui->buttonPaste->setStyleSheet("    #buttonPaste{border-radius:4px}   #buttonPaste:hover{background-color: lightgrey;}");
        ui->buttonSearch->setStyleSheet("   #buttonSearch{border-radius:4px}  #buttonBold:hover{background-color: lightgrey;}");
        ui->buttonColor->setStyleSheet("    #buttonColor{border-radius:4px}   #buttonBold:hover{background-color: lightgrey;}");

        //Menu Modify
        menuIcon.addPixmap(QPixmap(":/image/Editor/DarkMoon.png"),QIcon::Normal,QIcon::On);
        ui->actionDark_Mode->setText("Modalità Notte");
        ui->actionDark_Mode->setIcon(menuIcon);
    }

    //Set Other CSS
    AlignButtonStyleHandler();
    refreshFormatButtons();
    ui->RealTextEdit->setFocus();

}

void EditorWindow::AlignDXButtonHandler() {
    ui->buttonAlignDX->setChecked(true);
    ui->buttonAlignCX->setChecked(false);
    ui->buttonAlignSX->setChecked(false);
    ui->buttonAlignJFX->setChecked(false);
}
void EditorWindow::AlignCXButtonHandler() {
    ui->buttonAlignDX->setChecked(false);
    ui->buttonAlignCX->setChecked(true);
    ui->buttonAlignSX->setChecked(false);
    ui->buttonAlignJFX->setChecked(false);
}
void EditorWindow::AlignSXButtonHandler() {
    ui->buttonAlignDX->setChecked(false);
    ui->buttonAlignCX->setChecked(false);
    ui->buttonAlignSX->setChecked(true);
    ui->buttonAlignJFX->setChecked(false);
}

void EditorWindow::AlignJFXButtonHandler() {
    ui->buttonAlignDX->setChecked(false);
    ui->buttonAlignCX->setChecked(false);
    ui->buttonAlignSX->setChecked(false);
    ui->buttonAlignJFX->setChecked(true);
}

void EditorWindow::AlignNoneButtonHandler() {
    ui->buttonAlignDX->setChecked(false);
    ui->buttonAlignCX->setChecked(false);
    ui->buttonAlignSX->setChecked(false);
    ui->buttonAlignJFX->setChecked(false);
}

void EditorWindow::AlignButtonStyleHandler() {
   if(ui->buttonAlignCX->isChecked()) {
        ui->buttonAlignCX->setStyleSheet("  #buttonAlignCX{background-color:#AEAEAE; border-radius:4px;}");
        ui->buttonAlignSX->setStyleSheet("  #buttonAlignSX{border-radius:4px}    #buttonAlignSX:hover{background-color: lightgrey;}");
        ui->buttonAlignDX->setStyleSheet("  #buttonAlignDX{border-radius:4px}    #buttonAlignDX:hover{background-color: lightgrey;}");
        ui->buttonAlignJFX->setStyleSheet(" #buttonAlignJFX{border-radius:4px}   #buttonAlignJFX:hover{background-color: lightgrey;}");
    } else if(ui->buttonAlignSX->isChecked()) {
        ui->buttonAlignCX->setStyleSheet("  #buttonAlignCX{border-radius:4px}    #buttonAlignCX:hover{background-color: lightgrey;}");
        ui->buttonAlignSX->setStyleSheet("  #buttonAlignSX{background-color:#AEAEAE; border-radius:4px;}");
        ui->buttonAlignDX->setStyleSheet("  #buttonAlignDX{border-radius:4px}    #buttonAlignDX:hover{background-color: lightgrey;}");
        ui->buttonAlignJFX->setStyleSheet(" #buttonAlignJFX{border-radius:4px}   #buttonAlignJFX:hover{background-color: lightgrey;}");
    } else if(ui->buttonAlignDX->isChecked()) {
        ui->buttonAlignCX->setStyleSheet("  #buttonAlignCX{border-radius:4px}    #buttonAlignCX:hover{background-color: lightgrey;}");
        ui->buttonAlignSX->setStyleSheet("  #buttonAlignSX{border-radius:4px}    #buttonAlignSX:hover{background-color: lightgrey;}");
        ui->buttonAlignDX->setStyleSheet("  #buttonAlignDX{background-color:#AEAEAE; border-radius:4px;}");
        ui->buttonAlignJFX->setStyleSheet(" #buttonAlignJFX{border-radius:4px}   #buttonAlignJFX:hover{background-color: lightgrey;}");
    } else if(ui->buttonAlignJFX->isChecked()) {
        ui->buttonAlignCX->setStyleSheet("  #buttonAlignCX{border-radius:4px}    #buttonAlignCX:hover{background-color: lightgrey;}");
        ui->buttonAlignSX->setStyleSheet("  #buttonAlignSX{border-radius:4px}    #buttonAlignSX:hover{background-color: lightgrey;}");
        ui->buttonAlignDX->setStyleSheet("  #buttonAlignDX{border-radius:4px}    #buttonAlignDX:hover{background-color: lightgrey;}");
        ui->buttonAlignJFX->setStyleSheet(" #buttonAlignJFX{background-color:#AEAEAE; border-radius:4px;}");
    } else {
       ui->buttonAlignCX->setStyleSheet("   #buttonAlignCX{border-radius:4px}    #buttonAlignCX:hover{background-color: lightgrey;}");
       ui->buttonAlignSX->setStyleSheet("   #buttonAlignSX{border-radius:4px}    #buttonAlignSX:hover{background-color: lightgrey;}");
       ui->buttonAlignDX->setStyleSheet("   #buttonAlignDX{border-radius:4px}    #buttonAlignDX:hover{background-color: lightgrey;}");
       ui->buttonAlignJFX->setStyleSheet("  #buttonAlignJFX{border-radius:4px}   #buttonAlignJFX:hover{background-color: lightgrey;}");
    }
}

void EditorWindow::refreshFormatButtons() {
    if(ui->buttonBold->isChecked())
        ui->buttonBold->setStyleSheet("#buttonBold{background-color:#AEAEAE; border-radius:4px;}");
    else
        ui->buttonBold->setStyleSheet("#buttonBold{border-radius:4px}    #buttonBold:hover{background-color: lightgrey;}");
    if(ui->buttonItalic->isChecked())
        ui->buttonItalic->setStyleSheet("#buttonItalic{background-color:#AEAEAE; border-radius:4px;}");
    else
        ui->buttonItalic->setStyleSheet("#buttonItalic{border-radius:4px}    #buttonItalic:hover{background-color: lightgrey;}");
    if(ui->buttonUnderline->isChecked())
        ui->buttonUnderline->setStyleSheet("#buttonUnderline{background-color:#AEAEAE; border-radius:4px;}");
    else
        ui->buttonUnderline->setStyleSheet("#buttonUnderline{border-radius:4px}    #buttonUnderline:hover{background-color: lightgrey;}");
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


//---------------------- Other utility functions -----------------------------//

void EditorWindow::showPopupSuccess(QString result, std::string filename) {
    if(result == "LOGOUTURI_SUCCESS") {
        this->close();
        delete this;
    } else if (result == "RENAME_SUCCESS") {
        ui->DocNameButton->setText(QString::fromStdString(filename));
        _client->setFilename(QString::fromStdString(filename)); //Assign newText to the variable
        this->setWindowTitle("C.A.R.T.E. - " + QString::fromStdString(filename));
        ui->RealTextEdit->setFocus();
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
        QTextCharFormat newFormat;
        QTextBlockFormat newBlockFormat;
        QColor color(QString::fromStdString(s.getStyle().getColor()));

        /* Set format based on current symbol style received */
        s.getStyle().isBold() ? newFormat.setFontWeight(QFont::Bold) : newFormat.setFontWeight(QFont::Normal);
        s.getStyle().isItalic() ? newFormat.setFontItalic(true) : newFormat.setFontItalic(false);
        s.getStyle().isUnderlined() ? newFormat.setFontUnderline(true) : newFormat.setFontUnderline(false);
        newFormat.setFontFamily(QString::fromStdString(s.getStyle().getFontFamily()));
        newFormat.setFontPointSize(s.getStyle().getFontSize());
        newFormat.setBackground(color);
        newBlockFormat.setAlignment(static_cast<Qt::AlignmentFlag>(s.getStyle().getAlignment()));

        int endIndex;
        int pos = index++;
        c.hasSelection() ? endIndex = c.selectionEnd() : endIndex = -90;

        //if user2 insert a char at the end of the selection of user1 -> this can cause extension of user1's selection (that is wrong)
        if(c.hasSelection() && pos == endIndex) {
            int startIndex = c.selectionStart();
            int oldPos = c.position();

            /* Insert (formatted) char */
            c.setPosition(pos);
            c.setCharFormat(newFormat);
            c.insertText(static_cast<QString>(letter));
            c.setBlockFormat(newBlockFormat);

            /* Keep current selection */
            c.setPosition(oldPos == startIndex ? endIndex : startIndex, QTextCursor::MoveAnchor);
            c.setPosition(oldPos == startIndex ? startIndex : endIndex, QTextCursor::KeepAnchor);
            ui->RealTextEdit->setTextCursor(c);
        }
        else {
            /* Insert (formatted) char */
            c.setPosition(pos);
            c.setCharFormat(newFormat);
            c.insertText(static_cast<QString>(letter));
            c.setBlockFormat(newBlockFormat);
        }

        //if the selected sizes received are not an index of combobox, add them (and hide them)
        if(ui->fontSizeBox->findText(QString::number(s.getStyle().getFontSize())) == -1) {
            ui->fontSizeBox->addItem(QString::number(s.getStyle().getFontSize()));
            hideLastAddedItem(ui->fontSizeBox);
        }
    }
}

void EditorWindow::showSymbol(std::pair<int, wchar_t> tuple, symbolStyle style) {
    int pos = tuple.first;
    wchar_t c = tuple.second;
    QTextCharFormat format;
    QColor color(QString::fromStdString(style.getColor()));

    /* Set format based on style received */
    style.isBold() ? format.setFontWeight(QFont::Bold) : format.setFontWeight(QFont::Normal);
    format.setFontItalic(style.isItalic());
    format.setFontUnderline(style.isUnderlined());
    format.setFontFamily(QString::fromStdString(style.getFontFamily()));
    format.setFontPointSize(style.getFontSize());
    format.setBackground(color);

    QTextCursor cursor = ui->RealTextEdit->textCursor();
    int endIndex;
    cursor.hasSelection() ? endIndex = cursor.selectionEnd() : endIndex = -90;

    //if user2 insert a char at the end of the selection of user1 -> this can cause extension of user1's selection (that is wrong)
    if(cursor.hasSelection() && pos == endIndex) {
        int startIndex = cursor.selectionStart();
        int oldPos = cursor.position();

        /* Insert (formatted) char */
        cursor.setPosition(pos);
        cursor.setCharFormat(format);
        cursor.insertText(static_cast<QString>(c));

        /* Keep current selection */
        cursor.setPosition(oldPos == startIndex ? endIndex : startIndex, QTextCursor::MoveAnchor);
        cursor.setPosition(oldPos == startIndex ? startIndex : endIndex, QTextCursor::KeepAnchor);
        ui->RealTextEdit->setTextCursor(cursor);
    }
    else {
        /* Insert (formatted) char */
        cursor.setPosition(pos);
        cursor.setCharFormat(format);
        cursor.insertText(static_cast<QString>(c));
    }

    //if that selected size is not an index of combobox, add it (and hide it)
    if(ui->fontSizeBox->findText(QString::number(style.getFontSize())) == -1) {
        ui->fontSizeBox->addItem(QString::number(style.getFontSize()));
        hideLastAddedItem(ui->fontSizeBox);
        ui->RealTextEdit->setFontPointSize(cursor.charFormat().fontPointSize());
        ui->fontSizeBox->setCurrentText(QString::number(cursor.charFormat().fontPointSize()));
    }

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

    qDebug() << "Deleted char range" << endl;
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}

void EditorWindow::formatSymbols(int startIndex, int endIndex, int format) {
    QTextCursor cursor = ui->RealTextEdit->textCursor();
    QTextCharFormat newFormat;

    while(endIndex > startIndex) {
        cursor.setPosition(--endIndex);
        cursor.setPosition(endIndex+1, QTextCursor::KeepAnchor); //to select the char to be updated
        if(format == MAKE_BOLD)
            newFormat.setFontWeight(QFont::Bold);
        else if(format == MAKE_ITALIC)
            newFormat.setFontItalic(true);
        else if(format == MAKE_UNDERLINE)
            newFormat.setFontUnderline(true);
        else if(format == UNMAKE_BOLD)
            newFormat.setFontWeight(QFont::Normal);
        else if(format == UNMAKE_ITALIC)
            newFormat.setFontItalic(false);
        else if(format == UNMAKE_UNDERLINE)
            newFormat.setFontUnderline(false);
        cursor.mergeCharFormat(newFormat);
    }
    qDebug() << "Formatted char range" << endl;
    ui->RealTextEdit->setFocus();
}

void EditorWindow::hideAndChangeCustomFontSize() {
    /* Hide last added item */
    hideLastAddedItem(ui->fontSizeBox);

    /* Change font point size of the text edit */
    changedFontSize = true;
    if(!changedCurIndex)
        changedCurIndex = true;
    ui->RealTextEdit->setFontPointSize(ui->fontSizeBox->currentText().toInt());
    ui->RealTextEdit->setFocus();
}

void EditorWindow::resetFontSize() {
    QTextCursor cursor = ui->RealTextEdit->textCursor();

    //we don't want to apply the selected font size if the user loose focus on the combobox, but only when user press Enter
    if(!changedFontSize && !changedCurIndex) {
        if(changedCurIndex)
            setCurPointSize = false;
        else {
            cursor.setPosition(cursor.position()-1);
            cursor.setPosition(cursor.position()+1, QTextCursor::KeepAnchor); //to select the char to be updated
            ui->RealTextEdit->setFontPointSize(cursor.charFormat().fontPointSize());
        }
    }
    if(changedFontSize && changedCurIndex)
        changedCurIndex = false;
    changedFontSize = false;
}

void EditorWindow::changeFontSize(int startIndex, int endIndex, int fontSize) {
    QTextCursor cursor = ui->RealTextEdit->textCursor();
    QTextCharFormat newFormat;

    while(endIndex > startIndex) {
        cursor.setPosition(--endIndex);
        cursor.setPosition(endIndex+1, QTextCursor::KeepAnchor); //to select the char to be updated
        newFormat.setFontPointSize(fontSize);
        cursor.mergeCharFormat(newFormat);
    }
    qDebug() << "Changed font size in char range" << endl;
    ui->RealTextEdit->setFocus();
}

void EditorWindow::changeFontFamily(int startIndex, int endIndex, std::string fontFamily) {
    QTextCursor cursor = ui->RealTextEdit->textCursor();
    QTextCharFormat newFormat;

    while(endIndex > startIndex) {
        cursor.setPosition(--endIndex);
        cursor.setPosition(endIndex+1, QTextCursor::KeepAnchor); //to select the char to be updated
        newFormat.setFontFamily(QString::fromStdString(fontFamily));
        cursor.mergeCharFormat(newFormat);
    }
    qDebug() << "Changed font family in char range" << endl;
    ui->RealTextEdit->setFocus();
}

void EditorWindow::updateAlignmentButton() {
    setAlignmentButton(static_cast<Qt::AlignmentFlag>(static_cast<int>(ui->RealTextEdit->textCursor().blockFormat().alignment())));
    AlignButtonStyleHandler();
}

void EditorWindow::changeAlignment(int startBlock, int endBlock, int alignment) {
    QTextCursor cursor = ui->RealTextEdit->textCursor();
    QTextBlockFormat textBlockFormat;
    int oldPos = cursor.position();

    /* Change alignment of the 1st block */
    cursor.setPosition(startBlock);
    textBlockFormat = cursor.blockFormat();
    textBlockFormat.setAlignment(static_cast<Qt::AlignmentFlag>(alignment));
    cursor.mergeBlockFormat(textBlockFormat);
    cursor.movePosition(QTextCursor::EndOfBlock);
    int curPos = cursor.position();

    /* Change alignment of the next blocks, if requested */
    while(curPos < endBlock-1) {
        cursor.movePosition(QTextCursor::Right);
        textBlockFormat = cursor.blockFormat();
        textBlockFormat.setAlignment(static_cast<Qt::AlignmentFlag>(alignment));
        cursor.mergeBlockFormat(textBlockFormat);
        cursor.movePosition(QTextCursor::EndOfBlock);
        curPos = cursor.position();
    }

    /* Update cursor and style buttons */
    cursor.setPosition(oldPos);
    ui->RealTextEdit->setTextCursor(cursor);
    setAlignmentButton(static_cast<Qt::AlignmentFlag>(static_cast<int>(cursor.blockFormat().alignment())));
    AlignButtonStyleHandler();
    ui->RealTextEdit->setAlignment(cursor.blockFormat().alignment());

    qDebug() << "Changed alignment" << endl;
    ui->RealTextEdit->setFocus();
}

symbolStyle EditorWindow::getCurCharStyle() {
    bool isBold = ui->RealTextEdit->fontWeight()==QFont::Bold;
    int alignment = detectAlignment();
    std::string color = _client->getColor().toStdString();
    symbolStyle style = {isBold, ui->RealTextEdit->fontItalic(), ui->RealTextEdit->fontUnderline(), ui->fontFamilyBox->currentText().toStdString(), ui->fontSizeBox->currentText().toInt(), alignment, color};
    return style;
}

symbolStyle EditorWindow::getStyleFromHTMLStyles(QVector<std::pair<int,symbolStyle>>& styles) noexcept(false) {
    if(styles.empty())
        throw OperationNotSupported();
    symbolStyle style = styles.at(0).second;
    if(styles.at(0).first > 1)
        styles[0].first -= 1; //decrease the number of chars having same style
    else
        styles.pop_front(); //remove the style from the vector -> i.e. all chars with that style has been handled
    return style;
}

symbolStyle EditorWindow::constructSymStyle(QVector<QRegularExpression> rxs, QString str, int alignment) {
    bool isBold = rxs.at(0).match(str).captured(1) != "" && rxs.at(0).match(str).captured(1) == "600";
    bool isItalic = rxs.at(1).match(str).captured(1) != "" && rxs.at(1).match(str).captured(1) == "italic";
    bool isUnderlined = rxs.at(2).match(str).captured(1) != "" && rxs.at(2).match(str).captured(1) == "underline";
    std::string fontFamily = rxs.at(3).match(str).captured(1).toStdString();
    int fontSize = rxs.at(4).match(str).captured(1).toInt();
    if(fontSize == 0) fontSize = 1;
    std::string color = _client->getColor().toStdString();

    symbolStyle style = {isBold, isItalic, isUnderlined, fontFamily, fontSize, alignment, color}; //create the style for the current char
    return style;
}

QVector<std::pair<int,symbolStyle>> EditorWindow::getStylesFromHTML(QString htmlText, QTextCursor& cursor, QVector<int>& alignments) noexcept(false) {
    QVector<std::pair<int,symbolStyle>> finalVector;
    symbolStyle startStyle = getFirstCharStyle(cursor);
    htmlText = htmlText.mid(htmlText.indexOf("<p"), htmlText.length()).replace("\n", "<p VOID<span VOID>a</span>></p>");
qDebug() << "new html: " << htmlText;
    QRegularExpression rx("<span ([^<]+)</span>");
    QStringList list = getRegexListFromHTML(htmlText, rx);    
    QVector<QRegularExpression> rxs = getStyleRegexes();

    symbolStyle prevStyle = startStyle;
    foreach (QString s, list) {
        int numChars = s.mid(s.indexOf('>')).length()-1;
        if(alignments.empty() || numChars <= 0 || s.contains(" color:"))
            throw OperationNotSupported();
        qDebug() << "passato5";
        symbolStyle curStyle = constructSymStyle(rxs, s, alignments.first());
        qDebug() << curStyle.getFontSize();
        if((ui->fontFamilyBox->findText(QString::fromStdString(curStyle.getFontFamily())) == -1 &&
            curStyle.getFontFamily() != "") || curStyle.getFontSize() > 400 || curStyle.getFontSize() <= 0)
            throw OperationNotSupported();
        qDebug() << "passato6";
        alignments.erase(alignments.begin(), alignments.begin() + numChars);
        curStyle.getFontFamily() == "" ? curStyle = prevStyle : prevStyle = curStyle;
        finalVector.push_back(std::make_pair(numChars, curStyle));
    }
    qDebug() << "FINAL VECTOR:";
    for(const std::pair<int,symbolStyle>& p : finalVector)
        qDebug() << "(" << p.first << ",[" << p.second.isBold() << "," << p.second.isItalic() << "," << p.second.isUnderlined() << "," << QString::fromStdString(p.second.getFontFamily()) << "," << p.second.getFontSize() << "," << p.second.getAlignment() << "])";
    return finalVector;
}

QVector<std::pair<int,int>> EditorWindow::getAlignmentsFromHTML(QString htmlText, QTextCursor cursor) noexcept(false) {
    QVector<std::pair<int,int>> finalVec;
    int startAlignment = getFirstCharAlignment(cursor);

    /* Remove initial html header and substitute '\n' with empty paragraphs */
    htmlText = htmlText.mid(htmlText.indexOf("<p"), htmlText.length()).replace("\n", "<p VOID></p>");

    /* Split htmlText in many strings defined by the tags <p> e </p> (paragraphs) */
    QRegularExpression rx("<p (.*?)</p>");
    QStringList paragraphs = getRegexListFromHTML(htmlText, rx);

    if(paragraphs.empty())
        throw OperationNotSupported();
    if(paragraphs.length()==3 && paragraphs.at(0).contains("paragraph-type:empty") && paragraphs.at(2).contains("paragraph-type:empty")) {
        paragraphs.pop_back();
        paragraphs.pop_back();
    }

    /* Handle first paragraph -> each char of this paragraph will have the startAlignment */
    int totalChars = getTotalCharsInSpan(paragraphs.at(0));
    finalVec.push_back(std::make_pair(totalChars, startAlignment));
    paragraphs.pop_front();
    int prevAlignment = startAlignment;

    /* Handle other remaining paragraphs -> each char will have the alignment of the paragraph they belong to */
    foreach (QString s, paragraphs) {
        int paragAlignment = getParagAlignment(s);
        int totalChars = getTotalCharsInSpan(s);
        totalChars == 0 ? paragAlignment = prevAlignment : prevAlignment = paragAlignment;
        finalVec.push_back(std::make_pair(totalChars, paragAlignment));
        paragraphs.pop_front();
    }

    /* Remove first and last element if we've selected '\n' as first/last element */
    int len = finalVec.length();
    if(len > 1) {
        if(finalVec.at(0) == finalVec.at(1)) {
            finalVec.pop_front();
            --len;
        }
        if(len > 1 && finalVec.at(len-1) == finalVec.at(len-2))
            finalVec.pop_back();
    }

    /* Replace all 0s with 1s due to '\n' that is not considered as '<span>' tag */
    std::for_each(std::begin(finalVec), std::end(finalVec), [](std::pair<int,int>& p) {
        if(p.first  == 0)
            p.first = 1;
    });

    qDebug() << endl << "FINAL ALMNT VECTOR: " << finalVec;
    return finalVec;
}

int EditorWindow::getTotalCharsInSpan(QString text) {
    QRegularExpression spanRx("<span ([^<]+)</span>");
    QStringList spans = getRegexListFromHTML(text, spanRx);
    int totalChars = 0;
    foreach (QString s, spans) { //because chars can belong to the same span if they have the same style
        int numChars = s.mid(s.indexOf('>')).length()-1;
        totalChars += numChars;
    }
    return totalChars;
}

int EditorWindow::getParagAlignment(QString text) {
    int alignment;
    QRegularExpression rx("align=\"(.+?)\"");
    QString alignmentCaptured = rx.match(text).captured(1);
    if(alignmentCaptured.isNull())
        alignment = static_cast<int>(Qt::AlignLeft);
    else if(alignmentCaptured == "right")
        alignment = static_cast<int>(Qt::AlignRight);
    else if(alignmentCaptured == "center")
        alignment = static_cast<int>(Qt::AlignCenter);
    else if(alignmentCaptured == "justify")
        alignment = static_cast<int>(Qt::AlignJustify);
    else
        alignment = static_cast<int>(Qt::AlignLeft);
    return alignment;
}

QStringList EditorWindow::getRegexListFromHTML(QString text, QRegularExpression rx) {
    QStringList list;
    QRegularExpressionMatchIterator i = rx.globalMatch(text);
    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        QString word = match.captured(1);
        list << word;
    }
    return list;
}

QVector<QRegularExpression> EditorWindow::getStyleRegexes() {
    QVector<QRegularExpression> v;
    QRegularExpression fontFamilyRegex("font-family:'(.+?)';");
    QRegularExpression fontSizeRegex("font-size:(.+?)pt;");
    QRegularExpression fontWeightRegex("font-weight:(.+?);");
    QRegularExpression fontStyleRegex("font-style:(.+?);");
    QRegularExpression textDecorationRegex("text-decoration: (.+?);");
    v.push_back(fontWeightRegex);
    v.push_back(fontStyleRegex);
    v.push_back(textDecorationRegex);
    v.push_back(fontFamilyRegex);
    v.push_back(fontSizeRegex);
    return v;
}

int EditorWindow::getFirstCharAlignment(QTextCursor cursor) {
    int oldPos = cursor.position();
    int startAlignment;

    /* Get alignment of first char of the selection or the current alignment if there are no selection */
    if(cursor.hasSelection()) {
        int startIndex = cursor.selectionStart();
        cursor.setPosition(startIndex);
        QTextBlock block = cursor.block();
        cursor.movePosition(QTextCursor::Right);
        if(block != cursor.block()) //if we've selected 'newline' -> alignment will be that of the previous char
            cursor.movePosition(QTextCursor::Left);
    }
    startAlignment = static_cast<int>(cursor.blockFormat().alignment());
    cursor.setPosition(oldPos);
    return startAlignment;
}

symbolStyle EditorWindow::getFirstCharStyle(QTextCursor cursor) {
    int oldPos = cursor.position();
    symbolStyle startStyle;

    /* Get alignment of first char of the selection or the current alignment if there are no selection */
    if(cursor.hasSelection()) {
        int startIndex = cursor.selectionStart();
        cursor.setPosition(startIndex);
        QTextBlock block = cursor.block();
        cursor.movePosition(QTextCursor::Right);
        if(block != cursor.block()) //if we've selected 'newline' -> alignment will be that of the previous char
            cursor.movePosition(QTextCursor::Left);
    }
    //Get data
    bool bold = cursor.charFormat().fontWeight()==600 ? true : false;
    bool italic = cursor.charFormat().fontItalic();
    bool underline = cursor.charFormat().fontUnderline();
    std::string family = cursor.charFormat().fontFamily().toStdString();
    int size = static_cast<int>(cursor.charFormat().fontPointSize());
    int alignment = static_cast<int>(cursor.blockFormat().alignment());
    std::string color = _client->getColor().toStdString();

    startStyle = {bold, italic, underline, family, size, alignment, color};
    cursor.setPosition(oldPos);
    return startStyle;
}

void EditorWindow::sendFormatRequest(int format) {
    QTextCursor cursor = ui->RealTextEdit->textCursor();
    if(cursor.hasSelection()) {
        int startIndex = cursor.selectionStart();
        int endIndex = cursor.selectionEnd();

        //Serialize data
        json j;
        jsonUtility::to_json_format_range(j, "FORMAT_RANGE_REQUEST", startIndex, endIndex, format);
        const std::string req = j.dump();

        //Send data (header and body)
        sendRequestMsg(req);
    }
}

void EditorWindow::sendFontChangeRequest(int fontSize) {
    QTextCursor cursor = ui->RealTextEdit->textCursor();
    if(cursor.hasSelection()) {
        int startIndex = cursor.selectionStart();
        int endIndex = cursor.selectionEnd();

        //Serialize data
        json j;
        jsonUtility::to_json_fontsize_change(j, "FONTSIZE_CHANGE_REQUEST", startIndex, endIndex, fontSize);
        const std::string req = j.dump();

        //Send data (header and body)
        sendRequestMsg(req);
    }
}

void EditorWindow::sendAlignChangeRequest(int blockStart, int blockEnd, int alignment) {
    //Serialize data
    json j;
    jsonUtility::to_json_alignment_change(j, "ALIGNMENT_CHANGE_REQUEST", blockStart, blockEnd, alignment);
    const std::string req = j.dump();

    //Send data (header and body)
    sendRequestMsg(req);
}

void EditorWindow::sendFontChangeRequest(std::string fontFamily) {
    QTextCursor cursor = ui->RealTextEdit->textCursor();
    if(cursor.hasSelection()) {
        int startIndex = cursor.selectionStart();
        int endIndex = cursor.selectionEnd();

        //Serialize data
        json j;
        jsonUtility::to_json_fontfamily_change(j, "FONTFAMILY_CHANGE_REQUEST", startIndex, endIndex, fontFamily);
        const std::string req = j.dump();

        //Send data (header and body)
        sendRequestMsg(req);
    }
}

std::vector<bool> EditorWindow::calculateButtonChecks(QTextCursor& c) {
    int startIndex = c.selectionStart();
    int endIndex = c.selectionEnd();
    bool checkBold = false, checkItalic = false, checkUnderline = false,  uncheckAll = false;
    std::vector<std::vector<bool>> formatVectors; //vector for all chars in cursor selection
    std::vector<bool> vec(3); //vector for current char -> containing 3 values: isBold, isItalic, isUnderline
    int oldPos = c.position();

    while(endIndex > startIndex) { //loop over the cursor selection
        c.setPosition(endIndex--);
        vec = {c.charFormat().fontWeight()==QFont::Bold, c.charFormat().fontItalic(), c.charFormat().fontUnderline()};
        if(std::all_of(vec.begin(), vec.end(), [](bool val){return val == false;})) { //if all formats are false -> uncheckAll buttons and exit
            uncheckAll = true;
            break;
        }
        formatVectors.push_back(vec);
    }
    c.setPosition(oldPos);
    if(!uncheckAll) { //detect what format button has to be checked
        checkBold = formatVectors.at(0).at(0);
        checkItalic = formatVectors.at(0).at(1);
        checkUnderline = formatVectors.at(0).at(2);
        for(const std::vector<bool>& v : formatVectors) {
            if(!checkBold && !checkItalic && !checkUnderline)
                break;
            if(checkBold) checkBold = v.at(0);
            if(checkItalic) checkItalic = v.at(1);
            if(checkUnderline) checkUnderline = v.at(2);
        }
    }
    return {checkBold, checkItalic, checkUnderline};
}

int EditorWindow::calculateFontSizeComboBox(QTextCursor c) {
    int startIndex = c.selectionStart();
    int endIndex = c.selectionEnd();
    std::vector<int> vec;
    int curFontSize;
    bool isMixed = false;
    int oldPos = c.position();

    while(endIndex > startIndex) { //loop over the cursor selection
        c.setPosition(endIndex--, QTextCursor::KeepAnchor);
        curFontSize = static_cast<int>(c.charFormat().fontPointSize());
        vec.push_back(curFontSize);
        if(curFontSize != vec.at(0)) {
            isMixed = true;
            break;
        }
    }
    c.setPosition(oldPos);
    return isMixed ? -1 : vec.at(0);
}

int EditorWindow::calculateAlignmentButtons(QTextCursor c) {
    int startIndex = c.selectionStart();
    int endIndex = c.selectionEnd();
    std::vector<int> vec;
    int curAlignment;
    bool isMixed = false;
    int oldPos = c.position();
    int blockNum;

    while(endIndex > startIndex) { //loop over the cursor selection
        c.setPosition(startIndex++);
        blockNum = c.blockNumber();
        c.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor);
        //if block change (i.e. a newline is selected), get the alignment of the char at the left of the newline
        if(blockNum != c.blockNumber()) {
            c.movePosition(QTextCursor::Left, QTextCursor::KeepAnchor);
            curAlignment = static_cast<int>(c.blockFormat().alignment());
            c.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor);
        } else
            curAlignment = static_cast<int>(c.blockFormat().alignment());
        vec.push_back(curAlignment);
        if(curAlignment != vec.at(0)) {
            isMixed = true;
            break;
        }
    }
    c.setPosition(oldPos);
    return isMixed ? -1 : vec.at(0);
}

QString EditorWindow::calculateFontFamilyComboBox(QTextCursor c) {
    int startIndex = c.selectionStart();
    int endIndex = c.selectionEnd();
    std::vector<QString> vec;
    QString curFontFamily;
    bool isMixed = false;
    int oldPos = c.position();

    while(endIndex > startIndex) { //loop over the cursor selection
        c.setPosition(endIndex--, QTextCursor::KeepAnchor);
        curFontFamily = c.charFormat().fontFamily();
        vec.push_back(curFontFamily);
        if(curFontFamily != vec.at(0)) {
            isMixed = true;
            break;
        }
    }
    c.setPosition(oldPos);
    return isMixed ? "FONT_UNKNOWN" : vec.at(0);
}

void EditorWindow::hideLastAddedItem(QComboBox* combobox) {
    /* Hide new item created from the QComboBox list (because we don't want to display all the items user select) */
    QListView* view = qobject_cast<QListView *>(combobox->view());
    Q_ASSERT(view != nullptr);
    view->setRowHidden(combobox->count()-1, true);

    /* Hide the item also for the mouse wheel */
    QStandardItemModel* model = qobject_cast<QStandardItemModel*>(combobox->model());
    Q_ASSERT(model != nullptr);
    QStandardItem* item = model->item(combobox->count()-1);
    item->setFlags(item->flags() & ~Qt::ItemIsEnabled);
}

Qt::AlignmentFlag EditorWindow::detectAlignment() {
    if(ui->buttonAlignDX->isChecked())
        return Qt::AlignRight;
    else if(ui->buttonAlignCX->isChecked())
        return Qt::AlignCenter;
    else if(ui->buttonAlignJFX->isChecked())
        return Qt::AlignJustify;
    else
        return Qt::AlignLeft;
}

void EditorWindow::setAlignmentButton(Qt::AlignmentFlag alignment) {
    if(alignment == Qt::AlignRight)
        AlignDXButtonHandler();
    else if(alignment == Qt::AlignCenter)
        AlignCXButtonHandler();
    else if(alignment == Qt::AlignJustify)
        AlignJFXButtonHandler();
    else
        AlignSXButtonHandler();
}

void EditorWindow::alignSingleBlock(QTextCursor& cursor, Qt::AlignmentFlag alignment) {
    QTextBlockFormat textBlockFormat = cursor.blockFormat();
    textBlockFormat.setAlignment(alignment);
    cursor.mergeBlockFormat(textBlockFormat);
    ui->RealTextEdit->setTextCursor(cursor);
    if(ui->RealTextEdit->document()->lastBlock() == cursor.block()) //Qt considers <CR> in last line, even if I didn't press Return btn
        sendAlignChangeRequest(cursor.block().position(), cursor.block().position()+cursor.block().length()-1, alignment);
    else
        sendAlignChangeRequest(cursor.block().position(), cursor.block().position()+cursor.block().length(), alignment);
    //NB: cursor.block().length() considers also <CR>, while QTextCursor::EndOfBlock not!
}

void EditorWindow::alignMultipleBlocks(int startIndex, int endIndex, QTextCursor& cursor, Qt::AlignmentFlag alignment) {
    int oldPos = cursor.position();
    std::pair<int,int> positions = alignBlocks(startIndex, endIndex, cursor, alignment);
    cursor.setPosition(oldPos);
    ui->RealTextEdit->setTextCursor(cursor);
    sendAlignChangeRequest(positions.first, positions.second, alignment);
}

void EditorWindow::changeNextCharsAlignment(QTextCursor cursor, int startIndex, int endIndex) {
    int oldPos = cursor.position();

    /* Get alignment of the char prior to the selection and chars after the selection, until the end of the block */
    cursor.setPosition(startIndex);
    int finalAlignment = static_cast<int>(cursor.blockFormat().alignment());
    cursor.setPosition(endIndex);
    int charsAfterSelectionAlignment = static_cast<int>(cursor.blockFormat().alignment());

    /* Set alignment of the chars after selection to the alignment of the chars prior to the selection */
    if(finalAlignment != charsAfterSelectionAlignment) {
        if(ui->RealTextEdit->document()->lastBlock() == cursor.block()) //Qt considers <CR> in last line, even if I didn't press Return btn
            sendAlignChangeRequest(endIndex, cursor.block().position()+cursor.block().length()-1, finalAlignment);
        else
            sendAlignChangeRequest(endIndex, cursor.block().position()+cursor.block().length(), finalAlignment);
    }
    cursor.setPosition(oldPos); //reset position
}

std::pair<int,int> EditorWindow::alignBlocks(int startIndex, int endIndex, const QTextCursor& cursor, Qt::AlignmentFlag alignment) {
    QTextCursor tempCursor = cursor;
    QTextBlockFormat textBlockFormat;
    int startPos, endPos = -1;

    tempCursor.setPosition(startIndex);
    tempCursor.movePosition(QTextCursor::StartOfBlock);
    startPos = tempCursor.position();
    while(endPos < endIndex) {
        textBlockFormat = tempCursor.blockFormat();
        textBlockFormat.setAlignment(alignment);
        tempCursor.mergeBlockFormat(textBlockFormat);
        tempCursor.movePosition(QTextCursor::EndOfBlock); //NB: EndOfBlock does NOT consider <CR> (for ex.), so I have to move Right to reach the next block
        endPos = tempCursor.position();
        tempCursor.movePosition(QTextCursor::Right);
    }
    tempCursor.movePosition(QTextCursor::Left); //to check if we selected also the last block
    if(ui->RealTextEdit->document()->lastBlock() == tempCursor.block())
        return std::make_pair(startPos, endPos); //endPos and not endPos+1 due to the fact that Qt considers <CR> in last line, even if I didn't press Return btn
    else
        return std::make_pair(startPos, endPos+1); //endPos+1 to change alignment also for <CR>
}

bool EditorWindow::handleConnectionLoss() {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::warning(nullptr, "Attenzione", "Non sono riuscito a contattare il server!\n"
                                                        "Le ultime modifiche al documento potrebbero non essere state salvate\n"
                                                        "\n"
                                                        "Vuoi chiudere il programma?",  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        QApplication::exit(-1000);
    }else if(reply == QMessageBox::No){
        BruteClose=false;  //The user want to continue editing the document, maybe for save it locally.
    }
    return true;
}

void EditorWindow::setupInitialCondition() {
    ui->fontSizeBox->setCurrentText(QString::number(14));
    ui->fontFamilyBox->setCurrentIndex(ui->fontFamilyBox->findText("Times New Roman"));
    ui->buttonBold->setChecked(false);
    ui->buttonItalic->setChecked(false);
    ui->buttonUnderline->setChecked(false);
    QTextCursor c = ui->RealTextEdit->textCursor();
    if(c.blockFormat().alignment()==Qt::AlignRight)
        AlignDXButtonHandler();
    else if(c.blockFormat().alignment()==Qt::AlignCenter)
        AlignCXButtonHandler();
    else if(c.blockFormat().alignment()==Qt::AlignJustify)
        AlignJFXButtonHandler();
    else
        AlignSXButtonHandler();
}

void EditorWindow::removeCharRangeRequest(const QTextCursor& cursor) {
    int startIndex = cursor.selectionStart();
    int endIndex = cursor.selectionEnd();

    //Serialize data
    json j;
    jsonUtility::to_json_removal_range(j, "REMOVALRANGE_REQUEST", startIndex, endIndex);
    const std::string req = j.dump();

    //Send data (header and body)
    sendRequestMsg(req);
}

void EditorWindow::removeCharRequest(int pos) {
    //Serialize data
    json j;
    jsonUtility::to_json_removal(j, "REMOVAL_REQUEST", pos);
    const std::string req = j.dump();

    //Send data (header and body)
    sendRequestMsg(req);
}

void EditorWindow::insertCharRangeRequest(int pos, bool cursorHasSelection) noexcept(false) {
    QClipboard *clipboard = QApplication::clipboard();
    const QMimeData *mimeData = clipboard->mimeData();
    QTextCursor cursor = ui->RealTextEdit->textCursor();

    if(mimeData->hasText() && !mimeData->hasImage() && !mimeData->hasUrls() && !mimeData->html().contains("<a href")) {
        /* Get chars from clipboard mimeData */
        int numChars = mimeData->text().size(); //number of chars = number of iterations
        std::wstring str_to_paste = mimeData->text().toStdWString();
qDebug()<<mimeData->html();
        QVector<int> alignmentsValues;
        if(!cursorHasSelection) {
            /* Get alignments from HTML and extract values */
            try {
                QVector<std::pair<int,int>> alignments = getAlignmentsFromHTML(mimeData->html(), cursor);
                std::for_each(alignments.begin(), alignments.end(), [&](std::pair<int,int> pair) {
                    alignmentsValues.insert(alignmentsValues.end(), pair.first, pair.second);
                });
            } catch(OperationNotSupported& ex) {
                qDebug() << ex.what();
                throw OperationNotSupported(); //raise exception
            }
        } else {
            /* Get alignment from first char of the selection */
            int align = getFirstCharAlignment(cursor);
            std::fill_n(std::back_inserter(alignmentsValues), numChars, align);
        }

        if(alignmentsValues.length() != numChars || alignmentsValues.empty())
            throw OperationNotSupported();
qDebug() << "passato1";
        /* Get char styles from HTML */
        QVector<std::pair<int,symbolStyle>> styles;
        try {
            styles = getStylesFromHTML(mimeData->html(), cursor, alignmentsValues);
        } catch(OperationNotSupported& ex) {
            qDebug() << ex.what();
            throw OperationNotSupported(); //raise exception
        }
        qDebug() << "passato2";

        /* Update alignments vector of RealTextEdit */
        QVector<std::pair<int,int>> alignmentsVector;
        std::transform(std::begin(styles), std::end(styles), std::back_inserter(alignmentsVector),
                        [](std::pair<int,symbolStyle> const pair){ return std::make_pair(pair.first, pair.second.getAlignment()); });
        ui->RealTextEdit->setAlignmentsVector(alignmentsVector);

        std::vector<symbolInfo> infoSymbols;
        int index;
        wchar_t c;
        symbolStyle charStyle;

        /* Loop over mimeData chars and give the extracted style to each of them */
        for(int i=0; i<numChars; i++) {
            c = str_to_paste.c_str()[0]; //get wchar
            qDebug() << "char: " << c;
            str_to_paste.erase(0,1); //remove first wchar
            index = pos++; //get index
            qDebug() << "passatoX";
            try {
                charStyle = getStyleFromHTMLStyles(styles); //get the style
            } catch(OperationNotSupported& ex) {
                qDebug() << ex.what();
                throw OperationNotSupported(); //raise exception
            }
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
    } else {
        qDebug() << "Cannot paste this." << endl;
    }
}

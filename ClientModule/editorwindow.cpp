#include "editorwindow.h"
#include "ui_editorwindow.h"
#include "MyQTextEdit.h"
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
#include <QMenu>
#include <QCursor>
#include <QShortcut>

using json = nlohmann::json;

EditorWindow::EditorWindow(myClient* client, QWidget *parent): QMainWindow(parent), ui(new Ui::EditorWindow), _client(client) {
    auto t_start1 = std::chrono::high_resolution_clock::now();

    ui->setupUi(this);
    connect(_client, &myClient::editorResultSuccess, this, &EditorWindow::showPopupSuccess);
    connect(_client, &myClient::editorResultFailure, this, &EditorWindow::showPopupFailure);
    connect(_client, &myClient::insertSymbol, this, &EditorWindow::showSymbol);
    connect(_client, &myClient::eraseSymbols, this, &EditorWindow::eraseSymbols);
    connect(_client, &myClient::formatSymbols, this, &EditorWindow::formatSymbols);
    connect(_client, &myClient::changeFontSize, this, &EditorWindow::changeFontSize);
    connect(_client, &myClient::changeFontFamily, this, &EditorWindow::changeFontFamily);
    connect(_client, &myClient::changeAlignment, this, &EditorWindow::changeAlignment);
    connect(_client, &myClient::insertSymbols, this, &EditorWindow::showSymbolsAt);
    connect(_client, &myClient::removeRemoteCursor, ui->RealTextEdit, &MyQTextEdit::removeRemoteCursor);
    connect(_client, &myClient::getUserOffline, this, &EditorWindow::getUserOffline);
    connect(_client, &myClient::getUserOnline, this, &EditorWindow::getUserOnline);
    connect(_client, &myClient::changeRemoteCursor, ui->RealTextEdit, &MyQTextEdit::changeRemoteCursor);
    connect(_client, &myClient::showCollabColorsMap, this, &EditorWindow::showCollabColorsMap);
    connect(ui->fontSizeBox->lineEdit(), &QLineEdit::returnPressed, this, &EditorWindow::hideAndChangeCustomFontSize);
    connect(ui->fontSizeBox->lineEdit(), &QLineEdit::editingFinished, this, &EditorWindow::resetFontSize);
    connect(ui->RealTextEdit, &MyQTextEdit::updateAlignmentButton, this, &EditorWindow::updateAlignmentButton);
    connect(&ui->RealTextEdit->timer, &QTimer::timeout, ui->RealTextEdit, &MyQTextEdit::hideHorizontalRect);

    ui->listWidgetOn->setViewMode(QListView::ListMode);
    ui->listWidgetOn->setGridSize(QSize(215,40));
    ui->listWidgetOn->setIconSize(QSize(30,30));
    ui->listWidgetOn->setFlow(QListView::LeftToRight);
    ui->listWidgetOn->setWrapping(true);
    ui->listWidgetOn->setWordWrap(true);
    ui->listWidgetOn->setResizeMode(QListView::Adjust);
    ui->listWidgetOn->setAlternatingRowColors(false);
    ui->listWidgetOn->setMovement(QListView::Static);
    ui->listWidgetOn->setTextElideMode(Qt::ElideRight);

    ui->listWidgetOff->setViewMode(QListView::ListMode);
    ui->listWidgetOff->setGridSize(QSize(215,40));
    ui->listWidgetOff->setIconSize(QSize(30,30));
    ui->listWidgetOff->setFlow(QListView::LeftToRight);
    ui->listWidgetOff->setWrapping(true);
    ui->listWidgetOff->setWordWrap(true);
    ui->listWidgetOff->setResizeMode(QListView::Adjust);
    ui->listWidgetOff->setAlternatingRowColors(false);
    ui->listWidgetOff->setMovement(QListView::Static);
    ui->listWidgetOff->setTextElideMode(Qt::ElideRight);

    ui->listWidgetOn->setVerticalScrollBar(ui->verticalScrollBarOn);
    ui->listWidgetOff->setVerticalScrollBar(ui->verticalScrollBarOff);

    QString user = _client->getUsername();
    ui->labelUser->setText(user);

    QChar firstLetter;

    for (int i=0;i<user.length();i++){
        firstLetter = user.at(i);
        if(firstLetter.isLetter()){
            break;
        }
    }

    SimplifySingleCharForSorting(firstLetter,1);
    ui->profileButton->setText(firstLetter.toUpper());

    QColor color = _client->getColor();
    QString qss = QString("border-radius: 5px; \nbackground-color: %1; color:white;").arg(color.name());
    ui->profileButton->setStyleSheet(qss);

    QRegularExpressionValidator* fontSizeValidator;
    QIcon fontIcon(":/image/Editor/font.png");
    fontSizeValidator = new QRegularExpressionValidator(QRegularExpression("^(200|[1-9]|[1-9][0-9]|1[0-9][0-9])")); //from 1 to 200

    ui->fontSizeBox->lineEdit()->setValidator(fontSizeValidator);

    ui->RealTextEdit->setFontPointSize(14);
    ui->RealTextEdit->setFontFamily("Times New Roman");
    ui->RealTextEdit->setAcceptDrops(false);
    ui->RealTextEdit->setUndoRedoEnabled(false);
    ui->RealTextEdit->document()->setDocumentMargin(50);
    ui->fontFamilyBox->setCurrentText(ui->RealTextEdit->currentFont().family());
    for(int i=0; i<ui->fontFamilyBox->count(); i++) {
        ui->fontFamilyBox->setItemIcon(i, fontIcon);
    }
    ui->RealTextEdit->setEditorColor(_client->getColor());
    //ui->RealTextEdit->addRemoteCursor(_client->getUsername(), std::make_pair(_client->getColor(),0));
    cursorChangeRequest(0);
    hideLastAddedItem(ui->fontFamilyBox);
    qRegisterMetaType<std::vector<symbol>>("std::vector<symbol>");
    qRegisterMetaType<myCollabColorsMap>("std::map<std::string,std::pair<std::string,bool>");
    auto t_end1 = std::chrono::high_resolution_clock::now();
    double elapsed_time_ms1 = std::chrono::duration<double, std::milli>(t_end1-t_start1).count();
    std::cout << "EDITOR WINDOW CONSTRUCTOR - ELAPSED (ms): " << elapsed_time_ms1 << std::endl;

    showSymbolsAt(0, _client->getVector());
    auto t_start = std::chrono::high_resolution_clock::now();

    ui->RealTextEdit->installEventFilter(this);
    collabColorsRequest(_client->getFileURI());

    //Load Last User's Saved Setting
    LoadUserSetting();
    titlebarTimer = new QTimer(this);
    connect(titlebarTimer,SIGNAL(timeout()), this, SLOT(TitlebarChangeByTimer()));

    //Set docName on CollabBar
    SetDynamicDocNameLabel();
    auto t_end = std::chrono::high_resolution_clock::now();
    double elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end-t_start).count();
    std::cout << "EDITOR WINDOW CONSTRUCTOR AFTER SHOWSYMBOLS - ELAPSED (ms): " << elapsed_time_ms << std::endl;
}

EditorWindow::~EditorWindow() {
    delete ui;
}

/***************************************************************************************************************************************
 *                                                           INTERFACE                                                                 *
***************************************************************************************************************************************/

/***********************************************************************************
*                                 TOP BAR FUNCTION                                 *
************************************************************************************/
void EditorWindow::on_fileButton_clicked(){
    QMenu menuFile(this);

    //prepare icon
    QIcon icoSAVELORD;
    icoSAVELORD.addPixmap(QPixmap(":/image/Editor/save(1).png"),QIcon::Normal,QIcon::On);

    //prepare action
    QAction *uri = new QAction(tr("Invita tramite URI"), this);
    QAction *pdfExport = new QAction(icoSAVELORD, tr("Esporta come PDF"), this);
    QAction *rename = new QAction(tr("Rinomina"), this);
    QAction *close = new QAction(tr("Chiudi Documento"), this);


    //connect action
    connect(uri, &QAction::triggered, this, &EditorWindow::on_actionInvita_tramite_URI_triggered);
    connect(pdfExport, &QAction::triggered, this, &EditorWindow::on_actionEsporta_come_PDF_triggered);
    connect(rename, &QAction::triggered, this, &EditorWindow::on_actionRinomina_triggered);
    connect(close, &QAction::triggered, this, &EditorWindow::on_actionClose_triggered);

    //set tip
    uri->setStatusTip(tr("Invita un amico a collaborare su questo documento"));
    pdfExport->setStatusTip(tr("Esporta questo documento in formato PDF"));
    rename->setStatusTip(tr("Modifica il nome di questo documento"));
    close->setStatusTip(tr("Chiudi il documento corrente e torna al menu"));

    //prepare list of Shortcut
    QList<QKeySequence> shortcutUri, shortcutPdf, shortcutRinomina, shortcutClose;
    //shortcutUri.append(QKeySequence(Qt::CTRL + Qt::Key_?));       //WE HAVE A SHORTCUT FOR THIS?
    shortcutPdf.append(QKeySequence(Qt::CTRL + Qt::Key_S));         //CTRL+S
    shortcutRinomina.append(QKeySequence(Qt::CTRL + Qt::Key_R));    //CTRL+R
    shortcutClose.append(QKeySequence(Qt::CTRL + Qt::Key_Q));       //CTRL+Q

    //set Shortcut
    uri->setShortcuts(shortcutUri);
    pdfExport->setShortcuts(shortcutPdf);
    rename->setShortcuts(shortcutRinomina);
    close->setShortcuts(shortcutClose);

    //add action to menu
    menuFile.addAction(uri);
    menuFile.addAction(pdfExport);
    menuFile.addAction(rename);
    menuFile.addSeparator();
    menuFile.addAction(close);

    ui->fileButton->setMenu(&menuFile);
    ui->fileButton->showMenu();
}

void EditorWindow::on_visualizzaButton_clicked(){
    QMenu menuVisualizza(this);

    //prepare action
    QAction *fullscreen = new QAction( tr("Schermo Intero"), this);
    QAction *DayNNight = new QAction(  tr("Modalità Notte"), this);
    QAction *MenuCollab = new QAction( tr("Nascondi barra collaboratori"), this);
    QAction *Toolbar = new QAction( tr("Nascondi barra degli strumenti"), this);

    //Handle the dynamic part of this menu (if the action is checked)
    if(estate.GetFullScreen()==true){
        fullscreen->setText("Modalità Finestra");
    }
    if(estate.GetDarkMode()==true){
        QIcon icoDay;
        icoDay.addPixmap(QPixmap(":/image/Editor/DarkSun.png"),QIcon::Normal,QIcon::On);
        DayNNight->setIcon(icoDay);
        DayNNight->setText("Modalità Giorno");
    }else{
        //prepare icon
        QIcon icoDark;
        icoDark.addPixmap(QPixmap(":/image/Editor/DarkMoon.png"),QIcon::Normal,QIcon::On);
        DayNNight->setIcon(icoDark);
    }
    if(estate.GetCollaboratorBar()==false){
        MenuCollab->setText("Mostra barra collaboratori");
    }
    if(estate.GetToolbar()==false){
        Toolbar->setText("Mostra barra degli strumenti");
    }

    //connect action
    connect(fullscreen, &QAction::triggered, this, &EditorWindow::on_actionFullscreen_triggered);
    connect(DayNNight, &QAction::triggered, this, &EditorWindow::on_actionDark_Mode_triggered);
    connect(MenuCollab, &QAction::triggered, this, &EditorWindow::on_actionCollaboratori_triggered);
    connect(Toolbar, &QAction::triggered, this, &EditorWindow::on_actionToolbar_triggered);

    //set tip
    fullscreen->setStatusTip(tr("Passa in modalità fullscreen"));
    DayNNight->setStatusTip(tr("Alterna DayMode o DarkMode"));
    MenuCollab->setStatusTip(tr("Mostra o nascondi la barra dei collaboratori"));
    Toolbar->setStatusTip(tr("Mostra o nascondi la barra degli strumenti"));

    //prepare list of Shortcut
    QList<QKeySequence> shortcutFullS, shortcutDark, shortcutMenuC, shortcutToolbar;
    shortcutFullS.append(QKeySequence(Qt::CTRL + Qt::Key_F11));     //CTRL+F11
    shortcutDark.append(QKeySequence(Qt::CTRL + Qt::Key_D));        //CTRL+D
    //shortcutMenuC.append(QKeySequence(Qt::CTRL + Qt::Key_?));     //WE HAVE A SHORTCUT FOR THIS?
    shortcutToolbar.append(QKeySequence(Qt::CTRL + Qt::Key_M));        //CTRL+M

    //set Shortcut
    fullscreen->setShortcuts(shortcutFullS);
    DayNNight->setShortcuts(shortcutDark);
    MenuCollab->setShortcuts(shortcutMenuC);
    Toolbar->setShortcuts(shortcutToolbar);

    //add action to menu
    menuVisualizza.addAction(fullscreen);
    menuVisualizza.addAction(DayNNight);
    menuVisualizza.addSeparator();
    menuVisualizza.addAction(MenuCollab);
    menuVisualizza.addAction(Toolbar);

    ui->visualizzaButton->setMenu(&menuVisualizza);
    ui->visualizzaButton->showMenu();
}

void EditorWindow::on_modificaButton_clicked(){
    QMenu menuEdit(this);

    QTextCursor cursor = ui->RealTextEdit->textCursor();

    //prepare icon
    QIcon icoCPY, icoCUT, icoPAS, v2B, v2I, v2U;
    v2B.addPixmap(QPixmap(":/image/Editor/v2bold.png"),QIcon::Normal,QIcon::On);
    v2I.addPixmap(QPixmap(":/image/Editor/v2italic.png"),QIcon::Normal,QIcon::On);
    v2U.addPixmap(QPixmap(":/image/Editor/v2underline.png"),QIcon::Normal,QIcon::On);

    //prepare action
    QAction *cut = new QAction(icoCUT, tr("Taglia"), this);
    QAction *copy = new QAction(icoCPY, tr("Copia"), this);
    QAction *paste = new QAction(icoPAS, tr("Incolla"), this);
    QAction *selectAll = new QAction(tr("Seleziona tutto"), this);
    QAction *bold = new QAction(v2B, tr("Grassetto"), this);
    QAction *italic = new QAction(v2I, tr("Corsivo"), this);
    QAction *underl = new QAction(v2U, tr("Sottolineato"), this);

    //connect action
    connect(cut, &QAction::triggered, this, &EditorWindow::on_buttonCut_clicked);
    connect(copy, &QAction::triggered, this, &EditorWindow::on_buttonCopy_clicked);
    connect(paste, &QAction::triggered, this, &EditorWindow::on_buttonPaste_clicked);
    connect(selectAll, &QAction::triggered, this, &EditorWindow::on_actionSeleziona_Tutto_triggered);
    connect(bold, &QAction::triggered, this, &EditorWindow::on_actionGrassetto_triggered);
    connect(italic, &QAction::triggered, this, &EditorWindow::on_actionCorsivo_triggered);
    connect(underl, &QAction::triggered, this, &EditorWindow::on_actionSottolineato_triggered);

    //set tip
    cut->setStatusTip(tr("Taglia il codice selezionato"));
    copy->setStatusTip(tr("Copia il codice selezionato"));
    paste->setStatusTip(tr("Incolla il codice selezionato"));
    selectAll->setStatusTip(tr("Seleziona tutto il testo"));
    bold->setStatusTip(tr("Rende grassetto il testo"));
    italic->setStatusTip(tr("Rende corsivo il testo"));
    underl->setStatusTip(tr("Rende sottolineato il testo"));

    //disable some action if cursor hasn't selection
    if(!cursor.hasSelection()){
        cut->setEnabled(false);
        copy->setEnabled(false);
    }

    //set Shortcut
    cut->setShortcuts(QKeySequence::Cut);
    copy->setShortcuts(QKeySequence::Copy);
    paste->setShortcuts(QKeySequence::Paste);
    selectAll->setShortcuts(QKeySequence::SelectAll);
    bold->setShortcuts(QKeySequence::Bold);
    italic->setShortcuts(QKeySequence::Italic);
    underl->setShortcuts(QKeySequence::Underline);

    //add action to menu
    menuEdit.addAction(bold);
    menuEdit.addAction(italic);
    menuEdit.addAction(underl);
    menuEdit.addSeparator();
    menuEdit.addAction(cut);
    menuEdit.addAction(copy);
    menuEdit.addAction(paste);
    menuEdit.addSeparator();
    menuEdit.addAction(selectAll);

    ui->modificaButton->setMenu(&menuEdit);
    ui->modificaButton->showMenu();
}

void EditorWindow::on_strumentiButton_clicked(){
    QMenu menuStrumenti(this);

    QAction *option = new QAction(tr("Opzioni..."), this);

    //connect action
    connect(option, &QAction::triggered, this, &EditorWindow::on_actionOpzioni_triggered);

    //set tip
    option->setStatusTip(tr("Apre una finestra per regolare le impostazioni"));

    //prepare list of Shortcut
    QList<QKeySequence> shortcutOpzioni;
    shortcutOpzioni.append(QKeySequence(Qt::CTRL + Qt::Key_O));     //CTRL+O

    //set Shortcut
    option->setShortcuts(shortcutOpzioni);

    //add action to menu
    menuStrumenti.addAction(option);

    ui->strumentiButton->setMenu(&menuStrumenti);
    ui->strumentiButton->showMenu();
}

void EditorWindow::on_aboutButton_clicked(){
    QMenu menuAbout(this);

    QAction *about = new QAction(tr("About"), this);

    //connect action
    connect(about, &QAction::triggered, this, &EditorWindow::on_actionAbout_triggered);

    //set tip
    about->setStatusTip(tr("Apre una finestra con le informazioni "));

    //prepare list of Shortcut
    QList<QKeySequence> shortcutAbout;
    shortcutAbout.append(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_I));     //CTRL+Shift+I

    //set Shortcut
    about->setShortcuts(shortcutAbout);

    //add action to menu
    menuAbout.addAction(about);

    ui->aboutButton->setMenu(&menuAbout);
    ui->aboutButton->showMenu();
}


/***********************************************************************************
*                                  COLLABORATOR BAR                                *
************************************************************************************/


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
void EditorWindow::on_buttonColor_clicked() {
     qDebug() << ui->RealTextEdit->document()->toHtml();
     QString html = ui->RealTextEdit->document()->toHtml();

     if(ui->buttonColor->isChecked()) {
         ui->buttonColor->setChecked(true);
         ui->RealTextEdit->setBtnColorChecked(true);
         html = updateBackgroundColor(html, ALPHA_COLOR);
         ui->buttonColor->setStyleSheet("#buttonColor{background-color:#CACFD2; border-radius:4px;}");
     } else {
         ui->buttonColor->setChecked(false);
         ui->RealTextEdit->setBtnColorChecked(false);
         html = updateBackgroundColor(html, ALPHA_TRANSPARENT);
         ui->buttonColor->setStyleSheet("#buttonColor{border-radius:4px}    #buttonColor:hover{background-color: #BDC3C7;}");
     }
     ui->RealTextEdit->document()->setHtml(html);
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
        int startIndex = cursor.selectionStart();
        int endIndex = cursor.selectionEnd();
        changeNextCharsAlignment(cursor, startIndex, endIndex);
        removeCharRequest(startIndex, endIndex);
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
            int startIndex = cursor.selectionStart();
            int endIndex = cursor.selectionEnd();
            changeNextCharsAlignment(cursor, startIndex, endIndex);
            removeCharRequest(startIndex, endIndex);
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
*                                 REAL TEXT EDIT EVENT                             *
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

    /* REMOTE CURSOR */
    if(!ui->RealTextEdit->getRemoteCursors().empty())
        cursorChangeRequest(c.position());

    // Personal Solution to handle the QTBUG-29393 --> https://bugreports.qt.io/browse/QTBUG-29393
    // https://github.com/giovannic96/Real-time-collaborative-text-editor/issues/29
    //*****************************************************************************************************
    if(ui->RealTextEdit->fontPointSize() <= 0) {
        int dimensionFromOtherSide = (ui->fontSizeBox->currentText()).toInt();
        QString fontFamily = ui->fontFamilyBox->currentText();
        ui->RealTextEdit->setFontPointSize(dimensionFromOtherSide);
        ui->RealTextEdit->setFontFamily(fontFamily);
        qDebug()<<"Il Cursore è sicuramente in posizione iniziale";
    }

    //  Set TEXT FONT FAMILY
    //*****************************************************************************************************
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

    //  Set TEXT FONT SIZE
    //*****************************************************************************************************
    if(!c.hasSelection()) {
        int fontPointSize = static_cast<int>(ui->RealTextEdit->fontPointSize());
        ui->fontSizeBox->setCurrentText(QString::number(fontPointSize));
        ui->fontSizeBox->setCurrentIndex(ui->fontSizeBox->findText(ui->fontSizeBox->currentText()));
    }else{
        int fontSizeCalculated = calculateFontSizeComboBox(c);
        if(fontSizeCalculated == -1) {
            ui->fontSizeBox->setCurrentText(""); //blank text on item combobox
        }else{
            ui->fontSizeBox->setCurrentText(QString::number(fontSizeCalculated));
            ui->RealTextEdit->setFontPointSize(fontSizeCalculated); //set fontSize to common fontSize of the chars
        }
    }

    //  DETERMINES TEXT ALIGNMENT
    //*****************************************************************************************************
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

    //  DETERMINES TEXT FORMAT (Bold/Italic/Underline)
    //*****************************************************************************************************
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


void EditorWindow::on_RealTextEdit_textChanged(){
    int charCount = ui->RealTextEdit->toPlainText().count();
    int wordCount = ui->RealTextEdit->toPlainText().split(QRegExp("(\\s|\\n|\\r)+"), QString::SkipEmptyParts).count();
    int lineCount = ui->RealTextEdit->document()->blockCount();
    QString ZaChar = "Caratteri: "+QString::number(charCount);
    QString ZaLine;
    QString ZaWord = "Parole: "+QString::number(wordCount);
    if(charCount==0&&wordCount==0){
        ZaLine = "Linee: 0";
    }
    else{
        ZaLine = "Linee: "+QString::number(lineCount);

    }
    ui->label->setText(ZaChar);
    ui->label_2->setText(ZaWord);
    ui->label_3->setText(ZaLine);
}

void EditorWindow::on_RealTextEdit_customContextMenuRequested(const QPoint &pos){
    //Create an empty menu
    QMenu menu(this);

    //Find cursor in the text field
    QTextCursor cursor = ui->RealTextEdit->textCursor();

    //prepare icon
    QIcon icoCPY, icoCUT, icoPAS, v2B, v2I, v2U;
    icoCPY.addPixmap(QPixmap(":/image/Editor/copy.png"),QIcon::Normal,QIcon::On);
    icoCUT.addPixmap(QPixmap(":/image/Editor/cut.png"),QIcon::Normal,QIcon::On);
    icoPAS.addPixmap(QPixmap(":/image/Editor/paste.png"),QIcon::Normal,QIcon::On);
    v2B.addPixmap(QPixmap(":/image/Editor/v2bold.png"),QIcon::Normal,QIcon::On);
    v2I.addPixmap(QPixmap(":/image/Editor/v2italic.png"),QIcon::Normal,QIcon::On);
    v2U.addPixmap(QPixmap(":/image/Editor/v2underline.png"),QIcon::Normal,QIcon::On);

    //prepare action
    QAction *cut = new QAction(icoCUT, tr("Taglia"), this);
    QAction *copy = new QAction(icoCPY, tr("Copia"), this);
    QAction *paste = new QAction(icoPAS, tr("Incolla"), this);
    QAction *selectAll = new QAction(tr("Seleziona tutto"), this);
    QAction *bold = new QAction(v2B, tr("Grassetto"), this);
    QAction *italic = new QAction(v2I, tr("Corsivo"), this);
    QAction *underl = new QAction(v2U, tr("Sottolineato"), this);

    //connect action
    connect(cut, &QAction::triggered, this, &EditorWindow::on_buttonCut_clicked);
    connect(copy, &QAction::triggered, this, &EditorWindow::on_buttonCopy_clicked);
    connect(paste, &QAction::triggered, this, &EditorWindow::on_buttonPaste_clicked);
    connect(selectAll, &QAction::triggered, this, &EditorWindow::on_actionSeleziona_Tutto_triggered);
    connect(bold, &QAction::triggered, this, &EditorWindow::on_actionGrassetto_triggered);
    connect(italic, &QAction::triggered, this, &EditorWindow::on_actionCorsivo_triggered);
    connect(underl, &QAction::triggered, this, &EditorWindow::on_actionSottolineato_triggered);

    //set tip
    cut->setStatusTip(tr("Taglia il codice selezionato"));
    copy->setStatusTip(tr("Copia il codice selezionato"));
    paste->setStatusTip(tr("Incolla il codice selezionato"));
    selectAll->setStatusTip(tr("Seleziona tutto il testo"));
    bold->setStatusTip(tr("Rende grassetto il testo"));
    italic->setStatusTip(tr("Rende corsivo il testo"));
    underl->setStatusTip(tr("Rende sottolineato il testo"));

    //disable some action if cursor hasn't selection
    if(!cursor.hasSelection()){
        cut->setEnabled(false);
        copy->setEnabled(false);
    }

    //set Shortcut
    cut->setShortcuts(QKeySequence::Cut);
    copy->setShortcuts(QKeySequence::Copy);
    paste->setShortcuts(QKeySequence::Paste);
    selectAll->setShortcuts(QKeySequence::SelectAll);
    bold->setShortcuts(QKeySequence::Bold);
    italic->setShortcuts(QKeySequence::Italic);
    underl->setShortcuts(QKeySequence::Underline);

    //add action to menu
    menu.addAction(cut);
    menu.addAction(copy);
    menu.addAction(paste);
    menu.addSeparator();
    menu.addAction(bold);
    menu.addAction(italic);
    menu.addAction(underl);
    menu.addSeparator();
    menu.addAction(selectAll);

    //show menu
    menu.exec(ui->RealTextEdit->viewport()->mapToGlobal(pos)); //I don't know why, but it works! (I mean viewport->mapToGlobal)
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
                int startIndex = cursor.selectionStart();
                int endIndex = cursor.selectionEnd();
                changeNextCharsAlignment(cursor, startIndex, endIndex);
                removeCharRequest(startIndex, endIndex);
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
                    int startIndex = cursor.selectionStart();
                    int endIndex = cursor.selectionEnd();
                    changeNextCharsAlignment(cursor, startIndex, endIndex);
                    removeCharRequest(startIndex, endIndex);
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
        }
        //*********************************************** CTRL-H *************************************************
        else if((key == Qt::Key_H) && (modifiers == Qt::ControlModifier) && QApplication::keyboardModifiers()) {
            on_actionAbout_triggered();
            return true;
        }
        //*********************************************** CTRL-S *************************************************
        else if((key == Qt::Key_S) && (modifiers == Qt::ControlModifier) && QApplication::keyboardModifiers()) {
            on_actionEsporta_come_PDF_triggered();
            return true;
        }
        //*********************************************** CTRL-F11 *************************************************
        else if((key == Qt::Key_F11) && (modifiers == Qt::ControlModifier)) {
            on_actionFullscreen_triggered();
            return true;
        }
        //*********************************************** CTRL-Q *************************************************
        else if((key == Qt::Key_Q) && (modifiers == Qt::ControlModifier) && QApplication::keyboardModifiers()) {
            on_actionClose_triggered();
            return true;
        }
        //*********************************************** CTRL-R *************************************************
        else if((key == Qt::Key_R) && (modifiers == Qt::ControlModifier) && QApplication::keyboardModifiers()) {
            on_actionRinomina_triggered();
            return true;
        }
        //*********************************************** CTRL-D *************************************************
        else if((key == Qt::Key_D) && (modifiers == Qt::ControlModifier) && QApplication::keyboardModifiers()) {
            on_actionDark_Mode_triggered();
            return true;
        }
        //*********************************************** CTRL-I *************************************************
        else if((key == Qt::Key_I) && (modifiers == Qt::ControlModifier) && QApplication::keyboardModifiers()) {
            ui->buttonItalic->click();
            return true;
        }
        //*********************************************** CTRL-B *************************************************
        else if((key == Qt::Key_B) && (modifiers == Qt::ControlModifier) && QApplication::keyboardModifiers()) {
            ui->buttonBold->click();
            return true;
        }
        //*********************************************** CTRL-U *************************************************
        else if((key == Qt::Key_U) && (modifiers == Qt::ControlModifier) && QApplication::keyboardModifiers()) {
            ui->buttonUnderline->click();
            return true;
        }
        //*********************************************** CTRL-M *************************************************
        else if((key == Qt::Key_M) && (modifiers == Qt::ControlModifier) && QApplication::keyboardModifiers()) {
            on_actionToolbar_triggered();
            return true;
        }
        //*********************************************** CTRL-O *************************************************
        else if((key == Qt::Key_O) && (modifiers == Qt::ControlModifier) && QApplication::keyboardModifiers()) {
            on_actionOpzioni_triggered();
            return true;
        }
        //******************************************** ALL THE OTHER CTRL COMBINATION ****************************
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
                tempCursor.beginEditBlock();
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
                tempCursor.endEditBlock();

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
                cursor.beginEditBlock();
                cursor.setPosition(startIndex, QTextCursor::MoveAnchor);
                cursor.setPosition(endIndex, QTextCursor::KeepAnchor);
                cursor.mergeCharFormat(f);
                cursor.mergeBlockFormat(textBlockFormat);
                ui->RealTextEdit->mergeCurrentCharFormat(f);
                ui->RealTextEdit->setAlignment(textBlockFormat.alignment());
                ui->RealTextEdit->setTextCursor(cursor);
                cursor.endEditBlock();

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
                jsonUtility::to_json_removal_range(j, "REMOVAL_REQUEST", startIndex, endIndex);
                const std::string req = j.dump();

                //Send data (header and body)
                _client->sendRequestMsg(req);
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
            _client->sendRequestMsg(req);
            return QObject::eventFilter(obj, ev);
        } //******************************************** BACKSPACE *************************************************
        else if(key == Qt::Key_Backspace) {
            QTextCursor cursor = ui->RealTextEdit->textCursor();
            int pos = cursor.position();

            if(cursor.hasSelection()) { //Remove range of characters selected
                int startIndex = cursor.selectionStart();
                int endIndex = cursor.selectionEnd();

                /* Update new alignment */
                cursor.setPosition(cursor.selectionStart());
                QTextBlockFormat textBlockFormat;
                int firstCharAlignment = static_cast<int>(cursor.blockFormat().alignment());
                textBlockFormat.setAlignment(static_cast<Qt::AlignmentFlag>(firstCharAlignment));
                cursor.mergeBlockFormat(textBlockFormat);
                ui->RealTextEdit->setAlignment(textBlockFormat.alignment());
                setAlignmentButton(static_cast<Qt::AlignmentFlag>(static_cast<int>(textBlockFormat.alignment())));
                refreshFormatButtons();
                AlignButtonStyleHandler();
                cursor.setPosition(pos);

                /* Send requests */
                changeNextCharsAlignment(cursor, startIndex, endIndex);
                removeCharRequest(startIndex, endIndex);
            }
            else if(pos > 0) { //Remove only one character
                changeNextCharsAlignment(cursor, pos-1, pos);
                removeCharRequest(pos-1, pos);
            }
            return QObject::eventFilter(obj, ev);
        } //******************************************** CANC ******************************************************
        else if(key == Qt::Key_Delete) {
            QTextCursor cursor = ui->RealTextEdit->textCursor();
            int pos = cursor.position();

            if(cursor.hasSelection()) {
                int startIndex = cursor.selectionStart();
                int endIndex = cursor.selectionEnd();

                /* Update new alignment */
                cursor.setPosition(cursor.selectionStart());
                QTextBlockFormat textBlockFormat;
                int firstCharAlignment = static_cast<int>(cursor.blockFormat().alignment());
                textBlockFormat.setAlignment(static_cast<Qt::AlignmentFlag>(firstCharAlignment));
                cursor.mergeBlockFormat(textBlockFormat);
                ui->RealTextEdit->setAlignment(textBlockFormat.alignment());
                setAlignmentButton(static_cast<Qt::AlignmentFlag>(static_cast<int>(textBlockFormat.alignment())));
                refreshFormatButtons();
                AlignButtonStyleHandler();
                cursor.setPosition(pos);

                /* Send requests */
                changeNextCharsAlignment(cursor, startIndex, endIndex);
                removeCharRequest(startIndex, endIndex);
            }
            else if(pos >= 0 && pos < ui->RealTextEdit->toPlainText().size()) {
                changeNextCharsAlignment(cursor, pos, pos+1);
                removeCharRequest(pos, pos+1);
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
            QMessageBox message(this);
            message.setWindowTitle("Uscire?");
            message.setText("Vuoi chiudere il documento?");
            message.addButton("Chiudi", QMessageBox::DestructiveRole);
            message.addButton("Annulla", QMessageBox::RejectRole);
            int replay = message.exec();
            switch(replay){
                case 0:
                  event->ignore();
                  //close userProfile Window if it was opened;                 
                  if(!profile_closed){
                      delete up;
                  }
                  //close infoWindow if it was opened;
                  if(!infowindow_closed){
                      delete iw;
                  }
                  //close Settings Window if it was opened;
                  if(!settings_closed){
                      delete s;
                  }

                  CloseDocumentRequest(); //Return to MenuWindow (close only the current document)
                  break;
                case 1:
                  event->ignore();    //IGNORE FORCED CLOSE EVENT --> Stay in this window (EditorWindow)
                  break;
                default:
                  event->ignore();   //Should never reach this
                  break;
            }
        }
    }
}

/***************************************************************************************************************************************
 *                                                           ACTION                                                                    *
 *                                                                                                                                     *
 *                                           Action can be recallable with shortcut                                                    *
 ***************************************************************************************************************************************/

//FULLSCREEN ACTION      -->     CTRL+F11
void EditorWindow::on_actionFullscreen_triggered() {
   if(estate.GetFullScreen()==false) {
        estate.SetFullScreen(true);
        this->setWindowState(Qt::WindowFullScreen);
    } else if(estate.GetFullScreen()==true) {
        estate.SetFullScreen(false);
        this->setWindowState(Qt::WindowNoState); //WindowNoState save the old position and the old size of the window
    }
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}

//ABOUT ACTION           -->     CTRL+Shift+I
void EditorWindow::on_actionAbout_triggered() {
    openInfoWindows();
}

//CLOSE DOCUMENT ACTION  -->     CTRL+Q
void EditorWindow::on_actionClose_triggered() {
    CloseDocumentRequest();     //Return to MainWindow
}

//RENAME ACTION         -->     CTRL+R
void EditorWindow::on_actionRinomina_triggered() {
    bool ok, StayInThisWindow;
    QString newText = QInputDialog::getText(this, tr("Titolo documento"),
                                         tr("Inserisci un nome per il documento:"), QLineEdit::Normal, docName, &ok);

    if(ok && !newText.isEmpty() && newText.size()<=25) {
        //add character standardization
        QString filename = QLatin1String(newText.toUtf8());
        QByteArray ba_filename = filename.toLocal8Bit();
        const char *c_filename = ba_filename.data();
        //Serialize data
        json j;
        jsonUtility::to_jsonRenamefile(j, "RENAMEFILE_REQUEST", c_filename, _client->getFileURI().toStdString(), _client->getUsername().toStdString());
        const std::string req = j.dump();

        //Send data (header and body)
        _client->sendRequestMsg(req);
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
    QString fileName = QFileDialog::getSaveFileName(this,"Esporta come PDF", docName, "PDF File (*.pdf)");

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
            _client->sendRequestMsg(req);
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
    if(ui->listWidgetOn->isHidden()){
        showCollab();
    }
    else{
        hideCollab();
    }
    ui->RealTextEdit->setFocus(); //Return focus to textedit
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

//SELEZIONA TUTTO TRIGGERED    -->  CTRL + A
void EditorWindow::on_actionSeleziona_Tutto_triggered(){
   ui->RealTextEdit->selectAll();
}

//TOOLBAR TRIGGERED    -->  CTRL + M
void EditorWindow::on_actionToolbar_triggered(){
    if(estate.GetToolbar()==false){
        showToolbar();
    }
    else{
        hideToolbar();
    }
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}

//OPZIONI TRIGGERED    -->  CTRL + O
void EditorWindow::on_actionOpzioni_triggered(){
    openSettingsWindows();
}


/***************************************************************************************************************************************
 *                                               STANDALONE FUNCTION FOR GRAPHIC                                                       *
 *                                                                                                                                     *
 ***************************************************************************************************************************************/

void EditorWindow::PaintItBlack() {
    if(estate.GetDarkMode()==false) {
        qDebug() << estate.GetThemeDay();
        //I see a red door and I want it painted black, no colors anymore I want them to turn black
        estate.SetDarkMode(true);

        ApplyDarkMode();
        SetIconPackDarkMode();

        //Change the icon on TopBar menu
        QIcon menuIcon;
        menuIcon.addPixmap(QPixmap(":/image/Editor/DarkSun.png"),QIcon::Normal,QIcon::On);
        ui->actionDark_Mode->setIcon(menuIcon);

    }else if(estate.GetDarkMode()==true){
        //Shine on you crazy diamond
        estate.SetDarkMode(false);

        ApplyDayMode();
        SetIconPackDayMode();

        //Change the icon on TopBar menu
        QIcon menuIcon;
        menuIcon.addPixmap(QPixmap(":/image/Editor/DarkMoon.png"),QIcon::Normal,QIcon::On);
        ui->actionDark_Mode->setIcon(menuIcon);
    }

    //Set Other CSS
    AlignButtonStyleHandler();
    refreshFormatButtons();
    ui->RealTextEdit->setFocus();

}

void EditorWindow::ApplyDayMode(){
    if(estate.GetThemeDay()==1){
        installTheme_Day_ClassicBlue();
    }else if(estate.GetThemeDay()==2){
        installTheme_Day_PlainBlue();
    }else if(estate.GetThemeDay()==3){
        installTheme_Day_ElectricBlue();
    }else if(estate.GetThemeDay()==4){
        installTheme_Day_ClassicPurple();
    }else if(estate.GetThemeDay()==5){
        installTheme_Day_ClassicOrange();
    }else if(estate.GetThemeDay()==6){
        installTheme_Day_ClassicGreen();
    }else if(estate.GetThemeDay()==7){
        installTheme_Day_ClassicRed();
    }else if(estate.GetThemeDay()==8){
        installTheme_Day_Rainbow();
    }else if(estate.GetThemeDay()==9){
        installTheme_Day_FountainRainbow();
    }else if(estate.GetThemeDay()==10){
        installTheme_Day_Polito();
    }else if(estate.GetThemeDay()==11){
        installTheme_Day_Special();
    }

    //COLLAB BAR
    ui->label->setStyleSheet("color: grey");
    ui->label_2->setStyleSheet("color: grey");
    ui->label_3->setStyleSheet("color: grey");
    ui->labelCollOn->setStyleSheet("color: grey");
    ui->labelCollOff->setStyleSheet("color: grey");
    ui->listWidgetOn->setStyleSheet("border:none;\n background:transparent;\n color:black");
    ui->labelUser->setStyleSheet("color:black;");
}

void EditorWindow::ApplyDarkMode(){
    if(estate.GetThemeDark()==1){
        installTheme_Dark_ClassicOrange();
    }else if(estate.GetThemeDark()==2){
        installTheme_Dark_PlainOrange();
    }else if(estate.GetThemeDark()==3){
        installTheme_Dark_ElectricOrange();
    }else if(estate.GetThemeDark()==4){
        installTheme_Dark_ClassicPurple();
    }else if(estate.GetThemeDark()==5){
        installTheme_Dark_ClassicBlue();
    }else if(estate.GetThemeDark()==6){
        installTheme_Dark_ClassicGreen();
    }else if(estate.GetThemeDark()==7){
        installTheme_Dark_ClassicRed();
    }else if(estate.GetThemeDark()==8){
        installTheme_Dark_Rainbow();
    }else if(estate.GetThemeDark()==9){
        installTheme_Dark_FountainRainbow();
    }else if(estate.GetThemeDark()==10){
        installTheme_Dark_Polito();
    }else if(estate.GetThemeDark()==11){
        installTheme_Dark_Special();
    }


    //COLLAB BAR
    ui->label->setStyleSheet("color: #FFFFFF");
    ui->label_2->setStyleSheet("color: #FFFFFF");
    ui->label_3->setStyleSheet("color: #FFFFFF");
    ui->labelCollOn->setStyleSheet("color: #FFFFFF");
    ui->labelCollOff->setStyleSheet("color: #FFFFFF");
    ui->listWidgetOn->setStyleSheet("border:none;\n background:transparent;\n color:white");
    ui->labelUser->setStyleSheet("color:white;");

}

void EditorWindow::SetIconPackDayMode(){
    QIcon icoAC, icoAD, icoAS, icoJS, icoCPY, icoCUT, icoPAS, icoMAGN, icoCOL, v2B, v2I, v2U;
    icoAC.addPixmap(QPixmap(":/image/Editor/center-align.png"),QIcon::Normal,QIcon::On);
    icoAS.addPixmap(QPixmap(":/image/Editor/left-align.png"),QIcon::Normal,QIcon::On);
    icoAD.addPixmap(QPixmap(":/image/Editor/right-align.png"),QIcon::Normal,QIcon::On);
    icoJS.addPixmap(QPixmap(":/image/Editor/justify.png"),QIcon::Normal,QIcon::On);
    icoCPY.addPixmap(QPixmap(":/image/Editor/copy.png"),QIcon::Normal,QIcon::On);
    icoCUT.addPixmap(QPixmap(":/image/Editor/cut.png"),QIcon::Normal,QIcon::On);
    icoPAS.addPixmap(QPixmap(":/image/Editor/paste.png"),QIcon::Normal,QIcon::On);
    icoMAGN.addPixmap(QPixmap(":/image/Editor/Magnifier.png"),QIcon::Normal,QIcon::On);
    icoCOL.addPixmap(QPixmap(":/image/Editor/highlighter.png"),QIcon::Normal,QIcon::On);
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
    ui->buttonColor->setIcon(icoCOL);
    ui->buttonBold->setIcon(v2B);
    ui->buttonItalic->setIcon(v2I);
    ui->buttonUnderline->setIcon(v2U);
}

void EditorWindow::SetIconPackDarkMode(){
    QIcon icoAC, icoAD, icoAS, icoJS, icoCPY, icoCUT, icoPAS, icoMAGN, icoCOL, v2B, v2I, v2U;
    icoAC.addPixmap(QPixmap(":/image/DarkEditor/center-align.png"),QIcon::Normal,QIcon::On);
    icoAS.addPixmap(QPixmap(":/image/DarkEditor/left-align.png"),QIcon::Normal,QIcon::On);
    icoAD.addPixmap(QPixmap(":/image/DarkEditor/right-align.png"),QIcon::Normal,QIcon::On);
    icoJS.addPixmap(QPixmap(":/image/DarkEditor/justify.png"),QIcon::Normal,QIcon::On);
    icoCPY.addPixmap(QPixmap(":/image/DarkEditor/copy.png"),QIcon::Normal,QIcon::On);
    icoCUT.addPixmap(QPixmap(":/image/DarkEditor/cut.png"),QIcon::Normal,QIcon::On);
    icoPAS.addPixmap(QPixmap(":/image/DarkEditor/paste.png"),QIcon::Normal,QIcon::On);
    icoMAGN.addPixmap(QPixmap(":/image/DarkEditor/Magnifier.png"),QIcon::Normal,QIcon::On);
    icoCOL.addPixmap(QPixmap(":/image/DarkEditor/highlighter.png"),QIcon::Normal,QIcon::On);
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
    ui->buttonColor->setIcon(icoCOL);
    ui->buttonBold->setIcon(v2B);
    ui->buttonItalic->setIcon(v2I);
    ui->buttonUnderline->setIcon(v2U);
}

void EditorWindow::LoadUserSetting(){

    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "C.A.R.T.E. Studio", "C.A.R.T.E.");

    // LOAD AND SET "START" VALUE
    //*****************************************************************************************************
    settings.beginGroup("Start");
    estate.SetDarkMode(settings.value("darkmode", estate.GetDarkMode()).toBool());
    estate.SetCollaboratorBar(settings.value("collaboratorbar", estate.GetCollaboratorBar()).toBool());
    estate.SetToolbar(settings.value("toolbar", estate.GetToolbar()).toBool());
    settings.endGroup();

    if(estate.GetDarkMode() == true){
        //ApplyDarkMode();      <-- Not now! It has to be done after the LOAD AND SET "THEME" VALUE
        SetIconPackDarkMode();
        //Change the icon on TopBar menu
        QIcon menuIcon;
        menuIcon.addPixmap(QPixmap(":/image/Editor/DarkSun.png"),QIcon::Normal,QIcon::On);
        ui->actionDark_Mode->setIcon(menuIcon);
    }
    if(estate.GetCollaboratorBar() == false){
        hideCollab();
    }
    if(estate.GetToolbar() == false){
        hideToolbar();
    }


    // LOAD AND SET "TITLEBAR" VALUE
    //*****************************************************************************************************
    settings.beginGroup("Titlebar");
    estate.SetTitlebar(settings.value("titlebar", estate.GetTitlebar()).toInt());
    settings.endGroup();

    if(estate.GetTitlebar()==1){            // [1]=DocName
        textOnTitleBar = docName;
    }else if(estate.GetTitlebar()==2){      // [2]=ProgName
        textOnTitleBar = "C.A.R.T.E.";
    }else if(estate.GetTitlebar()==3){      // [3]=Prog+Doc
        textOnTitleBar = "C.A.R.T.E. - " + docName;
    }else if(estate.GetTitlebar()==4){      // [4]=Alternate
        //Do nothing. TitlebarChangeByTimer is handle it by titlebarTimer, and is started/enabled when I load titlebar value to [4]
    }
    this->setWindowTitle(textOnTitleBar);


    // LOAD AND SET "THEME" VALUE
    //*****************************************************************************************************
    settings.beginGroup("Theme");
    estate.SetThemeDay(settings.value("dayTheme", estate.GetThemeDay()).toInt());
    estate.SetThemeDark(settings.value("darkTheme", estate.GetThemeDark()).toInt());
    settings.endGroup();

    // SET THEME COLOUR SCHEME
    //*****************************************************************************************************
    if(estate.GetDarkMode() == true){
        ApplyDarkMode();
    }else{
        ApplyDayMode();
    }

}

void EditorWindow::TitlebarChangeByTimer(){

    if(estate.GetTitlebar()==4){

        titlebarTimer->start(3000);
        if(estate.GetTitlebarAlternate()==true){
            textOnTitleBar = "C.A.R.T.E.";
            estate.SetTitlebarAlternate(false);
        }else{
            textOnTitleBar = docName;
            estate.SetTitlebarAlternate(true);
        }
        this->setWindowTitle(textOnTitleBar);

    }else if(estate.GetTitlebar()==5){

       titlebarTimer->start(250);
       textOnTitleBar = "C.A.R.T.E.";
       int a = estate.GetTitlebarCounter();
       if(estate.GetTitlebarAlternate()==true){
           a-=-1;
           estate.SetTitlebarCounter(a);
           for(int i=0; i<=a; i++){
               textOnTitleBar.push_front("         ");
           }
           if(a>=25){
               estate.SetTitlebarAlternate(false);
           }
       }else{
           textOnTitleBar = "C.A.R.T.E.";
           estate.SetTitlebarAlternate(true);
           estate.SetTitlebar(5);
           estate.SetTitlebarCounter(0);
       }
       this->setWindowTitle(textOnTitleBar);
    }

}

void EditorWindow::installTheme_Day_ClassicBlue(){
    //GENERAL COLOR
    ui->editorFrame->setStyleSheet("   #editorFrame{   background: url(:/image/Editor/sfondo.png);}");
    ui->RealTextEdit->setStyleSheet("  #RealTextEdit{  color: black; background: #FFFFFF; border-left: 2px solid #404040;}");
    ui->DocNameLabel->setStyleSheet("  #DocNameLabel{ background-color:transparent; border: transparent; color: #0683FF;}");
    ui->opaqueLogo->setStyleSheet("background: url(:/image/Editor/logo.png)");

    //TOP FRAME
    ui->frameTopBar->setStyleSheet("#frameTopBar{           background:qlineargradient(x1:0, y1:1, x2:1, y2:1, stop:0#0683FF stop:0.53#0683FF stop:0.54#0683FF stop:0.63#005DBA stop:0.64#005DBA stop:0.88 #0A5597);}");
    ui->fileButton->setStyleSheet("#fileButton{             color:white; border:none;}  #fileButton:hover{background-color: #075299;}       #fileButton:pressed {background-color: #075299;}");
    ui->visualizzaButton->setStyleSheet("#visualizzaButton{ color:white; border:none;}  #visualizzaButton:hover{background-color: #075299;} #visualizzaButton:pressed {background-color: #075299;}");
    ui->modificaButton->setStyleSheet("#modificaButton{     color:white; border:none;}  #modificaButton:hover{background-color: #075299;}   #modificaButton:pressed {background-color: #075299;}");
    ui->strumentiButton->setStyleSheet("#strumentiButton{   color:white; border:none;}  #strumentiButton:hover{background-color: #075299;}  #strumentiButton:pressed {background-color: #075299;}");
    ui->aboutButton->setStyleSheet("#aboutButton{           color:white; border:none;}  #aboutButton:hover{background-color: #075299;}      #aboutButton:pressed {background-color: #075299;}");
}


void EditorWindow::installTheme_Day_PlainBlue(){
    //GENERAL COLOR
    ui->editorFrame->setStyleSheet("   #editorFrame{   background: url(:/image/Editor/sfondo.png);}");
    ui->RealTextEdit->setStyleSheet("  #RealTextEdit{  color: black; background: #FFFFFF; border-left: 2px solid #404040;}");
    ui->DocNameLabel->setStyleSheet("  #DocNameLabel{ background-color:transparent; border: transparent; color: #505050;}");
    ui->opaqueLogo->setStyleSheet("background: url(:/image/Editor/logo.png)");

    //TOP FRAME
    ui->frameTopBar->setStyleSheet("#frameTopBar{           background: #0A5597;}");
    ui->fileButton->setStyleSheet("#fileButton{             color:white; border:none;}  #fileButton:hover{background-color: #0E79D8;}       #fileButton:pressed {background-color: #57ABF4;}");
    ui->visualizzaButton->setStyleSheet("#visualizzaButton{ color:white; border:none;}  #visualizzaButton:hover{background-color: #0E79D8;} #visualizzaButton:pressed {background-color: #57ABF4;}");
    ui->modificaButton->setStyleSheet("#modificaButton{     color:white; border:none;}  #modificaButton:hover{background-color: #0E79D8;}   #modificaButton:pressed {background-color: #57ABF4;}");
    ui->strumentiButton->setStyleSheet("#strumentiButton{   color:white; border:none;}  #strumentiButton:hover{background-color: #0E79D8;}  #strumentiButton:pressed {background-color: #57ABF4;}");
    ui->aboutButton->setStyleSheet("#aboutButton{           color:white; border:none;}  #aboutButton:hover{background-color: #0E79D8;}      #aboutButton:pressed {background-color: #57ABF4;}");
}

void EditorWindow::installTheme_Day_ElectricBlue(){
    //GENERAL COLOR
    ui->editorFrame->setStyleSheet("   #editorFrame{   background: white;}");
    ui->RealTextEdit->setStyleSheet("  #RealTextEdit{  color: black; background: #FFFFFF; border-left: 2px solid #404040;}");
    ui->DocNameLabel->setStyleSheet("  #DocNameLabel{ background-color:transparent; border: transparent; color: #505050;}");
    ui->opaqueLogo->setStyleSheet("background: url(:/image/Editor/logo.png)");

    //TOP FRAME
    ui->frameTopBar->setStyleSheet("#frameTopBar{            background:#0000FF;}");
    ui->fileButton->setStyleSheet("#fileButton{             color:white; border:none;}  #fileButton:hover{background-color: #000099;}       #fileButton:pressed {background-color: #000066;}");
    ui->visualizzaButton->setStyleSheet("#visualizzaButton{ color:white; border:none;}  #visualizzaButton:hover{background-color: #000099;} #visualizzaButton:pressed {background-color: #000066;}");
    ui->modificaButton->setStyleSheet("#modificaButton{     color:white; border:none;}  #modificaButton:hover{background-color: #000099;}   #modificaButton:pressed {background-color: #000066;}");
    ui->strumentiButton->setStyleSheet("#strumentiButton{   color:white; border:none;}  #strumentiButton:hover{background-color: #000099;}  #strumentiButton:pressed {background-color: #000066;}");
    ui->aboutButton->setStyleSheet("#aboutButton{           color:white; border:none;}  #aboutButton:hover{background-color: #000099;}      #aboutButton:pressed {background-color: #000066;}");
}

void EditorWindow::installTheme_Day_ClassicPurple(){
    //GENERAL COLOR
    ui->editorFrame->setStyleSheet("   #editorFrame{   background: url(:/image/Editor/sfondo.png);}");
    ui->RealTextEdit->setStyleSheet("  #RealTextEdit{  color: black; background: #FFFFFF; border-left: 2px solid #404040;}");
    ui->DocNameLabel->setStyleSheet("  #DocNameLabel{ background-color:transparent; border: transparent; color: #505050;}");
    ui->opaqueLogo->setStyleSheet("background: url(:/image/Editor/logo.png)");

    //TOP FRAME
    ui->frameTopBar->setStyleSheet("#frameTopBar{          background: qlineargradient(x1:0, y1:1, x2:1, y2:1, stop:0#6600FF stop:0.53#6600FF stop:0.54#6600FF stop:0.63#5200CC stop:0.64#5200CC stop:0.88 #3D0099);}");
    ui->fileButton->setStyleSheet("#fileButton{           color:white; border:none;}    #fileButton:hover{background-color: #3D0099;}       #fileButton:pressed {background-color: #330080;}");
    ui->visualizzaButton->setStyleSheet("#visualizzaButton{color:white; border:none;}   #visualizzaButton:hover{background-color: #3D0099;} #visualizzaButton:pressed {background-color: #330080;}");
    ui->modificaButton->setStyleSheet("#modificaButton{   color:white; border:none;}    #modificaButton:hover{background-color: #3D0099;}   #modificaButton:pressed {background-color: #330080;}");
    ui->strumentiButton->setStyleSheet("#strumentiButton{ color:white; border:none;}    #strumentiButton:hover{background-color: #3D0099;}  #strumentiButton:pressed {background-color: #330080;}");
    ui->aboutButton->setStyleSheet("#aboutButton{         color:white; border:none;}    #aboutButton:hover{background-color: #3D0099;}      #aboutButton:pressed {background-color: #330080;}");

}


void EditorWindow::installTheme_Day_ClassicOrange(){
    //GENERAL COLOR
    ui->editorFrame->setStyleSheet("   #editorFrame{   background: url(:/image/Editor/sfondo.png);}");
    ui->RealTextEdit->setStyleSheet("  #RealTextEdit{  color: black; background: #FFFFFF; border-left: 2px solid #404040;}");
    ui->DocNameLabel->setStyleSheet("  #DocNameLabel{ background-color:transparent; border: transparent; color: #505050;}");
    ui->opaqueLogo->setStyleSheet("background: url(:/image/Editor/logo.png)");

    //TOP FRAME
    ui->frameTopBar->setStyleSheet("#frameTopBar{          background: qlineargradient(x1:0, y1:1, x2:1, y2:1, stop:0#FFB533 stop:0.53#FFB533 stop:0.54#FFB533 stop:0.63#FFA200 stop:0.64#FFA200 stop:0.88 #FF8000);}");
    ui->fileButton->setStyleSheet("#fileButton{           color:black; border:none;}    #fileButton:hover{background-color: #e67300;}       #fileButton:pressed {background-color: #e67300;}");
    ui->visualizzaButton->setStyleSheet("#visualizzaButton{color:black; border:none;}   #visualizzaButton:hover{background-color: #e67300;} #visualizzaButton:pressed {background-color: #e67300;}");
    ui->modificaButton->setStyleSheet("#modificaButton{   color:black; border:none;}    #modificaButton:hover{background-color: #e67300;}   #modificaButton:pressed {background-color: #e67300;}");
    ui->strumentiButton->setStyleSheet("#strumentiButton{ color:black; border:none;}    #strumentiButton:hover{background-color: #e67300;}  #strumentiButton:pressed {background-color: #e67300;}");
    ui->aboutButton->setStyleSheet("#aboutButton{         color:black; border:none;}    #aboutButton:hover{background-color: #e67300;}      #aboutButton:pressed {background-color: #e67300;}");
}


void EditorWindow::installTheme_Day_ClassicGreen(){
    //GENERAL COLOR
    ui->editorFrame->setStyleSheet("   #editorFrame{   background: url(:/image/Editor/sfondo.png);}");
    ui->RealTextEdit->setStyleSheet("  #RealTextEdit{  color: black; background: #FFFFFF; border-left: 2px solid #404040;}");
    ui->DocNameLabel->setStyleSheet("  #DocNameLabel{ background-color:transparent; border: transparent; color: #505050;}");
    ui->opaqueLogo->setStyleSheet("background: url(:/image/Editor/logo.png)");

    //TOP FRAME
    ui->frameTopBar->setStyleSheet("#frameTopBar{           background:qlineargradient(x1:0, y1:1, x2:1, y2:1, stop:0#00CC00 stop:0.53#00CC00 stop:0.54#00CC00 stop:0.63#009900 stop:0.64#009900 stop:0.88 #006600);}");
    ui->fileButton->setStyleSheet("#fileButton{             color:white; border:none;}  #fileButton:hover{background-color: #008000;}       #fileButton:pressed {background-color: #004D00;}");
    ui->visualizzaButton->setStyleSheet("#visualizzaButton{ color:white; border:none;}  #visualizzaButton:hover{background-color: #008000;} #visualizzaButton:pressed {background-color: #004D00;}");
    ui->modificaButton->setStyleSheet("#modificaButton{     color:white; border:none;}  #modificaButton:hover{background-color: #008000;}   #modificaButton:pressed {background-color: #004D00;}");
    ui->strumentiButton->setStyleSheet("#strumentiButton{   color:white; border:none;}  #strumentiButton:hover{background-color: #008000;}  #strumentiButton:pressed {background-color: #004D00;}");
    ui->aboutButton->setStyleSheet("#aboutButton{           color:white; border:none;}  #aboutButton:hover{background-color: #008000;}      #aboutButton:pressed {background-color: #004D00;}");
}


void EditorWindow::installTheme_Day_ClassicRed(){
    //GENERAL COLOR
    ui->editorFrame->setStyleSheet("   #editorFrame{   background: url(:/image/Editor/sfondo.png);}");
    ui->RealTextEdit->setStyleSheet("  #RealTextEdit{  color: black; background: #FFFFFF; border-left: 2px solid #404040;}");
    ui->DocNameLabel->setStyleSheet("  #DocNameLabel{ background-color:transparent; border: transparent; color: #505050;}");
    ui->opaqueLogo->setStyleSheet("background: url(:/image/Editor/logo.png)");

    //TOP FRAME
    ui->frameTopBar->setStyleSheet("#frameTopBar{           background:qlineargradient(x1:0, y1:1, x2:1, y2:1, stop:0#CC0000 stop:0.53#CC0000 stop:0.54#CC0000 stop:0.63#990000 stop:0.64#990000 stop:0.88 #660000);}");
    ui->fileButton->setStyleSheet("#fileButton{             color:white; border:none;}  #fileButton:hover{background-color: #800000;}       #fileButton:pressed {background-color: #4D0000;}");
    ui->visualizzaButton->setStyleSheet("#visualizzaButton{ color:white; border:none;}  #visualizzaButton:hover{background-color: #800000;} #visualizzaButton:pressed {background-color: #4D0000;}");
    ui->modificaButton->setStyleSheet("#modificaButton{     color:white; border:none;}  #modificaButton:hover{background-color: #800000;}   #modificaButton:pressed {background-color: #4D0000;}");
    ui->strumentiButton->setStyleSheet("#strumentiButton{   color:white; border:none;}  #strumentiButton:hover{background-color: #800000;}  #strumentiButton:pressed {background-color: #4D0000;}");
    ui->aboutButton->setStyleSheet("#aboutButton{           color:white; border:none;}  #aboutButton:hover{background-color: #800000;}      #aboutButton:pressed {background-color: #4D0000;}");

}

void EditorWindow::installTheme_Day_Rainbow(){
    //GENERAL COLOR
    ui->editorFrame->setStyleSheet("   #editorFrame{   background: url(:/image/Editor/sfondo.png);}");
    ui->RealTextEdit->setStyleSheet("  #RealTextEdit{  color: black; background: #FFFFFF; border-left: 2px solid #404040;}");
    ui->DocNameLabel->setStyleSheet("  #DocNameLabel{ background-color:transparent; border: transparent; color: #505050;}");
    ui->opaqueLogo->setStyleSheet("background: url(:/image/Editor/logo.png)");

    //TOP FRAME

    ui->frameTopBar->setStyleSheet("#frameTopBar{           background:qlineargradient(x1:0, y1:1, x2:1, y2:1, stop:0#FFFFFF stop:0.50#FFFFFF  stop:0.57#FF0000 stop:0.65#FF9900 stop:0.72#FFFF00 stop:0.80#40FF00 stop:0.87#00FFFF stop:0.92#0000FF stop:0.97#FF00FF);}");
    ui->fileButton->setStyleSheet("#fileButton{             color:black; border:none;}  #fileButton:hover{background-color: #CCCCCC;}       #fileButton:pressed {background-color: #999999;}");
    ui->visualizzaButton->setStyleSheet("#visualizzaButton{ color:black; border:none;}  #visualizzaButton:hover{background-color: #CCCCCC;} #visualizzaButton:pressed {background-color: #999999;}");
    ui->modificaButton->setStyleSheet("#modificaButton{     color:black; border:none;}  #modificaButton:hover{background-color: #CCCCCC;}   #modificaButton:pressed {background-color: #999999;}");
    ui->strumentiButton->setStyleSheet("#strumentiButton{   color:black; border:none;}  #strumentiButton:hover{background-color: #CCCCCC;}  #strumentiButton:pressed {background-color: #999999;}");
    ui->aboutButton->setStyleSheet("#aboutButton{           color:black; border:none;}  #aboutButton:hover{background-color: #CCCCCC;}      #aboutButton:pressed {background-color: #999999;}");
}

void EditorWindow::installTheme_Day_FountainRainbow(){
    //GENERAL COLOR
    ui->editorFrame->setStyleSheet("   #editorFrame{   background: url(:/image/Editor/sfondo.png);}");
    ui->RealTextEdit->setStyleSheet("  #RealTextEdit{  color: black; background: #FFFFFF; border-left: 2px solid #404040;}");
    ui->DocNameLabel->setStyleSheet("  #DocNameLabel{ background-color:transparent; border: transparent; color: #505050;}");
    ui->opaqueLogo->setStyleSheet("background: url(:/image/Editor/logo.png)");

    //TOP FRAME
    ui->frameTopBar->setStyleSheet("#frameTopBar{           background:qlineargradient(x1:0, y1:1, x2:1, y2:1, stop:0#FF0000 stop:0.16#FF9900 stop:0.32#FFFF00 stop:0.48#40FF00 stop:0.66#00FFFF stop:0.82#0000FF stop:0.98#FF00FF);}");
    ui->fileButton->setStyleSheet("#fileButton{             color:black; background-color:transparent; border:none;}  #fileButton:hover{background-color: transparent;}       #fileButton:pressed {background-color: transparent;}");
    ui->visualizzaButton->setStyleSheet("#visualizzaButton{ color:black; background-color:transparent; border:none;}  #visualizzaButton:hover{background-color: transparent;} #visualizzaButton:pressed {background-color: transparent;}");
    ui->modificaButton->setStyleSheet("#modificaButton{     color:black; background-color:transparent; border:none;}  #modificaButton:hover{background-color: transparent;}   #modificaButton:pressed {background-color: transparent;}");
    ui->strumentiButton->setStyleSheet("#strumentiButton{   color:black; background-color:transparent; border:none;}  #strumentiButton:hover{background-color: transparent;}  #strumentiButton:pressed {background-color: transparent;}");
    ui->aboutButton->setStyleSheet("#aboutButton{           color:black; background-color:transparent; border:none;}  #aboutButton:hover{background-color: transparent;}      #aboutButton:pressed {background-color: transparent;}");
}

void EditorWindow::installTheme_Day_Polito(){
    //GENERAL COLOR
    ui->editorFrame->setStyleSheet("   #editorFrame{   background: url(:/image/Editor/sfondo.png);}");
    ui->RealTextEdit->setStyleSheet("  #RealTextEdit{  color: black; background: #FFFFFF; border-left: 2px solid #404040;}");
    ui->DocNameLabel->setStyleSheet("  #DocNameLabel{ background-color:transparent; border: transparent; color: #505050;}");
    ui->opaqueLogo->setStyleSheet("background: url(:/image/Editor/polilogo.png)");

    //TOP FRAME
    ui->frameTopBar->setStyleSheet("#frameTopBar{           background:#003576;}");
    ui->fileButton->setStyleSheet("#fileButton{             color:white; border:none;}  #fileButton:hover{background-color: #00224d;}       #fileButton:pressed {background-color: #000b1a;}");
    ui->visualizzaButton->setStyleSheet("#visualizzaButton{ color:white; border:none;}  #visualizzaButton:hover{background-color: #00224d;} #visualizzaButton:pressed {background-color: #000b1a;}");
    ui->modificaButton->setStyleSheet("#modificaButton{     color:white; border:none;}  #modificaButton:hover{background-color: #00224d;}   #modificaButton:pressed {background-color: #000b1a;}");
    ui->strumentiButton->setStyleSheet("#strumentiButton{   color:white; border:none;}  #strumentiButton:hover{background-color: #00224d;}  #strumentiButton:pressed {background-color: #000b1a;}");
    ui->aboutButton->setStyleSheet("#aboutButton{           color:white; border:none;}  #aboutButton:hover{background-color: #00224d;}      #aboutButton:pressed {background-color: #000b1a;}");
}

void EditorWindow::installTheme_Day_Special(){
    //GENERAL COLOR
    ui->editorFrame->setStyleSheet("   #editorFrame{   background: url(:/image/Editor/sfondo.png);}");
    ui->RealTextEdit->setStyleSheet("  #RealTextEdit{  color: black; background: #FFFFFF; border-left: 2px solid #404040;}");
    ui->DocNameLabel->setStyleSheet("  #DocNameLabel{ background-color:transparent; border: transparent; color: #505050;}");
    ui->opaqueLogo->setStyleSheet("background: url(:/image/Editor/logo.png)");

    //TOP FRAME
    ui->frameTopBar->setStyleSheet("#frameTopBar{           background: url(:/image/Editor/hidrologo.jpg);}");
    ui->fileButton->setStyleSheet("#fileButton{             color:white; border:none;}  #fileButton:hover{background-color: transparent;}       #fileButton:pressed {background-color: transparent;}");
    ui->visualizzaButton->setStyleSheet("#visualizzaButton{ color:white; border:none;}  #visualizzaButton:hover{background-color: transparent;} #visualizzaButton:pressed {background-color: transparent;}");
    ui->modificaButton->setStyleSheet("#modificaButton{     color:white; border:none;}  #modificaButton:hover{background-color: transparent;}   #modificaButton:pressed {background-color: transparent;}");
    ui->strumentiButton->setStyleSheet("#strumentiButton{   color:white; border:none;}  #strumentiButton:hover{background-color: transparent;}  #strumentiButton:pressed {background-color: transparent;}");
    ui->aboutButton->setStyleSheet("#aboutButton{           color:white; border:none;}  #aboutButton:hover{background-color: transparent;}      #aboutButton:pressed {background-color: transparent;}");
}


/*****************************************************************DARK THEME BEGIN*************************************************************************************/

void EditorWindow::installTheme_Dark_ClassicOrange(){
    //GENERAL COLOR
    ui->editorFrame->setStyleSheet("   #editorFrame{   background: url(:/image/DarkEditor/sfondo.png);}");
    ui->RealTextEdit->setStyleSheet("   #RealTextEdit{  color: white; background: #333333; border-left: 2px solid #e6e6e6;}");
    ui->DocNameLabel->setStyleSheet("  #DocNameLabel{   background-color:transparent; border: transparent; color: #ff8000;}");
    ui->opaqueLogo->setStyleSheet("background: url(:/image/Editor/logo.png)");

    //TOP FRAME
    ui->frameTopBar->setStyleSheet("#frameTopBar{          background: qlineargradient(x1:0, y1:1, x2:1, y2:1, stop:0#FFB533 stop:0.53#FFB533 stop:0.54#FFB533 stop:0.63#FFA200 stop:0.64#FFA200 stop:0.88 #FF8000);}");
    ui->fileButton->setStyleSheet("#fileButton{           color:black; border:none;}    #fileButton:hover{background-color: #e67300;}       #fileButton:pressed {background-color: #e67300;}");
    ui->visualizzaButton->setStyleSheet("#visualizzaButton{color:black; border:none;}   #visualizzaButton:hover{background-color: #e67300;} #visualizzaButton:pressed {background-color: #e67300;}");
    ui->modificaButton->setStyleSheet("#modificaButton{   color:black; border:none;}    #modificaButton:hover{background-color: #e67300;}   #modificaButton:pressed {background-color: #e67300;}");
    ui->strumentiButton->setStyleSheet("#strumentiButton{ color:black; border:none;}    #strumentiButton:hover{background-color: #e67300;}  #strumentiButton:pressed {background-color: #e67300;}");
    ui->aboutButton->setStyleSheet("#aboutButton{         color:black; border:none;}    #aboutButton:hover{background-color: #e67300;}      #aboutButton:pressed {background-color: #e67300;}");

}


void EditorWindow::installTheme_Dark_PlainOrange(){
    //GENERAL COLOR
    ui->editorFrame->setStyleSheet("   #editorFrame{   background: #1A1A1A;}");
    ui->RealTextEdit->setStyleSheet("  #RealTextEdit{  color: white; background: #333333; border-left: 2px solid #e6e6e6;}");
    ui->DocNameLabel->setStyleSheet("  #DocNameLabel{  background-color:transparent; border: transparent; color: #ff8000;}");
    ui->opaqueLogo->setStyleSheet("background: url(:/image/Editor/logo.png)");

    //TOP FRAME
    ui->frameTopBar->setStyleSheet("#frameTopBar{         background: #FF8000;}");
    ui->fileButton->setStyleSheet("#fileButton{           color:black; border:none;}    #fileButton:hover{background-color: #FFAD33;}       #fileButton:pressed {background-color: #FFC266;}");
    ui->visualizzaButton->setStyleSheet("#visualizzaButton{color:black; border:none;}   #visualizzaButton:hover{background-color: #FFAD33;} #visualizzaButton:pressed {background-color: #FFC266;}");
    ui->modificaButton->setStyleSheet("#modificaButton{   color:black; border:none;}    #modificaButton:hover{background-color: #FFAD33;}   #modificaButton:pressed {background-color: #FFC266;}");
    ui->strumentiButton->setStyleSheet("#strumentiButton{ color:black; border:none;}    #strumentiButton:hover{background-color: #FFAD33;}  #strumentiButton:pressed {background-color: #FFC266;}");
    ui->aboutButton->setStyleSheet("#aboutButton{         color:black; border:none;}    #aboutButton:hover{background-color: #FFAD33;}      #aboutButton:pressed {background-color: #FFC266;}");

}


void EditorWindow::installTheme_Dark_ElectricOrange(){
    //GENERAL COLOR
    ui->editorFrame->setStyleSheet("    #editorFrame{   background: black;}");
    ui->RealTextEdit->setStyleSheet("   #RealTextEdit{  color: white; background: #111111; border-left: 2px solid #e6e6e6;}");
    ui->DocNameLabel->setStyleSheet("  #DocNameLabel{   background-color:transparent; border: transparent; color: #ff8000;}");
    ui->opaqueLogo->setStyleSheet("background: url(:/image/Editor/logo.png)");

    //TOP FRAME
    ui->frameTopBar->setStyleSheet("#frameTopBar{         background: qlineargradient(x1:0, y1:1, x2:1, y2:1, stop:0#FFFF00 stop:0.60#FFFF00 stop:0.99#FF0000);}");
    ui->fileButton->setStyleSheet("#fileButton{           color:black; border:none;}    #fileButton:hover{background-color: #FF9900;}       #fileButton:pressed {background-color: #FF0000;}");
    ui->visualizzaButton->setStyleSheet("#visualizzaButton{color:black; border:none;}   #visualizzaButton:hover{background-color: #FF9900;} #visualizzaButton:pressed {background-color: #FF0000;}");
    ui->modificaButton->setStyleSheet("#modificaButton{   color:black; border:none;}    #modificaButton:hover{background-color: #FF9900;}   #modificaButton:pressed {background-color: #FF0000;}");
    ui->strumentiButton->setStyleSheet("#strumentiButton{ color:black; border:none;}    #strumentiButton:hover{background-color: #FF9900;}  #strumentiButton:pressed {background-color: #FF0000;}");
    ui->aboutButton->setStyleSheet("#aboutButton{         color:black; border:none;}    #aboutButton:hover{background-color: #FF9900;}      #aboutButton:pressed {background-color: #FF0000;}");

}


void EditorWindow::installTheme_Dark_ClassicPurple(){
    //GENERAL COLOR
    ui->editorFrame->setStyleSheet("   #editorFrame{   background: url(:/image/DarkEditor/sfondo.png);}");
    ui->RealTextEdit->setStyleSheet("   #RealTextEdit{  color: white; background: #333333; border-left: 2px solid #e6e6e6;}");
    ui->DocNameLabel->setStyleSheet("  #DocNameLabel{   background-color:transparent; border: transparent; color: #ff8000;}");
    ui->opaqueLogo->setStyleSheet("background: url(:/image/Editor/logo.png)");

    //TOP FRAME
    ui->frameTopBar->setStyleSheet("#frameTopBar{          background: qlineargradient(x1:0, y1:1, x2:1, y2:1, stop:0#6600FF stop:0.53#6600FF stop:0.54#6600FF stop:0.63#5200CC stop:0.64#5200CC stop:0.88 #3D0099);}");
    ui->fileButton->setStyleSheet("#fileButton{           color:white; border:none;}    #fileButton:hover{background-color: #3D0099;}       #fileButton:pressed {background-color: #330080;}");
    ui->visualizzaButton->setStyleSheet("#visualizzaButton{color:white; border:none;}   #visualizzaButton:hover{background-color: #3D0099;} #visualizzaButton:pressed {background-color: #330080;}");
    ui->modificaButton->setStyleSheet("#modificaButton{   color:white; border:none;}    #modificaButton:hover{background-color: #3D0099;}   #modificaButton:pressed {background-color: #330080;}");
    ui->strumentiButton->setStyleSheet("#strumentiButton{ color:white; border:none;}    #strumentiButton:hover{background-color: #3D0099;}  #strumentiButton:pressed {background-color: #330080;}");
    ui->aboutButton->setStyleSheet("#aboutButton{         color:white; border:none;}    #aboutButton:hover{background-color: #3D0099;}      #aboutButton:pressed {background-color: #330080;}");

}


void EditorWindow::installTheme_Dark_ClassicBlue(){
    //GENERAL COLOR
    ui->editorFrame->setStyleSheet("   #editorFrame{   background: url(:/image/DarkEditor/sfondo.png);}");
    ui->RealTextEdit->setStyleSheet("   #RealTextEdit{  color: white; background: #333333; border-left: 2px solid #e6e6e6;}");
    ui->DocNameLabel->setStyleSheet("  #DocNameLabel{   background-color:transparent; border: transparent; color: #ff8000;}");
    ui->opaqueLogo->setStyleSheet("background: url(:/image/Editor/logo.png)");

    //TOP FRAME
    ui->frameTopBar->setStyleSheet("#frameTopBar{           background:qlineargradient(x1:0, y1:1, x2:1, y2:1, stop:0#0683FF stop:0.53#0683FF stop:0.54#0683FF stop:0.63#005DBA stop:0.64#005DBA stop:0.88 #0A5597);}");
    ui->fileButton->setStyleSheet("#fileButton{             color:white; border:none;}  #fileButton:hover{background-color: #075299;}       #fileButton:pressed {background-color: #075299;}");
    ui->visualizzaButton->setStyleSheet("#visualizzaButton{ color:white; border:none;}  #visualizzaButton:hover{background-color: #075299;} #visualizzaButton:pressed {background-color: #075299;}");
    ui->modificaButton->setStyleSheet("#modificaButton{     color:white; border:none;}  #modificaButton:hover{background-color: #075299;}   #modificaButton:pressed {background-color: #075299;}");
    ui->strumentiButton->setStyleSheet("#strumentiButton{   color:white; border:none;}  #strumentiButton:hover{background-color: #075299;}  #strumentiButton:pressed {background-color: #075299;}");
    ui->aboutButton->setStyleSheet("#aboutButton{           color:white; border:none;}  #aboutButton:hover{background-color: #075299;}      #aboutButton:pressed {background-color: #075299;}");
}


void EditorWindow::installTheme_Dark_ClassicGreen(){
    //GENERAL COLOR
    ui->editorFrame->setStyleSheet("   #editorFrame{   background: url(:/image/DarkEditor/sfondo.png);}");
    ui->RealTextEdit->setStyleSheet("   #RealTextEdit{  color: white; background: #333333; border-left: 2px solid #e6e6e6;}");
    ui->DocNameLabel->setStyleSheet("  #DocNameLabel{   background-color:transparent; border: transparent; color: #ff8000;}");
    ui->opaqueLogo->setStyleSheet("background: url(:/image/Editor/logo.png)");

    //TOP FRAME
    ui->frameTopBar->setStyleSheet("#frameTopBar{           background:qlineargradient(x1:0, y1:1, x2:1, y2:1, stop:0#00CC00 stop:0.53#00CC00 stop:0.54#00CC00 stop:0.63#009900 stop:0.64#009900 stop:0.88 #006600);}");
    ui->fileButton->setStyleSheet("#fileButton{             color:white; border:none;}  #fileButton:hover{background-color: #008000;}       #fileButton:pressed {background-color: #004D00;}");
    ui->visualizzaButton->setStyleSheet("#visualizzaButton{ color:white; border:none;}  #visualizzaButton:hover{background-color: #008000;} #visualizzaButton:pressed {background-color: #004D00;}");
    ui->modificaButton->setStyleSheet("#modificaButton{     color:white; border:none;}  #modificaButton:hover{background-color: #008000;}   #modificaButton:pressed {background-color: #004D00;}");
    ui->strumentiButton->setStyleSheet("#strumentiButton{   color:white; border:none;}  #strumentiButton:hover{background-color: #008000;}  #strumentiButton:pressed {background-color: #004D00;}");
    ui->aboutButton->setStyleSheet("#aboutButton{           color:white; border:none;}  #aboutButton:hover{background-color: #008000;}      #aboutButton:pressed {background-color: #004D00;}");
}

void EditorWindow::installTheme_Dark_ClassicRed(){
    //GENERAL COLOR
    ui->editorFrame->setStyleSheet("   #editorFrame{   background: url(:/image/DarkEditor/sfondo.png);}");
    ui->RealTextEdit->setStyleSheet("   #RealTextEdit{  color: white; background: #333333; border-left: 2px solid #e6e6e6;}");
    ui->DocNameLabel->setStyleSheet("  #DocNameLabel{   background-color:transparent; border: transparent; color: #ff8000;}");
    ui->opaqueLogo->setStyleSheet("background: url(:/image/Editor/logo.png)");

    //TOP FRAME
    ui->frameTopBar->setStyleSheet("#frameTopBar{           background:qlineargradient(x1:0, y1:1, x2:1, y2:1, stop:0#CC0000 stop:0.53#CC0000 stop:0.54#CC0000 stop:0.63#990000 stop:0.64#990000 stop:0.88 #660000);}");
    ui->fileButton->setStyleSheet("#fileButton{             color:white; border:none;}  #fileButton:hover{background-color: #800000;}       #fileButton:pressed {background-color: #4D0000;}");
    ui->visualizzaButton->setStyleSheet("#visualizzaButton{ color:white; border:none;}  #visualizzaButton:hover{background-color: #800000;} #visualizzaButton:pressed {background-color: #4D0000;}");
    ui->modificaButton->setStyleSheet("#modificaButton{     color:white; border:none;}  #modificaButton:hover{background-color: #800000;}   #modificaButton:pressed {background-color: #4D0000;}");
    ui->strumentiButton->setStyleSheet("#strumentiButton{   color:white; border:none;}  #strumentiButton:hover{background-color: #800000;}  #strumentiButton:pressed {background-color: #4D0000;}");
    ui->aboutButton->setStyleSheet("#aboutButton{           color:white; border:none;}  #aboutButton:hover{background-color: #800000;}      #aboutButton:pressed {background-color: #4D0000;}");
}

void EditorWindow::installTheme_Dark_Rainbow(){
    //GENERAL COLOR
    ui->editorFrame->setStyleSheet("   #editorFrame{   background: url(:/image/DarkEditor/sfondo.png);}");
    ui->RealTextEdit->setStyleSheet("   #RealTextEdit{  color: white; background: #333333; border-left: 2px solid #e6e6e6;}");
    ui->DocNameLabel->setStyleSheet("  #DocNameLabel{   background-color:transparent; border: transparent; color: #ff8000;}");
    ui->opaqueLogo->setStyleSheet("background: url(:/image/Editor/logo.png)");

    //TOP FRAME
    ui->frameTopBar->setStyleSheet("#frameTopBar{           background:qlineargradient(x1:0, y1:1, x2:1, y2:1, stop:0#000000 stop:0.50#000000  stop:0.57#FF0000 stop:0.65#FF9900 stop:0.72#FFFF00 stop:0.80#40FF00 stop:0.87#00FFFF stop:0.92#0000FF stop:0.97#FF00FF);}");
    ui->fileButton->setStyleSheet("#fileButton{             color:white; border:none;}  #fileButton:hover{background-color: #4D4D4D;}       #fileButton:pressed {background-color: #666666;}");
    ui->visualizzaButton->setStyleSheet("#visualizzaButton{ color:white; border:none;}  #visualizzaButton:hover{background-color: #4D4D4D;} #visualizzaButton:pressed {background-color: #666666;}");
    ui->modificaButton->setStyleSheet("#modificaButton{     color:white; border:none;}  #modificaButton:hover{background-color: #4D4D4D;}   #modificaButton:pressed {background-color: #666666;}");
    ui->strumentiButton->setStyleSheet("#strumentiButton{   color:white; border:none;}  #strumentiButton:hover{background-color: #4D4D4D;}  #strumentiButton:pressed {background-color: #666666;}");
    ui->aboutButton->setStyleSheet("#aboutButton{           color:white; border:none;}  #aboutButton:hover{background-color: #4D4D4D;}      #aboutButton:pressed {background-color: #666666;}");
}

void EditorWindow::installTheme_Dark_FountainRainbow(){
    //GENERAL COLOR
    ui->editorFrame->setStyleSheet("   #editorFrame{   background: url(:/image/DarkEditor/sfondo.png);}");
    ui->RealTextEdit->setStyleSheet("   #RealTextEdit{  color: white; background: #333333; border-left: 2px solid #e6e6e6;}");
    ui->DocNameLabel->setStyleSheet("  #DocNameLabel{   background-color:transparent; border: transparent; color: #ff8000;}");
    ui->opaqueLogo->setStyleSheet("background: url(:/image/Editor/logo.png)");

    //TOP FRAME
    ui->frameTopBar->setStyleSheet("#frameTopBar{           background:qlineargradient(x1:0, y1:1, x2:1, y2:1, stop:0#FF0000 stop:0.16#FF9900 stop:0.32#FFFF00 stop:0.48#40FF00 stop:0.66#00FFFF stop:0.82#0000FF stop:0.98#FF00FF);}");
    ui->fileButton->setStyleSheet("#fileButton{             color:black; background-color:transparent; border:none;}  #fileButton:hover{background-color: transparent;}       #fileButton:pressed {background-color: transparent;}");
    ui->visualizzaButton->setStyleSheet("#visualizzaButton{ color:black; background-color:transparent; border:none;}  #visualizzaButton:hover{background-color: transparent;} #visualizzaButton:pressed {background-color: transparent;}");
    ui->modificaButton->setStyleSheet("#modificaButton{     color:black; background-color:transparent; border:none;}  #modificaButton:hover{background-color: transparent;}   #modificaButton:pressed {background-color: transparent;}");
    ui->strumentiButton->setStyleSheet("#strumentiButton{   color:black; background-color:transparent; border:none;}  #strumentiButton:hover{background-color: transparent;}  #strumentiButton:pressed {background-color: transparent;}");
    ui->aboutButton->setStyleSheet("#aboutButton{           color:black; background-color:transparent; border:none;}  #aboutButton:hover{background-color: transparent;}      #aboutButton:pressed {background-color: transparent;}");
}

void EditorWindow::installTheme_Dark_Polito(){
    //GENERAL COLOR
    ui->editorFrame->setStyleSheet("   #editorFrame{   background: url(:/image/DarkEditor/sfondo.png);}");
    ui->RealTextEdit->setStyleSheet("   #RealTextEdit{  color: white; background: #333333; border-left: 2px solid #e6e6e6;}");
    ui->DocNameLabel->setStyleSheet("  #DocNameLabel{   background-color:transparent; border: transparent; color: #ff8000;}");
    ui->opaqueLogo->setStyleSheet("background: url(:/image/Editor/polilogo.png)");

    //TOP FRAME
    ui->frameTopBar->setStyleSheet("#frameTopBar{           background:#003576;}");
    ui->fileButton->setStyleSheet("#fileButton{             color:white; border:none;}  #fileButton:hover{background-color: #00224d;}       #fileButton:pressed {background-color: #000b1a;}");
    ui->visualizzaButton->setStyleSheet("#visualizzaButton{ color:white; border:none;}  #visualizzaButton:hover{background-color: #00224d;} #visualizzaButton:pressed {background-color: #000b1a;}");
    ui->modificaButton->setStyleSheet("#modificaButton{     color:white; border:none;}  #modificaButton:hover{background-color: #00224d;}   #modificaButton:pressed {background-color: #000b1a;}");
    ui->strumentiButton->setStyleSheet("#strumentiButton{   color:white; border:none;}  #strumentiButton:hover{background-color: #00224d;}  #strumentiButton:pressed {background-color: #000b1a;}");
    ui->aboutButton->setStyleSheet("#aboutButton{           color:white; border:none;}  #aboutButton:hover{background-color: #00224d;}      #aboutButton:pressed {background-color: #000b1a;}");
}

void EditorWindow::installTheme_Dark_Special(){
    //GENERAL COLOR
    ui->editorFrame->setStyleSheet("   #editorFrame{   background: url(:/image/DarkEditor/sfondo.png);}");
    ui->RealTextEdit->setStyleSheet("   #RealTextEdit{  color: white; background: #333333; border-left: 2px solid #e6e6e6;}");
    ui->DocNameLabel->setStyleSheet("  #DocNameLabel{   background-color:transparent; border: transparent; color: #ff8000;}");
    ui->opaqueLogo->setStyleSheet("background: url(:/image/Editor/logo.png)");

    //TOP FRAME
    ui->frameTopBar->setStyleSheet("#frameTopBar{           background: url(:/image/Editor/hidrologo.jpg);}");
    ui->fileButton->setStyleSheet("#fileButton{             color:white; border:none;}  #fileButton:hover{background-color: transparent;}       #fileButton:pressed {background-color: transparent;}");
    ui->visualizzaButton->setStyleSheet("#visualizzaButton{ color:white; border:none;}  #visualizzaButton:hover{background-color: transparent;} #visualizzaButton:pressed {background-color: transparent;}");
    ui->modificaButton->setStyleSheet("#modificaButton{     color:white; border:none;}  #modificaButton:hover{background-color: transparent;}   #modificaButton:pressed {background-color: transparent;}");
    ui->strumentiButton->setStyleSheet("#strumentiButton{   color:white; border:none;}  #strumentiButton:hover{background-color: transparent;}  #strumentiButton:pressed {background-color: transparent;}");
    ui->aboutButton->setStyleSheet("#aboutButton{           color:white; border:none;}  #aboutButton:hover{background-color: transparent;}      #aboutButton:pressed {background-color: transparent;}");
}

/***************************************************************************************************************************************
 *                                                    STANDALONE FUNCTION                                                              *
 *                                                                                                                                     *
 ***************************************************************************************************************************************/
//Return to MenuWindow
void EditorWindow::CloseDocumentRequest() {
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
    _client->sendRequestMsg(req);
}


//Set the button checked-status of Alignment buttons
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


//Set the button style if Alignment is checked
void EditorWindow::AlignButtonStyleHandler() {
   if(ui->buttonAlignCX->isChecked()) {
        ui->buttonAlignCX->setStyleSheet("  #buttonAlignCX{background-color:#CACFD2; border-radius:4px;}");
        ui->buttonAlignSX->setStyleSheet("  #buttonAlignSX{border-radius:4px}    #buttonAlignSX:hover{background-color: #909497;}");
        ui->buttonAlignDX->setStyleSheet("  #buttonAlignDX{border-radius:4px}    #buttonAlignDX:hover{background-color: #909497;}");
        ui->buttonAlignJFX->setStyleSheet(" #buttonAlignJFX{border-radius:4px}   #buttonAlignJFX:hover{background-color: #909497;}");
    } else if(ui->buttonAlignSX->isChecked()) {
        ui->buttonAlignCX->setStyleSheet("  #buttonAlignCX{border-radius:4px}    #buttonAlignCX:hover{background-color: #909497;}");
        ui->buttonAlignSX->setStyleSheet("  #buttonAlignSX{background-color:#CACFD2; border-radius:4px;}");
        ui->buttonAlignDX->setStyleSheet("  #buttonAlignDX{border-radius:4px}    #buttonAlignDX:hover{background-color: #909497;}");
        ui->buttonAlignJFX->setStyleSheet(" #buttonAlignJFX{border-radius:4px}   #buttonAlignJFX:hover{background-color: #909497;}");
    } else if(ui->buttonAlignDX->isChecked()) {
        ui->buttonAlignCX->setStyleSheet("  #buttonAlignCX{border-radius:4px}    #buttonAlignCX:hover{background-color: #909497;}");
        ui->buttonAlignSX->setStyleSheet("  #buttonAlignSX{border-radius:4px}    #buttonAlignSX:hover{background-color: #909497;}");
        ui->buttonAlignDX->setStyleSheet("  #buttonAlignDX{background-color:#CACFD2; border-radius:4px;}");
        ui->buttonAlignJFX->setStyleSheet(" #buttonAlignJFX{border-radius:4px}   #buttonAlignJFX:hover{background-color: #909497;}");
    } else if(ui->buttonAlignJFX->isChecked()) {
        ui->buttonAlignCX->setStyleSheet("  #buttonAlignCX{border-radius:4px}    #buttonAlignCX:hover{background-color: #909497;}");
        ui->buttonAlignSX->setStyleSheet("  #buttonAlignSX{border-radius:4px}    #buttonAlignSX:hover{background-color: #909497;}");
        ui->buttonAlignDX->setStyleSheet("  #buttonAlignDX{border-radius:4px}    #buttonAlignDX:hover{background-color: #909497;}");
        ui->buttonAlignJFX->setStyleSheet(" #buttonAlignJFX{background-color:#CACFD2; border-radius:4px;}");
    } else {
       ui->buttonAlignCX->setStyleSheet("   #buttonAlignCX{border-radius:4px}    #buttonAlignCX:hover{background-color: #909497;}");
       ui->buttonAlignSX->setStyleSheet("   #buttonAlignSX{border-radius:4px}    #buttonAlignSX:hover{background-color: #909497;}");
       ui->buttonAlignDX->setStyleSheet("   #buttonAlignDX{border-radius:4px}    #buttonAlignDX:hover{background-color: #909497;}");
       ui->buttonAlignJFX->setStyleSheet("  #buttonAlignJFX{border-radius:4px}   #buttonAlignJFX:hover{background-color: #909497;}");
    }
}

//Set the button style if Bold/Italic/Underline is checked
void EditorWindow::refreshFormatButtons() {
    if(ui->buttonBold->isChecked())
        ui->buttonBold->setStyleSheet("#buttonBold{background-color:#CACFD2; border-radius:4px;}");
    else
        ui->buttonBold->setStyleSheet("#buttonBold{border-radius:4px}    #buttonBold:hover{background-color: #909497;}");
    if(ui->buttonItalic->isChecked())
        ui->buttonItalic->setStyleSheet("#buttonItalic{background-color:#CACFD2; border-radius:4px;}");
    else
        ui->buttonItalic->setStyleSheet("#buttonItalic{border-radius:4px}    #buttonItalic:hover{background-color: #909497;}");
    if(ui->buttonUnderline->isChecked())
        ui->buttonUnderline->setStyleSheet("#buttonUnderline{background-color:#CACFD2; border-radius:4px;}");
    else
        ui->buttonUnderline->setStyleSheet("#buttonUnderline{border-radius:4px}    #buttonUnderline:hover{background-color: #909497;}");
}

void EditorWindow::hideCollab(){
    estate.SetCollaboratorBar(false);
    ui->listWidgetOn->hide();
    ui->listWidgetOff->hide();
    ui->labelUser->hide();
    ui->profileButton->hide();
    ui->label->hide();
    ui->label_2->hide();
    ui->label_3->hide();
    ui->labelCollOn->hide();
    ui->labelCollOff->hide();
    ui->line->hide();
    ui->line_2->hide();
    ui->line_3->hide();
    ui->DocNameLabel->hide();
    ui->verticalLayout_5->setContentsMargins(10,5,0,0);
}

void EditorWindow::showCollab(){
    estate.SetCollaboratorBar(true);
    ui->listWidgetOn->show();
    ui->listWidgetOff->show();
    ui->labelUser->show();
    ui->profileButton->show();
    ui->label->show();
    ui->label_2->show();
    ui->label_3->show();
    ui->labelCollOn->show();
    ui->labelCollOff->show();
    ui->line->show();
    ui->line_2->show();
    ui->line_3->show();
    ui->DocNameLabel->show();
    ui->verticalLayout_5->setContentsMargins(0,5,35,0);
}

void EditorWindow::showToolbar(){
    estate.SetToolbar(true);
    ui->buttonBold->show();
    ui->buttonItalic->show();
    ui->buttonUnderline->show();
    ui->fontFamilyBox->show();
    ui->fontSizeBox->show();
    ui->buttonAlignCX->show();
    ui->buttonAlignDX->show();
    ui->buttonAlignSX->show();
    ui->buttonAlignJFX->show();
    ui->buttonCopy->show();
    ui->buttonCut->show();
    ui->buttonPaste->show();
    ui->buttonColor->show();
}

void EditorWindow::hideToolbar(){
    estate.SetToolbar(false);
    ui->buttonBold->hide();
    ui->buttonItalic->hide();
    ui->buttonUnderline->hide();
    ui->fontFamilyBox->hide();
    ui->fontSizeBox->hide();
    ui->buttonAlignCX->hide();
    ui->buttonAlignDX->hide();
    ui->buttonAlignSX->hide();
    ui->buttonAlignJFX->hide();
    ui->buttonCopy->hide();
    ui->buttonCut->hide();
    ui->buttonPaste->hide();
    ui->buttonColor->hide();
}

//HANDLE LOSS OF CONNECTION
bool EditorWindow::handleConnectionLoss() {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::warning(nullptr, "Attenzione", "Non sono riuscito a contattare il server!\n"
                                                        "\n"
                                                        "Vuoi chiudere il programma?",  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        QApplication::exit(-1000);
    }else if(reply == QMessageBox::No){
        BruteClose=false;  //The user want to continue editing the document, maybe for save it locally.
    }
    return true;
}

//INITIAL CONDITION OF TEXT
void EditorWindow::setupInitialCondition(){
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

void EditorWindow::SetDynamicDocNameLabel(){

    ui->DocNameLabel->setText(docName); //Update docNameLabel after rename! Important!!!

    ui->DocNameLabel->adjustSize();
    ui->DocNameLabel->resize(ui->DocNameLabel->sizeHint());
    qDebug() << "DocNameLabel pixel width is --> " << ui->DocNameLabel->width();
    if(ui->DocNameLabel->width() > 240){
        QFontMetrics metrics(ui->DocNameLabel->font());
        QString elidedText = metrics.elidedText(docName, Qt::ElideRight, ui->DocNameLabel->width());
        ui->DocNameLabel->setText(elidedText);
    }
}


/***************************************************************************************************************************************
 *                                                ONE INSTANCE HANDLER FUNCTION                                                        *
 *                                                                                                                                     *
 ***************************************************************************************************************************************/
void EditorWindow:: setUserProfileClosed(){
    profile_closed = true;
}

void EditorWindow::on_profileButton_clicked() {
    if(profile_closed){//you can access to the stats, else you must close the current UserProfile Window

        QString filename, owner, timestamp;
        QList<QListWidgetItem*> fileItem;
        int Contafile=0;
        int ContaFileOwner=0;

        if(!_client->getVectorFile().empty()) {
            std::vector<File> files = _client->getVectorFile();
            foreach (File f, files) {
                filename  = QString::fromUtf8(f.getfilename().c_str());
                owner     = QString::fromUtf8(f.getowner().c_str());
                timestamp = QString::fromUtf8(f.gettimestamp().c_str());
                Contafile++;
                if(owner==_client->getUsername()){
                    ContaFileOwner++;
                }
            }
        } else {
            Contafile=0;
            ContaFileOwner=0;
        }

        up = new UserProfile(_client, _client->getUsername(), _client->getMail(), Contafile, ContaFileOwner); //with parameters
        connect(up, &UserProfile::closeUserProfile, this, &EditorWindow::setUserProfileClosed);
        profile_closed = false;
        //up->show(); Not necessary is done by the costructor
    }
}

void EditorWindow::setSettingsClosed(){
    settings_closed = true;
    LoadUserSetting(); //Load Users settings after close "settings window"
}

void EditorWindow::openSettingsWindows(){
    if(settings_closed){//you can access to the stats, else you must close the current Settings Window

        s = new Settings(estate);
        connect(s, &Settings::closeSettings, this, &EditorWindow::setSettingsClosed);
        s->show();
        settings_closed = false;
    }
}

void EditorWindow::setInfoWindowClosed(){
    infowindow_closed = true;
}

void EditorWindow::openInfoWindows(){
    if(infowindow_closed){//you can access to the stats, else you must close the current Settings Window
        iw = new infoWindow();
        connect(iw, &infoWindow::closeInfoWindow, this, &EditorWindow::setInfoWindowClosed);
        //->show() is already done by constructo of infowindow
        //iw->show();
        infowindow_closed = false;
    }
}



/***************************************************************************************************************************************
 *                                                    OTHER SLOT FUNCTION                                                              *
 *                                                                                                                                     *
 ***************************************************************************************************************************************/

void EditorWindow::showPopupSuccess(QString result, std::string filename) {
    if(result == "LOGOUTURI_SUCCESS") {
        this->close();
        delete this;
    } else if (result == "RENAME_SUCCESS") {
        //filename.toLatin1() is not necessary because the conversione is done by the server in action NEWFILE_REQUEST, RENAMEFILE_REQUEST
        docName = QString::fromStdString(filename);
        SetDynamicDocNameLabel();
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

void EditorWindow::showCollabColorsMap(myCollabColorsMap collabColorsMap) {

    //this will show remote cursor of other users
    cursorChangeRequest(ui->RealTextEdit->textCursor().position());

    ui->listWidgetOn->clear();
    ui->listWidgetOff->clear();

    QString username=nullptr, itemString=nullptr, user=nullptr, color=nullptr, ic=nullptr;
    QChar firstLetter;
    QList<QListWidgetItem*> fileItem;
    QListWidgetItem* itemOn;
    QListWidgetItem* itemOff;
    QLinearGradient gradient = QLinearGradient(35, 35, 36, 35);
    QBrush brush;

    for(std::map<std::string, std::pair<std::string,bool>>::const_iterator it = collabColorsMap.begin(); it != collabColorsMap.end(); ++it){
        user = QString::fromStdString(it->first);
        color = QString::fromStdString(it->second.first);
        bool isOnline = it->second.second;
        username = _client->getUsername();

        if(username==user)
            continue;

        for (int i=0;i<user.length();i++) {
            firstLetter = user.at(i);
            if(firstLetter.isLetter())
                break;
        }

        firstLetter = SimplifySingleCharForSorting(firstLetter,1);
        ic = QString(":/image/Letters/%1.png").arg(firstLetter.toUpper());

        if(isOnline) {
            color[1]='f';
            color[2]='f';
            gradient.setColorAt(0,QColor(color));
            gradient.setColorAt(1,Qt::transparent);
            brush = QBrush(gradient);
            itemOn = new QListWidgetItem(itemString, ui->listWidgetOn);
            itemOn->setText(" "+user);
            itemOn->setIcon(QIcon(ic));
            itemOn->setBackground(brush);
            itemOn->setToolTip("Mostrare mail");
            fileItem.append(itemOn);
        }
        else {
            gradient.setColorAt(0,QColor(color));
            gradient.setColorAt(1,Qt::transparent);
            brush = QBrush(gradient);
            itemOff = new QListWidgetItem(itemString, ui->listWidgetOff);
            itemOff->setText(" "+user);
            itemOff->setIcon(QIcon(ic));
            itemOff->setBackground(brush);
            itemOff->setToolTip("Mostrare mail");
            fileItem.append(itemOff);
        }
     }
}

void EditorWindow::getUserOffline(myCollabColorsMap collabColorsMap) {
    showCollabColorsMap(collabColorsMap);
}

void EditorWindow::getUserOnline(myCollabColorsMap collabColorsMap) {
    showCollabColorsMap(collabColorsMap);
}

void EditorWindow::showSymbolsAt(int firstIndex, std::vector<symbol> symbols) {
    wchar_t letter;
    int index = firstIndex;
    QTextCursor c = ui->RealTextEdit->textCursor();

    auto t_start1 = std::chrono::high_resolution_clock::now();

    c.beginEditBlock();
    foreach (symbol s, symbols) {
        letter = s.getLetter();
        QTextCharFormat newFormat;
        QTextBlockFormat newBlockFormat;

        /* Apply transparency (put 01 as alpha value) if btn color is unchecked */
        QString colorStr = QString::fromStdString(s.getStyle().getColor());
        if(!ui->buttonColor->isChecked()) {
            colorStr[1] = '0';
            colorStr[2] = '1';
        }
        QColor color(colorStr);

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
        int oldPos = pos < c.position() ? c.position()+1 : c.position();

        //if user2 insert a char at the end of the selection of user1 -> this can cause extension of user1's selection (that is wrong)
        if(c.hasSelection() && pos == endIndex) {
            int startIndex = c.selectionStart();

            /* Insert (formatted) char */
            c.setPosition(pos);
            c.setCharFormat(newFormat);
            c.insertText(static_cast<QString>(letter));
            c.setBlockFormat(newBlockFormat);

            /* Keep current selection */
            c.setPosition(oldPos == startIndex ? endIndex : startIndex, QTextCursor::MoveAnchor);
            c.setPosition(oldPos == startIndex ? startIndex : endIndex, QTextCursor::KeepAnchor);
        }
        else {
            /* Insert (formatted) char */
            c.setPosition(pos);
            c.setCharFormat(newFormat);
            c.insertText(static_cast<QString>(letter));
            c.setBlockFormat(newBlockFormat);
            c.setPosition(oldPos);
        }

        //if the selected sizes received are not an index of combobox, add them (and hide them)
        if(ui->fontSizeBox->findText(QString::number(s.getStyle().getFontSize())) == -1) {
            ui->fontSizeBox->addItem(QString::number(s.getStyle().getFontSize()));
            hideLastAddedItem(ui->fontSizeBox);
        }
    }
    c.endEditBlock();
    ui->RealTextEdit->setTextCursor(c);

    auto t_end1 = std::chrono::high_resolution_clock::now();
    double elapsed_time_ms1 = std::chrono::duration<double, std::milli>(t_end1-t_start1).count();
    std::cout << "SHOW SYMBOLS AT - ELAPSED (ms): " << elapsed_time_ms1 << std::endl;
}

void EditorWindow::showSymbol(std::pair<int, wchar_t> tuple, symbolStyle style) {
    int pos = tuple.first;
    wchar_t c = tuple.second;
    QTextCharFormat format;

    /* Apply transparency (put 01 as alpha value) if btn color is unchecked */
    QString colorStr = QString::fromStdString(style.getColor());
    if(!ui->buttonColor->isChecked()) {
        colorStr[1] = '0';
        colorStr[2] = '1';
    }
    QColor color(colorStr);

    /* Set format based on style received */
    style.isBold() ? format.setFontWeight(QFont::Bold) : format.setFontWeight(QFont::Normal);
    format.setFontItalic(style.isItalic());
    format.setFontUnderline(style.isUnderlined());
    format.setFontFamily(QString::fromStdString(style.getFontFamily()));
    format.setFontPointSize(style.getFontSize());
    format.setBackground(color);

    QTextCursor cursor = ui->RealTextEdit->textCursor();
    cursor.beginEditBlock();

    int endIndex;
    cursor.hasSelection() ? endIndex = cursor.selectionEnd() : endIndex = -90;
    int oldPos = pos < cursor.position() ? cursor.position()+1 : cursor.position();

    //if user2 insert a char at the end of the selection of user1 -> this can cause extension of user1's selection (that is wrong)
    if(cursor.hasSelection() && pos == endIndex) {
        int startIndex = cursor.selectionStart();

        /* Insert (formatted) char */
        cursor.setPosition(pos);
        cursor.setCharFormat(format);
        cursor.insertText(static_cast<QString>(c));

        /* Keep current selection */
        cursor.setPosition(oldPos == startIndex ? endIndex : startIndex, QTextCursor::MoveAnchor);
        cursor.setPosition(oldPos == startIndex ? startIndex : endIndex, QTextCursor::KeepAnchor);
    }
    else {
        /* Insert (formatted) char */
        cursor.setPosition(pos);
        cursor.setCharFormat(format);
        cursor.insertText(static_cast<QString>(c));
        cursor.setPosition(oldPos);
    }

    //if that selected size is not an index of combobox, add it (and hide it)
    if(ui->fontSizeBox->findText(QString::number(style.getFontSize())) == -1) {
        ui->fontSizeBox->addItem(QString::number(style.getFontSize()));
        hideLastAddedItem(ui->fontSizeBox);
        ui->RealTextEdit->setFontPointSize(cursor.charFormat().fontPointSize());
        ui->fontSizeBox->setCurrentText(QString::number(cursor.charFormat().fontPointSize()));
    }
    cursor.endEditBlock();
    ui->RealTextEdit->setTextCursor(cursor);

    qDebug() << "Written in pos: " << pos << endl;
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}

void EditorWindow::eraseSymbols(int startIndex, int endIndex) {
    QTextCursor cursor = ui->RealTextEdit->textCursor();

    cursor.beginEditBlock();
    cursor.setPosition(endIndex);
    cursor.setPosition(startIndex, QTextCursor::KeepAnchor);
    cursor.removeSelectedText();
    cursor.endEditBlock();

    qDebug() << "Deleted char range" << endl;
    ui->RealTextEdit->setFocus(); //Return focus to textedit
}

void EditorWindow::formatSymbols(int startIndex, int endIndex, int format) {
    QTextCursor cursor = ui->RealTextEdit->textCursor();
    QTextCharFormat newFormat;

    cursor.beginEditBlock();
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
    cursor.endEditBlock();

    qDebug() << "Formatted char range" << endl;
    ui->RealTextEdit->setFocus();
}

void EditorWindow::hideAndChangeCustomFontSize() {
    /* Hide last added item */
    if(!(std::find(sizeVector.begin(), sizeVector.end(), ui->fontSizeBox->currentText().toInt()) != sizeVector.end()))
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

    cursor.beginEditBlock();
    while(endIndex > startIndex) {
        cursor.setPosition(--endIndex);
        cursor.setPosition(endIndex+1, QTextCursor::KeepAnchor); //to select the char to be updated
        newFormat.setFontPointSize(fontSize);
        cursor.mergeCharFormat(newFormat);
    }
    cursor.endEditBlock();

    qDebug() << "Changed font size in char range" << endl;
    ui->RealTextEdit->setFocus();
}

void EditorWindow::changeFontFamily(int startIndex, int endIndex, std::string fontFamily) {
    QTextCursor cursor = ui->RealTextEdit->textCursor();
    QTextCharFormat newFormat;

    cursor.beginEditBlock();
    while(endIndex > startIndex) {
        cursor.setPosition(--endIndex);
        cursor.setPosition(endIndex+1, QTextCursor::KeepAnchor); //to select the char to be updated
        newFormat.setFontFamily(QString::fromStdString(fontFamily));
        cursor.mergeCharFormat(newFormat);
    }
    cursor.endEditBlock();

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

    cursor.beginEditBlock();
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
    cursor.endEditBlock();
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
        symbolStyle curStyle = constructSymStyle(rxs, s, alignments.first());
        qDebug() << curStyle.getFontSize();
        if((ui->fontFamilyBox->findText(QString::fromStdString(curStyle.getFontFamily())) == -1 &&
            curStyle.getFontFamily() != "") || curStyle.getFontSize() > 200 || curStyle.getFontSize() <= 0)
            throw OperationNotSupported();
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
        _client->sendRequestMsg(req);
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
        _client->sendRequestMsg(req);
    }
}

void EditorWindow::sendAlignChangeRequest(int blockStart, int blockEnd, int alignment) {
    //Serialize data
    json j;
    jsonUtility::to_json_alignment_change(j, "ALIGNMENT_CHANGE_REQUEST", blockStart, blockEnd, alignment);
    const std::string req = j.dump();

    //Send data (header and body)
    _client->sendRequestMsg(req);
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
        _client->sendRequestMsg(req);
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

QString EditorWindow::updateBackgroundColor(QString html, QString finalAlpha) {
    QRegularExpression rx("background-color:rgba(([^;]+));");
    QStringList list = getRegexListFromHTML(html, rx);
    foreach (QString s, list) {
        QString originalBackColor = s;
        int index = s.lastIndexOf(",");
        QString curAlpha = s.mid(index+1, s.length()-index-2);
        html.replace(originalBackColor, s.replace(curAlpha, finalAlpha));
    }
    return html;
}

void EditorWindow::removeCharRequest(int startIndex, int endIndex) {
    //Serialize data
    json j;
    jsonUtility::to_json_removal_range(j, "REMOVAL_REQUEST", startIndex, endIndex);
    const std::string req = j.dump();

    //Send data (header and body)
    _client->sendRequestMsg(req);
}

void EditorWindow::cursorChangeRequest(int pos) {
    //Serialize data
    json j;
    jsonUtility::to_json_cursor_change_req(j, "CURSOR_CHANGE_REQUEST", pos);
    const std::string req = j.dump();

    //Send data (header and body)
    _client->sendRequestMsg(req);
}

void EditorWindow::collabColorsRequest(QString uri) {
    //Serialize data
    json j;
    jsonUtility::to_json_collab_colors(j, "COLLAB_COLORS_REQUEST", uri.toStdString());
    const std::string req = j.dump();

    //Send data (header and body)
    _client->sendRequestMsg(req);
}

void EditorWindow::insertCharRangeRequest(int pos, bool cursorHasSelection) noexcept(false) {
    QClipboard *clipboard = QApplication::clipboard();
    const QMimeData *mimeData = clipboard->mimeData();
    QTextCursor cursor = ui->RealTextEdit->textCursor();

    auto t_start1 = std::chrono::high_resolution_clock::now();

    if(mimeData->hasText() && !mimeData->hasImage() && !mimeData->hasUrls() && !mimeData->html().contains("<a href")) {
        /* Get chars from clipboard mimeData */
        int numChars = mimeData->text().size(); //number of chars = number of iterations
        std::wstring str_to_paste = mimeData->text().toStdWString();

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
        /* Get char styles from HTML */
        QVector<std::pair<int,symbolStyle>> styles;
        try {
            styles = getStylesFromHTML(mimeData->html(), cursor, alignmentsValues);
        } catch(OperationNotSupported& ex) {
            qDebug() << ex.what();
            throw OperationNotSupported(); //raise exception
        }

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

        auto t_end1 = std::chrono::high_resolution_clock::now();
        double elapsed_time_ms1 = std::chrono::duration<double, std::milli>(t_end1-t_start1).count();
        std::cout << "insertCharRangeRequest ELAPSED: " << elapsed_time_ms1 << std::endl;

        //Send data (header and body)
        _client->sendRequestMsg(req);
    } else {
        qDebug() << "Cannot paste this." << endl;
    }
}


QChar EditorWindow::SimplifySingleCharForSorting(QChar c, bool changeToLowerCase) {

    if ( ( c >= 0xC0 && c <= 0xC5 ) || ( c >= 0xE1 && c <= 0xE5 ) || c == 0xAA )
        return ( ( c >= 0xC0 && c <= 0xC5 ) && !changeToLowerCase ) ? 'A' : 'a';
    if ( ( c >= 0xC8 && c <= 0xCB ) || ( c >= 0xE8 && c <= 0xEB ) )
        return ( c > 0xCB || changeToLowerCase ) ? 'e' : 'E';
    if ( ( c >= 0xCC && c <= 0xCF ) || ( c >= 0xEC && c <= 0xEF ) )
        return ( c > 0xCF || changeToLowerCase ) ? 'i' : 'I';
    if ( ( c >= 0xD2 && c <= 0xD6 ) || ( c >= 0xF2 && c <= 0xF6 ) || c == 0xBA )
        return ( ( c >= 0xD2 && c <= 0xD6 ) && !changeToLowerCase ) ? 'O' : 'o';
    if ( ( c >= 0xD9 && c <= 0xDC ) || ( c >= 0xF9 && c <= 0xFC ) )
        return ( c > 0xDC || changeToLowerCase ) ? 'u' : 'U';
    if ( c == 0xA9 || c == 0xC7 || c == 0xE7 )
        return ( c == 0xC7 && !changeToLowerCase ) ? 'C' : 'c';
    if ( c == 0xD1 || c == 0xF1 )
        return ( c == 0xD1 && !changeToLowerCase ) ? 'N' : 'n';
    if ( c == 0xAE )
        return 'r';
    if ( c == 0xDF )
        return 's';
    if ( c == 0x8E || c == 0x9E )
        return ( c == 0x8E && !changeToLowerCase ) ? 'Z' : 'z';
    if ( c == 0x9F || c == 0xDD || c == 0xFD || c == 0xFF )
        return ( ( c == 0x9F || c == 0xDD ) && !changeToLowerCase ) ? 'Y' : 'y';
    return c;
}

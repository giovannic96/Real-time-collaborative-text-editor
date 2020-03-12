#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H

#include <QMainWindow>
#include <QTextCursor>
#include <QComboBox>
#include "jsonUtility.h"
#include "message.h"
#include "myClient.h"

#define ALPHA_TRANSPARENT "0.003922"
#define ALPHA_COLOR "0.529412"

class QEvent;
namespace Ui {class EditorWindow;}

struct OperationNotSupported : public std::exception {
    const char * what () const noexcept override {
        return "Operation not supported";
    }
};

class EditorWindow : public QMainWindow {
    Q_OBJECT

public:
    EditorWindow(myClient* client, QWidget *parent = nullptr);
    ~EditorWindow();

private slots:
    /************************************
     *            INTERFACE             *
     ************************************/
    void on_DocNameButton_clicked();

    //Change style of the text
    void on_buttonBold_clicked();
    void on_buttonItalic_clicked();
    void on_buttonUnderline_clicked();
    void on_buttonColor_clicked();

    //Align the text
    void on_buttonAlignDX_clicked();
    void on_buttonAlignCX_clicked();
    void on_buttonAlignSX_clicked();
    void on_buttonAlignJFX_clicked();

    //Modify the text
    void on_buttonCut_clicked();
    void on_buttonPaste_clicked();
    void on_buttonCopy_clicked();

    //Highlight the text
    void on_buttonSearch_clicked();

    //Modify font and size of text
    void on_fontSizeBox_currentIndexChanged(int index);
    void on_fontFamilyBox_currentIndexChanged(int index);
    void on_fontSizeBox_activated(int index);

    //RealTextEdit Event
    void on_RealTextEdit_cursorPositionChanged();
    void on_RealTextEdit_selectionChanged();

    /************************************
     *               EVENT              *
     ************************************/
    bool eventFilter(QObject *obj, QEvent *ev);
    void keyPressEvent(QKeyEvent *e);   //Handle Shortcut of Action
    void closeEvent(QCloseEvent * event);

    /************************************
     *              ACTION              *
     ************************************/
    void on_actionFullscreen_triggered();
    void on_actionNew_triggered();
    void on_actionAbout_triggered();
    void on_actionClose_triggered();
    void on_actionEsci_triggered();
    void on_actionRinomina_triggered();
    void on_actionEsporta_come_PDF_triggered();
    void on_actionInvita_tramite_URI_triggered();
    void on_actionDark_Mode_triggered();
    void on_actionCollaboratori_triggered();
    void on_actionGrassetto_triggered();
    void on_actionCorsivo_triggered();
    void on_actionSottolineato_triggered();
    void on_actionSeleziona_Tutto_triggered();

    /************************************
     *        STANDALONE FUNCTION       *
     ************************************/
    void CloseDocumentRequest();
    void PaintItBlack();
    void AlignSXButtonHandler();
    void AlignCXButtonHandler();
    void AlignDXButtonHandler();
    void AlignJFXButtonHandler();
    void AlignNoneButtonHandler();
    void AlignButtonStyleHandler();
    void refreshFormatButtons();
    void hideCollab();
    void showCollab();
    bool handleConnectionLoss();
    void setupInitialCondition();
    void on_RealTextEdit_textChanged();
    void on_RealTextEdit_customContextMenuRequested(const QPoint &pos);

    /************************************
     *        OTHER SLOTS FUNCTION      *
     ************************************/



    void on_profileButton_clicked();

public slots:
    void showPopupSuccess(QString result, std::string filename = "");
    void showPopupFailure(QString result);
    void showSymbol(std::pair<int, wchar_t> tuple, symbolStyle style);
    void eraseSymbol(int index);
    void eraseSymbols(int startIndex, int endIndex);
    void formatSymbols(int startIndex, int endIndex, int format);
    void hideAndChangeCustomFontSize();
    void resetFontSize();
    void changeFontSize(int startIndex, int endIndex, int fontSize);
    void changeFontFamily(int startIndex, int endIndex, std::string fontFamily);
    void changeAlignment(int startBlock, int endBlock, int alignment);
    void showSymbolsAt(int startIndex, std::vector<symbol> symbols);
    void updateAlignmentButton();

private:
    Ui::EditorWindow *ui;
    void sendRequestMsg(std::string req);
    myClient *_client;
    QString docName = _client->getFilename().toLatin1(); //toLatin1 accept accented chars
    QString textOnTitleBar;
    bool BruteClose=true;
    bool SchermoIntero=false;
    bool DarkMode=false;
    symbolStyle getCurCharStyle();
    symbolStyle getStyleFromHTMLStyles(QVector<std::pair<int,symbolStyle>>& styles);
    QVector<QRegularExpression> getStyleRegexes();
    symbolStyle constructSymStyle(QVector<QRegularExpression> rxs, QString str, int alignment);
    symbolStyle getFirstCharStyle(QTextCursor cursor);
    QVector<std::pair<int,symbolStyle>> getStylesFromHTML(QString htmlText, QTextCursor& cursor, QVector<int>& alignments);
    QVector<std::pair<int,int>> getAlignmentsFromHTML(QString htmlText, QTextCursor cursor);
    std::vector<bool> calculateButtonChecks(QTextCursor& c);
    int calculateFontSizeComboBox(QTextCursor c);
    int calculateAlignmentButtons(QTextCursor c);
    QString calculateFontFamilyComboBox(QTextCursor c);
    void hideLastAddedItem(QComboBox* combobox);
    QString updateBackgroundColor(QString html, QString finalAlpha);
    int getIndexFromFontSize(int fontSize);
    /* Requests */
    void insertCharRangeRequest(int pos, bool cursorHasSelection);
    void removeCharRequest(int pos);
    void removeCharRangeRequest(const QTextCursor& cursor);
    void sendFormatRequest(int format);
    void sendFontChangeRequest(int fontSize);
    void sendFontChangeRequest(std::string fontFamily);
    void sendAlignChangeRequest(int blockStart, int blockEnd, int alignment);
    /* Alignment */
    void alignSingleBlock(QTextCursor& cursor, Qt::AlignmentFlag alignment);
    void alignMultipleBlocks(int startIndex, int endIndex, QTextCursor& cursor, Qt::AlignmentFlag alignment);
    std::pair<int,int> alignBlocks(int startIndex, int endIndex, const QTextCursor& cursor, Qt::AlignmentFlag alignment);
    Qt::AlignmentFlag detectAlignment();
    int getFirstCharAlignment(QTextCursor cursor);
    QStringList getRegexListFromHTML(QString text, QRegularExpression rx);
    int getParagAlignment(QString text);
    int getTotalCharsInSpan(QString text);
    void setAlignmentButton(Qt::AlignmentFlag alignment);
    void changeNextCharsAlignment(QTextCursor cursor, int startIndex, int endIndex);
    /* Variables */
    bool changedFontSize = false, changedCurIndex = false, setCurPointSize = false;
    enum formatType {MAKE_BOLD=0, MAKE_ITALIC=1, MAKE_UNDERLINE=2, UNMAKE_BOLD=3, UNMAKE_ITALIC=4, UNMAKE_UNDERLINE=5, FORMAT_UNKNOWN=6, CHANGE_FONT_SIZE=7};

};

#endif // EDITORWINDOW_H

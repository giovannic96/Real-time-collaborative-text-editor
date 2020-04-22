#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H

#include <QMainWindow>
#include <QTextCursor>
#include <QComboBox>
#include <QMetaType>
#include "jsonUtility.h"
#include "message.h"
#include "myClient.h"
#include "editorstate.h"
#include "settings.h"
#include "qlistwidget.h"
#include "userprofile.h"
#include"infowindow.h"
#include "settings.h"

#define ALPHA_TRANSPARENT "0.003922"
#define ALPHA_COLOR "0.529412"

class QEvent;
namespace Ui {class EditorWindow;}

struct OperationNotSupported : public std::exception {
    const char * what () const noexcept override {
        return "Operation not supported";
    }
};
typedef std::map<std::string, std::pair<std::string,bool>> myCollabColorsMap;

class EditorWindow : public QMainWindow {
    Q_OBJECT

public:
    EditorWindow(myClient* client, QWidget *parent = nullptr);
    ~EditorWindow();

private slots:
    /************************************
     *            INTERFACE             *
     ************************************/

    //TopMenuBar
    void on_fileButton_clicked();
    void on_visualizzaButton_clicked();
    void on_modificaButton_clicked();
    void on_strumentiButton_clicked();
    void on_aboutButton_clicked();

    //CollaboratorBar

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

    //Modify font and size of text
    void on_fontSizeBox_currentIndexChanged(int index);
    void on_fontFamilyBox_currentIndexChanged(int index);
    void on_fontSizeBox_activated(int index);

    //RealTextEdit Event
    void on_RealTextEdit_cursorPositionChanged();
    void on_RealTextEdit_selectionChanged();
    void on_RealTextEdit_textChanged();
    void on_RealTextEdit_customContextMenuRequested(const QPoint &pos);

    /************************************
     *               EVENT              *
     ************************************/
    bool eventFilter(QObject *obj, QEvent *ev);
    void closeEvent(QCloseEvent * event);

    /************************************
     *              ACTION              *
     ************************************/
    void on_actionFullscreen_triggered();
    void on_actionAbout_triggered();
    void on_actionClose_triggered();
    void on_actionRinomina_triggered();
    void on_actionEsporta_come_PDF_triggered();
    void on_actionInvita_tramite_URI_triggered();
    void on_actionDark_Mode_triggered();
    void on_actionCollaboratori_triggered();
    void on_actionGrassetto_triggered();
    void on_actionCorsivo_triggered();
    void on_actionSottolineato_triggered();
    void on_actionSeleziona_Tutto_triggered();
    void on_actionToolbar_triggered();
    void on_actionOpzioni_triggered();

    /************************************
     * STANDALONE FUNCTION FOR GRAPHIC  *
     ************************************/
    void PaintItBlack();
    void ApplyDayMode();
    void ApplyDarkMode();
    void SetIconPackDayMode();
    void SetIconPackDarkMode();
    void LoadUserSetting();
    void TitlebarChangeByTimer();
    /**********THEME SELECTOR***********/
    void installTheme_Day_ClassicBlue();
    void installTheme_Day_PlainBlue();
    void installTheme_Day_ElectricBlue();
    void installTheme_Day_ClassicPurple();
    void installTheme_Day_ClassicOrange();
    void installTheme_Day_ClassicGreen();
    void installTheme_Day_ClassicRed();
    void installTheme_Day_Rainbow();
    void installTheme_Day_FountainRainbow();
    void installTheme_Day_Polito();
    void installTheme_Day_Special();
    void installTheme_Dark_ClassicOrange();
    void installTheme_Dark_PlainOrange();
    void installTheme_Dark_ElectricOrange();
    void installTheme_Dark_ClassicPurple();
    void installTheme_Dark_ClassicBlue();
    void installTheme_Dark_ClassicGreen();
    void installTheme_Dark_ClassicRed();
    void installTheme_Dark_Rainbow();
    void installTheme_Dark_FountainRainbow();
    void installTheme_Dark_Polito();
    void installTheme_Dark_Special();


    /************************************
     *        STANDALONE FUNCTION       *
     ************************************/
    void CloseDocumentRequest();
    void AlignSXButtonHandler();
    void AlignCXButtonHandler();
    void AlignDXButtonHandler();
    void AlignJFXButtonHandler();
    void AlignNoneButtonHandler();
    void AlignButtonStyleHandler();
    void refreshFormatButtons();
    void hideCollab();
    void showCollab();
    void showToolbar();
    void hideToolbar();
    bool handleConnectionLoss();
    void setupInitialCondition();
    void SetDynamicDocNameLabel();

    /************************************
     *  ONE INSTANCE HANDLER FUNCTION   *
     ************************************/
    void on_profileButton_clicked();
    void setUserProfileClosed();
    void setSettingsClosed();
    void openSettingsWindows();
    void setInfoWindowClosed();
    void openInfoWindows();
    void goodbyeClient();

signals:
    void closeEditor();

    /************************************
     *        OTHER SLOTS FUNCTION      *
     ************************************/
public slots:
    void showPopupSuccess(QString result, std::string filename = "");
    void showPopupFailure(QString result);
    void showSymbol(std::pair<int, wchar_t> tuple, symbolStyle style);
    void eraseSymbols(int startIndex, int endIndex);
    void formatSymbols(int startIndex, int endIndex, int format);
    void hideAndChangeCustomFontSize();
    void resetFontSize();
    void changeFontSize(int startIndex, int endIndex, int fontSize);
    void changeFontFamily(int startIndex, int endIndex, std::string fontFamily);
    void changeAlignment(int startBlock, int endBlock, int alignment);
    void showSymbolsAt(int startIndex, std::vector<symbol> symbols);
    void getUserOffline(myCollabColorsMap collabColorsMap);
    void getUserOnline(myCollabColorsMap collabColorsMap);
    void updateAlignmentButton();
    void showCollabColorsMap(myCollabColorsMap collabColorsMap);

private:
    EditorState estate;
    Ui::EditorWindow *ui;
    myClient *_client;
    QString docName = _client->getFilename().toLatin1(); //toLatin1 accept accented chars
    QString textOnTitleBar;
    QTimer *titlebarTimer;
    bool BruteClose=true;
    std::vector<int> sizeVector = {8, 9, 10, 11, 12, 14, 18, 24, 30, 36, 48, 60, 72, 96};
    void setupListWidgets();
    void setupTextEdit();
    void setupColor();
    void setupValidator();
    void setupFirstLetter();
    void setupFontIcon();
    void setupTitlebarTimer();
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
    void cursorChangeRequest(int pos);
    void collabColorsRequest(QString uri);
    void removeCharRequest(const std::vector<std::pair<int,int>>& symbolsId);
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
    QChar SimplifySingleCharForSorting( QChar c, bool changeToLowerCase);

    //Boolean for check if only one instance of following window is created
    bool profile_closed = true;
    bool settings_closed = true;
    bool infowindow_closed = true;
    UserProfile *up;
    infoWindow *iw;
    Settings * s;


};

#endif // EDITORWINDOW_H

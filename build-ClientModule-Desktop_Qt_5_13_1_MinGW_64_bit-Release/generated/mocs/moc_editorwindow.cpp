/****************************************************************************
** Meta object code from reading C++ file 'editorwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../ClientModule/editorwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'editorwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_EditorWindow_t {
    QByteArrayData data[134];
    char stringdata0[2781];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_EditorWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_EditorWindow_t qt_meta_stringdata_EditorWindow = {
    {
QT_MOC_LITERAL(0, 0, 12), // "EditorWindow"
QT_MOC_LITERAL(1, 13, 11), // "closeEditor"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 21), // "on_fileButton_clicked"
QT_MOC_LITERAL(4, 48, 27), // "on_visualizzaButton_clicked"
QT_MOC_LITERAL(5, 76, 25), // "on_modificaButton_clicked"
QT_MOC_LITERAL(6, 102, 26), // "on_strumentiButton_clicked"
QT_MOC_LITERAL(7, 129, 22), // "on_aboutButton_clicked"
QT_MOC_LITERAL(8, 152, 21), // "on_buttonBold_clicked"
QT_MOC_LITERAL(9, 174, 23), // "on_buttonItalic_clicked"
QT_MOC_LITERAL(10, 198, 26), // "on_buttonUnderline_clicked"
QT_MOC_LITERAL(11, 225, 22), // "on_buttonColor_clicked"
QT_MOC_LITERAL(12, 248, 24), // "on_buttonAlignDX_clicked"
QT_MOC_LITERAL(13, 273, 24), // "on_buttonAlignCX_clicked"
QT_MOC_LITERAL(14, 298, 24), // "on_buttonAlignSX_clicked"
QT_MOC_LITERAL(15, 323, 25), // "on_buttonAlignJFX_clicked"
QT_MOC_LITERAL(16, 349, 20), // "on_buttonCut_clicked"
QT_MOC_LITERAL(17, 370, 22), // "on_buttonPaste_clicked"
QT_MOC_LITERAL(18, 393, 21), // "on_buttonCopy_clicked"
QT_MOC_LITERAL(19, 415, 34), // "on_fontSizeBox_currentIndexCh..."
QT_MOC_LITERAL(20, 450, 5), // "index"
QT_MOC_LITERAL(21, 456, 36), // "on_fontFamilyBox_currentIndex..."
QT_MOC_LITERAL(22, 493, 24), // "on_fontSizeBox_activated"
QT_MOC_LITERAL(23, 518, 37), // "on_RealTextEdit_cursorPositio..."
QT_MOC_LITERAL(24, 556, 32), // "on_RealTextEdit_selectionChanged"
QT_MOC_LITERAL(25, 589, 27), // "on_RealTextEdit_textChanged"
QT_MOC_LITERAL(26, 617, 42), // "on_RealTextEdit_customContext..."
QT_MOC_LITERAL(27, 660, 3), // "pos"
QT_MOC_LITERAL(28, 664, 11), // "eventFilter"
QT_MOC_LITERAL(29, 676, 3), // "obj"
QT_MOC_LITERAL(30, 680, 7), // "QEvent*"
QT_MOC_LITERAL(31, 688, 2), // "ev"
QT_MOC_LITERAL(32, 691, 10), // "closeEvent"
QT_MOC_LITERAL(33, 702, 12), // "QCloseEvent*"
QT_MOC_LITERAL(34, 715, 5), // "event"
QT_MOC_LITERAL(35, 721, 29), // "on_actionFullscreen_triggered"
QT_MOC_LITERAL(36, 751, 24), // "on_actionAbout_triggered"
QT_MOC_LITERAL(37, 776, 24), // "on_actionClose_triggered"
QT_MOC_LITERAL(38, 801, 27), // "on_actionRinomina_triggered"
QT_MOC_LITERAL(39, 829, 35), // "on_actionEsporta_come_PDF_tri..."
QT_MOC_LITERAL(40, 865, 37), // "on_actionInvita_tramite_URI_t..."
QT_MOC_LITERAL(41, 903, 28), // "on_actionDark_Mode_triggered"
QT_MOC_LITERAL(42, 932, 32), // "on_actionCollaboratori_triggered"
QT_MOC_LITERAL(43, 965, 28), // "on_actionGrassetto_triggered"
QT_MOC_LITERAL(44, 994, 26), // "on_actionCorsivo_triggered"
QT_MOC_LITERAL(45, 1021, 31), // "on_actionSottolineato_triggered"
QT_MOC_LITERAL(46, 1053, 34), // "on_actionSeleziona_Tutto_trig..."
QT_MOC_LITERAL(47, 1088, 26), // "on_actionToolbar_triggered"
QT_MOC_LITERAL(48, 1115, 26), // "on_actionOpzioni_triggered"
QT_MOC_LITERAL(49, 1142, 12), // "PaintItBlack"
QT_MOC_LITERAL(50, 1155, 12), // "ApplyDayMode"
QT_MOC_LITERAL(51, 1168, 13), // "ApplyDarkMode"
QT_MOC_LITERAL(52, 1182, 18), // "SetIconPackDayMode"
QT_MOC_LITERAL(53, 1201, 19), // "SetIconPackDarkMode"
QT_MOC_LITERAL(54, 1221, 15), // "LoadUserSetting"
QT_MOC_LITERAL(55, 1237, 21), // "TitlebarChangeByTimer"
QT_MOC_LITERAL(56, 1259, 28), // "installTheme_Day_ClassicBlue"
QT_MOC_LITERAL(57, 1288, 26), // "installTheme_Day_PlainBlue"
QT_MOC_LITERAL(58, 1315, 29), // "installTheme_Day_ElectricBlue"
QT_MOC_LITERAL(59, 1345, 30), // "installTheme_Day_ClassicPurple"
QT_MOC_LITERAL(60, 1376, 30), // "installTheme_Day_ClassicOrange"
QT_MOC_LITERAL(61, 1407, 29), // "installTheme_Day_ClassicGreen"
QT_MOC_LITERAL(62, 1437, 27), // "installTheme_Day_ClassicRed"
QT_MOC_LITERAL(63, 1465, 24), // "installTheme_Day_Rainbow"
QT_MOC_LITERAL(64, 1490, 32), // "installTheme_Day_FountainRainbow"
QT_MOC_LITERAL(65, 1523, 23), // "installTheme_Day_Polito"
QT_MOC_LITERAL(66, 1547, 24), // "installTheme_Day_Special"
QT_MOC_LITERAL(67, 1572, 31), // "installTheme_Dark_ClassicOrange"
QT_MOC_LITERAL(68, 1604, 29), // "installTheme_Dark_PlainOrange"
QT_MOC_LITERAL(69, 1634, 32), // "installTheme_Dark_ElectricOrange"
QT_MOC_LITERAL(70, 1667, 31), // "installTheme_Dark_ClassicPurple"
QT_MOC_LITERAL(71, 1699, 29), // "installTheme_Dark_ClassicBlue"
QT_MOC_LITERAL(72, 1729, 30), // "installTheme_Dark_ClassicGreen"
QT_MOC_LITERAL(73, 1760, 28), // "installTheme_Dark_ClassicRed"
QT_MOC_LITERAL(74, 1789, 25), // "installTheme_Dark_Rainbow"
QT_MOC_LITERAL(75, 1815, 33), // "installTheme_Dark_FountainRai..."
QT_MOC_LITERAL(76, 1849, 24), // "installTheme_Dark_Polito"
QT_MOC_LITERAL(77, 1874, 25), // "installTheme_Dark_Special"
QT_MOC_LITERAL(78, 1900, 20), // "CloseDocumentRequest"
QT_MOC_LITERAL(79, 1921, 20), // "AlignSXButtonHandler"
QT_MOC_LITERAL(80, 1942, 20), // "AlignCXButtonHandler"
QT_MOC_LITERAL(81, 1963, 20), // "AlignDXButtonHandler"
QT_MOC_LITERAL(82, 1984, 21), // "AlignJFXButtonHandler"
QT_MOC_LITERAL(83, 2006, 22), // "AlignNoneButtonHandler"
QT_MOC_LITERAL(84, 2029, 23), // "AlignButtonStyleHandler"
QT_MOC_LITERAL(85, 2053, 20), // "refreshFormatButtons"
QT_MOC_LITERAL(86, 2074, 10), // "hideCollab"
QT_MOC_LITERAL(87, 2085, 10), // "showCollab"
QT_MOC_LITERAL(88, 2096, 11), // "showToolbar"
QT_MOC_LITERAL(89, 2108, 11), // "hideToolbar"
QT_MOC_LITERAL(90, 2120, 20), // "handleConnectionLoss"
QT_MOC_LITERAL(91, 2141, 21), // "setupInitialCondition"
QT_MOC_LITERAL(92, 2163, 22), // "SetDynamicDocNameLabel"
QT_MOC_LITERAL(93, 2186, 24), // "on_profileButton_clicked"
QT_MOC_LITERAL(94, 2211, 20), // "setUserProfileClosed"
QT_MOC_LITERAL(95, 2232, 17), // "setSettingsClosed"
QT_MOC_LITERAL(96, 2250, 19), // "openSettingsWindows"
QT_MOC_LITERAL(97, 2270, 19), // "setInfoWindowClosed"
QT_MOC_LITERAL(98, 2290, 15), // "openInfoWindows"
QT_MOC_LITERAL(99, 2306, 13), // "goodbyeClient"
QT_MOC_LITERAL(100, 2320, 16), // "showPopupSuccess"
QT_MOC_LITERAL(101, 2337, 6), // "result"
QT_MOC_LITERAL(102, 2344, 11), // "std::string"
QT_MOC_LITERAL(103, 2356, 8), // "filename"
QT_MOC_LITERAL(104, 2365, 16), // "showPopupFailure"
QT_MOC_LITERAL(105, 2382, 10), // "showSymbol"
QT_MOC_LITERAL(106, 2393, 22), // "std::pair<int,wchar_t>"
QT_MOC_LITERAL(107, 2416, 5), // "tuple"
QT_MOC_LITERAL(108, 2422, 11), // "symbolStyle"
QT_MOC_LITERAL(109, 2434, 5), // "style"
QT_MOC_LITERAL(110, 2440, 12), // "eraseSymbols"
QT_MOC_LITERAL(111, 2453, 10), // "startIndex"
QT_MOC_LITERAL(112, 2464, 8), // "endIndex"
QT_MOC_LITERAL(113, 2473, 13), // "formatSymbols"
QT_MOC_LITERAL(114, 2487, 6), // "format"
QT_MOC_LITERAL(115, 2494, 27), // "hideAndChangeCustomFontSize"
QT_MOC_LITERAL(116, 2522, 13), // "resetFontSize"
QT_MOC_LITERAL(117, 2536, 14), // "changeFontSize"
QT_MOC_LITERAL(118, 2551, 8), // "fontSize"
QT_MOC_LITERAL(119, 2560, 16), // "changeFontFamily"
QT_MOC_LITERAL(120, 2577, 10), // "fontFamily"
QT_MOC_LITERAL(121, 2588, 15), // "changeAlignment"
QT_MOC_LITERAL(122, 2604, 10), // "startBlock"
QT_MOC_LITERAL(123, 2615, 8), // "endBlock"
QT_MOC_LITERAL(124, 2624, 9), // "alignment"
QT_MOC_LITERAL(125, 2634, 13), // "showSymbolsAt"
QT_MOC_LITERAL(126, 2648, 19), // "std::vector<symbol>"
QT_MOC_LITERAL(127, 2668, 7), // "symbols"
QT_MOC_LITERAL(128, 2676, 14), // "getUserOffline"
QT_MOC_LITERAL(129, 2691, 17), // "myCollabColorsMap"
QT_MOC_LITERAL(130, 2709, 15), // "collabColorsMap"
QT_MOC_LITERAL(131, 2725, 13), // "getUserOnline"
QT_MOC_LITERAL(132, 2739, 21), // "updateAlignmentButton"
QT_MOC_LITERAL(133, 2761, 19) // "showCollabColorsMap"

    },
    "EditorWindow\0closeEditor\0\0"
    "on_fileButton_clicked\0on_visualizzaButton_clicked\0"
    "on_modificaButton_clicked\0"
    "on_strumentiButton_clicked\0"
    "on_aboutButton_clicked\0on_buttonBold_clicked\0"
    "on_buttonItalic_clicked\0"
    "on_buttonUnderline_clicked\0"
    "on_buttonColor_clicked\0on_buttonAlignDX_clicked\0"
    "on_buttonAlignCX_clicked\0"
    "on_buttonAlignSX_clicked\0"
    "on_buttonAlignJFX_clicked\0"
    "on_buttonCut_clicked\0on_buttonPaste_clicked\0"
    "on_buttonCopy_clicked\0"
    "on_fontSizeBox_currentIndexChanged\0"
    "index\0on_fontFamilyBox_currentIndexChanged\0"
    "on_fontSizeBox_activated\0"
    "on_RealTextEdit_cursorPositionChanged\0"
    "on_RealTextEdit_selectionChanged\0"
    "on_RealTextEdit_textChanged\0"
    "on_RealTextEdit_customContextMenuRequested\0"
    "pos\0eventFilter\0obj\0QEvent*\0ev\0"
    "closeEvent\0QCloseEvent*\0event\0"
    "on_actionFullscreen_triggered\0"
    "on_actionAbout_triggered\0"
    "on_actionClose_triggered\0"
    "on_actionRinomina_triggered\0"
    "on_actionEsporta_come_PDF_triggered\0"
    "on_actionInvita_tramite_URI_triggered\0"
    "on_actionDark_Mode_triggered\0"
    "on_actionCollaboratori_triggered\0"
    "on_actionGrassetto_triggered\0"
    "on_actionCorsivo_triggered\0"
    "on_actionSottolineato_triggered\0"
    "on_actionSeleziona_Tutto_triggered\0"
    "on_actionToolbar_triggered\0"
    "on_actionOpzioni_triggered\0PaintItBlack\0"
    "ApplyDayMode\0ApplyDarkMode\0"
    "SetIconPackDayMode\0SetIconPackDarkMode\0"
    "LoadUserSetting\0TitlebarChangeByTimer\0"
    "installTheme_Day_ClassicBlue\0"
    "installTheme_Day_PlainBlue\0"
    "installTheme_Day_ElectricBlue\0"
    "installTheme_Day_ClassicPurple\0"
    "installTheme_Day_ClassicOrange\0"
    "installTheme_Day_ClassicGreen\0"
    "installTheme_Day_ClassicRed\0"
    "installTheme_Day_Rainbow\0"
    "installTheme_Day_FountainRainbow\0"
    "installTheme_Day_Polito\0"
    "installTheme_Day_Special\0"
    "installTheme_Dark_ClassicOrange\0"
    "installTheme_Dark_PlainOrange\0"
    "installTheme_Dark_ElectricOrange\0"
    "installTheme_Dark_ClassicPurple\0"
    "installTheme_Dark_ClassicBlue\0"
    "installTheme_Dark_ClassicGreen\0"
    "installTheme_Dark_ClassicRed\0"
    "installTheme_Dark_Rainbow\0"
    "installTheme_Dark_FountainRainbow\0"
    "installTheme_Dark_Polito\0"
    "installTheme_Dark_Special\0"
    "CloseDocumentRequest\0AlignSXButtonHandler\0"
    "AlignCXButtonHandler\0AlignDXButtonHandler\0"
    "AlignJFXButtonHandler\0AlignNoneButtonHandler\0"
    "AlignButtonStyleHandler\0refreshFormatButtons\0"
    "hideCollab\0showCollab\0showToolbar\0"
    "hideToolbar\0handleConnectionLoss\0"
    "setupInitialCondition\0SetDynamicDocNameLabel\0"
    "on_profileButton_clicked\0setUserProfileClosed\0"
    "setSettingsClosed\0openSettingsWindows\0"
    "setInfoWindowClosed\0openInfoWindows\0"
    "goodbyeClient\0showPopupSuccess\0result\0"
    "std::string\0filename\0showPopupFailure\0"
    "showSymbol\0std::pair<int,wchar_t>\0"
    "tuple\0symbolStyle\0style\0eraseSymbols\0"
    "startIndex\0endIndex\0formatSymbols\0"
    "format\0hideAndChangeCustomFontSize\0"
    "resetFontSize\0changeFontSize\0fontSize\0"
    "changeFontFamily\0fontFamily\0changeAlignment\0"
    "startBlock\0endBlock\0alignment\0"
    "showSymbolsAt\0std::vector<symbol>\0"
    "symbols\0getUserOffline\0myCollabColorsMap\0"
    "collabColorsMap\0getUserOnline\0"
    "updateAlignmentButton\0showCollabColorsMap"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EditorWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
     107,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  549,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,  550,    2, 0x08 /* Private */,
       4,    0,  551,    2, 0x08 /* Private */,
       5,    0,  552,    2, 0x08 /* Private */,
       6,    0,  553,    2, 0x08 /* Private */,
       7,    0,  554,    2, 0x08 /* Private */,
       8,    0,  555,    2, 0x08 /* Private */,
       9,    0,  556,    2, 0x08 /* Private */,
      10,    0,  557,    2, 0x08 /* Private */,
      11,    0,  558,    2, 0x08 /* Private */,
      12,    0,  559,    2, 0x08 /* Private */,
      13,    0,  560,    2, 0x08 /* Private */,
      14,    0,  561,    2, 0x08 /* Private */,
      15,    0,  562,    2, 0x08 /* Private */,
      16,    0,  563,    2, 0x08 /* Private */,
      17,    0,  564,    2, 0x08 /* Private */,
      18,    0,  565,    2, 0x08 /* Private */,
      19,    1,  566,    2, 0x08 /* Private */,
      21,    1,  569,    2, 0x08 /* Private */,
      22,    1,  572,    2, 0x08 /* Private */,
      23,    0,  575,    2, 0x08 /* Private */,
      24,    0,  576,    2, 0x08 /* Private */,
      25,    0,  577,    2, 0x08 /* Private */,
      26,    1,  578,    2, 0x08 /* Private */,
      28,    2,  581,    2, 0x08 /* Private */,
      32,    1,  586,    2, 0x08 /* Private */,
      35,    0,  589,    2, 0x08 /* Private */,
      36,    0,  590,    2, 0x08 /* Private */,
      37,    0,  591,    2, 0x08 /* Private */,
      38,    0,  592,    2, 0x08 /* Private */,
      39,    0,  593,    2, 0x08 /* Private */,
      40,    0,  594,    2, 0x08 /* Private */,
      41,    0,  595,    2, 0x08 /* Private */,
      42,    0,  596,    2, 0x08 /* Private */,
      43,    0,  597,    2, 0x08 /* Private */,
      44,    0,  598,    2, 0x08 /* Private */,
      45,    0,  599,    2, 0x08 /* Private */,
      46,    0,  600,    2, 0x08 /* Private */,
      47,    0,  601,    2, 0x08 /* Private */,
      48,    0,  602,    2, 0x08 /* Private */,
      49,    0,  603,    2, 0x08 /* Private */,
      50,    0,  604,    2, 0x08 /* Private */,
      51,    0,  605,    2, 0x08 /* Private */,
      52,    0,  606,    2, 0x08 /* Private */,
      53,    0,  607,    2, 0x08 /* Private */,
      54,    0,  608,    2, 0x08 /* Private */,
      55,    0,  609,    2, 0x08 /* Private */,
      56,    0,  610,    2, 0x08 /* Private */,
      57,    0,  611,    2, 0x08 /* Private */,
      58,    0,  612,    2, 0x08 /* Private */,
      59,    0,  613,    2, 0x08 /* Private */,
      60,    0,  614,    2, 0x08 /* Private */,
      61,    0,  615,    2, 0x08 /* Private */,
      62,    0,  616,    2, 0x08 /* Private */,
      63,    0,  617,    2, 0x08 /* Private */,
      64,    0,  618,    2, 0x08 /* Private */,
      65,    0,  619,    2, 0x08 /* Private */,
      66,    0,  620,    2, 0x08 /* Private */,
      67,    0,  621,    2, 0x08 /* Private */,
      68,    0,  622,    2, 0x08 /* Private */,
      69,    0,  623,    2, 0x08 /* Private */,
      70,    0,  624,    2, 0x08 /* Private */,
      71,    0,  625,    2, 0x08 /* Private */,
      72,    0,  626,    2, 0x08 /* Private */,
      73,    0,  627,    2, 0x08 /* Private */,
      74,    0,  628,    2, 0x08 /* Private */,
      75,    0,  629,    2, 0x08 /* Private */,
      76,    0,  630,    2, 0x08 /* Private */,
      77,    0,  631,    2, 0x08 /* Private */,
      78,    0,  632,    2, 0x08 /* Private */,
      79,    0,  633,    2, 0x08 /* Private */,
      80,    0,  634,    2, 0x08 /* Private */,
      81,    0,  635,    2, 0x08 /* Private */,
      82,    0,  636,    2, 0x08 /* Private */,
      83,    0,  637,    2, 0x08 /* Private */,
      84,    0,  638,    2, 0x08 /* Private */,
      85,    0,  639,    2, 0x08 /* Private */,
      86,    0,  640,    2, 0x08 /* Private */,
      87,    0,  641,    2, 0x08 /* Private */,
      88,    0,  642,    2, 0x08 /* Private */,
      89,    0,  643,    2, 0x08 /* Private */,
      90,    0,  644,    2, 0x08 /* Private */,
      91,    0,  645,    2, 0x08 /* Private */,
      92,    0,  646,    2, 0x08 /* Private */,
      93,    0,  647,    2, 0x08 /* Private */,
      94,    0,  648,    2, 0x08 /* Private */,
      95,    0,  649,    2, 0x08 /* Private */,
      96,    0,  650,    2, 0x08 /* Private */,
      97,    0,  651,    2, 0x08 /* Private */,
      98,    0,  652,    2, 0x08 /* Private */,
      99,    0,  653,    2, 0x08 /* Private */,
     100,    2,  654,    2, 0x0a /* Public */,
     100,    1,  659,    2, 0x2a /* Public | MethodCloned */,
     104,    1,  662,    2, 0x0a /* Public */,
     105,    2,  665,    2, 0x0a /* Public */,
     110,    2,  670,    2, 0x0a /* Public */,
     113,    3,  675,    2, 0x0a /* Public */,
     115,    0,  682,    2, 0x0a /* Public */,
     116,    0,  683,    2, 0x0a /* Public */,
     117,    3,  684,    2, 0x0a /* Public */,
     119,    3,  691,    2, 0x0a /* Public */,
     121,    3,  698,    2, 0x0a /* Public */,
     125,    2,  705,    2, 0x0a /* Public */,
     128,    1,  710,    2, 0x0a /* Public */,
     131,    1,  713,    2, 0x0a /* Public */,
     132,    0,  716,    2, 0x0a /* Public */,
     133,    1,  717,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   20,
    QMetaType::Void, QMetaType::Int,   20,
    QMetaType::Void, QMetaType::Int,   20,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,   27,
    QMetaType::Bool, QMetaType::QObjectStar, 0x80000000 | 30,   29,   31,
    QMetaType::Void, 0x80000000 | 33,   34,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 102,  101,  103,
    QMetaType::Void, QMetaType::QString,  101,
    QMetaType::Void, QMetaType::QString,  101,
    QMetaType::Void, 0x80000000 | 106, 0x80000000 | 108,  107,  109,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  111,  112,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,  111,  112,  114,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,  111,  112,  118,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, 0x80000000 | 102,  111,  112,  120,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,  122,  123,  124,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 126,  111,  127,
    QMetaType::Void, 0x80000000 | 129,  130,
    QMetaType::Void, 0x80000000 | 129,  130,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 129,  130,

       0        // eod
};

void EditorWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<EditorWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->closeEditor(); break;
        case 1: _t->on_fileButton_clicked(); break;
        case 2: _t->on_visualizzaButton_clicked(); break;
        case 3: _t->on_modificaButton_clicked(); break;
        case 4: _t->on_strumentiButton_clicked(); break;
        case 5: _t->on_aboutButton_clicked(); break;
        case 6: _t->on_buttonBold_clicked(); break;
        case 7: _t->on_buttonItalic_clicked(); break;
        case 8: _t->on_buttonUnderline_clicked(); break;
        case 9: _t->on_buttonColor_clicked(); break;
        case 10: _t->on_buttonAlignDX_clicked(); break;
        case 11: _t->on_buttonAlignCX_clicked(); break;
        case 12: _t->on_buttonAlignSX_clicked(); break;
        case 13: _t->on_buttonAlignJFX_clicked(); break;
        case 14: _t->on_buttonCut_clicked(); break;
        case 15: _t->on_buttonPaste_clicked(); break;
        case 16: _t->on_buttonCopy_clicked(); break;
        case 17: _t->on_fontSizeBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: _t->on_fontFamilyBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 19: _t->on_fontSizeBox_activated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 20: _t->on_RealTextEdit_cursorPositionChanged(); break;
        case 21: _t->on_RealTextEdit_selectionChanged(); break;
        case 22: _t->on_RealTextEdit_textChanged(); break;
        case 23: _t->on_RealTextEdit_customContextMenuRequested((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 24: { bool _r = _t->eventFilter((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QEvent*(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 25: _t->closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        case 26: _t->on_actionFullscreen_triggered(); break;
        case 27: _t->on_actionAbout_triggered(); break;
        case 28: _t->on_actionClose_triggered(); break;
        case 29: _t->on_actionRinomina_triggered(); break;
        case 30: _t->on_actionEsporta_come_PDF_triggered(); break;
        case 31: _t->on_actionInvita_tramite_URI_triggered(); break;
        case 32: _t->on_actionDark_Mode_triggered(); break;
        case 33: _t->on_actionCollaboratori_triggered(); break;
        case 34: _t->on_actionGrassetto_triggered(); break;
        case 35: _t->on_actionCorsivo_triggered(); break;
        case 36: _t->on_actionSottolineato_triggered(); break;
        case 37: _t->on_actionSeleziona_Tutto_triggered(); break;
        case 38: _t->on_actionToolbar_triggered(); break;
        case 39: _t->on_actionOpzioni_triggered(); break;
        case 40: _t->PaintItBlack(); break;
        case 41: _t->ApplyDayMode(); break;
        case 42: _t->ApplyDarkMode(); break;
        case 43: _t->SetIconPackDayMode(); break;
        case 44: _t->SetIconPackDarkMode(); break;
        case 45: _t->LoadUserSetting(); break;
        case 46: _t->TitlebarChangeByTimer(); break;
        case 47: _t->installTheme_Day_ClassicBlue(); break;
        case 48: _t->installTheme_Day_PlainBlue(); break;
        case 49: _t->installTheme_Day_ElectricBlue(); break;
        case 50: _t->installTheme_Day_ClassicPurple(); break;
        case 51: _t->installTheme_Day_ClassicOrange(); break;
        case 52: _t->installTheme_Day_ClassicGreen(); break;
        case 53: _t->installTheme_Day_ClassicRed(); break;
        case 54: _t->installTheme_Day_Rainbow(); break;
        case 55: _t->installTheme_Day_FountainRainbow(); break;
        case 56: _t->installTheme_Day_Polito(); break;
        case 57: _t->installTheme_Day_Special(); break;
        case 58: _t->installTheme_Dark_ClassicOrange(); break;
        case 59: _t->installTheme_Dark_PlainOrange(); break;
        case 60: _t->installTheme_Dark_ElectricOrange(); break;
        case 61: _t->installTheme_Dark_ClassicPurple(); break;
        case 62: _t->installTheme_Dark_ClassicBlue(); break;
        case 63: _t->installTheme_Dark_ClassicGreen(); break;
        case 64: _t->installTheme_Dark_ClassicRed(); break;
        case 65: _t->installTheme_Dark_Rainbow(); break;
        case 66: _t->installTheme_Dark_FountainRainbow(); break;
        case 67: _t->installTheme_Dark_Polito(); break;
        case 68: _t->installTheme_Dark_Special(); break;
        case 69: _t->CloseDocumentRequest(); break;
        case 70: _t->AlignSXButtonHandler(); break;
        case 71: _t->AlignCXButtonHandler(); break;
        case 72: _t->AlignDXButtonHandler(); break;
        case 73: _t->AlignJFXButtonHandler(); break;
        case 74: _t->AlignNoneButtonHandler(); break;
        case 75: _t->AlignButtonStyleHandler(); break;
        case 76: _t->refreshFormatButtons(); break;
        case 77: _t->hideCollab(); break;
        case 78: _t->showCollab(); break;
        case 79: _t->showToolbar(); break;
        case 80: _t->hideToolbar(); break;
        case 81: { bool _r = _t->handleConnectionLoss();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 82: _t->setupInitialCondition(); break;
        case 83: _t->SetDynamicDocNameLabel(); break;
        case 84: _t->on_profileButton_clicked(); break;
        case 85: _t->setUserProfileClosed(); break;
        case 86: _t->setSettingsClosed(); break;
        case 87: _t->openSettingsWindows(); break;
        case 88: _t->setInfoWindowClosed(); break;
        case 89: _t->openInfoWindows(); break;
        case 90: _t->goodbyeClient(); break;
        case 91: _t->showPopupSuccess((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< std::string(*)>(_a[2]))); break;
        case 92: _t->showPopupSuccess((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 93: _t->showPopupFailure((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 94: _t->showSymbol((*reinterpret_cast< std::pair<int,wchar_t>(*)>(_a[1])),(*reinterpret_cast< symbolStyle(*)>(_a[2]))); break;
        case 95: _t->eraseSymbols((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 96: _t->formatSymbols((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 97: _t->hideAndChangeCustomFontSize(); break;
        case 98: _t->resetFontSize(); break;
        case 99: _t->changeFontSize((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 100: _t->changeFontFamily((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< std::string(*)>(_a[3]))); break;
        case 101: _t->changeAlignment((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 102: _t->showSymbolsAt((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< std::vector<symbol>(*)>(_a[2]))); break;
        case 103: _t->getUserOffline((*reinterpret_cast< myCollabColorsMap(*)>(_a[1]))); break;
        case 104: _t->getUserOnline((*reinterpret_cast< myCollabColorsMap(*)>(_a[1]))); break;
        case 105: _t->updateAlignmentButton(); break;
        case 106: _t->showCollabColorsMap((*reinterpret_cast< myCollabColorsMap(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 103:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< myCollabColorsMap >(); break;
            }
            break;
        case 104:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< myCollabColorsMap >(); break;
            }
            break;
        case 106:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< myCollabColorsMap >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (EditorWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EditorWindow::closeEditor)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject EditorWindow::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_EditorWindow.data,
    qt_meta_data_EditorWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *EditorWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EditorWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_EditorWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int EditorWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 107)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 107;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 107)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 107;
    }
    return _id;
}

// SIGNAL 0
void EditorWindow::closeEditor()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

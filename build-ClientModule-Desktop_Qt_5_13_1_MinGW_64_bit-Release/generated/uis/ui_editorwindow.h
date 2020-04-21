/********************************************************************************
** Form generated from reading UI file 'editorwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITORWINDOW_H
#define UI_EDITORWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <myqtextedit.h>

QT_BEGIN_NAMESPACE

class Ui_EditorWindow
{
public:
    QAction *actionNew;
    QAction *actionSave;
    QAction *actionFullscreen;
    QAction *actionAbout;
    QAction *actionClose;
    QAction *actionInvita_tramite_URI;
    QAction *actionEsporta_come_PDF;
    QAction *actionRinomina;
    QAction *actionDark_Mode;
    QAction *actionCollaboratori;
    QAction *actionGrassetto;
    QAction *actionCorsivo;
    QAction *actionSottolineato;
    QAction *actionEsci;
    QAction *actionSeleziona_Tutto;
    QAction *actionToolbar;
    QAction *actionOpzioni;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_2;
    QFrame *editorFrame;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_5;
    QFrame *frameTopBar;
    QHBoxLayout *horizontalLayout_14;
    QPushButton *fileButton;
    QPushButton *visualizzaButton;
    QPushButton *modificaButton;
    QPushButton *strumentiButton;
    QPushButton *aboutButton;
    QSpacerItem *horizontalSpacer_3;
    QLabel *opaqueLogo;
    QHBoxLayout *horizontalLayout_10;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *buttonBold;
    QPushButton *buttonItalic;
    QPushButton *buttonUnderline;
    QFrame *line_4;
    QHBoxLayout *horizontalLayout_9;
    QComboBox *fontFamilyBox;
    QComboBox *fontSizeBox;
    QFrame *line_5;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *buttonAlignSX;
    QPushButton *buttonAlignCX;
    QPushButton *buttonAlignDX;
    QPushButton *buttonAlignJFX;
    QFrame *line_6;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *buttonCopy;
    QPushButton *buttonCut;
    QPushButton *buttonPaste;
    QFrame *line_7;
    QHBoxLayout *horizontalLayout_13;
    QPushButton *buttonColor;
    QSpacerItem *horizontalSpacer_2;
    MyQTextEdit *RealTextEdit;
    QFrame *line;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *profileButton;
    QLabel *labelUser;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *verticalSpacer_5;
    QFrame *line_2;
    QSpacerItem *verticalSpacer;
    QLabel *DocNameLabel;
    QSpacerItem *verticalSpacer_7;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QSpacerItem *verticalSpacer_4;
    QFrame *line_3;
    QSpacerItem *verticalSpacer_8;
    QSpacerItem *verticalSpacer_6;
    QLabel *labelCollOn;
    QSpacerItem *verticalSpacer_9;
    QHBoxLayout *horizontalLayout_11;
    QListWidget *listWidgetOn;
    QScrollBar *verticalScrollBarOn;
    QSpacerItem *verticalSpacer_11;
    QLabel *labelCollOff;
    QSpacerItem *verticalSpacer_10;
    QHBoxLayout *horizontalLayout_12;
    QListWidget *listWidgetOff;
    QScrollBar *verticalScrollBarOff;

    void setupUi(QMainWindow *EditorWindow)
    {
        if (EditorWindow->objectName().isEmpty())
            EditorWindow->setObjectName(QString::fromUtf8("EditorWindow"));
        EditorWindow->resize(950, 600);
        EditorWindow->setMinimumSize(QSize(950, 500));
        actionNew = new QAction(EditorWindow);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        actionSave = new QAction(EditorWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/image/Editor/save(1).png"), QSize(), QIcon::Normal, QIcon::On);
        actionSave->setIcon(icon);
        actionFullscreen = new QAction(EditorWindow);
        actionFullscreen->setObjectName(QString::fromUtf8("actionFullscreen"));
        actionFullscreen->setCheckable(true);
        actionAbout = new QAction(EditorWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionClose = new QAction(EditorWindow);
        actionClose->setObjectName(QString::fromUtf8("actionClose"));
        actionInvita_tramite_URI = new QAction(EditorWindow);
        actionInvita_tramite_URI->setObjectName(QString::fromUtf8("actionInvita_tramite_URI"));
        actionEsporta_come_PDF = new QAction(EditorWindow);
        actionEsporta_come_PDF->setObjectName(QString::fromUtf8("actionEsporta_come_PDF"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/image/Editor/save(1).png"), QSize(), QIcon::Normal, QIcon::Off);
        actionEsporta_come_PDF->setIcon(icon1);
        actionRinomina = new QAction(EditorWindow);
        actionRinomina->setObjectName(QString::fromUtf8("actionRinomina"));
        actionDark_Mode = new QAction(EditorWindow);
        actionDark_Mode->setObjectName(QString::fromUtf8("actionDark_Mode"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/image/Editor/DarkMoon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDark_Mode->setIcon(icon2);
        actionCollaboratori = new QAction(EditorWindow);
        actionCollaboratori->setObjectName(QString::fromUtf8("actionCollaboratori"));
        actionGrassetto = new QAction(EditorWindow);
        actionGrassetto->setObjectName(QString::fromUtf8("actionGrassetto"));
        actionGrassetto->setCheckable(false);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/image/Editor/v2bold.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionGrassetto->setIcon(icon3);
        actionCorsivo = new QAction(EditorWindow);
        actionCorsivo->setObjectName(QString::fromUtf8("actionCorsivo"));
        actionCorsivo->setCheckable(false);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/image/Editor/v2italic.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCorsivo->setIcon(icon4);
        actionSottolineato = new QAction(EditorWindow);
        actionSottolineato->setObjectName(QString::fromUtf8("actionSottolineato"));
        actionSottolineato->setCheckable(false);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/image/Editor/v2underline.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSottolineato->setIcon(icon5);
        actionEsci = new QAction(EditorWindow);
        actionEsci->setObjectName(QString::fromUtf8("actionEsci"));
        actionSeleziona_Tutto = new QAction(EditorWindow);
        actionSeleziona_Tutto->setObjectName(QString::fromUtf8("actionSeleziona_Tutto"));
        actionToolbar = new QAction(EditorWindow);
        actionToolbar->setObjectName(QString::fromUtf8("actionToolbar"));
        actionOpzioni = new QAction(EditorWindow);
        actionOpzioni->setObjectName(QString::fromUtf8("actionOpzioni"));
        centralwidget = new QWidget(EditorWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setMinimumSize(QSize(950, 500));
        centralwidget->setStyleSheet(QString::fromUtf8("#centralwidget{\n"
"background: url(:/image/Editor/sfondo.png);\n"
"}"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setSizeConstraint(QLayout::SetFixedSize);
        editorFrame = new QFrame(centralwidget);
        editorFrame->setObjectName(QString::fromUtf8("editorFrame"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(editorFrame->sizePolicy().hasHeightForWidth());
        editorFrame->setSizePolicy(sizePolicy);
        editorFrame->setMinimumSize(QSize(821, 20));
        QFont font;
        font.setFamily(QString::fromUtf8("Calibri"));
        font.setPointSize(14);
        editorFrame->setFont(font);
        editorFrame->setStyleSheet(QString::fromUtf8(""));
        editorFrame->setFrameShape(QFrame::StyledPanel);
        editorFrame->setFrameShadow(QFrame::Raised);
        editorFrame->setMidLineWidth(0);
        verticalLayout_3 = new QVBoxLayout(editorFrame);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(0);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setSizeConstraint(QLayout::SetMinimumSize);
        horizontalLayout_5->setContentsMargins(0, -1, -1, -1);
        frameTopBar = new QFrame(editorFrame);
        frameTopBar->setObjectName(QString::fromUtf8("frameTopBar"));
        frameTopBar->setMinimumSize(QSize(0, 45));
        frameTopBar->setMaximumSize(QSize(16777215, 45));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Verdana"));
        font1.setPointSize(11);
        frameTopBar->setFont(font1);
        frameTopBar->setStyleSheet(QString::fromUtf8("#frameTopBar{\n"
"	background: qlineargradient(\n"
"		x1: 0, y1: 1, x2: 1, y2: 1,\n"
"		stop: 0 #0076EC,\n"
"		stop:0.53 #0076EC,\n"
"		stop:0.54 #0076EC,\n"
"		stop:0.63 #005DBA,\n"
"		stop:0.64 #005DBA,\n"
"		stop:0.88 #0A5597\n"
"	);\n"
"}\n"
"\n"
"#frameTopBar:menu-indicator{ image:none; }\n"
"\n"
"\n"
""));
        frameTopBar->setFrameShape(QFrame::StyledPanel);
        frameTopBar->setFrameShadow(QFrame::Raised);
        horizontalLayout_14 = new QHBoxLayout(frameTopBar);
        horizontalLayout_14->setSpacing(0);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        horizontalLayout_14->setContentsMargins(0, 0, 0, 0);
        fileButton = new QPushButton(frameTopBar);
        fileButton->setObjectName(QString::fromUtf8("fileButton"));
        fileButton->setMinimumSize(QSize(60, 45));
        fileButton->setMaximumSize(QSize(60, 45));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Verdana"));
        font2.setPointSize(11);
        font2.setBold(false);
        font2.setWeight(50);
        fileButton->setFont(font2);
        fileButton->setCursor(QCursor(Qt::PointingHandCursor));
        fileButton->setStyleSheet(QString::fromUtf8("#fileButton {\n"
"	border:none;\n"
"	background:url(:/image/Editor/file.png);\n"
"}\n"
"\n"
"#fileButton:hover {\n"
"	background-color: #075299;\n"
"}\n"
"\n"
"#fileButton:pressed {\n"
"	background-color: #075299;\n"
"}\n"
"\n"
"#fileButton:menu-indicator{ image:none; }"));
        fileButton->setIconSize(QSize(0, 0));

        horizontalLayout_14->addWidget(fileButton);

        visualizzaButton = new QPushButton(frameTopBar);
        visualizzaButton->setObjectName(QString::fromUtf8("visualizzaButton"));
        visualizzaButton->setMinimumSize(QSize(105, 45));
        visualizzaButton->setMaximumSize(QSize(105, 45));
        visualizzaButton->setFont(font2);
        visualizzaButton->setCursor(QCursor(Qt::PointingHandCursor));
        visualizzaButton->setStyleSheet(QString::fromUtf8("#visualizzaButton {\n"
"	border: none;\n"
"	background:url(:/image/Editor/visualizza.png);\n"
"}\n"
"\n"
"#visualizzaButton:hover {\n"
"	background-color: #075299;\n"
"}\n"
"\n"
"#visualizzaButton:pressed {\n"
"	background-color: #075299;\n"
"}\n"
"\n"
"#visualizzaButton:menu-indicator{ image:none; }"));
        visualizzaButton->setIconSize(QSize(0, 0));

        horizontalLayout_14->addWidget(visualizzaButton);

        modificaButton = new QPushButton(frameTopBar);
        modificaButton->setObjectName(QString::fromUtf8("modificaButton"));
        modificaButton->setMinimumSize(QSize(95, 45));
        modificaButton->setMaximumSize(QSize(9, 45));
        modificaButton->setFont(font2);
        modificaButton->setCursor(QCursor(Qt::PointingHandCursor));
        modificaButton->setStyleSheet(QString::fromUtf8("#modificaButton {\n"
"	border: none;\n"
"	background:url(:/image/Editor/modifica.png);\n"
"}\n"
"\n"
"#modificaButton:hover {\n"
"	background-color: #075299;\n"
"}\n"
"\n"
"#modificaButton:pressed {\n"
"	background-color: #075299;\n"
"}\n"
"\n"
"#modificaButton:menu-indicator{ image:none; }"));
        modificaButton->setIconSize(QSize(0, 0));

        horizontalLayout_14->addWidget(modificaButton);

        strumentiButton = new QPushButton(frameTopBar);
        strumentiButton->setObjectName(QString::fromUtf8("strumentiButton"));
        strumentiButton->setMinimumSize(QSize(110, 45));
        strumentiButton->setMaximumSize(QSize(110, 45));
        strumentiButton->setFont(font1);
        strumentiButton->setCursor(QCursor(Qt::PointingHandCursor));
        strumentiButton->setStyleSheet(QString::fromUtf8("#strumentiButton {\n"
"	border: none;\n"
"	background:url(:/image/Editor/strumenti.png);\n"
"}\n"
"\n"
"#strumentiButton:hover {\n"
"	background-color: #075299;\n"
"}\n"
"\n"
"#strumentiButton:pressed {\n"
"	background-color: #075299;\n"
"}\n"
"\n"
"#strumentiButton:menu-indicator{ image:none; }"));
        strumentiButton->setIconSize(QSize(0, 0));

        horizontalLayout_14->addWidget(strumentiButton);

        aboutButton = new QPushButton(frameTopBar);
        aboutButton->setObjectName(QString::fromUtf8("aboutButton"));
        aboutButton->setMinimumSize(QSize(40, 45));
        aboutButton->setMaximumSize(QSize(40, 45));
        aboutButton->setFont(font2);
        aboutButton->setCursor(QCursor(Qt::PointingHandCursor));
        aboutButton->setStyleSheet(QString::fromUtf8("#aboutButton {\n"
"	border: none;\n"
"	background:url(:/image/Editor/about.png);\n"
"}\n"
"\n"
"#aboutButton:hover {\n"
"	background-color: #075299;\n"
"}\n"
"\n"
"#aboutButton:pressed {\n"
"	background-color: #075299;\n"
"}\n"
"\n"
"#aboutButton:menu-indicator{ image:none; }"));
        aboutButton->setIconSize(QSize(0, 0));

        horizontalLayout_14->addWidget(aboutButton);

        horizontalSpacer_3 = new QSpacerItem(10, 15, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_14->addItem(horizontalSpacer_3);

        opaqueLogo = new QLabel(frameTopBar);
        opaqueLogo->setObjectName(QString::fromUtf8("opaqueLogo"));
        opaqueLogo->setMinimumSize(QSize(370, 45));
        opaqueLogo->setMaximumSize(QSize(370, 45));
        opaqueLogo->setStyleSheet(QString::fromUtf8("background: url(:/image/Editor/logo.png)"));

        horizontalLayout_14->addWidget(opaqueLogo);


        horizontalLayout_5->addWidget(frameTopBar);


        verticalLayout_3->addLayout(horizontalLayout_5);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(5);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        horizontalLayout_10->setSizeConstraint(QLayout::SetFixedSize);
        horizontalLayout_10->setContentsMargins(40, 5, 0, 10);
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(14);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 5, 35, -1);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(8);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setSizeConstraint(QLayout::SetNoConstraint);
        horizontalLayout_4->setContentsMargins(0, 5, 0, 0);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(1);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        buttonBold = new QPushButton(editorFrame);
        buttonBold->setObjectName(QString::fromUtf8("buttonBold"));
        buttonBold->setMinimumSize(QSize(34, 30));
        buttonBold->setMaximumSize(QSize(34, 30));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Calibri"));
        font3.setPointSize(23);
        font3.setBold(true);
        font3.setUnderline(false);
        font3.setWeight(75);
        font3.setStrikeOut(false);
        buttonBold->setFont(font3);
        buttonBold->setCursor(QCursor(Qt::PointingHandCursor));
        buttonBold->setStyleSheet(QString::fromUtf8("#buttonBold {\n"
"	border-radius: 4px;\n"
"}\n"
"\n"
"#buttonBold:hover {\n"
"	background-color: #BDC3C7;\n"
"}\n"
""));
        buttonBold->setIcon(icon3);
        buttonBold->setIconSize(QSize(22, 22));
        buttonBold->setCheckable(true);

        horizontalLayout_3->addWidget(buttonBold);

        buttonItalic = new QPushButton(editorFrame);
        buttonItalic->setObjectName(QString::fromUtf8("buttonItalic"));
        buttonItalic->setMinimumSize(QSize(34, 30));
        buttonItalic->setMaximumSize(QSize(34, 30));
        QFont font4;
        font4.setFamily(QString::fromUtf8("Calibri"));
        font4.setPointSize(27);
        font4.setBold(true);
        font4.setItalic(true);
        font4.setUnderline(false);
        font4.setWeight(75);
        font4.setStrikeOut(false);
        buttonItalic->setFont(font4);
        buttonItalic->setCursor(QCursor(Qt::PointingHandCursor));
        buttonItalic->setStyleSheet(QString::fromUtf8("#buttonItalic {\n"
"	border-radius: 4px;\n"
"}\n"
"\n"
"#buttonItalic:hover {\n"
"	background-color: #BDC3C7;\n"
"}\n"
""));
        buttonItalic->setIcon(icon4);
        buttonItalic->setIconSize(QSize(22, 22));
        buttonItalic->setCheckable(true);

        horizontalLayout_3->addWidget(buttonItalic);

        buttonUnderline = new QPushButton(editorFrame);
        buttonUnderline->setObjectName(QString::fromUtf8("buttonUnderline"));
        buttonUnderline->setMinimumSize(QSize(34, 30));
        buttonUnderline->setMaximumSize(QSize(34, 30));
        QFont font5;
        font5.setFamily(QString::fromUtf8("Calibri"));
        font5.setPointSize(18);
        font5.setBold(true);
        font5.setUnderline(true);
        font5.setWeight(75);
        font5.setStrikeOut(false);
        buttonUnderline->setFont(font5);
        buttonUnderline->setCursor(QCursor(Qt::PointingHandCursor));
        buttonUnderline->setStyleSheet(QString::fromUtf8("#buttonUnderline {\n"
"	border-radius: 4px;\n"
"}\n"
"\n"
"#buttonUnderline:hover {\n"
"	background-color: #BDC3C7;\n"
"}\n"
""));
        buttonUnderline->setIcon(icon5);
        buttonUnderline->setIconSize(QSize(22, 22));
        buttonUnderline->setCheckable(true);

        horizontalLayout_3->addWidget(buttonUnderline);


        horizontalLayout_4->addLayout(horizontalLayout_3);

        line_4 = new QFrame(editorFrame);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setMinimumSize(QSize(1, 0));
        line_4->setMaximumSize(QSize(1, 16777215));
        line_4->setStyleSheet(QString::fromUtf8("border:none;\n"
"background-color: lightgrey;\n"
"\n"
""));
        line_4->setFrameShape(QFrame::VLine);
        line_4->setFrameShadow(QFrame::Sunken);

        horizontalLayout_4->addWidget(line_4);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(3);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        fontFamilyBox = new QComboBox(editorFrame);
        fontFamilyBox->addItem(QString());
        fontFamilyBox->addItem(QString());
        fontFamilyBox->addItem(QString());
        fontFamilyBox->addItem(QString());
        fontFamilyBox->addItem(QString());
        fontFamilyBox->addItem(QString());
        fontFamilyBox->addItem(QString());
        fontFamilyBox->addItem(QString());
        fontFamilyBox->addItem(QString());
        fontFamilyBox->addItem(QString());
        fontFamilyBox->addItem(QString());
        fontFamilyBox->addItem(QString());
        fontFamilyBox->addItem(QString());
        fontFamilyBox->addItem(QString());
        fontFamilyBox->addItem(QString());
        fontFamilyBox->addItem(QString());
        fontFamilyBox->addItem(QString());
        fontFamilyBox->setObjectName(QString::fromUtf8("fontFamilyBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(fontFamilyBox->sizePolicy().hasHeightForWidth());
        fontFamilyBox->setSizePolicy(sizePolicy1);
        fontFamilyBox->setMinimumSize(QSize(0, 23));
        fontFamilyBox->setMaximumSize(QSize(16777215, 23));
        QFont font6;
        font6.setFamily(QString::fromUtf8("Segoe UI"));
        font6.setPointSize(10);
        fontFamilyBox->setFont(font6);
        fontFamilyBox->setCursor(QCursor(Qt::PointingHandCursor));
        fontFamilyBox->setStyleSheet(QString::fromUtf8("QAbstractItemView::item {\n"
"margin-top: 3px;\n"
"}"));
        fontFamilyBox->setMaxVisibleItems(16);
        fontFamilyBox->setInsertPolicy(QComboBox::NoInsert);
        fontFamilyBox->setIconSize(QSize(12, 12));

        horizontalLayout_9->addWidget(fontFamilyBox);

        fontSizeBox = new QComboBox(editorFrame);
        fontSizeBox->addItem(QString());
        fontSizeBox->addItem(QString());
        fontSizeBox->addItem(QString());
        fontSizeBox->addItem(QString());
        fontSizeBox->addItem(QString());
        fontSizeBox->addItem(QString());
        fontSizeBox->addItem(QString());
        fontSizeBox->addItem(QString());
        fontSizeBox->addItem(QString());
        fontSizeBox->addItem(QString());
        fontSizeBox->addItem(QString());
        fontSizeBox->addItem(QString());
        fontSizeBox->addItem(QString());
        fontSizeBox->addItem(QString());
        fontSizeBox->setObjectName(QString::fromUtf8("fontSizeBox"));
        fontSizeBox->setMinimumSize(QSize(50, 23));
        fontSizeBox->setMaximumSize(QSize(44, 23));
        fontSizeBox->setSizeIncrement(QSize(0, 0));
        fontSizeBox->setBaseSize(QSize(0, 0));
        fontSizeBox->setCursor(QCursor(Qt::PointingHandCursor));
        fontSizeBox->setAutoFillBackground(false);
        fontSizeBox->setStyleSheet(QString::fromUtf8(""));
        fontSizeBox->setEditable(true);
        fontSizeBox->setMaxVisibleItems(10);
        fontSizeBox->setIconSize(QSize(18, 16));

        horizontalLayout_9->addWidget(fontSizeBox);


        horizontalLayout_4->addLayout(horizontalLayout_9);

        line_5 = new QFrame(editorFrame);
        line_5->setObjectName(QString::fromUtf8("line_5"));
        line_5->setMinimumSize(QSize(1, 0));
        line_5->setMaximumSize(QSize(1, 16777215));
        line_5->setStyleSheet(QString::fromUtf8("border:none;\n"
"background-color: lightgrey;\n"
"\n"
""));
        line_5->setFrameShape(QFrame::VLine);
        line_5->setFrameShadow(QFrame::Sunken);

        horizontalLayout_4->addWidget(line_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(2);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        buttonAlignSX = new QPushButton(editorFrame);
        buttonAlignSX->setObjectName(QString::fromUtf8("buttonAlignSX"));
        buttonAlignSX->setMinimumSize(QSize(34, 30));
        buttonAlignSX->setMaximumSize(QSize(34, 30));
        QFont font7;
        font7.setPointSize(9);
        font7.setBold(true);
        font7.setUnderline(false);
        font7.setWeight(75);
        font7.setStrikeOut(false);
        buttonAlignSX->setFont(font7);
        buttonAlignSX->setCursor(QCursor(Qt::PointingHandCursor));
        buttonAlignSX->setStyleSheet(QString::fromUtf8("#buttonAlignSX{\n"
"	border-radius: 4px;\n"
"}\n"
"\n"
"#buttonAlignSX:hover{\n"
"	background-color: #BDC3C7;\n"
"}\n"
""));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/image/Editor/left-align.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonAlignSX->setIcon(icon6);
        buttonAlignSX->setIconSize(QSize(30, 30));
        buttonAlignSX->setCheckable(true);

        horizontalLayout_6->addWidget(buttonAlignSX);

        buttonAlignCX = new QPushButton(editorFrame);
        buttonAlignCX->setObjectName(QString::fromUtf8("buttonAlignCX"));
        buttonAlignCX->setMinimumSize(QSize(34, 30));
        buttonAlignCX->setMaximumSize(QSize(34, 30));
        QFont font8;
        font8.setPointSize(10);
        font8.setBold(true);
        font8.setUnderline(false);
        font8.setWeight(75);
        font8.setStrikeOut(false);
        buttonAlignCX->setFont(font8);
        buttonAlignCX->setCursor(QCursor(Qt::PointingHandCursor));
        buttonAlignCX->setStyleSheet(QString::fromUtf8("#buttonAlignCX{\n"
"	border-radius: 4px;\n"
"}\n"
"\n"
"#buttonAlignCX:hover{\n"
"	background-color: #BDC3C7;\n"
"}\n"
""));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/image/Editor/center-align.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonAlignCX->setIcon(icon7);
        buttonAlignCX->setIconSize(QSize(30, 30));
        buttonAlignCX->setCheckable(true);

        horizontalLayout_6->addWidget(buttonAlignCX);

        buttonAlignDX = new QPushButton(editorFrame);
        buttonAlignDX->setObjectName(QString::fromUtf8("buttonAlignDX"));
        buttonAlignDX->setMinimumSize(QSize(34, 30));
        buttonAlignDX->setMaximumSize(QSize(34, 30));
        buttonAlignDX->setFont(font8);
        buttonAlignDX->setCursor(QCursor(Qt::PointingHandCursor));
        buttonAlignDX->setStyleSheet(QString::fromUtf8("#buttonAlignDX{\n"
"	border-radius: 4px;\n"
"}\n"
"\n"
"#buttonAlignDX:hover{\n"
"	background-color: #BDC3C7;\n"
"}\n"
""));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/image/Editor/right-align.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonAlignDX->setIcon(icon8);
        buttonAlignDX->setIconSize(QSize(30, 30));
        buttonAlignDX->setCheckable(true);

        horizontalLayout_6->addWidget(buttonAlignDX);

        buttonAlignJFX = new QPushButton(editorFrame);
        buttonAlignJFX->setObjectName(QString::fromUtf8("buttonAlignJFX"));
        buttonAlignJFX->setMinimumSize(QSize(34, 30));
        buttonAlignJFX->setMaximumSize(QSize(34, 30));
        buttonAlignJFX->setFont(font8);
        buttonAlignJFX->setCursor(QCursor(Qt::PointingHandCursor));
        buttonAlignJFX->setStyleSheet(QString::fromUtf8("#buttonAlignJFX{\n"
"	border-radius: 4px;\n"
"}\n"
"\n"
"#buttonAlignJFX:hover{\n"
"	background-color: #BDC3C7;\n"
"}\n"
""));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/image/Editor/justify.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonAlignJFX->setIcon(icon9);
        buttonAlignJFX->setIconSize(QSize(30, 30));
        buttonAlignJFX->setCheckable(true);

        horizontalLayout_6->addWidget(buttonAlignJFX);


        horizontalLayout_4->addLayout(horizontalLayout_6);

        line_6 = new QFrame(editorFrame);
        line_6->setObjectName(QString::fromUtf8("line_6"));
        line_6->setMinimumSize(QSize(1, 0));
        line_6->setMaximumSize(QSize(1, 16777215));
        line_6->setStyleSheet(QString::fromUtf8("border:none;\n"
"background-color: lightgrey;\n"
"\n"
""));
        line_6->setFrameShape(QFrame::VLine);
        line_6->setFrameShadow(QFrame::Sunken);

        horizontalLayout_4->addWidget(line_6);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(1);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        buttonCopy = new QPushButton(editorFrame);
        buttonCopy->setObjectName(QString::fromUtf8("buttonCopy"));
        buttonCopy->setMinimumSize(QSize(34, 30));
        buttonCopy->setMaximumSize(QSize(34, 30));
        buttonCopy->setFont(font8);
        buttonCopy->setCursor(QCursor(Qt::PointingHandCursor));
        buttonCopy->setStyleSheet(QString::fromUtf8("#buttonCopy {\n"
"	border-radius: 4px;\n"
"}\n"
"\n"
"#buttonCopy:hover {\n"
"	background-color: #BDC3C7;\n"
"}\n"
""));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/image/Editor/copy.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonCopy->setIcon(icon10);
        buttonCopy->setIconSize(QSize(30, 30));

        horizontalLayout_8->addWidget(buttonCopy);

        buttonCut = new QPushButton(editorFrame);
        buttonCut->setObjectName(QString::fromUtf8("buttonCut"));
        buttonCut->setMinimumSize(QSize(34, 30));
        buttonCut->setMaximumSize(QSize(34, 30));
        buttonCut->setFont(font8);
        buttonCut->setCursor(QCursor(Qt::PointingHandCursor));
        buttonCut->setStyleSheet(QString::fromUtf8("#buttonCut {\n"
"	border-radius: 4px;\n"
"}\n"
"\n"
"#buttonCut:hover {\n"
"	background-color: #BDC3C7;\n"
"}\n"
""));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/image/Editor/cut.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonCut->setIcon(icon11);
        buttonCut->setIconSize(QSize(30, 30));

        horizontalLayout_8->addWidget(buttonCut);

        buttonPaste = new QPushButton(editorFrame);
        buttonPaste->setObjectName(QString::fromUtf8("buttonPaste"));
        buttonPaste->setMinimumSize(QSize(34, 30));
        buttonPaste->setMaximumSize(QSize(34, 30));
        buttonPaste->setFont(font8);
        buttonPaste->setCursor(QCursor(Qt::PointingHandCursor));
        buttonPaste->setStyleSheet(QString::fromUtf8("#buttonPaste {\n"
"	border-radius: 4px;\n"
"}\n"
"\n"
"#buttonPaste:hover {\n"
"	background-color: #BDC3C7;\n"
"}\n"
""));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/image/Editor/paste.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonPaste->setIcon(icon12);
        buttonPaste->setIconSize(QSize(30, 30));

        horizontalLayout_8->addWidget(buttonPaste);


        horizontalLayout_4->addLayout(horizontalLayout_8);

        line_7 = new QFrame(editorFrame);
        line_7->setObjectName(QString::fromUtf8("line_7"));
        line_7->setMinimumSize(QSize(1, 0));
        line_7->setMaximumSize(QSize(1, 16777215));
        line_7->setStyleSheet(QString::fromUtf8("border:none;\n"
"background-color: lightgrey;\n"
"\n"
""));
        line_7->setFrameShape(QFrame::VLine);
        line_7->setFrameShadow(QFrame::Sunken);

        horizontalLayout_4->addWidget(line_7);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(2);
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        horizontalLayout_13->setContentsMargins(0, -1, -1, -1);
        buttonColor = new QPushButton(editorFrame);
        buttonColor->setObjectName(QString::fromUtf8("buttonColor"));
        buttonColor->setMinimumSize(QSize(34, 30));
        buttonColor->setMaximumSize(QSize(34, 30));
        buttonColor->setFont(font8);
        buttonColor->setCursor(QCursor(Qt::PointingHandCursor));
        buttonColor->setStyleSheet(QString::fromUtf8("#buttonColor{\n"
"	border-radius: 4px;\n"
"}\n"
"\n"
"#buttonColor:hover{\n"
"	background-color: #BDC3C7;\n"
"}\n"
""));
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/image/Editor/highlighter.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonColor->setIcon(icon13);
        buttonColor->setIconSize(QSize(30, 30));
        buttonColor->setCheckable(true);

        horizontalLayout_13->addWidget(buttonColor);


        horizontalLayout_4->addLayout(horizontalLayout_13);

        horizontalSpacer_2 = new QSpacerItem(100, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);


        verticalLayout_5->addLayout(horizontalLayout_4);

        RealTextEdit = new MyQTextEdit(editorFrame);
        RealTextEdit->setObjectName(QString::fromUtf8("RealTextEdit"));
        QSizePolicy sizePolicy2(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(RealTextEdit->sizePolicy().hasHeightForWidth());
        RealTextEdit->setSizePolicy(sizePolicy2);
        RealTextEdit->setMinimumSize(QSize(500, 0));
        QFont font9;
        font9.setFamily(QString::fromUtf8("Times New Roman"));
        font9.setPointSize(14);
        font9.setBold(false);
        font9.setWeight(50);
        font9.setStrikeOut(false);
        RealTextEdit->setFont(font9);
        RealTextEdit->setContextMenuPolicy(Qt::CustomContextMenu);
        RealTextEdit->setStyleSheet(QString::fromUtf8(" #RealTextEdit{  \n"
"background: #FFFFFF; \n"
"border-left: 2px solid #404040\n"
";}"));

        verticalLayout_5->addWidget(RealTextEdit);


        horizontalLayout_10->addLayout(verticalLayout_5);

        line = new QFrame(editorFrame);
        line->setObjectName(QString::fromUtf8("line"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(line->sizePolicy().hasHeightForWidth());
        line->setSizePolicy(sizePolicy3);
        line->setMinimumSize(QSize(5, 0));
        line->setMaximumSize(QSize(5, 16777215));
        line->setStyleSheet(QString::fromUtf8("border:none;\n"
"background-color: lightgrey;\n"
"\n"
""));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout_10->addWidget(line);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, -1, 0, -1);
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Maximum);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(10);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        profileButton = new QPushButton(editorFrame);
        profileButton->setObjectName(QString::fromUtf8("profileButton"));
        profileButton->setMinimumSize(QSize(40, 40));
        profileButton->setMaximumSize(QSize(40, 40));
        QFont font10;
        font10.setPointSize(16);
        font10.setBold(true);
        font10.setWeight(75);
        profileButton->setFont(font10);
        profileButton->setCursor(QCursor(Qt::PointingHandCursor));
        profileButton->setStyleSheet(QString::fromUtf8("border:none;\n"
"border-radius: 4px;"));
        profileButton->setIconSize(QSize(0, 0));

        horizontalLayout_7->addWidget(profileButton);

        labelUser = new QLabel(editorFrame);
        labelUser->setObjectName(QString::fromUtf8("labelUser"));
        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(labelUser->sizePolicy().hasHeightForWidth());
        labelUser->setSizePolicy(sizePolicy4);
        labelUser->setMinimumSize(QSize(0, 40));
        labelUser->setMaximumSize(QSize(16777215, 40));
        QFont font11;
        font11.setFamily(QString::fromUtf8("Calibri"));
        font11.setPointSize(18);
        font11.setBold(true);
        font11.setWeight(75);
        labelUser->setFont(font11);
        labelUser->setLayoutDirection(Qt::LeftToRight);
        labelUser->setStyleSheet(QString::fromUtf8("#labelCollab{\n"
"	background-color:transparent;\n"
"	color: #505050;\n"
"	border-bottom: 2px solid lightgrey;\n"
"}"));
        labelUser->setAlignment(Qt::AlignCenter);

        horizontalLayout_7->addWidget(labelUser);

        horizontalSpacer = new QSpacerItem(50, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_7);

        verticalSpacer_3 = new QSpacerItem(20, 6, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout->addItem(verticalSpacer_3);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Maximum);

        verticalLayout->addItem(verticalSpacer_5);

        line_2 = new QFrame(editorFrame);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setMinimumSize(QSize(0, 1));
        line_2->setMaximumSize(QSize(16777215, 1));
        line_2->setStyleSheet(QString::fromUtf8("border:none;\n"
"background-color: lightgrey;\n"
"\n"
""));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_2);

        verticalSpacer = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout->addItem(verticalSpacer);

        DocNameLabel = new QLabel(editorFrame);
        DocNameLabel->setObjectName(QString::fromUtf8("DocNameLabel"));
        QSizePolicy sizePolicy5(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(DocNameLabel->sizePolicy().hasHeightForWidth());
        DocNameLabel->setSizePolicy(sizePolicy5);
        DocNameLabel->setMinimumSize(QSize(0, 40));
        DocNameLabel->setMaximumSize(QSize(250, 40));
        DocNameLabel->setSizeIncrement(QSize(0, 0));
        DocNameLabel->setBaseSize(QSize(0, 0));
        QFont font12;
        font12.setFamily(QString::fromUtf8("Calibri"));
        font12.setPointSize(17);
        font12.setBold(true);
        font12.setWeight(75);
        DocNameLabel->setFont(font12);
        DocNameLabel->setStyleSheet(QString::fromUtf8("#DocNameLabel{\n"
"	color: #505050;\n"
"}"));
        DocNameLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(DocNameLabel);

        verticalSpacer_7 = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout->addItem(verticalSpacer_7);

        label = new QLabel(editorFrame);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font13;
        font13.setFamily(QString::fromUtf8("Calibri"));
        font13.setPointSize(12);
        font13.setBold(true);
        font13.setWeight(75);
        label->setFont(font13);
        label->setStyleSheet(QString::fromUtf8("color:grey;"));

        verticalLayout->addWidget(label);

        label_2 = new QLabel(editorFrame);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font13);
        label_2->setStyleSheet(QString::fromUtf8("color:grey;"));

        verticalLayout->addWidget(label_2);

        label_3 = new QLabel(editorFrame);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font13);
        label_3->setStyleSheet(QString::fromUtf8("color:grey;"));

        verticalLayout->addWidget(label_3);

        verticalSpacer_4 = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout->addItem(verticalSpacer_4);

        line_3 = new QFrame(editorFrame);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setMinimumSize(QSize(0, 1));
        line_3->setMaximumSize(QSize(16777215, 1));
        line_3->setStyleSheet(QString::fromUtf8("border:none;\n"
"background-color: lightgrey;\n"
"\n"
""));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_3);

        verticalSpacer_8 = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout->addItem(verticalSpacer_8);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Maximum);

        verticalLayout->addItem(verticalSpacer_6);

        labelCollOn = new QLabel(editorFrame);
        labelCollOn->setObjectName(QString::fromUtf8("labelCollOn"));
        labelCollOn->setFont(font13);
        labelCollOn->setStyleSheet(QString::fromUtf8("color: grey;"));

        verticalLayout->addWidget(labelCollOn);

        verticalSpacer_9 = new QSpacerItem(20, 6, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout->addItem(verticalSpacer_9);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(0);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        listWidgetOn = new QListWidget(editorFrame);
        listWidgetOn->setObjectName(QString::fromUtf8("listWidgetOn"));
        sizePolicy2.setHeightForWidth(listWidgetOn->sizePolicy().hasHeightForWidth());
        listWidgetOn->setSizePolicy(sizePolicy2);
        listWidgetOn->setMinimumSize(QSize(250, 0));
        listWidgetOn->setMaximumSize(QSize(250, 16777215));
        listWidgetOn->setFont(font13);
        listWidgetOn->setStyleSheet(QString::fromUtf8("#listWidgetOn{\n"
"border:transparent;\n"
"background: transparent;\n"
"}\n"
"\n"
"QToolTip { \n"
"	color: #000000; \n"
"	background-color: #FFF2BF; \n"
"	border: 0px; \n"
"}"));
        listWidgetOn->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        listWidgetOn->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        listWidgetOn->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        listWidgetOn->setAutoScroll(false);
        listWidgetOn->setAutoScrollMargin(16);
        listWidgetOn->setEditTriggers(QAbstractItemView::NoEditTriggers);
        listWidgetOn->setProperty("showDropIndicator", QVariant(false));
        listWidgetOn->setDefaultDropAction(Qt::IgnoreAction);
        listWidgetOn->setSelectionMode(QAbstractItemView::NoSelection);
        listWidgetOn->setSelectionBehavior(QAbstractItemView::SelectRows);
        listWidgetOn->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        listWidgetOn->setSpacing(6);

        horizontalLayout_11->addWidget(listWidgetOn);

        verticalScrollBarOn = new QScrollBar(editorFrame);
        verticalScrollBarOn->setObjectName(QString::fromUtf8("verticalScrollBarOn"));
        verticalScrollBarOn->setEnabled(true);
        QSizePolicy sizePolicy6(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(verticalScrollBarOn->sizePolicy().hasHeightForWidth());
        verticalScrollBarOn->setSizePolicy(sizePolicy6);
        verticalScrollBarOn->setMinimumSize(QSize(8, 0));
        verticalScrollBarOn->setMaximumSize(QSize(8, 16777215));
        verticalScrollBarOn->setSizeIncrement(QSize(0, 0));
        verticalScrollBarOn->setStyleSheet(QString::fromUtf8("QScrollBar:vertical {\n"
"			border-radius: 4px;\n"
"            background: lightgrey;\n"
"            width:8px;    \n"
"        }\n"
"\n"
"        QScrollBar::handle:vertical {         \n"
"       \n"
"            min-height: 0px;\n"
"          	border: 0px solid red;\n"
"			border-radius: 4px;\n"
"			background-color: #80808080;\n"
"        }\n"
"        QScrollBar::add-line:vertical {       \n"
"            height: 0px;\n"
"            subcontrol-position: bottom;\n"
"            subcontrol-origin: margin;\n"
"        }\n"
"        QScrollBar::sub-line:vertical {\n"
"            height: 0 px;\n"
"            subcontrol-position: top;\n"
"            subcontrol-origin: margin;\n"
"        }"));
        verticalScrollBarOn->setOrientation(Qt::Vertical);

        horizontalLayout_11->addWidget(verticalScrollBarOn);


        verticalLayout->addLayout(horizontalLayout_11);

        verticalSpacer_11 = new QSpacerItem(20, 6, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout->addItem(verticalSpacer_11);

        labelCollOff = new QLabel(editorFrame);
        labelCollOff->setObjectName(QString::fromUtf8("labelCollOff"));
        labelCollOff->setFont(font13);
        labelCollOff->setStyleSheet(QString::fromUtf8("color: grey;"));

        verticalLayout->addWidget(labelCollOff);

        verticalSpacer_10 = new QSpacerItem(20, 6, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout->addItem(verticalSpacer_10);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(0);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        listWidgetOff = new QListWidget(editorFrame);
        listWidgetOff->setObjectName(QString::fromUtf8("listWidgetOff"));
        sizePolicy2.setHeightForWidth(listWidgetOff->sizePolicy().hasHeightForWidth());
        listWidgetOff->setSizePolicy(sizePolicy2);
        listWidgetOff->setMinimumSize(QSize(250, 0));
        listWidgetOff->setMaximumSize(QSize(250, 16777215));
        listWidgetOff->setFont(font13);
        listWidgetOff->setLayoutDirection(Qt::LeftToRight);
        listWidgetOff->setStyleSheet(QString::fromUtf8("#listWidgetOff{\n"
"border:transparent;\n"
"background: transparent;\n"
"color: rgb(159,159,159);\n"
"}\n"
"\n"
"QToolTip { \n"
"	color: #000000; \n"
"	background-color: #FFF2BF; \n"
"	border: 0px; \n"
"}"));
        listWidgetOff->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        listWidgetOff->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        listWidgetOff->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        listWidgetOff->setAutoScroll(false);
        listWidgetOff->setAutoScrollMargin(16);
        listWidgetOff->setEditTriggers(QAbstractItemView::NoEditTriggers);
        listWidgetOff->setProperty("showDropIndicator", QVariant(false));
        listWidgetOff->setDefaultDropAction(Qt::IgnoreAction);
        listWidgetOff->setSelectionMode(QAbstractItemView::NoSelection);
        listWidgetOff->setSelectionBehavior(QAbstractItemView::SelectItems);
        listWidgetOff->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        listWidgetOff->setSpacing(6);
        listWidgetOff->setSelectionRectVisible(false);

        horizontalLayout_12->addWidget(listWidgetOff);

        verticalScrollBarOff = new QScrollBar(editorFrame);
        verticalScrollBarOff->setObjectName(QString::fromUtf8("verticalScrollBarOff"));
        sizePolicy6.setHeightForWidth(verticalScrollBarOff->sizePolicy().hasHeightForWidth());
        verticalScrollBarOff->setSizePolicy(sizePolicy6);
        verticalScrollBarOff->setMinimumSize(QSize(8, 0));
        verticalScrollBarOff->setMaximumSize(QSize(8, 16777215));
        verticalScrollBarOff->setStyleSheet(QString::fromUtf8("QScrollBar:vertical {\n"
"			border-radius: 4px;\n"
"            background: lightgrey;\n"
"            width:8px;    \n"
"        }\n"
"\n"
"        QScrollBar::handle:vertical {         \n"
"       \n"
"            min-height: 0px;\n"
"          	border: 0px solid red;\n"
"			border-radius: 4px;\n"
"			background-color: #80808080;\n"
"        }\n"
"        QScrollBar::add-line:vertical {       \n"
"            height: 0px;\n"
"            subcontrol-position: bottom;\n"
"            subcontrol-origin: margin;\n"
"        }\n"
"        QScrollBar::sub-line:vertical {\n"
"            height: 0 px;\n"
"            subcontrol-position: top;\n"
"            subcontrol-origin: margin;\n"
"        }"));
        verticalScrollBarOff->setOrientation(Qt::Vertical);

        horizontalLayout_12->addWidget(verticalScrollBarOff);


        verticalLayout->addLayout(horizontalLayout_12);


        horizontalLayout->addLayout(verticalLayout);


        verticalLayout_4->addLayout(horizontalLayout);


        horizontalLayout_10->addLayout(verticalLayout_4);


        verticalLayout_3->addLayout(horizontalLayout_10);


        horizontalLayout_2->addWidget(editorFrame);


        gridLayout->addLayout(horizontalLayout_2, 2, 0, 1, 1);

        EditorWindow->setCentralWidget(centralwidget);

        retranslateUi(EditorWindow);

        fontFamilyBox->setCurrentIndex(13);
        fontSizeBox->setCurrentIndex(5);


        QMetaObject::connectSlotsByName(EditorWindow);
    } // setupUi

    void retranslateUi(QMainWindow *EditorWindow)
    {
        EditorWindow->setWindowTitle(QCoreApplication::translate("EditorWindow", "MainWindow", nullptr));
        actionNew->setText(QCoreApplication::translate("EditorWindow", "Nuovo Documento", nullptr));
#if QT_CONFIG(shortcut)
        actionNew->setShortcut(QCoreApplication::translate("EditorWindow", "Ctrl+N", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSave->setText(QCoreApplication::translate("EditorWindow", "Salva", nullptr));
#if QT_CONFIG(shortcut)
        actionSave->setShortcut(QCoreApplication::translate("EditorWindow", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
        actionFullscreen->setText(QCoreApplication::translate("EditorWindow", "Schermo Intero", nullptr));
#if QT_CONFIG(tooltip)
        actionFullscreen->setToolTip(QCoreApplication::translate("EditorWindow", "Schermo Intero", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionFullscreen->setShortcut(QCoreApplication::translate("EditorWindow", "Ctrl+F11", nullptr));
#endif // QT_CONFIG(shortcut)
        actionAbout->setText(QCoreApplication::translate("EditorWindow", "?", nullptr));
#if QT_CONFIG(shortcut)
        actionAbout->setShortcut(QCoreApplication::translate("EditorWindow", "Ctrl+H", nullptr));
#endif // QT_CONFIG(shortcut)
        actionClose->setText(QCoreApplication::translate("EditorWindow", "Chiudi Documento", nullptr));
#if QT_CONFIG(shortcut)
        actionClose->setShortcut(QCoreApplication::translate("EditorWindow", "Ctrl+Q", nullptr));
#endif // QT_CONFIG(shortcut)
        actionInvita_tramite_URI->setText(QCoreApplication::translate("EditorWindow", "Invita tramite URI", nullptr));
        actionEsporta_come_PDF->setText(QCoreApplication::translate("EditorWindow", "Esporta come PDF", nullptr));
#if QT_CONFIG(shortcut)
        actionEsporta_come_PDF->setShortcut(QCoreApplication::translate("EditorWindow", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
        actionRinomina->setText(QCoreApplication::translate("EditorWindow", "Rinomina", nullptr));
#if QT_CONFIG(shortcut)
        actionRinomina->setShortcut(QCoreApplication::translate("EditorWindow", "Ctrl+R", nullptr));
#endif // QT_CONFIG(shortcut)
        actionDark_Mode->setText(QCoreApplication::translate("EditorWindow", "Modalit\303\240 Notte", nullptr));
#if QT_CONFIG(tooltip)
        actionDark_Mode->setToolTip(QCoreApplication::translate("EditorWindow", "Modalit\303\240 Notte", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionDark_Mode->setShortcut(QCoreApplication::translate("EditorWindow", "Ctrl+D", nullptr));
#endif // QT_CONFIG(shortcut)
        actionCollaboratori->setText(QCoreApplication::translate("EditorWindow", "Nascondi Collaboratori", nullptr));
        actionGrassetto->setText(QCoreApplication::translate("EditorWindow", "Grassetto", nullptr));
#if QT_CONFIG(shortcut)
        actionGrassetto->setShortcut(QCoreApplication::translate("EditorWindow", "Ctrl+B", nullptr));
#endif // QT_CONFIG(shortcut)
        actionCorsivo->setText(QCoreApplication::translate("EditorWindow", "Corsivo", nullptr));
#if QT_CONFIG(shortcut)
        actionCorsivo->setShortcut(QCoreApplication::translate("EditorWindow", "Ctrl+I", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSottolineato->setText(QCoreApplication::translate("EditorWindow", "Sottolineato", nullptr));
#if QT_CONFIG(shortcut)
        actionSottolineato->setShortcut(QCoreApplication::translate("EditorWindow", "Ctrl+U", nullptr));
#endif // QT_CONFIG(shortcut)
        actionEsci->setText(QCoreApplication::translate("EditorWindow", "Esci", nullptr));
#if QT_CONFIG(shortcut)
        actionEsci->setShortcut(QCoreApplication::translate("EditorWindow", "Ctrl+Shift+Q", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSeleziona_Tutto->setText(QCoreApplication::translate("EditorWindow", "Seleziona Tutto", nullptr));
#if QT_CONFIG(shortcut)
        actionSeleziona_Tutto->setShortcut(QCoreApplication::translate("EditorWindow", "Ctrl+A", nullptr));
#endif // QT_CONFIG(shortcut)
        actionToolbar->setText(QCoreApplication::translate("EditorWindow", "Toolbar", nullptr));
#if QT_CONFIG(shortcut)
        actionToolbar->setShortcut(QCoreApplication::translate("EditorWindow", "Ctrl+M", nullptr));
#endif // QT_CONFIG(shortcut)
        actionOpzioni->setText(QCoreApplication::translate("EditorWindow", "Opzioni", nullptr));
#if QT_CONFIG(shortcut)
        actionOpzioni->setShortcut(QCoreApplication::translate("EditorWindow", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
        fileButton->setText(QString());
#if QT_CONFIG(shortcut)
        fileButton->setShortcut(QString());
#endif // QT_CONFIG(shortcut)
        visualizzaButton->setText(QString());
        modificaButton->setText(QString());
        strumentiButton->setText(QString());
        aboutButton->setText(QString());
        opaqueLogo->setText(QString());
        buttonBold->setText(QString());
        buttonItalic->setText(QString());
        buttonUnderline->setText(QString());
        fontFamilyBox->setItemText(0, QCoreApplication::translate("EditorWindow", "Arial", nullptr));
        fontFamilyBox->setItemText(1, QCoreApplication::translate("EditorWindow", "Arial Black", nullptr));
        fontFamilyBox->setItemText(2, QCoreApplication::translate("EditorWindow", "Comic Sans MS", nullptr));
        fontFamilyBox->setItemText(3, QCoreApplication::translate("EditorWindow", "Courier New", nullptr));
        fontFamilyBox->setItemText(4, QCoreApplication::translate("EditorWindow", "Franklin Gothic Medium", nullptr));
        fontFamilyBox->setItemText(5, QCoreApplication::translate("EditorWindow", "Georgia", nullptr));
        fontFamilyBox->setItemText(6, QCoreApplication::translate("EditorWindow", "Impact", nullptr));
        fontFamilyBox->setItemText(7, QCoreApplication::translate("EditorWindow", "Lucida Console", nullptr));
        fontFamilyBox->setItemText(8, QCoreApplication::translate("EditorWindow", "Lucida Sans Unicode", nullptr));
        fontFamilyBox->setItemText(9, QCoreApplication::translate("EditorWindow", "Microsoft Sans Serif", nullptr));
        fontFamilyBox->setItemText(10, QCoreApplication::translate("EditorWindow", "Palatino Linotype", nullptr));
        fontFamilyBox->setItemText(11, QCoreApplication::translate("EditorWindow", "Sylfaen", nullptr));
        fontFamilyBox->setItemText(12, QCoreApplication::translate("EditorWindow", "Tahoma", nullptr));
        fontFamilyBox->setItemText(13, QCoreApplication::translate("EditorWindow", "Times New Roman", nullptr));
        fontFamilyBox->setItemText(14, QCoreApplication::translate("EditorWindow", "Trebuchet MS", nullptr));
        fontFamilyBox->setItemText(15, QCoreApplication::translate("EditorWindow", "Verdana", nullptr));
        fontFamilyBox->setItemText(16, QString());

        fontFamilyBox->setCurrentText(QCoreApplication::translate("EditorWindow", "Times New Roman", nullptr));
        fontSizeBox->setItemText(0, QCoreApplication::translate("EditorWindow", "8", nullptr));
        fontSizeBox->setItemText(1, QCoreApplication::translate("EditorWindow", "9", nullptr));
        fontSizeBox->setItemText(2, QCoreApplication::translate("EditorWindow", "10", nullptr));
        fontSizeBox->setItemText(3, QCoreApplication::translate("EditorWindow", "11", nullptr));
        fontSizeBox->setItemText(4, QCoreApplication::translate("EditorWindow", "12", nullptr));
        fontSizeBox->setItemText(5, QCoreApplication::translate("EditorWindow", "14", nullptr));
        fontSizeBox->setItemText(6, QCoreApplication::translate("EditorWindow", "18", nullptr));
        fontSizeBox->setItemText(7, QCoreApplication::translate("EditorWindow", "24", nullptr));
        fontSizeBox->setItemText(8, QCoreApplication::translate("EditorWindow", "30", nullptr));
        fontSizeBox->setItemText(9, QCoreApplication::translate("EditorWindow", "36", nullptr));
        fontSizeBox->setItemText(10, QCoreApplication::translate("EditorWindow", "48", nullptr));
        fontSizeBox->setItemText(11, QCoreApplication::translate("EditorWindow", "60", nullptr));
        fontSizeBox->setItemText(12, QCoreApplication::translate("EditorWindow", "72", nullptr));
        fontSizeBox->setItemText(13, QCoreApplication::translate("EditorWindow", "96", nullptr));

        fontSizeBox->setCurrentText(QCoreApplication::translate("EditorWindow", "14", nullptr));
        buttonAlignSX->setText(QString());
        buttonAlignCX->setText(QString());
        buttonAlignDX->setText(QString());
        buttonAlignJFX->setText(QString());
        buttonCopy->setText(QString());
        buttonCut->setText(QString());
        buttonPaste->setText(QString());
        buttonColor->setText(QString());
        profileButton->setText(QString());
        labelUser->setText(QCoreApplication::translate("EditorWindow", "CURRENT USER", nullptr));
        DocNameLabel->setText(QCoreApplication::translate("EditorWindow", "DocumentNameGoesHere", nullptr));
        label->setText(QCoreApplication::translate("EditorWindow", "Caratteri: 0", nullptr));
        label_2->setText(QCoreApplication::translate("EditorWindow", "Parole: 0", nullptr));
        label_3->setText(QCoreApplication::translate("EditorWindow", "Linee: 0", nullptr));
        labelCollOn->setText(QCoreApplication::translate("EditorWindow", "Collaboratori online", nullptr));
        labelCollOff->setText(QCoreApplication::translate("EditorWindow", "Collaboratori offline", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditorWindow: public Ui_EditorWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITORWINDOW_H

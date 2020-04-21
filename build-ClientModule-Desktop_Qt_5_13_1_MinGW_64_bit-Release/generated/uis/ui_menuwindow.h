/********************************************************************************
** Form generated from reading UI file 'menuwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MENUWINDOW_H
#define UI_MENUWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MenuWindow
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *selectPage;
    QPushButton *uriDoc;
    QPushButton *Username;
    QPushButton *newDoc;
    QPushButton *listFiles;
    QPushButton *LogoutButton;
    QWidget *openDocPage;
    QListWidget *listWidget;
    QPushButton *backButton;
    QLabel *noFile;
    QPushButton *exitButton;

    void setupUi(QMainWindow *MenuWindow)
    {
        if (MenuWindow->objectName().isEmpty())
            MenuWindow->setObjectName(QString::fromUtf8("MenuWindow"));
        MenuWindow->resize(652, 800);
        MenuWindow->setMinimumSize(QSize(600, 750));
        MenuWindow->setMaximumSize(QSize(652, 800));
        MenuWindow->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(MenuWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(0, 0, 652, 800));
        selectPage = new QWidget();
        selectPage->setObjectName(QString::fromUtf8("selectPage"));
        selectPage->setStyleSheet(QString::fromUtf8("#selectPage{border-image: url(:/image/startMinimal.png);}"));
        uriDoc = new QPushButton(selectPage);
        uriDoc->setObjectName(QString::fromUtf8("uriDoc"));
        uriDoc->setGeometry(QRect(360, 418, 251, 281));
        uriDoc->setCursor(QCursor(Qt::PointingHandCursor));
        uriDoc->setStyleSheet(QString::fromUtf8("#uriDoc{\n"
"	background-color:transparent;\n"
"	border: transparent;\n"
"}\n"
"\n"
"#uriDoc:hover {\n"
"    border: 5px solid #BFB054;\n"
"	border-radius: 10px;\n"
"}\n"
""));
        uriDoc->setIconSize(QSize(13, 13));
        Username = new QPushButton(selectPage);
        Username->setObjectName(QString::fromUtf8("Username"));
        Username->setGeometry(QRect(36, 112, 251, 281));
        Username->setCursor(QCursor(Qt::PointingHandCursor));
        Username->setStyleSheet(QString::fromUtf8("#Username{\n"
"	background-color:transparent;\n"
"	border: transparent;\n"
"}\n"
"\n"
"#Username:hover {\n"
"    border: 5px solid #27754D;\n"
"	border-radius: 10px;\n"
"}\n"
""));
        newDoc = new QPushButton(selectPage);
        newDoc->setObjectName(QString::fromUtf8("newDoc"));
        newDoc->setGeometry(QRect(360, 112, 251, 281));
        newDoc->setCursor(QCursor(Qt::PointingHandCursor));
        newDoc->setStyleSheet(QString::fromUtf8("#newDoc{\n"
"	background-color:transparent;\n"
"	border: transparent;\n"
"}\n"
"\n"
"#newDoc:hover {\n"
"    border: 5px solid #962333;\n"
"	border-radius: 10px;\n"
"}\n"
""));
        newDoc->setIconSize(QSize(13, 13));
        listFiles = new QPushButton(selectPage);
        listFiles->setObjectName(QString::fromUtf8("listFiles"));
        listFiles->setGeometry(QRect(36, 418, 251, 281));
        listFiles->setCursor(QCursor(Qt::PointingHandCursor));
        listFiles->setStyleSheet(QString::fromUtf8("#listFiles{\n"
"	background-color:transparent;\n"
"	border: transparent\n"
"}\n"
"\n"
"#listFiles:hover {\n"
"    border: 5px solid #204177;\n"
"	border-radius: 10px;\n"
"}"));
        listFiles->setIconSize(QSize(13, 13));
        LogoutButton = new QPushButton(selectPage);
        LogoutButton->setObjectName(QString::fromUtf8("LogoutButton"));
        LogoutButton->setGeometry(QRect(247, 715, 159, 61));
        LogoutButton->setCursor(QCursor(Qt::PointingHandCursor));
        LogoutButton->setStyleSheet(QString::fromUtf8("#LogoutButton{	\n"
"background-color:transparent;\n"
"border: transparent;}\n"
"\n"
"#LogoutButton:hover {\n"
" border: 3px solid black;\n"
"border-radius: 5px;\n"
"}"));
        stackedWidget->addWidget(selectPage);
        openDocPage = new QWidget();
        openDocPage->setObjectName(QString::fromUtf8("openDocPage"));
        openDocPage->setStyleSheet(QString::fromUtf8("#openDocPage{border-image: url(:/image/fileWindow.png);}"));
        listWidget = new QListWidget(openDocPage);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(41, 220, 571, 481));
        listWidget->setStyleSheet(QString::fromUtf8("#listWidget{\n"
"	background-color:transparent;\n"
"	border: none;\n"
"	border-top: 2px solid lightgrey;\n"
"	padding: 20px;\n"
"}\n"
"\n"
"QToolTip { \n"
"	color: #000000; \n"
"	background-color: #FFF2BF; \n"
"	border: 0px; \n"
"}\n"
""));
        backButton = new QPushButton(openDocPage);
        backButton->setObjectName(QString::fromUtf8("backButton"));
        backButton->setGeometry(QRect(259, 715, 131, 61));
        backButton->setCursor(QCursor(Qt::PointingHandCursor));
        backButton->setStyleSheet(QString::fromUtf8("#backButton{	\n"
"background-color:transparent;\n"
"border: transparent;}\n"
"\n"
"#backButton:hover {\n"
" border: 3px solid black;\n"
"border-radius: 5px;\n"
"}"));
        noFile = new QLabel(openDocPage);
        noFile->setObjectName(QString::fromUtf8("noFile"));
        noFile->setGeometry(QRect(40, 440, 571, 41));
        QFont font;
        font.setFamily(QString::fromUtf8("Calibri"));
        font.setPointSize(20);
        font.setBold(true);
        font.setWeight(75);
        noFile->setFont(font);
        noFile->setStyleSheet(QString::fromUtf8("#noFile{\n"
"	color: grey\n"
"}"));
        noFile->setAlignment(Qt::AlignCenter);
        stackedWidget->addWidget(openDocPage);
        exitButton = new QPushButton(centralwidget);
        exitButton->setObjectName(QString::fromUtf8("exitButton"));
        exitButton->setGeometry(QRect(621, 2, 30, 24));
        exitButton->setCursor(QCursor(Qt::PointingHandCursor));
        exitButton->setStyleSheet(QString::fromUtf8("background-color: Transparent;\n"
"border: none;\n"
"background-repeat:no-repeat;\n"
""));
        exitButton->setIconSize(QSize(25, 25));
        MenuWindow->setCentralWidget(centralwidget);

        retranslateUi(MenuWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MenuWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MenuWindow)
    {
        MenuWindow->setWindowTitle(QCoreApplication::translate("MenuWindow", "MainWindow", nullptr));
        uriDoc->setText(QString());
        Username->setText(QString());
        newDoc->setText(QString());
        listFiles->setText(QString());
        LogoutButton->setText(QString());
        backButton->setText(QString());
        noFile->setText(QCoreApplication::translate("MenuWindow", "Non hai nessun documento da editare!", nullptr));
        exitButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MenuWindow: public Ui_MenuWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENUWINDOW_H

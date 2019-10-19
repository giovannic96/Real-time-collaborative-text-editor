/********************************************************************************
** Form generated from reading UI file 'startmenu.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STARTMENU_H
#define UI_STARTMENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StartMenu
{
public:
    QWidget *centralwidget;
    QLabel *version;
    QPushButton *exitButton;
    QPushButton *Username;
    QPushButton *LogoutButton;

    void setupUi(QMainWindow *StartMenu)
    {
        if (StartMenu->objectName().isEmpty())
            StartMenu->setObjectName(QString::fromUtf8("StartMenu"));
        StartMenu->resize(900, 525);
        StartMenu->setMinimumSize(QSize(900, 525));
        StartMenu->setMaximumSize(QSize(900, 525));
        StartMenu->setStyleSheet(QString::fromUtf8("#centralwidget {border-image: url(:/image/start.jpg);}"));
        centralwidget = new QWidget(StartMenu);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        version = new QLabel(centralwidget);
        version->setObjectName(QString::fromUtf8("version"));
        version->setGeometry(QRect(10, 500, 191, 16));
        QFont font;
        font.setFamily(QString::fromUtf8("MS Shell Dlg 2"));
        font.setItalic(true);
        version->setFont(font);
        version->setStyleSheet(QString::fromUtf8("color: #EAFF00;"));
        exitButton = new QPushButton(centralwidget);
        exitButton->setObjectName(QString::fromUtf8("exitButton"));
        exitButton->setGeometry(QRect(870, 0, 29, 23));
        exitButton->setCursor(QCursor(Qt::PointingHandCursor));
        exitButton->setStyleSheet(QString::fromUtf8("background-color: Transparent;\n"
"background-repeat:no-repeat;\n"
""));
        exitButton->setIconSize(QSize(25, 25));
        Username = new QPushButton(centralwidget);
        Username->setObjectName(QString::fromUtf8("Username"));
        Username->setGeometry(QRect(670, 180, 211, 23));
        Username->setStyleSheet(QString::fromUtf8("#Username{\n"
"	text-align: left;\n"
"	color: #0000FF;\n"
"	font-size: 20px;\n"
"	background-color:transparent;\n"
"	border: transparent;\n"
"}\n"
"#Username:hover{\n"
"	text-decoration: underline;\n"
"}\n"
""));
        LogoutButton = new QPushButton(centralwidget);
        LogoutButton->setObjectName(QString::fromUtf8("LogoutButton"));
        LogoutButton->setGeometry(QRect(670, 470, 131, 41));
        LogoutButton->setMaximumSize(QSize(16777199, 16777215));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        LogoutButton->setFont(font1);
        LogoutButton->setCursor(QCursor(Qt::PointingHandCursor));
        LogoutButton->setStyleSheet(QString::fromUtf8("#LogoutButton{\n"
"	color: rgb(255, 255, 255); \n"
"	background-color: rgb(20, 115, 255); \n"
"	font-size: 16px; \n"
"	border-radius: 20px; \n"
"	border: 3px solid rgb(28, 110, 164);\n"
"}\n"
"#LogoutButton:hover{\n"
"	background-color: rgb(28, 110, 164);\n"
"}\n"
"#LogoutButton:pressed{\n"
"	background-color: rgb(20, 78, 117);\n"
"}"));
        StartMenu->setCentralWidget(centralwidget);

        retranslateUi(StartMenu);

        QMetaObject::connectSlotsByName(StartMenu);
    } // setupUi

    void retranslateUi(QMainWindow *StartMenu)
    {
        StartMenu->setWindowTitle(QCoreApplication::translate("StartMenu", "MainWindow", nullptr));
        version->setText(QCoreApplication::translate("StartMenu", "QuestoTestoVieneSostituitoDaVersione", nullptr));
        exitButton->setText(QString());
        Username->setText(QCoreApplication::translate("StartMenu", "UsernameGoesHere", nullptr));
        LogoutButton->setText(QCoreApplication::translate("StartMenu", "Disconnettiti", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StartMenu: public Ui_StartMenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTMENU_H

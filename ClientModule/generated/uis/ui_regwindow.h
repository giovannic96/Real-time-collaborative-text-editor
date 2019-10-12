/********************************************************************************
** Form generated from reading UI file 'regwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGWINDOW_H
#define UI_REGWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RegWindow
{
public:
    QWidget *centralwidget;
    QLineEdit *LineEditPasswordForm;
    QPushButton *AccediButton;
    QPushButton *SignUpButton;
    QLabel *label;
    QPushButton *exitButton;
    QLineEdit *LineEditUsernameForm;
    QLabel *version;
    QLineEdit *LineEditMailForm;

    void setupUi(QMainWindow *RegWindow)
    {
        if (RegWindow->objectName().isEmpty())
            RegWindow->setObjectName(QString::fromUtf8("RegWindow"));
        RegWindow->resize(384, 667);
        RegWindow->setMinimumSize(QSize(384, 667));
        RegWindow->setMaximumSize(QSize(384, 667));
        centralwidget = new QWidget(RegWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        LineEditPasswordForm = new QLineEdit(centralwidget);
        LineEditPasswordForm->setObjectName(QString::fromUtf8("LineEditPasswordForm"));
        LineEditPasswordForm->setGeometry(QRect(50, 440, 281, 41));
        LineEditPasswordForm->setStyleSheet(QString::fromUtf8("background-color:rgb(255, 255, 255);\n"
"border: 1px solid gray;\n"
"border-radius: 15px;\n"
"padding: 0 8px;\n"
"selection-background-color: darkgray;\n"
"font-size: 16px;\n"
""));
        LineEditPasswordForm->setEchoMode(QLineEdit::Password);
        AccediButton = new QPushButton(centralwidget);
        AccediButton->setObjectName(QString::fromUtf8("AccediButton"));
        AccediButton->setGeometry(QRect(240, 280, 61, 23));
        QFont font;
        font.setPointSize(12);
        AccediButton->setFont(font);
        AccediButton->setStyleSheet(QString::fromUtf8("#AccediButton {\n"
"color: #0033CC;\n"
"background-color: Transparent;\n"
"background-repeat:no-repeat;\n"
"}\n"
"\n"
"#AccediButton:hover {\n"
"color: #0040FF;\n"
"text-decoration: underline;\n"
"}"));
        SignUpButton = new QPushButton(centralwidget);
        SignUpButton->setObjectName(QString::fromUtf8("SignUpButton"));
        SignUpButton->setGeometry(QRect(130, 506, 121, 41));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        SignUpButton->setFont(font1);
        SignUpButton->setStyleSheet(QString::fromUtf8("#SignUpButton{color: rgb(255, 255, 255); \n"
"background-color: rgb(20, 115, 255); \n"
"font-size: 16px; \n"
"border-radius: 20px; \n"
"border: 3px solid rgb(28, 110, 164);\n"
"}\n"
"#SignUpButton:hover{\n"
"background-color: rgb(28, 110, 164);\n"
"}\n"
"#SignUpButton:pressed{\n"
"background-color: rgb(20, 78, 117);\n"
"}"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(70, 280, 151, 21));
        label->setFont(font);
        exitButton = new QPushButton(centralwidget);
        exitButton->setObjectName(QString::fromUtf8("exitButton"));
        exitButton->setGeometry(QRect(340, 0, 41, 31));
        exitButton->setStyleSheet(QString::fromUtf8("background-color: Transparent;\n"
"background-repeat:no-repeat;\n"
""));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/image/basics-22-128.png"), QSize(), QIcon::Normal, QIcon::Off);
        exitButton->setIcon(icon);
        exitButton->setIconSize(QSize(25, 25));
        LineEditUsernameForm = new QLineEdit(centralwidget);
        LineEditUsernameForm->setObjectName(QString::fromUtf8("LineEditUsernameForm"));
        LineEditUsernameForm->setGeometry(QRect(50, 380, 281, 41));
        LineEditUsernameForm->setStyleSheet(QString::fromUtf8("background-color:rgb(255, 255, 255);\n"
"border: 1px solid gray;\n"
"border-radius: 15px;\n"
"padding: 0 8px;\n"
"selection-background-color: darkgray;\n"
"font-size: 16px;\n"
""));
        version = new QLabel(centralwidget);
        version->setObjectName(QString::fromUtf8("version"));
        version->setGeometry(QRect(10, 640, 191, 16));
        QFont font2;
        font2.setItalic(true);
        version->setFont(font2);
        version->setStyleSheet(QString::fromUtf8("color: #EAFF00;"));
        LineEditMailForm = new QLineEdit(centralwidget);
        LineEditMailForm->setObjectName(QString::fromUtf8("LineEditMailForm"));
        LineEditMailForm->setGeometry(QRect(50, 320, 281, 41));
        LineEditMailForm->setStyleSheet(QString::fromUtf8("background-color:rgb(255, 255, 255);\n"
"border: 1px solid gray;\n"
"border-radius: 15px;\n"
"padding: 0 8px;\n"
"selection-background-color: darkgray;\n"
"font-size: 16px;\n"
""));
        RegWindow->setCentralWidget(centralwidget);

        retranslateUi(RegWindow);

        QMetaObject::connectSlotsByName(RegWindow);
    } // setupUi

    void retranslateUi(QMainWindow *RegWindow)
    {
        RegWindow->setWindowTitle(QCoreApplication::translate("RegWindow", "MainWindow", nullptr));
        LineEditPasswordForm->setInputMask(QString());
        LineEditPasswordForm->setText(QString());
        LineEditPasswordForm->setPlaceholderText(QCoreApplication::translate("RegWindow", "Password", nullptr));
        AccediButton->setText(QCoreApplication::translate("RegWindow", "Accedi", nullptr));
        SignUpButton->setText(QCoreApplication::translate("RegWindow", "Registrati", nullptr));
        label->setText(QCoreApplication::translate("RegWindow", "Hai gi\303\240 un account?", nullptr));
        exitButton->setText(QString());
        LineEditUsernameForm->setText(QString());
        LineEditUsernameForm->setPlaceholderText(QCoreApplication::translate("RegWindow", "Username", nullptr));
        version->setText(QCoreApplication::translate("RegWindow", "QuestoTestoVieneSostituitoDaVersione", nullptr));
        LineEditMailForm->setText(QString());
        LineEditMailForm->setPlaceholderText(QCoreApplication::translate("RegWindow", "Email", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RegWindow: public Ui_RegWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGWINDOW_H

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
    QPushButton *SignUpButton;
    QPushButton *exitButton;
    QLineEdit *LineEditUsernameForm;
    QLabel *version;
    QLineEdit *LineEditMailForm;
    QPushButton *AccediButton;
    QLabel *label;

    void setupUi(QMainWindow *RegWindow)
    {
        if (RegWindow->objectName().isEmpty())
            RegWindow->setObjectName(QString::fromUtf8("RegWindow"));
        RegWindow->resize(900, 525);
        RegWindow->setMinimumSize(QSize(900, 525));
        RegWindow->setMaximumSize(QSize(900, 525));
        RegWindow->setStyleSheet(QString::fromUtf8("#centralwidget {border-image: url(:/image/registrazione.jpg);}"));
        centralwidget = new QWidget(RegWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setStyleSheet(QString::fromUtf8(""));
        LineEditPasswordForm = new QLineEdit(centralwidget);
        LineEditPasswordForm->setObjectName(QString::fromUtf8("LineEditPasswordForm"));
        LineEditPasswordForm->setGeometry(QRect(630, 274, 231, 31));
        LineEditPasswordForm->setStyleSheet(QString::fromUtf8("background-color:transparent;\n"
"border: transparent;\n"
"padding: 0 8px;\n"
"selection-background-color: darkgray;\n"
"font-size: 16px;\n"
""));
        LineEditPasswordForm->setEchoMode(QLineEdit::Password);
        SignUpButton = new QPushButton(centralwidget);
        SignUpButton->setObjectName(QString::fromUtf8("SignUpButton"));
        SignUpButton->setGeometry(QRect(740, 320, 121, 41));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        SignUpButton->setFont(font);
        SignUpButton->setCursor(QCursor(Qt::PointingHandCursor));
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
        exitButton = new QPushButton(centralwidget);
        exitButton->setObjectName(QString::fromUtf8("exitButton"));
        exitButton->setGeometry(QRect(870, 0, 29, 23));
        exitButton->setCursor(QCursor(Qt::PointingHandCursor));
        exitButton->setStyleSheet(QString::fromUtf8("background-color: Transparent;\n"
"background-repeat:no-repeat;\n"
""));
        exitButton->setIconSize(QSize(25, 25));
        LineEditUsernameForm = new QLineEdit(centralwidget);
        LineEditUsernameForm->setObjectName(QString::fromUtf8("LineEditUsernameForm"));
        LineEditUsernameForm->setGeometry(QRect(630, 186, 231, 31));
        LineEditUsernameForm->setStyleSheet(QString::fromUtf8("background-color:transparent;\n"
"border: transparent;\n"
"padding: 0 8px;\n"
"selection-background-color: darkgray;\n"
"font-size: 16px;\n"
""));
        version = new QLabel(centralwidget);
        version->setObjectName(QString::fromUtf8("version"));
        version->setGeometry(QRect(10, 500, 191, 16));
        QFont font1;
        font1.setItalic(true);
        version->setFont(font1);
        version->setStyleSheet(QString::fromUtf8("color: #EAFF00;"));
        LineEditMailForm = new QLineEdit(centralwidget);
        LineEditMailForm->setObjectName(QString::fromUtf8("LineEditMailForm"));
        LineEditMailForm->setGeometry(QRect(630, 230, 231, 31));
        LineEditMailForm->setStyleSheet(QString::fromUtf8("background-color:transparent;\n"
"border: transparent;\n"
"padding: 0 8px;\n"
"selection-background-color: darkgray;\n"
"font-size: 16px;\n"
""));
        AccediButton = new QPushButton(centralwidget);
        AccediButton->setObjectName(QString::fromUtf8("AccediButton"));
        AccediButton->setGeometry(QRect(760, 480, 81, 23));
        QFont font2;
        font2.setPointSize(12);
        AccediButton->setFont(font2);
        AccediButton->setCursor(QCursor(Qt::PointingHandCursor));
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
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(610, 480, 151, 21));
        label->setFont(font2);
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
        SignUpButton->setText(QCoreApplication::translate("RegWindow", "Registrati", nullptr));
        exitButton->setText(QString());
        LineEditUsernameForm->setText(QString());
        LineEditUsernameForm->setPlaceholderText(QCoreApplication::translate("RegWindow", "Username", nullptr));
        version->setText(QCoreApplication::translate("RegWindow", "QuestoTestoVieneSostituitoDaVersione", nullptr));
        LineEditMailForm->setText(QString());
        LineEditMailForm->setPlaceholderText(QCoreApplication::translate("RegWindow", "Email", nullptr));
        AccediButton->setText(QCoreApplication::translate("RegWindow", "Accedi", nullptr));
        label->setText(QCoreApplication::translate("RegWindow", "Hai gi\303\240 un account?", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RegWindow: public Ui_RegWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGWINDOW_H

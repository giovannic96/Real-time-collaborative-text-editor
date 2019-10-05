/********************************************************************************
** Form generated from reading UI file 'loginwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWINDOW_H
#define UI_LOGINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginWindow
{
public:
    QWidget *centralwidget;
    QPushButton *exitButton;
    QLineEdit *LineEditUsernameForm;
    QLineEdit *LineEditPasswordForm;
    QPushButton *LoginButton;
    QLabel *version;
    QPushButton *ForgotPasswordButton;
    QPushButton *RegistratiButton;
    QLabel *label;
    QLabel *label_status;

    void setupUi(QMainWindow *LoginWindow)
    {
        if (LoginWindow->objectName().isEmpty())
            LoginWindow->setObjectName(QString::fromUtf8("LoginWindow"));
        LoginWindow->resize(384, 667);
        LoginWindow->setMinimumSize(QSize(384, 667));
        LoginWindow->setMaximumSize(QSize(384, 667));
        centralwidget = new QWidget(LoginWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
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
        LineEditUsernameForm->setGeometry(QRect(50, 320, 281, 41));
        LineEditUsernameForm->setStyleSheet(QString::fromUtf8("background-color:rgb(255, 255, 255);\n"
"border: 1px solid gray;\n"
"border-radius: 15px;\n"
"padding: 0 8px;\n"
"selection-background-color: darkgray;\n"
"font-size: 16px;\n"
""));
        LineEditPasswordForm = new QLineEdit(centralwidget);
        LineEditPasswordForm->setObjectName(QString::fromUtf8("LineEditPasswordForm"));
        LineEditPasswordForm->setGeometry(QRect(50, 380, 281, 41));
        LineEditPasswordForm->setStyleSheet(QString::fromUtf8("background-color:rgb(255, 255, 255);\n"
"border: 1px solid gray;\n"
"border-radius: 15px;\n"
"padding: 0 8px;\n"
"selection-background-color: darkgray;\n"
"font-size: 16px;\n"
""));
        LineEditPasswordForm->setEchoMode(QLineEdit::Password);
        LoginButton = new QPushButton(centralwidget);
        LoginButton->setObjectName(QString::fromUtf8("LoginButton"));
        LoginButton->setGeometry(QRect(130, 447, 121, 41));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        LoginButton->setFont(font);
        LoginButton->setStyleSheet(QString::fromUtf8("#LoginButton{color: rgb(255, 255, 255); \n"
"background-color: rgb(20, 115, 255); \n"
"font-size: 16px; \n"
"border-radius: 20px; \n"
"border: 3px solid rgb(28, 110, 164);\n"
"}\n"
"#LoginButton:hover{\n"
"background-color: rgb(28, 110, 164);\n"
"}\n"
"#LoginButton:pressed{\n"
"background-color: rgb(20, 78, 117);\n"
"}"));
        version = new QLabel(centralwidget);
        version->setObjectName(QString::fromUtf8("version"));
        version->setGeometry(QRect(10, 640, 191, 16));
        QFont font1;
        font1.setItalic(true);
        version->setFont(font1);
        version->setStyleSheet(QString::fromUtf8("color: #EAFF00;"));
        ForgotPasswordButton = new QPushButton(centralwidget);
        ForgotPasswordButton->setObjectName(QString::fromUtf8("ForgotPasswordButton"));
        ForgotPasswordButton->setGeometry(QRect(100, 507, 181, 21));
        QFont font2;
        font2.setPointSize(10);
        ForgotPasswordButton->setFont(font2);
        ForgotPasswordButton->setStyleSheet(QString::fromUtf8("#ForgotPasswordButton {\n"
"color: #505050;\n"
"background-color: Transparent;\n"
"background-repeat:no-repeat;\n"
"}\n"
"\n"
"#ForgotPasswordButton:hover {\n"
"color: #505050;\n"
"background-color: Transparent;\n"
"background-repeat:no-repeat;\n"
"text-decoration: underline;\n"
"}"));
        RegistratiButton = new QPushButton(centralwidget);
        RegistratiButton->setObjectName(QString::fromUtf8("RegistratiButton"));
        RegistratiButton->setGeometry(QRect(200, 280, 81, 23));
        QFont font3;
        font3.setPointSize(12);
        RegistratiButton->setFont(font3);
        RegistratiButton->setStyleSheet(QString::fromUtf8("#RegistratiButton {\n"
"color: #0033CC;\n"
"background-color: Transparent;\n"
"background-repeat:no-repeat;\n"
"}\n"
"\n"
"#RegistratiButton:hover {\n"
"color: #0040FF;\n"
"text-decoration: underline;\n"
"}"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(110, 280, 91, 21));
        label->setFont(font3);
        label_status = new QLabel(centralwidget);
        label_status->setObjectName(QString::fromUtf8("label_status"));
        label_status->setGeometry(QRect(40, 190, 55, 16));
        LoginWindow->setCentralWidget(centralwidget);

        retranslateUi(LoginWindow);

        QMetaObject::connectSlotsByName(LoginWindow);
    } // setupUi

    void retranslateUi(QMainWindow *LoginWindow)
    {
        LoginWindow->setWindowTitle(QCoreApplication::translate("LoginWindow", "LoginWindow", nullptr));
        exitButton->setText(QString());
        LineEditUsernameForm->setText(QString());
        LineEditUsernameForm->setPlaceholderText(QCoreApplication::translate("LoginWindow", "Username", nullptr));
        LineEditPasswordForm->setInputMask(QString());
        LineEditPasswordForm->setText(QString());
        LineEditPasswordForm->setPlaceholderText(QCoreApplication::translate("LoginWindow", "Password", nullptr));
        LoginButton->setText(QCoreApplication::translate("LoginWindow", "Accedi", nullptr));
        version->setText(QCoreApplication::translate("LoginWindow", "QuestoTestoVieneSostituitoDaVersione", nullptr));
        ForgotPasswordButton->setText(QCoreApplication::translate("LoginWindow", "Password dimenticata?", nullptr));
        RegistratiButton->setText(QCoreApplication::translate("LoginWindow", "Registrati", nullptr));
        label->setText(QCoreApplication::translate("LoginWindow", "Sei nuovo?", nullptr));
        label_status->setText(QCoreApplication::translate("LoginWindow", "Status", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginWindow: public Ui_LoginWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWINDOW_H

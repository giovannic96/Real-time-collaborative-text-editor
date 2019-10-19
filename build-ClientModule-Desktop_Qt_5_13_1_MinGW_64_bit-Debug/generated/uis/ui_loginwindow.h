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
    QLineEdit *LineEditUsernameForm;
    QLineEdit *LineEditPasswordForm;
    QPushButton *LoginButton;
    QLabel *version;
    QPushButton *ForgotPasswordButton;
    QPushButton *RegistratiButton;
    QLabel *label;
    QLabel *label_status;
    QPushButton *exitButton;
    QPushButton *LoginAdmin;

    void setupUi(QMainWindow *LoginWindow)
    {
        if (LoginWindow->objectName().isEmpty())
            LoginWindow->setObjectName(QString::fromUtf8("LoginWindow"));
        LoginWindow->resize(900, 525);
        LoginWindow->setMinimumSize(QSize(900, 525));
        LoginWindow->setMaximumSize(QSize(900, 525));
        LoginWindow->setStyleSheet(QString::fromUtf8("#centralwidget {border-image: url(:/image/accesso.jpg);}"));
        centralwidget = new QWidget(LoginWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        LineEditUsernameForm = new QLineEdit(centralwidget);
        LineEditUsernameForm->setObjectName(QString::fromUtf8("LineEditUsernameForm"));
        LineEditUsernameForm->setGeometry(QRect(630, 216, 231, 31));
        LineEditUsernameForm->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"border-radius: 15px;\n"
"padding: 0 8px;\n"
"selection-background-color: darkgray;\n"
"font-size: 16px;\n"
""));
        LineEditPasswordForm = new QLineEdit(centralwidget);
        LineEditPasswordForm->setObjectName(QString::fromUtf8("LineEditPasswordForm"));
        LineEditPasswordForm->setGeometry(QRect(630, 263, 231, 31));
        LineEditPasswordForm->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"border-radius: 15px;\n"
"padding: 0 8px;\n"
"selection-background-color: darkgray;\n"
"font-size: 16px;\n"
""));
        LineEditPasswordForm->setEchoMode(QLineEdit::Password);
        LoginButton = new QPushButton(centralwidget);
        LoginButton->setObjectName(QString::fromUtf8("LoginButton"));
        LoginButton->setGeometry(QRect(740, 310, 121, 41));
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
        version->setGeometry(QRect(10, 500, 191, 16));
        QFont font1;
        font1.setItalic(true);
        version->setFont(font1);
        version->setStyleSheet(QString::fromUtf8("color: #EAFF00;"));
        ForgotPasswordButton = new QPushButton(centralwidget);
        ForgotPasswordButton->setObjectName(QString::fromUtf8("ForgotPasswordButton"));
        ForgotPasswordButton->setGeometry(QRect(640, 360, 181, 21));
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
        RegistratiButton->setGeometry(QRect(740, 480, 81, 23));
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
        label->setGeometry(QRect(650, 480, 91, 21));
        label->setFont(font3);
        label_status = new QLabel(centralwidget);
        label_status->setObjectName(QString::fromUtf8("label_status"));
        label_status->setGeometry(QRect(480, 490, 55, 16));
        label_status->setStyleSheet(QString::fromUtf8("color: #EAFF00;"));
        exitButton = new QPushButton(centralwidget);
        exitButton->setObjectName(QString::fromUtf8("exitButton"));
        exitButton->setGeometry(QRect(870, 0, 29, 23));
        exitButton->setCursor(QCursor(Qt::PointingHandCursor));
        exitButton->setStyleSheet(QString::fromUtf8("background-color: Transparent;\n"
"background-repeat:no-repeat;\n"
""));
        exitButton->setIconSize(QSize(25, 25));
        LoginAdmin = new QPushButton(centralwidget);
        LoginAdmin->setObjectName(QString::fromUtf8("LoginAdmin"));
        LoginAdmin->setGeometry(QRect(630, 400, 201, 41));
        LoginAdmin->setFont(font);
        LoginAdmin->setStyleSheet(QString::fromUtf8("#LoginAdmin{color: rgb(255, 255, 255); \n"
"background-color: rgb(255, 0, 0); \n"
"font-size: 16px; \n"
"border-radius: 20px; \n"
"border: 3px solid #B30000;\n"
"}\n"
"#LoginAdmin:hover{\n"
"background-color: #B30000;\n"
"}\n"
"#LoginAdmin:pressed{\n"
"background-color: #800000;\n"
"}"));
        LoginWindow->setCentralWidget(centralwidget);

        retranslateUi(LoginWindow);

        QMetaObject::connectSlotsByName(LoginWindow);
    } // setupUi

    void retranslateUi(QMainWindow *LoginWindow)
    {
        LoginWindow->setWindowTitle(QCoreApplication::translate("LoginWindow", "LoginWindow", nullptr));
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
        exitButton->setText(QString());
        LoginAdmin->setText(QCoreApplication::translate("LoginWindow", "Accedi (Admin Mode)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginWindow: public Ui_LoginWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWINDOW_H

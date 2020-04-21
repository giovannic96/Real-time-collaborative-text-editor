/********************************************************************************
** Form generated from reading UI file 'startwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STARTWINDOW_H
#define UI_STARTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StartWindow
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *loginPage;
    QPushButton *LoginButton;
    QLineEdit *LoginPasswordForm;
    QPushButton *RegisterButton;
    QLineEdit *LoginUsernameForm;
    QLabel *label_status;
    QPushButton *eyeButton;
    QWidget *regPage;
    QLineEdit *RegUsernameForm;
    QLineEdit *RegMailForm;
    QPushButton *SignUpButton;
    QPushButton *AccediButton;
    QLineEdit *RegPasswordForm;
    QLabel *passERR;
    QLabel *usernameERR;
    QLabel *mailERR;
    QPushButton *exitButton;
    QLabel *version;

    void setupUi(QMainWindow *StartWindow)
    {
        if (StartWindow->objectName().isEmpty())
            StartWindow->setObjectName(QString::fromUtf8("StartWindow"));
        StartWindow->resize(1100, 641);
        StartWindow->setMinimumSize(QSize(900, 525));
        StartWindow->setMaximumSize(QSize(1100, 641));
        centralwidget = new QWidget(StartWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(0, 0, 1100, 641));
        loginPage = new QWidget();
        loginPage->setObjectName(QString::fromUtf8("loginPage"));
        loginPage->setStyleSheet(QString::fromUtf8("#loginPage {border-image: url(:/image/accesso.png);}"));
        LoginButton = new QPushButton(loginPage);
        LoginButton->setObjectName(QString::fromUtf8("LoginButton"));
        LoginButton->setGeometry(QRect(836, 490, 121, 41));
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
        LoginPasswordForm = new QLineEdit(loginPage);
        LoginPasswordForm->setObjectName(QString::fromUtf8("LoginPasswordForm"));
        LoginPasswordForm->setGeometry(QRect(787, 363, 231, 30));
        QFont font1;
        LoginPasswordForm->setFont(font1);
        LoginPasswordForm->setContextMenuPolicy(Qt::NoContextMenu);
        LoginPasswordForm->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"border-radius: 15px;\n"
"padding: 0 8px;\n"
"selection-background-color: darkgray;\n"
"font-size: 18px;\n"
""));
        LoginPasswordForm->setEchoMode(QLineEdit::Password);
        RegisterButton = new QPushButton(loginPage);
        RegisterButton->setObjectName(QString::fromUtf8("RegisterButton"));
        RegisterButton->setGeometry(QRect(525, 90, 155, 35));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Calibri"));
        font2.setPointSize(16);
        font2.setBold(true);
        font2.setWeight(75);
        RegisterButton->setFont(font2);
        RegisterButton->setCursor(QCursor(Qt::PointingHandCursor));
        RegisterButton->setLayoutDirection(Qt::LeftToRight);
        RegisterButton->setAutoFillBackground(false);
        RegisterButton->setStyleSheet(QString::fromUtf8("#RegisterButton {\n"
"border:none;\n"
"background-image:url(:/image/registratiButton1.png)\n"
"}\n"
"\n"
"#RegisterButton:hover {\n"
"border:none;\n"
"background-image:url(:/image/registratiButton2.png)\n"
"}"));
        LoginUsernameForm = new QLineEdit(loginPage);
        LoginUsernameForm->setObjectName(QString::fromUtf8("LoginUsernameForm"));
        LoginUsernameForm->setGeometry(QRect(787, 303, 231, 30));
        LoginUsernameForm->setFont(font1);
        LoginUsernameForm->setContextMenuPolicy(Qt::NoContextMenu);
        LoginUsernameForm->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"border-radius: 15px;\n"
"padding: 0 8px;\n"
"selection-background-color: darkgray;\n"
"font-size: 18px;\n"
""));
        label_status = new QLabel(loginPage);
        label_status->setObjectName(QString::fromUtf8("label_status"));
        label_status->setGeometry(QRect(10, 604, 81, 16));
        label_status->setStyleSheet(QString::fromUtf8("color: #EAFF00;"));
        eyeButton = new QPushButton(loginPage);
        eyeButton->setObjectName(QString::fromUtf8("eyeButton"));
        eyeButton->setGeometry(QRect(1025, 370, 20, 20));
        eyeButton->setMinimumSize(QSize(20, 20));
        eyeButton->setMaximumSize(QSize(20, 20));
        eyeButton->setStyleSheet(QString::fromUtf8("#eyeButton{\n"
"	border-image: url(:image/showPassword.png);\n"
"}"));
        eyeButton->setCheckable(true);
        stackedWidget->addWidget(loginPage);
        regPage = new QWidget();
        regPage->setObjectName(QString::fromUtf8("regPage"));
        regPage->setStyleSheet(QString::fromUtf8("#regPage {border-image: url(:/image/registrazione.png);}"));
        RegUsernameForm = new QLineEdit(regPage);
        RegUsernameForm->setObjectName(QString::fromUtf8("RegUsernameForm"));
        RegUsernameForm->setGeometry(QRect(791, 302, 231, 30));
        RegUsernameForm->setContextMenuPolicy(Qt::NoContextMenu);
        RegUsernameForm->setStyleSheet(QString::fromUtf8("background-color:transparent;\n"
"border: transparent;\n"
"padding: 0 8px;\n"
"selection-background-color: darkgray;\n"
"font-size: 18px;\n"
""));
        RegMailForm = new QLineEdit(regPage);
        RegMailForm->setObjectName(QString::fromUtf8("RegMailForm"));
        RegMailForm->setGeometry(QRect(791, 419, 231, 30));
        RegMailForm->setContextMenuPolicy(Qt::NoContextMenu);
        RegMailForm->setStyleSheet(QString::fromUtf8("background-color:transparent;\n"
"border: transparent;\n"
"padding: 0 8px;\n"
"selection-background-color: darkgray;\n"
"font-size: 18px;\n"
""));
        SignUpButton = new QPushButton(regPage);
        SignUpButton->setObjectName(QString::fromUtf8("SignUpButton"));
        SignUpButton->setGeometry(QRect(836, 490, 121, 41));
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
        AccediButton = new QPushButton(regPage);
        AccediButton->setObjectName(QString::fromUtf8("AccediButton"));
        AccediButton->setGeometry(QRect(580, 30, 100, 35));
        AccediButton->setFont(font2);
        AccediButton->setCursor(QCursor(Qt::PointingHandCursor));
        AccediButton->setStyleSheet(QString::fromUtf8("#AccediButton {\n"
"border:none;\n"
"background-image:url(:/image/accediButton1.png)\n"
"}\n"
"\n"
"#AccediButton:hover {\n"
"border:none;\n"
"background-image:url(:/image/accediButton2.png)\n"
"}"));
        RegPasswordForm = new QLineEdit(regPage);
        RegPasswordForm->setObjectName(QString::fromUtf8("RegPasswordForm"));
        RegPasswordForm->setGeometry(QRect(791, 362, 231, 30));
        RegPasswordForm->setContextMenuPolicy(Qt::NoContextMenu);
        RegPasswordForm->setStyleSheet(QString::fromUtf8("background-color:transparent;\n"
"border: transparent;\n"
"padding: 0 8px;\n"
"selection-background-color: darkgray;\n"
"font-size: 18px;\n"
""));
        RegPasswordForm->setEchoMode(QLineEdit::Password);
        passERR = new QLabel(regPage);
        passERR->setObjectName(QString::fromUtf8("passERR"));
        passERR->setGeometry(QRect(800, 401, 241, 21));
        passERR->setStyleSheet(QString::fromUtf8("background: #FFF2BF"));
        usernameERR = new QLabel(regPage);
        usernameERR->setObjectName(QString::fromUtf8("usernameERR"));
        usernameERR->setGeometry(QRect(800, 345, 241, 21));
        usernameERR->setStyleSheet(QString::fromUtf8("background: #FFF2BF"));
        mailERR = new QLabel(regPage);
        mailERR->setObjectName(QString::fromUtf8("mailERR"));
        mailERR->setGeometry(QRect(801, 458, 241, 21));
        mailERR->setStyleSheet(QString::fromUtf8("background: #FFF2BF"));
        stackedWidget->addWidget(regPage);
        exitButton = new QPushButton(centralwidget);
        exitButton->setObjectName(QString::fromUtf8("exitButton"));
        exitButton->setGeometry(QRect(1068, 2, 30, 24));
        exitButton->setCursor(QCursor(Qt::PointingHandCursor));
        exitButton->setStyleSheet(QString::fromUtf8("background-color: Transparent;\n"
"background-repeat:no-repeat;\n"
""));
        exitButton->setIconSize(QSize(25, 25));
        version = new QLabel(centralwidget);
        version->setObjectName(QString::fromUtf8("version"));
        version->setGeometry(QRect(10, 620, 191, 16));
        QFont font3;
        font3.setItalic(true);
        version->setFont(font3);
        version->setStyleSheet(QString::fromUtf8("color: #EAFF00;"));
        StartWindow->setCentralWidget(centralwidget);
        QWidget::setTabOrder(RegUsernameForm, RegPasswordForm);
        QWidget::setTabOrder(RegPasswordForm, RegMailForm);
        QWidget::setTabOrder(RegMailForm, LoginUsernameForm);
        QWidget::setTabOrder(LoginUsernameForm, LoginPasswordForm);
        QWidget::setTabOrder(LoginPasswordForm, LoginButton);
        QWidget::setTabOrder(LoginButton, RegisterButton);
        QWidget::setTabOrder(RegisterButton, SignUpButton);
        QWidget::setTabOrder(SignUpButton, AccediButton);
        QWidget::setTabOrder(AccediButton, exitButton);

        retranslateUi(StartWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(StartWindow);
    } // setupUi

    void retranslateUi(QMainWindow *StartWindow)
    {
        StartWindow->setWindowTitle(QCoreApplication::translate("StartWindow", "MainWindow", nullptr));
        LoginButton->setText(QCoreApplication::translate("StartWindow", "Accedi", nullptr));
        LoginPasswordForm->setInputMask(QString());
        LoginPasswordForm->setText(QString());
        LoginPasswordForm->setPlaceholderText(QCoreApplication::translate("StartWindow", "Password", nullptr));
        RegisterButton->setText(QString());
        LoginUsernameForm->setText(QString());
        LoginUsernameForm->setPlaceholderText(QCoreApplication::translate("StartWindow", "Username", nullptr));
        label_status->setText(QCoreApplication::translate("StartWindow", "Status", nullptr));
        eyeButton->setText(QString());
        RegUsernameForm->setText(QString());
        RegUsernameForm->setPlaceholderText(QCoreApplication::translate("StartWindow", "Username", nullptr));
        RegMailForm->setText(QString());
        RegMailForm->setPlaceholderText(QCoreApplication::translate("StartWindow", "Email", nullptr));
        SignUpButton->setText(QCoreApplication::translate("StartWindow", "Registrati", nullptr));
        AccediButton->setText(QString());
        RegPasswordForm->setInputMask(QString());
        RegPasswordForm->setText(QString());
        RegPasswordForm->setPlaceholderText(QCoreApplication::translate("StartWindow", "Password", nullptr));
        passERR->setText(QCoreApplication::translate("StartWindow", "<html><head/><body><p align=\"center\">La password deve contenere almeno 6 caratteri</p></body></html>", nullptr));
        usernameERR->setText(QCoreApplication::translate("StartWindow", "<html><head/><body><p align=\"center\">Inserire un username</p></body></html>", nullptr));
        mailERR->setText(QCoreApplication::translate("StartWindow", "<html><head/><body><p align=\"center\">Inserire una mail valida</p></body></html>", nullptr));
        exitButton->setText(QString());
        version->setText(QCoreApplication::translate("StartWindow", "QuestoTestoVieneSostituitoDaVersione", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StartWindow: public Ui_StartWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTWINDOW_H

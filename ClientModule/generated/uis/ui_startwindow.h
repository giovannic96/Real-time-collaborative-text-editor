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
#include <QtGui/QIcon>
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
    QPushButton *LoginAdmin;
    QLabel *Seinuovo;
    QPushButton *LoginButton;
    QLineEdit *LoginPasswordForm;
    QPushButton *RegisterButton;
    QPushButton *ForgotPasswordButton;
    QLineEdit *LoginUsernameForm;
    QLabel *label_status;
    QWidget *regPage;
    QLabel *Haigiaaccount;
    QLineEdit *RegUsernameForm;
    QLineEdit *RegMailForm;
    QPushButton *SignUpButton;
    QPushButton *AccediButton;
    QLineEdit *RegPasswordForm;
    QWidget *menuPage;
    QPushButton *LogoutButton;
    QPushButton *openEditor;
    QPushButton *Username;
    QPushButton *exitButton;
    QLabel *version;

    void setupUi(QMainWindow *StartWindow)
    {
        if (StartWindow->objectName().isEmpty())
            StartWindow->setObjectName(QString::fromUtf8("StartWindow"));
        StartWindow->resize(900, 525);
        StartWindow->setMinimumSize(QSize(900, 525));
        StartWindow->setMaximumSize(QSize(900, 525));
        centralwidget = new QWidget(StartWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(0, 0, 900, 525));
        loginPage = new QWidget();
        loginPage->setObjectName(QString::fromUtf8("loginPage"));
        loginPage->setStyleSheet(QString::fromUtf8("#loginPage {border-image: url(:/image/accesso.png);}"));
        LoginAdmin = new QPushButton(loginPage);
        LoginAdmin->setObjectName(QString::fromUtf8("LoginAdmin"));
        LoginAdmin->setGeometry(QRect(510, 400, 201, 41));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
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
        Seinuovo = new QLabel(loginPage);
        Seinuovo->setObjectName(QString::fromUtf8("Seinuovo"));
        Seinuovo->setGeometry(QRect(650, 480, 91, 21));
        QFont font1;
        font1.setPointSize(12);
        Seinuovo->setFont(font1);
        LoginButton = new QPushButton(loginPage);
        LoginButton->setObjectName(QString::fromUtf8("LoginButton"));
        LoginButton->setGeometry(QRect(740, 310, 121, 41));
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
        LoginPasswordForm->setGeometry(QRect(641, 258, 231, 31));
        LoginPasswordForm->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"border-radius: 15px;\n"
"padding: 0 8px;\n"
"selection-background-color: darkgray;\n"
"font-size: 16px;\n"
""));
        LoginPasswordForm->setEchoMode(QLineEdit::Password);
        RegisterButton = new QPushButton(loginPage);
        RegisterButton->setObjectName(QString::fromUtf8("RegisterButton"));
        RegisterButton->setGeometry(QRect(740, 480, 81, 23));
        RegisterButton->setFont(font1);
        RegisterButton->setStyleSheet(QString::fromUtf8("#RegistratiButton {\n"
"color: #0033CC;\n"
"background-color: Transparent;\n"
"background-repeat:no-repeat;\n"
"}\n"
"\n"
"#RegistratiButton:hover {\n"
"color: #0040FF;\n"
"text-decoration: underline;\n"
"}"));
        ForgotPasswordButton = new QPushButton(loginPage);
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
        LoginUsernameForm = new QLineEdit(loginPage);
        LoginUsernameForm->setObjectName(QString::fromUtf8("LoginUsernameForm"));
        LoginUsernameForm->setGeometry(QRect(641, 210, 231, 31));
        LoginUsernameForm->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"border-radius: 15px;\n"
"padding: 0 8px;\n"
"selection-background-color: darkgray;\n"
"font-size: 16px;\n"
""));
        label_status = new QLabel(loginPage);
        label_status->setObjectName(QString::fromUtf8("label_status"));
        label_status->setGeometry(QRect(10, 487, 81, 16));
        label_status->setStyleSheet(QString::fromUtf8("color: #EAFF00;"));
        stackedWidget->addWidget(loginPage);
        regPage = new QWidget();
        regPage->setObjectName(QString::fromUtf8("regPage"));
        regPage->setStyleSheet(QString::fromUtf8("#regPage {border-image: url(:/image/registrazione.png);}"));
        Haigiaaccount = new QLabel(regPage);
        Haigiaaccount->setObjectName(QString::fromUtf8("Haigiaaccount"));
        Haigiaaccount->setGeometry(QRect(610, 480, 151, 21));
        Haigiaaccount->setFont(font1);
        RegUsernameForm = new QLineEdit(regPage);
        RegUsernameForm->setObjectName(QString::fromUtf8("RegUsernameForm"));
        RegUsernameForm->setGeometry(QRect(641, 210, 231, 31));
        RegUsernameForm->setStyleSheet(QString::fromUtf8("background-color:transparent;\n"
"border: transparent;\n"
"padding: 0 8px;\n"
"selection-background-color: darkgray;\n"
"font-size: 16px;\n"
""));
        RegMailForm = new QLineEdit(regPage);
        RegMailForm->setObjectName(QString::fromUtf8("RegMailForm"));
        RegMailForm->setGeometry(QRect(641, 307, 231, 31));
        RegMailForm->setStyleSheet(QString::fromUtf8("background-color:transparent;\n"
"border: transparent;\n"
"padding: 0 8px;\n"
"selection-background-color: darkgray;\n"
"font-size: 16px;\n"
""));
        SignUpButton = new QPushButton(regPage);
        SignUpButton->setObjectName(QString::fromUtf8("SignUpButton"));
        SignUpButton->setGeometry(QRect(740, 370, 121, 41));
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
        AccediButton->setGeometry(QRect(760, 480, 81, 23));
        AccediButton->setFont(font1);
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
        RegPasswordForm = new QLineEdit(regPage);
        RegPasswordForm->setObjectName(QString::fromUtf8("RegPasswordForm"));
        RegPasswordForm->setGeometry(QRect(641, 258, 231, 31));
        RegPasswordForm->setStyleSheet(QString::fromUtf8("background-color:transparent;\n"
"border: transparent;\n"
"padding: 0 8px;\n"
"selection-background-color: darkgray;\n"
"font-size: 16px;\n"
""));
        RegPasswordForm->setEchoMode(QLineEdit::Password);
        stackedWidget->addWidget(regPage);
        menuPage = new QWidget();
        menuPage->setObjectName(QString::fromUtf8("menuPage"));
        menuPage->setStyleSheet(QString::fromUtf8("#menuPage {border-image: url(:/image/start.png);}"));
        LogoutButton = new QPushButton(menuPage);
        LogoutButton->setObjectName(QString::fromUtf8("LogoutButton"));
        LogoutButton->setGeometry(QRect(670, 470, 131, 41));
        LogoutButton->setMaximumSize(QSize(16777199, 16777215));
        LogoutButton->setFont(font);
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
        openEditor = new QPushButton(menuPage);
        openEditor->setObjectName(QString::fromUtf8("openEditor"));
        openEditor->setGeometry(QRect(600, 290, 131, 31));
        openEditor->setStyleSheet(QString::fromUtf8("#openEditor{\n"
"	text-align: left;\n"
"	color: #0000FF;\n"
"	font-size: 20px;\n"
"	background-color:transparent;\n"
"	border: transparent;\n"
"}\n"
"#openEditor:hover{\n"
"	text-decoration: underline;\n"
"}\n"
""));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/image/397435-200.png"), QSize(), QIcon::Normal, QIcon::Off);
        openEditor->setIcon(icon);
        openEditor->setIconSize(QSize(13, 13));
        Username = new QPushButton(menuPage);
        Username->setObjectName(QString::fromUtf8("Username"));
        Username->setGeometry(QRect(670, 200, 211, 23));
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
        stackedWidget->addWidget(menuPage);
        exitButton = new QPushButton(centralwidget);
        exitButton->setObjectName(QString::fromUtf8("exitButton"));
        exitButton->setGeometry(QRect(870, 0, 29, 23));
        exitButton->setCursor(QCursor(Qt::PointingHandCursor));
        exitButton->setStyleSheet(QString::fromUtf8("background-color: Transparent;\n"
"background-repeat:no-repeat;\n"
""));
        exitButton->setIconSize(QSize(25, 25));
        version = new QLabel(centralwidget);
        version->setObjectName(QString::fromUtf8("version"));
        version->setGeometry(QRect(10, 503, 191, 16));
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
        QWidget::setTabOrder(LoginButton, ForgotPasswordButton);
        QWidget::setTabOrder(ForgotPasswordButton, RegisterButton);
        QWidget::setTabOrder(RegisterButton, LogoutButton);
        QWidget::setTabOrder(LogoutButton, SignUpButton);
        QWidget::setTabOrder(SignUpButton, AccediButton);
        QWidget::setTabOrder(AccediButton, exitButton);
        QWidget::setTabOrder(exitButton, LoginAdmin);
        QWidget::setTabOrder(LoginAdmin, Username);
        QWidget::setTabOrder(Username, openEditor);

        retranslateUi(StartWindow);

        QMetaObject::connectSlotsByName(StartWindow);
    } // setupUi

    void retranslateUi(QMainWindow *StartWindow)
    {
        StartWindow->setWindowTitle(QCoreApplication::translate("StartWindow", "MainWindow", nullptr));
        LoginAdmin->setText(QCoreApplication::translate("StartWindow", "Accedi (Admin Mode)", nullptr));
        Seinuovo->setText(QCoreApplication::translate("StartWindow", "Sei nuovo?", nullptr));
        LoginButton->setText(QCoreApplication::translate("StartWindow", "Accedi", nullptr));
        LoginPasswordForm->setInputMask(QString());
        LoginPasswordForm->setText(QString());
        LoginPasswordForm->setPlaceholderText(QCoreApplication::translate("StartWindow", "Password", nullptr));
        RegisterButton->setText(QCoreApplication::translate("StartWindow", "Registrati", nullptr));
        ForgotPasswordButton->setText(QCoreApplication::translate("StartWindow", "Password dimenticata?", nullptr));
        LoginUsernameForm->setText(QString());
        LoginUsernameForm->setPlaceholderText(QCoreApplication::translate("StartWindow", "Username", nullptr));
        label_status->setText(QCoreApplication::translate("StartWindow", "Status", nullptr));
        Haigiaaccount->setText(QCoreApplication::translate("StartWindow", "Hai gi\303\240 un account?", nullptr));
        RegUsernameForm->setText(QString());
        RegUsernameForm->setPlaceholderText(QCoreApplication::translate("StartWindow", "Username", nullptr));
        RegMailForm->setText(QString());
        RegMailForm->setPlaceholderText(QCoreApplication::translate("StartWindow", "Email", nullptr));
        SignUpButton->setText(QCoreApplication::translate("StartWindow", "Registrati", nullptr));
        AccediButton->setText(QCoreApplication::translate("StartWindow", "Accedi", nullptr));
        RegPasswordForm->setInputMask(QString());
        RegPasswordForm->setText(QString());
        RegPasswordForm->setPlaceholderText(QCoreApplication::translate("StartWindow", "Password", nullptr));
        LogoutButton->setText(QCoreApplication::translate("StartWindow", "Disconnettiti", nullptr));
        openEditor->setText(QCoreApplication::translate("StartWindow", "Apri File", nullptr));
        Username->setText(QCoreApplication::translate("StartWindow", "UsernameGoesHere", nullptr));
        exitButton->setText(QString());
        version->setText(QCoreApplication::translate("StartWindow", "QuestoTestoVieneSostituitoDaVersione", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StartWindow: public Ui_StartWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTWINDOW_H

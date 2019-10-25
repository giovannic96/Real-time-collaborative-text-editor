/********************************************************************************
** Form generated from reading UI file 'userprofile.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERPROFILE_H
#define UI_USERPROFILE_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UserProfile
{
public:
    QPushButton *exitButton;
    QPushButton *UserImageButton;
    QLabel *Username;
    QLabel *Mail;
    QWidget *widget;

    void setupUi(QWidget *UserProfile)
    {
        if (UserProfile->objectName().isEmpty())
            UserProfile->setObjectName(QString::fromUtf8("UserProfile"));
        UserProfile->resize(437, 600);
        UserProfile->setStyleSheet(QString::fromUtf8("#UserProfile{border-image: url(:/image/infoprofile.png);}"));
        exitButton = new QPushButton(UserProfile);
        exitButton->setObjectName(QString::fromUtf8("exitButton"));
        exitButton->setGeometry(QRect(403, 7, 29, 23));
        exitButton->setCursor(QCursor(Qt::PointingHandCursor));
        exitButton->setStyleSheet(QString::fromUtf8("background-color: Transparent;\n"
"background-repeat:no-repeat;\n"
""));
        UserImageButton = new QPushButton(UserProfile);
        UserImageButton->setObjectName(QString::fromUtf8("UserImageButton"));
        UserImageButton->setGeometry(QRect(12, 112, 128, 128));
        UserImageButton->setCursor(QCursor(Qt::PointingHandCursor));
        UserImageButton->setStyleSheet(QString::fromUtf8(""));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/image/Immagine.png"), QSize(), QIcon::Normal, QIcon::Off);
        UserImageButton->setIcon(icon);
        UserImageButton->setIconSize(QSize(128, 128));
        Username = new QLabel(UserProfile);
        Username->setObjectName(QString::fromUtf8("Username"));
        Username->setGeometry(QRect(230, 370, 231, 31));
        Username->setStyleSheet(QString::fromUtf8("color: #0000FF;\n"
"font-size: 20px;"));
        Mail = new QLabel(UserProfile);
        Mail->setObjectName(QString::fromUtf8("Mail"));
        Mail->setGeometry(QRect(230, 430, 231, 31));
        Mail->setStyleSheet(QString::fromUtf8("color: #0000FF;\n"
"font-size: 20px;"));
        widget = new QWidget(UserProfile);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 437, 600));
        widget->setStyleSheet(QString::fromUtf8("border-image: url(:/image/infoprofile.png);"));
        widget->raise();
        exitButton->raise();
        UserImageButton->raise();
        Username->raise();
        Mail->raise();

        retranslateUi(UserProfile);

        QMetaObject::connectSlotsByName(UserProfile);
    } // setupUi

    void retranslateUi(QWidget *UserProfile)
    {
        UserProfile->setWindowTitle(QCoreApplication::translate("UserProfile", "Form", nullptr));
        exitButton->setText(QString());
        UserImageButton->setText(QString());
        Username->setText(QCoreApplication::translate("UserProfile", "Username", nullptr));
        Mail->setText(QCoreApplication::translate("UserProfile", "Mail", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UserProfile: public Ui_UserProfile {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERPROFILE_H

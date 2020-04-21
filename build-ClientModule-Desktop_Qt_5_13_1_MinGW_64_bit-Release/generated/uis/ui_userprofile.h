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
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UserProfile
{
public:
    QWidget *widget;
    QLabel *otherFile;
    QLabel *Username;
    QLabel *Mail;
    QLabel *totFile;
    QLabel *myFile;
    QPushButton *UserImageButton;
    QPushButton *exitButton;

    void setupUi(QWidget *UserProfile)
    {
        if (UserProfile->objectName().isEmpty())
            UserProfile->setObjectName(QString::fromUtf8("UserProfile"));
        UserProfile->resize(330, 505);
        UserProfile->setMinimumSize(QSize(330, 505));
        UserProfile->setMaximumSize(QSize(330, 505));
        UserProfile->setStyleSheet(QString::fromUtf8("background:transparent;"));
        widget = new QWidget(UserProfile);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 330, 505));
        widget->setMinimumSize(QSize(330, 505));
        widget->setMaximumSize(QSize(330, 505));
        widget->setAutoFillBackground(false);
        widget->setStyleSheet(QString::fromUtf8("#widget{\n"
"background:url(:image/userProfile.png);\n"
"}"));
        otherFile = new QLabel(widget);
        otherFile->setObjectName(QString::fromUtf8("otherFile"));
        otherFile->setGeometry(QRect(207, 320, 100, 50));
        otherFile->setMinimumSize(QSize(100, 50));
        otherFile->setMaximumSize(QSize(100, 50));
        QFont font;
        font.setFamily(QString::fromUtf8("Calibri"));
        font.setPointSize(36);
        font.setBold(true);
        font.setWeight(75);
        otherFile->setFont(font);
        otherFile->setStyleSheet(QString::fromUtf8("color:grey;"));
        otherFile->setAlignment(Qt::AlignCenter);
        Username = new QLabel(widget);
        Username->setObjectName(QString::fromUtf8("Username"));
        Username->setGeometry(QRect(16, 120, 300, 50));
        Username->setMinimumSize(QSize(300, 50));
        Username->setMaximumSize(QSize(300, 50));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Calibri"));
        font1.setPointSize(20);
        font1.setBold(true);
        font1.setWeight(75);
        Username->setFont(font1);
        Username->setStyleSheet(QString::fromUtf8("color:black;"));
        Username->setAlignment(Qt::AlignCenter);
        Mail = new QLabel(widget);
        Mail->setObjectName(QString::fromUtf8("Mail"));
        Mail->setGeometry(QRect(16, 160, 300, 50));
        Mail->setMinimumSize(QSize(300, 50));
        Mail->setMaximumSize(QSize(300, 50));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Calibri"));
        font2.setPointSize(12);
        font2.setBold(false);
        font2.setWeight(50);
        Mail->setFont(font2);
        Mail->setStyleSheet(QString::fromUtf8("color:grey;"));
        Mail->setAlignment(Qt::AlignCenter);
        totFile = new QLabel(widget);
        totFile->setObjectName(QString::fromUtf8("totFile"));
        totFile->setGeometry(QRect(16, 238, 300, 50));
        totFile->setMinimumSize(QSize(300, 50));
        totFile->setMaximumSize(QSize(300, 50));
        totFile->setFont(font);
        totFile->setStyleSheet(QString::fromUtf8("color:grey;"));
        totFile->setAlignment(Qt::AlignCenter);
        myFile = new QLabel(widget);
        myFile->setObjectName(QString::fromUtf8("myFile"));
        myFile->setGeometry(QRect(27, 320, 100, 50));
        myFile->setMinimumSize(QSize(100, 50));
        myFile->setMaximumSize(QSize(100, 50));
        myFile->setFont(font);
        myFile->setStyleSheet(QString::fromUtf8("color:grey;"));
        myFile->setAlignment(Qt::AlignCenter);
        UserImageButton = new QPushButton(widget);
        UserImageButton->setObjectName(QString::fromUtf8("UserImageButton"));
        UserImageButton->setGeometry(QRect(119, 7, 94, 94));
        UserImageButton->setMinimumSize(QSize(94, 94));
        UserImageButton->setMaximumSize(QSize(94, 94));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Calibri"));
        font3.setPointSize(72);
        font3.setBold(false);
        font3.setWeight(50);
        UserImageButton->setFont(font3);
        UserImageButton->setCursor(QCursor(Qt::ArrowCursor));
        UserImageButton->setStyleSheet(QString::fromUtf8("#UserImageButton{\n"
"border-radius: 18px;\n"
"background:black;\n"
"color:white;\n"
"}"));
        UserImageButton->setIconSize(QSize(90, 90));
        exitButton = new QPushButton(widget);
        exitButton->setObjectName(QString::fromUtf8("exitButton"));
        exitButton->setGeometry(QRect(290, 55, 23, 23));
        exitButton->setMinimumSize(QSize(23, 23));
        exitButton->setMaximumSize(QSize(23, 23));
        QFont font4;
        font4.setPointSize(12);
        font4.setBold(true);
        font4.setWeight(75);
        exitButton->setFont(font4);
        exitButton->setCursor(QCursor(Qt::PointingHandCursor));
        exitButton->setStyleSheet(QString::fromUtf8("#exitButton{\n"
"background: transparent;\n"
"border:none;\n"
"}\n"
""));

        retranslateUi(UserProfile);

        QMetaObject::connectSlotsByName(UserProfile);
    } // setupUi

    void retranslateUi(QWidget *UserProfile)
    {
        UserProfile->setWindowTitle(QCoreApplication::translate("UserProfile", "Form", nullptr));
        otherFile->setText(QString());
        Username->setText(QCoreApplication::translate("UserProfile", "username", nullptr));
        Mail->setText(QCoreApplication::translate("UserProfile", "username@mail.it", nullptr));
        totFile->setText(QString());
        myFile->setText(QString());
        UserImageButton->setText(QString());
        exitButton->setText(QCoreApplication::translate("UserProfile", "X", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UserProfile: public Ui_UserProfile {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERPROFILE_H

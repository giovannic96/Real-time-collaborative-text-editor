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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UserProfile
{
public:
    QPushButton *exitButton;
    QPushButton *UserImageButton;

    void setupUi(QWidget *UserProfile)
    {
        if (UserProfile->objectName().isEmpty())
            UserProfile->setObjectName(QString::fromUtf8("UserProfile"));
        UserProfile->resize(400, 600);
        exitButton = new QPushButton(UserProfile);
        exitButton->setObjectName(QString::fromUtf8("exitButton"));
        exitButton->setGeometry(QRect(360, 0, 29, 23));
        exitButton->setCursor(QCursor(Qt::PointingHandCursor));
        exitButton->setStyleSheet(QString::fromUtf8("background-color: Transparent;\n"
"background-repeat:no-repeat;\n"
""));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/image/basics-22-128.png"), QSize(), QIcon::Normal, QIcon::Off);
        exitButton->setIcon(icon);
        exitButton->setIconSize(QSize(25, 25));
        UserImageButton = new QPushButton(UserProfile);
        UserImageButton->setObjectName(QString::fromUtf8("UserImageButton"));
        UserImageButton->setGeometry(QRect(120, 40, 168, 168));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/image/Immagine.png"), QSize(), QIcon::Normal, QIcon::Off);
        UserImageButton->setIcon(icon1);
        UserImageButton->setIconSize(QSize(168, 168));

        retranslateUi(UserProfile);

        QMetaObject::connectSlotsByName(UserProfile);
    } // setupUi

    void retranslateUi(QWidget *UserProfile)
    {
        UserProfile->setWindowTitle(QCoreApplication::translate("UserProfile", "Form", nullptr));
        exitButton->setText(QString());
        UserImageButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class UserProfile: public Ui_UserProfile {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERPROFILE_H

/********************************************************************************
** Form generated from reading UI file 'debugroom.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEBUGROOM_H
#define UI_DEBUGROOM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DebugRoom
{
public:
    QWidget *centralwidget;
    QPushButton *StartButton;
    QPushButton *UserProfileButton;
    QPushButton *EditorButton;
    QLabel *label;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *DebugRoom)
    {
        if (DebugRoom->objectName().isEmpty())
            DebugRoom->setObjectName(QString::fromUtf8("DebugRoom"));
        DebugRoom->resize(356, 600);
        centralwidget = new QWidget(DebugRoom);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setStyleSheet(QString::fromUtf8("background-color: black"));
        StartButton = new QPushButton(centralwidget);
        StartButton->setObjectName(QString::fromUtf8("StartButton"));
        StartButton->setGeometry(QRect(80, 90, 201, 41));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        StartButton->setFont(font);
        StartButton->setStyleSheet(QString::fromUtf8("#StartButton{color: rgb(255, 255, 255); \n"
"background-color: rgb(255, 0, 0); \n"
"font-size: 16px; \n"
"border-radius: 20px; \n"
"border: 3px solid #B30000;\n"
"}\n"
"#StartButton:hover{\n"
"background-color: #B30000;\n"
"}\n"
"#StartButton:pressed{\n"
"background-color: #800000;\n"
"}"));
        UserProfileButton = new QPushButton(centralwidget);
        UserProfileButton->setObjectName(QString::fromUtf8("UserProfileButton"));
        UserProfileButton->setGeometry(QRect(80, 150, 201, 41));
        UserProfileButton->setFont(font);
        UserProfileButton->setStyleSheet(QString::fromUtf8("#UserProfileButton{color: rgb(0, 0, 0); \n"
"background-color: #FFFF00; \n"
"font-size: 16px; \n"
"border-radius: 20px; \n"
"border: 3px solid #CCCC00;\n"
"}\n"
"#UserProfileButton:hover{\n"
"background-color: #CCCC00;\n"
"}\n"
"#UserProfileButton:pressed{\n"
"background-color: #808000;\n"
"}"));
        EditorButton = new QPushButton(centralwidget);
        EditorButton->setObjectName(QString::fromUtf8("EditorButton"));
        EditorButton->setGeometry(QRect(80, 210, 201, 41));
        EditorButton->setFont(font);
        EditorButton->setStyleSheet(QString::fromUtf8("#EditorButton{color: rgb(255, 255, 255);\n"
"background-color: #0000FF;\n"
"font-size: 16px; \n"
"border-radius: 20px; \n"
"border: 3px solid #0000CC;\n"
"}\n"
"#EditorButton:hover{\n"
"background-color: #0000CC;\n"
"}\n"
"#EditorButton:pressed{\n"
"background-color: #008080;\n"
"}"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 341, 41));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Comic Sans MS"));
        font1.setPointSize(14);
        font1.setBold(true);
        font1.setWeight(75);
        label->setFont(font1);
        label->setLayoutDirection(Qt::LeftToRight);
        label->setStyleSheet(QString::fromUtf8("color: #00FF00;\n"
"text-align: center;"));
        DebugRoom->setCentralWidget(centralwidget);
        UserProfileButton->raise();
        EditorButton->raise();
        label->raise();
        StartButton->raise();
        menubar = new QMenuBar(DebugRoom);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 356, 21));
        DebugRoom->setMenuBar(menubar);
        statusbar = new QStatusBar(DebugRoom);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        DebugRoom->setStatusBar(statusbar);

        retranslateUi(DebugRoom);

        QMetaObject::connectSlotsByName(DebugRoom);
    } // setupUi

    void retranslateUi(QMainWindow *DebugRoom)
    {
        DebugRoom->setWindowTitle(QCoreApplication::translate("DebugRoom", "MainWindow", nullptr));
        StartButton->setText(QCoreApplication::translate("DebugRoom", "START WINDOW", nullptr));
        UserProfileButton->setText(QCoreApplication::translate("DebugRoom", "USER PROFILE", nullptr));
        EditorButton->setText(QCoreApplication::translate("DebugRoom", "EDITOR", nullptr));
        label->setText(QCoreApplication::translate("DebugRoom", "    Enrico & Rinaldo Debug Room", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DebugRoom: public Ui_DebugRoom {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEBUGROOM_H

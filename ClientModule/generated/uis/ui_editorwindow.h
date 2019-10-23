/********************************************************************************
** Form generated from reading UI file 'editorwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITORWINDOW_H
#define UI_EDITORWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EditorWindow
{
public:
    QAction *actionNew;
    QAction *actionLoad;
    QAction *actionSave;
    QAction *action_2;
    QAction *actionExit;
    QWidget *centralwidget;
    QFrame *frame;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *DocName;
    QPushButton *pushButton_3;
    QFrame *frame_2;
    QTextEdit *textEdit;
    QMenuBar *menubar;
    QMenu *menuFile;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *EditorWindow)
    {
        if (EditorWindow->objectName().isEmpty())
            EditorWindow->setObjectName(QString::fromUtf8("EditorWindow"));
        EditorWindow->resize(1213, 728);
        actionNew = new QAction(EditorWindow);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        actionLoad = new QAction(EditorWindow);
        actionLoad->setObjectName(QString::fromUtf8("actionLoad"));
        actionSave = new QAction(EditorWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        action_2 = new QAction(EditorWindow);
        action_2->setObjectName(QString::fromUtf8("action_2"));
        actionExit = new QAction(EditorWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        centralwidget = new QWidget(EditorWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        frame = new QFrame(centralwidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(0, 0, 1221, 80));
        frame->setStyleSheet(QString::fromUtf8("background-color:rgb(10, 85, 151)"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        pushButton = new QPushButton(frame);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(10, 0, 75, 23));
        pushButton_2 = new QPushButton(frame);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(1172, 0, 41, 23));
        pushButton_2->setStyleSheet(QString::fromUtf8("#pushButton_2{\n"
"	border: transparent;\n"
"	background-color: transparent;\n"
"}\n"
"#pushButton_2:hover{\n"
"	background-color: red;\n"
"}#pushButton_2:hover{\n"
"	background-color: red;\n"
"}"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/image/basics-22-128.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_2->setIcon(icon);
        DocName = new QLabel(frame);
        DocName->setObjectName(QString::fromUtf8("DocName"));
        DocName->setGeometry(QRect(460, 10, 291, 20));
        QFont font;
        font.setPointSize(11);
        font.setBold(true);
        font.setWeight(75);
        DocName->setFont(font);
        DocName->setStyleSheet(QString::fromUtf8("Color: yellow;\n"
"text-align: right;"));
        DocName->setAlignment(Qt::AlignCenter);
        pushButton_3 = new QPushButton(frame);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(730, 10, 75, 23));
        frame_2 = new QFrame(centralwidget);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setGeometry(QRect(170, 100, 851, 441));
        frame_2->setStyleSheet(QString::fromUtf8("background-color: white;"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        textEdit = new QTextEdit(frame_2);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(20, 70, 801, 231));
        textEdit->setStyleSheet(QString::fromUtf8("border: transparent;"));
        EditorWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(EditorWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1213, 21));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        EditorWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(EditorWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        EditorWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionLoad);
        menuFile->addAction(actionSave);
        menuFile->addSeparator();
        menuFile->addAction(action_2);
        menuFile->addAction(actionExit);

        retranslateUi(EditorWindow);

        QMetaObject::connectSlotsByName(EditorWindow);
    } // setupUi

    void retranslateUi(QMainWindow *EditorWindow)
    {
        EditorWindow->setWindowTitle(QCoreApplication::translate("EditorWindow", "MainWindow", nullptr));
        actionNew->setText(QCoreApplication::translate("EditorWindow", "New", nullptr));
        actionLoad->setText(QCoreApplication::translate("EditorWindow", "Load", nullptr));
        actionSave->setText(QCoreApplication::translate("EditorWindow", "Save", nullptr));
        action_2->setText(QCoreApplication::translate("EditorWindow", "?", nullptr));
        actionExit->setText(QCoreApplication::translate("EditorWindow", "Exit", nullptr));
        pushButton->setText(QCoreApplication::translate("EditorWindow", "PushButton", nullptr));
        pushButton_2->setText(QString());
        DocName->setText(QCoreApplication::translate("EditorWindow", "DocumentNameGoesHere.txt", nullptr));
        pushButton_3->setText(QCoreApplication::translate("EditorWindow", "Rename", nullptr));
        menuFile->setTitle(QCoreApplication::translate("EditorWindow", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditorWindow: public Ui_EditorWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITORWINDOW_H

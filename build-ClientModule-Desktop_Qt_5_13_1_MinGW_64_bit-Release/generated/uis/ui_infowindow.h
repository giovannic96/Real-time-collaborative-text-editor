/********************************************************************************
** Form generated from reading UI file 'infowindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INFOWINDOW_H
#define UI_INFOWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_infoWindow
{
public:
    QFrame *frame;
    QPushButton *exitButton_2;
    QPushButton *exitButton;
    QLabel *version;
    QLabel *label_2;
    QPushButton *giovanni;
    QPushButton *rinaldo;
    QPushButton *enrico;
    QPushButton *francesco;

    void setupUi(QWidget *infoWindow)
    {
        if (infoWindow->objectName().isEmpty())
            infoWindow->setObjectName(QString::fromUtf8("infoWindow"));
        infoWindow->resize(699, 400);
        infoWindow->setStyleSheet(QString::fromUtf8(""));
        frame = new QFrame(infoWindow);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(0, 0, 701, 411));
        frame->setStyleSheet(QString::fromUtf8("#frame{\n"
"	border-image: url(:/image/InfoWindow.png);\n"
"}"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        exitButton_2 = new QPushButton(frame);
        exitButton_2->setObjectName(QString::fromUtf8("exitButton_2"));
        exitButton_2->setGeometry(QRect(620, 370, 71, 23));
        exitButton = new QPushButton(frame);
        exitButton->setObjectName(QString::fromUtf8("exitButton"));
        exitButton->setGeometry(QRect(661, -1, 41, 23));
        exitButton->setStyleSheet(QString::fromUtf8("background-color: Transparent;\n"
"border:none;\n"
"background-repeat:no-repeat;"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/image/basics-22-128.png"), QSize(), QIcon::Normal, QIcon::Off);
        exitButton->setIcon(icon);
        version = new QLabel(frame);
        version->setObjectName(QString::fromUtf8("version"));
        version->setGeometry(QRect(15, 117, 401, 41));
        QFont font;
        font.setPointSize(14);
        font.setItalic(false);
        version->setFont(font);
        version->setStyleSheet(QString::fromUtf8("color: #EAFF00;"));
        version->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(frame);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 160, 491, 231));
        label_2->setStyleSheet(QString::fromUtf8("color: white;"));
        label_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        giovanni = new QPushButton(frame);
        giovanni->setObjectName(QString::fromUtf8("giovanni"));
        giovanni->setGeometry(QRect(27, 220, 101, 23));
        giovanni->setCursor(QCursor(Qt::PointingHandCursor));
        rinaldo = new QPushButton(frame);
        rinaldo->setObjectName(QString::fromUtf8("rinaldo"));
        rinaldo->setGeometry(QRect(27, 245, 101, 23));
        rinaldo->setCursor(QCursor(Qt::PointingHandCursor));
        enrico = new QPushButton(frame);
        enrico->setObjectName(QString::fromUtf8("enrico"));
        enrico->setGeometry(QRect(27, 270, 101, 23));
        enrico->setCursor(QCursor(Qt::PointingHandCursor));
        francesco = new QPushButton(frame);
        francesco->setObjectName(QString::fromUtf8("francesco"));
        francesco->setGeometry(QRect(27, 294, 111, 23));
        francesco->setCursor(QCursor(Qt::PointingHandCursor));

        retranslateUi(infoWindow);

        QMetaObject::connectSlotsByName(infoWindow);
    } // setupUi

    void retranslateUi(QWidget *infoWindow)
    {
        infoWindow->setWindowTitle(QCoreApplication::translate("infoWindow", "Form", nullptr));
        exitButton_2->setText(QCoreApplication::translate("infoWindow", "CHIUDI", nullptr));
        exitButton->setText(QString());
        version->setText(QCoreApplication::translate("infoWindow", "QuestoTestoVieneSostituitoDaVersione", nullptr));
        label_2->setText(QCoreApplication::translate("infoWindow", "<html><head/><body><p>Progetto realizzato ai fini del corso di &quot;Programmazione di Sistema&quot; bla bla bla...</p><p><span style=\" font-weight:600;\"><br/></span>In ordine di cognome:</p><p><span style=\" font-weight:600;\">- Giovanni Cal\303\240</span></p><p><span style=\" font-weight:600;\">- Rinaldo Clemente</span></p><p><span style=\" font-weight:600;\">- Enrico Mancuso</span></p><p><span style=\" font-weight:600;\">- Francesco Raitano</span></p><p>Copyright \302\251 2019</p></body></html>", nullptr));
        giovanni->setText(QString());
        rinaldo->setText(QString());
        enrico->setText(QString());
        francesco->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class infoWindow: public Ui_infoWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INFOWINDOW_H

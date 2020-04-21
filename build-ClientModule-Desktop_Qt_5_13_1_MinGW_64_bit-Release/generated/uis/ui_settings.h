/********************************************************************************
** Form generated from reading UI file 'settings.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGS_H
#define UI_SETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Settings
{
public:
    QPushButton *Save;
    QTabWidget *tabWidget;
    QWidget *tab;
    QLabel *label;
    QLabel *label_3;
    QLabel *label_4;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QRadioButton *dayRadio;
    QRadioButton *darkRadio;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_4;
    QRadioButton *toolShowRadio;
    QRadioButton *toolHideRadio;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_3;
    QRadioButton *collabShowRadio;
    QRadioButton *collabHideRadio;
    QWidget *tab_2;
    QLabel *label_2;
    QWidget *layoutWidget3;
    QVBoxLayout *verticalLayout_2;
    QRadioButton *titleRadio1;
    QRadioButton *titleRadio2;
    QRadioButton *titleRadio3;
    QRadioButton *titleRadio4;
    QRadioButton *titleRadio5;
    QLabel *PreviewBar;
    QLabel *PreviewBar_2;
    QLabel *PreviewBar_3;
    QLabel *PreviewBar_4;
    QLabel *PreviewBar_5;
    QWidget *tab_3;
    QLabel *label_6;
    QLabel *label_5;
    QComboBox *ComboDay;
    QComboBox *ComboDark;
    QLabel *PreviewThemeDay;
    QFrame *line;
    QLabel *PreviewThemeDark;
    QPushButton *Abort;
    QPushButton *Default;

    void setupUi(QWidget *Settings)
    {
        if (Settings->objectName().isEmpty())
            Settings->setObjectName(QString::fromUtf8("Settings"));
        Settings->resize(560, 340);
        Settings->setMinimumSize(QSize(560, 340));
        Settings->setMaximumSize(QSize(560, 340));
        Save = new QPushButton(Settings);
        Save->setObjectName(QString::fromUtf8("Save"));
        Save->setGeometry(QRect(470, 310, 75, 23));
        tabWidget = new QTabWidget(Settings);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(10, 10, 541, 291));
        tabWidget->setMinimumSize(QSize(300, 0));
        tabWidget->setMaximumSize(QSize(16777215, 16777215));
        QFont font;
        font.setPointSize(8);
        tabWidget->setFont(font);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        label = new QLabel(tab);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(-5, 64, 141, 51));
        QFont font1;
        font1.setPointSize(12);
        label->setFont(font1);
        label->setAlignment(Qt::AlignCenter);
        label_3 = new QLabel(tab);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(340, 69, 191, 41));
        label_3->setFont(font1);
        label_3->setAlignment(Qt::AlignCenter);
        label_4 = new QLabel(tab);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(138, 64, 211, 51));
        label_4->setFont(font1);
        label_4->setAlignment(Qt::AlignCenter);
        layoutWidget = new QWidget(tab);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 112, 111, 52));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        dayRadio = new QRadioButton(layoutWidget);
        dayRadio->setObjectName(QString::fromUtf8("dayRadio"));
        QFont font2;
        font2.setPointSize(11);
        dayRadio->setFont(font2);
        dayRadio->setChecked(true);

        verticalLayout->addWidget(dayRadio);

        darkRadio = new QRadioButton(layoutWidget);
        darkRadio->setObjectName(QString::fromUtf8("darkRadio"));
        darkRadio->setFont(font2);

        verticalLayout->addWidget(darkRadio);

        layoutWidget1 = new QWidget(tab);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(187, 112, 101, 52));
        verticalLayout_4 = new QVBoxLayout(layoutWidget1);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        toolShowRadio = new QRadioButton(layoutWidget1);
        toolShowRadio->setObjectName(QString::fromUtf8("toolShowRadio"));
        toolShowRadio->setFont(font2);
        toolShowRadio->setChecked(true);

        verticalLayout_4->addWidget(toolShowRadio);

        toolHideRadio = new QRadioButton(layoutWidget1);
        toolHideRadio->setObjectName(QString::fromUtf8("toolHideRadio"));
        toolHideRadio->setFont(font2);

        verticalLayout_4->addWidget(toolHideRadio);

        layoutWidget2 = new QWidget(tab);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(353, 112, 101, 52));
        verticalLayout_3 = new QVBoxLayout(layoutWidget2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        collabShowRadio = new QRadioButton(layoutWidget2);
        collabShowRadio->setObjectName(QString::fromUtf8("collabShowRadio"));
        collabShowRadio->setFont(font2);
        collabShowRadio->setChecked(true);

        verticalLayout_3->addWidget(collabShowRadio);

        collabHideRadio = new QRadioButton(layoutWidget2);
        collabHideRadio->setObjectName(QString::fromUtf8("collabHideRadio"));
        collabHideRadio->setFont(font2);

        verticalLayout_3->addWidget(collabHideRadio);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        label_2 = new QLabel(tab_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 5, 131, 31));
        label_2->setFont(font1);
        layoutWidget3 = new QWidget(tab_2);
        layoutWidget3->setObjectName(QString::fromUtf8("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(10, 40, 531, 222));
        verticalLayout_2 = new QVBoxLayout(layoutWidget3);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        titleRadio1 = new QRadioButton(layoutWidget3);
        titleRadio1->setObjectName(QString::fromUtf8("titleRadio1"));
        titleRadio1->setMinimumSize(QSize(0, 40));
        titleRadio1->setFont(font2);
        titleRadio1->setStyleSheet(QString::fromUtf8("border-bottom:1px solid lightgrey;"));
        titleRadio1->setChecked(true);

        verticalLayout_2->addWidget(titleRadio1);

        titleRadio2 = new QRadioButton(layoutWidget3);
        titleRadio2->setObjectName(QString::fromUtf8("titleRadio2"));
        titleRadio2->setMinimumSize(QSize(0, 40));
        titleRadio2->setFont(font2);
        titleRadio2->setStyleSheet(QString::fromUtf8("border-bottom:1px solid lightgrey;"));
        titleRadio2->setChecked(false);

        verticalLayout_2->addWidget(titleRadio2);

        titleRadio3 = new QRadioButton(layoutWidget3);
        titleRadio3->setObjectName(QString::fromUtf8("titleRadio3"));
        titleRadio3->setMinimumSize(QSize(0, 40));
        titleRadio3->setFont(font2);
        titleRadio3->setStyleSheet(QString::fromUtf8("border-bottom:1px solid lightgrey;"));

        verticalLayout_2->addWidget(titleRadio3);

        titleRadio4 = new QRadioButton(layoutWidget3);
        titleRadio4->setObjectName(QString::fromUtf8("titleRadio4"));
        titleRadio4->setMinimumSize(QSize(0, 40));
        titleRadio4->setFont(font2);
        titleRadio4->setStyleSheet(QString::fromUtf8("border-bottom:1px solid lightgrey;"));

        verticalLayout_2->addWidget(titleRadio4);

        titleRadio5 = new QRadioButton(layoutWidget3);
        titleRadio5->setObjectName(QString::fromUtf8("titleRadio5"));
        titleRadio5->setMinimumSize(QSize(0, 40));
        titleRadio5->setFont(font2);
        titleRadio5->setStyleSheet(QString::fromUtf8("border-bottom:1px solid lightgrey;"));

        verticalLayout_2->addWidget(titleRadio5);

        PreviewBar = new QLabel(tab_2);
        PreviewBar->setObjectName(QString::fromUtf8("PreviewBar"));
        PreviewBar->setGeometry(QRect(333, 47, 200, 30));
        PreviewBar->setStyleSheet(QString::fromUtf8("background:url(:/image/Settings/nomeDoc.png);"));
        PreviewBar_2 = new QLabel(tab_2);
        PreviewBar_2->setObjectName(QString::fromUtf8("PreviewBar_2"));
        PreviewBar_2->setGeometry(QRect(333, 90, 200, 30));
        PreviewBar_2->setStyleSheet(QString::fromUtf8("background:url(:/image/Settings/carte.png);"));
        PreviewBar_3 = new QLabel(tab_2);
        PreviewBar_3->setObjectName(QString::fromUtf8("PreviewBar_3"));
        PreviewBar_3->setGeometry(QRect(333, 133, 200, 30));
        PreviewBar_3->setStyleSheet(QString::fromUtf8("background:url(:/image/Settings/carteNomeDoc.png);"));
        PreviewBar_4 = new QLabel(tab_2);
        PreviewBar_4->setObjectName(QString::fromUtf8("PreviewBar_4"));
        PreviewBar_4->setGeometry(QRect(333, 176, 200, 30));
        PreviewBar_4->setStyleSheet(QString::fromUtf8("background:url(:/image/Settings/carte.png);"));
        PreviewBar_5 = new QLabel(tab_2);
        PreviewBar_5->setObjectName(QString::fromUtf8("PreviewBar_5"));
        PreviewBar_5->setGeometry(QRect(333, 219, 200, 30));
        PreviewBar_5->setStyleSheet(QString::fromUtf8("background:url(:/image/Settings/carte.png);"));
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        label_6 = new QLabel(tab_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(10, 140, 101, 30));
        label_6->setMinimumSize(QSize(0, 30));
        label_6->setMaximumSize(QSize(16777215, 30));
        label_6->setFont(font1);
        label_5 = new QLabel(tab_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 20, 101, 30));
        label_5->setMinimumSize(QSize(0, 30));
        label_5->setMaximumSize(QSize(16777215, 30));
        label_5->setFont(font1);
        ComboDay = new QComboBox(tab_3);
        ComboDay->addItem(QString());
        ComboDay->addItem(QString());
        ComboDay->addItem(QString());
        ComboDay->addItem(QString());
        ComboDay->addItem(QString());
        ComboDay->addItem(QString());
        ComboDay->addItem(QString());
        ComboDay->addItem(QString());
        ComboDay->addItem(QString());
        ComboDay->addItem(QString());
        ComboDay->addItem(QString());
        ComboDay->setObjectName(QString::fromUtf8("ComboDay"));
        ComboDay->setGeometry(QRect(120, 20, 151, 22));
        ComboDark = new QComboBox(tab_3);
        ComboDark->addItem(QString());
        ComboDark->addItem(QString());
        ComboDark->addItem(QString());
        ComboDark->addItem(QString());
        ComboDark->addItem(QString());
        ComboDark->addItem(QString());
        ComboDark->addItem(QString());
        ComboDark->addItem(QString());
        ComboDark->addItem(QString());
        ComboDark->addItem(QString());
        ComboDark->addItem(QString());
        ComboDark->setObjectName(QString::fromUtf8("ComboDark"));
        ComboDark->setGeometry(QRect(120, 140, 151, 22));
        PreviewThemeDay = new QLabel(tab_3);
        PreviewThemeDay->setObjectName(QString::fromUtf8("PreviewThemeDay"));
        PreviewThemeDay->setGeometry(QRect(323, 14, 185, 120));
        PreviewThemeDay->setMinimumSize(QSize(0, 0));
        PreviewThemeDay->setStyleSheet(QString::fromUtf8(""));
        line = new QFrame(tab_3);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(299, 7, 2, 250));
        line->setMinimumSize(QSize(0, 250));
        line->setStyleSheet(QString::fromUtf8("background:lightgrey;\n"
"border:none;"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        PreviewThemeDark = new QLabel(tab_3);
        PreviewThemeDark->setObjectName(QString::fromUtf8("PreviewThemeDark"));
        PreviewThemeDark->setGeometry(QRect(323, 141, 185, 120));
        PreviewThemeDark->setMinimumSize(QSize(0, 0));
        tabWidget->addTab(tab_3, QString());
        Abort = new QPushButton(Settings);
        Abort->setObjectName(QString::fromUtf8("Abort"));
        Abort->setGeometry(QRect(380, 310, 75, 23));
        Default = new QPushButton(Settings);
        Default->setObjectName(QString::fromUtf8("Default"));
        Default->setGeometry(QRect(20, 310, 75, 23));

        retranslateUi(Settings);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Settings);
    } // setupUi

    void retranslateUi(QWidget *Settings)
    {
        Settings->setWindowTitle(QCoreApplication::translate("Settings", "Form", nullptr));
        Save->setText(QCoreApplication::translate("Settings", "Salva", nullptr));
        label->setText(QCoreApplication::translate("Settings", "Colore Editor", nullptr));
        label_3->setText(QCoreApplication::translate("Settings", "Barra Collaboratori", nullptr));
        label_4->setText(QCoreApplication::translate("Settings", "Barra degli Strumenti", nullptr));
        dayRadio->setText(QCoreApplication::translate("Settings", "DayMode", nullptr));
        darkRadio->setText(QCoreApplication::translate("Settings", "DarkMode", nullptr));
        toolShowRadio->setText(QCoreApplication::translate("Settings", "Mostra", nullptr));
        toolHideRadio->setText(QCoreApplication::translate("Settings", "Nascondi", nullptr));
        collabShowRadio->setText(QCoreApplication::translate("Settings", "Mostra", nullptr));
        collabHideRadio->setText(QCoreApplication::translate("Settings", "Nascondi", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("Settings", "All'avvio", nullptr));
        label_2->setText(QCoreApplication::translate("Settings", "Visualizza", nullptr));
        titleRadio1->setText(QCoreApplication::translate("Settings", "Nome documento", nullptr));
        titleRadio2->setText(QCoreApplication::translate("Settings", "C.A.R.T.E", nullptr));
        titleRadio3->setText(QCoreApplication::translate("Settings", "C.A.R.T.E. + Nome documento", nullptr));
        titleRadio4->setText(QCoreApplication::translate("Settings", "Alterna C.A.R.T.E. / Nome documento", nullptr));
        titleRadio5->setText(QCoreApplication::translate("Settings", "C.A.R.T.E. animato", nullptr));
        PreviewBar->setText(QString());
        PreviewBar_2->setText(QString());
        PreviewBar_3->setText(QString());
        PreviewBar_4->setText(QString());
        PreviewBar_5->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("Settings", "Titolo", nullptr));
        label_6->setText(QCoreApplication::translate("Settings", "DarkMode", nullptr));
        label_5->setText(QCoreApplication::translate("Settings", "DayMode", nullptr));
        ComboDay->setItemText(0, QCoreApplication::translate("Settings", "Classic Blue", nullptr));
        ComboDay->setItemText(1, QCoreApplication::translate("Settings", "Plain Blue", nullptr));
        ComboDay->setItemText(2, QCoreApplication::translate("Settings", "Electric Blue", nullptr));
        ComboDay->setItemText(3, QCoreApplication::translate("Settings", "Classic Purple", nullptr));
        ComboDay->setItemText(4, QCoreApplication::translate("Settings", "Classic Orange", nullptr));
        ComboDay->setItemText(5, QCoreApplication::translate("Settings", "Classic Green", nullptr));
        ComboDay->setItemText(6, QCoreApplication::translate("Settings", "Classic Red", nullptr));
        ComboDay->setItemText(7, QCoreApplication::translate("Settings", "Fantasy", nullptr));
        ComboDay->setItemText(8, QCoreApplication::translate("Settings", "Rainbow", nullptr));
        ComboDay->setItemText(9, QCoreApplication::translate("Settings", "Polito", nullptr));
        ComboDay->setItemText(10, QCoreApplication::translate("Settings", "Special", nullptr));

        ComboDark->setItemText(0, QCoreApplication::translate("Settings", "Classic Orange", nullptr));
        ComboDark->setItemText(1, QCoreApplication::translate("Settings", "Plain Orange", nullptr));
        ComboDark->setItemText(2, QCoreApplication::translate("Settings", "Electric Orange", nullptr));
        ComboDark->setItemText(3, QCoreApplication::translate("Settings", "Classic Purple", nullptr));
        ComboDark->setItemText(4, QCoreApplication::translate("Settings", "Classic Blue", nullptr));
        ComboDark->setItemText(5, QCoreApplication::translate("Settings", "Classic Green", nullptr));
        ComboDark->setItemText(6, QCoreApplication::translate("Settings", "Classic Red", nullptr));
        ComboDark->setItemText(7, QCoreApplication::translate("Settings", "Fantasy", nullptr));
        ComboDark->setItemText(8, QCoreApplication::translate("Settings", "Rainbow", nullptr));
        ComboDark->setItemText(9, QCoreApplication::translate("Settings", "Polito", nullptr));
        ComboDark->setItemText(10, QCoreApplication::translate("Settings", "Special", nullptr));

        PreviewThemeDay->setText(QString());
        PreviewThemeDark->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("Settings", "Temi", nullptr));
        Abort->setText(QCoreApplication::translate("Settings", "Annulla", nullptr));
        Default->setText(QCoreApplication::translate("Settings", "Ripristina", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Settings: public Ui_Settings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGS_H

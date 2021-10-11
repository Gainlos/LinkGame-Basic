/********************************************************************************
** Form generated from reading UI file 'menu.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MENU_H
#define UI_MENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Menu
{
public:
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *single_btn;
    QPushButton *double_btn;
    QPushButton *contiue_btn;
    QPushButton *exit_btn;
    QLabel *label;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Menu)
    {
        if (Menu->objectName().isEmpty())
            Menu->setObjectName(QString::fromUtf8("Menu"));
        Menu->resize(800, 600);
        centralwidget = new QWidget(Menu);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(310, 120, 160, 311));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        single_btn = new QPushButton(verticalLayoutWidget);
        single_btn->setObjectName(QString::fromUtf8("single_btn"));
        QFont font;
        font.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font.setPointSize(11);
        single_btn->setFont(font);

        verticalLayout->addWidget(single_btn);

        double_btn = new QPushButton(verticalLayoutWidget);
        double_btn->setObjectName(QString::fromUtf8("double_btn"));
        double_btn->setFont(font);

        verticalLayout->addWidget(double_btn);

        contiue_btn = new QPushButton(verticalLayoutWidget);
        contiue_btn->setObjectName(QString::fromUtf8("contiue_btn"));
        contiue_btn->setFont(font);

        verticalLayout->addWidget(contiue_btn);

        exit_btn = new QPushButton(verticalLayoutWidget);
        exit_btn->setObjectName(QString::fromUtf8("exit_btn"));
        exit_btn->setFont(font);

        verticalLayout->addWidget(exit_btn);

        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(300, 40, 171, 51));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\215\216\346\226\207\346\226\260\351\255\217"));
        font1.setPointSize(36);
        font1.setBold(false);
        font1.setItalic(false);
        font1.setWeight(50);
        label->setFont(font1);
        Menu->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Menu);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 26));
        Menu->setMenuBar(menubar);
        statusbar = new QStatusBar(Menu);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        Menu->setStatusBar(statusbar);

        retranslateUi(Menu);

        QMetaObject::connectSlotsByName(Menu);
    } // setupUi

    void retranslateUi(QMainWindow *Menu)
    {
        Menu->setWindowTitle(QCoreApplication::translate("Menu", "MainWindow", nullptr));
        single_btn->setText(QCoreApplication::translate("Menu", "\345\215\225\344\272\272\346\270\270\346\210\217", nullptr));
        double_btn->setText(QCoreApplication::translate("Menu", "\345\217\214\344\272\272\346\270\270\346\210\217", nullptr));
        contiue_btn->setText(QCoreApplication::translate("Menu", "\347\273\247\347\273\255\346\270\270\346\210\217", nullptr));
        exit_btn->setText(QCoreApplication::translate("Menu", "\351\200\200\345\207\272", nullptr));
        label->setText(QCoreApplication::translate("Menu", "\350\277\236\350\277\236\347\234\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Menu: public Ui_Menu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENU_H

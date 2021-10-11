/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *save;
    QPushButton *pause;
    QPushButton *exit;
    QSpacerItem *horizontalSpacer;
    QLCDNumber *Timer;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *Point_2;
    QSpacerItem *horizontalSpacer_2;
    QLabel *Point_1;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(794, 653);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(20, 10, 761, 41));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        save = new QPushButton(horizontalLayoutWidget);
        save->setObjectName(QString::fromUtf8("save"));
        QFont font;
        font.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font.setPointSize(11);
        save->setFont(font);

        horizontalLayout->addWidget(save);

        pause = new QPushButton(horizontalLayoutWidget);
        pause->setObjectName(QString::fromUtf8("pause"));
        pause->setFont(font);

        horizontalLayout->addWidget(pause);

        exit = new QPushButton(horizontalLayoutWidget);
        exit->setObjectName(QString::fromUtf8("exit"));
        exit->setFont(font);

        horizontalLayout->addWidget(exit);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        Timer = new QLCDNumber(horizontalLayoutWidget);
        Timer->setObjectName(QString::fromUtf8("Timer"));

        horizontalLayout->addWidget(Timer);

        horizontalLayoutWidget_2 = new QWidget(centralwidget);
        horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(30, 550, 731, 47));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        Point_2 = new QLabel(horizontalLayoutWidget_2);
        Point_2->setObjectName(QString::fromUtf8("Point_2"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Calibri"));
        font1.setPointSize(14);
        Point_2->setFont(font1);

        horizontalLayout_2->addWidget(Point_2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        Point_1 = new QLabel(horizontalLayoutWidget_2);
        Point_1->setObjectName(QString::fromUtf8("Point_1"));
        Point_1->setFont(font1);

        horizontalLayout_2->addWidget(Point_1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 794, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        save->setText(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230", nullptr));
        pause->setText(QCoreApplication::translate("MainWindow", "\346\232\202\345\201\234", nullptr));
        exit->setText(QCoreApplication::translate("MainWindow", "exit", nullptr));
        Point_2->setText(QCoreApplication::translate("MainWindow", "Points:              ", nullptr));
        Point_1->setText(QCoreApplication::translate("MainWindow", "Points:               ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

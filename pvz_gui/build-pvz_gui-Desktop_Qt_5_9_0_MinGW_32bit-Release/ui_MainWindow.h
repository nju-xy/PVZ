/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *gameButton;
    QPushButton *exitButton;
    QLabel *label;
    QPushButton *gameButton_3;
    QPushButton *rankingButton;
    QPushButton *gameButton_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1000, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gameButton = new QPushButton(centralwidget);
        gameButton->setObjectName(QStringLiteral("gameButton"));
        gameButton->setGeometry(QRect(180, 220, 200, 60));
        QFont font;
        font.setPointSize(15);
        gameButton->setFont(font);
        exitButton = new QPushButton(centralwidget);
        exitButton->setObjectName(QStringLiteral("exitButton"));
        exitButton->setGeometry(QRect(380, 450, 200, 60));
        exitButton->setFont(font);
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(375, 110, 251, 60));
        QFont font1;
        font1.setPointSize(25);
        font1.setBold(true);
        font1.setWeight(75);
        label->setFont(font1);
        gameButton_3 = new QPushButton(centralwidget);
        gameButton_3->setObjectName(QStringLiteral("gameButton_3"));
        gameButton_3->setGeometry(QRect(580, 220, 200, 60));
        gameButton_3->setFont(font);
        rankingButton = new QPushButton(centralwidget);
        rankingButton->setObjectName(QStringLiteral("rankingButton"));
        rankingButton->setGeometry(QRect(580, 350, 200, 60));
        rankingButton->setFont(font);
        gameButton_2 = new QPushButton(centralwidget);
        gameButton_2->setObjectName(QStringLiteral("gameButton_2"));
        gameButton_2->setGeometry(QRect(180, 350, 200, 60));
        gameButton_2->setFont(font);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1000, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        gameButton->setText(QApplication::translate("MainWindow", "\346\231\256\351\200\232\351\232\276\345\272\246", Q_NULLPTR));
        exitButton->setText(QApplication::translate("MainWindow", "\351\200\200\345\207\272\346\270\270\346\210\217", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "\346\244\215\347\211\251\345\244\247\346\210\230\345\203\265\345\260\270", Q_NULLPTR));
        gameButton_3->setText(QApplication::translate("MainWindow", "\350\277\267\351\233\276\346\250\241\345\274\217", Q_NULLPTR));
        rankingButton->setText(QApplication::translate("MainWindow", "\346\216\222\350\241\214\346\246\234", Q_NULLPTR));
        gameButton_2->setText(QApplication::translate("MainWindow", "\345\233\260\351\232\276\351\232\276\345\272\246", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

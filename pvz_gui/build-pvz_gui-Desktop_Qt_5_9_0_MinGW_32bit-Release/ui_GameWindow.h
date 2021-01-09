/********************************************************************************
** Form generated from reading UI file 'GameWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEWINDOW_H
#define UI_GAMEWINDOW_H

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

class Ui_GameWindow
{
public:
    QWidget *centralwidget;
    QPushButton *returnButton;
    QPushButton *stopButton;
    QLabel *label;
    QLabel *label_record;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *GameWindow)
    {
        if (GameWindow->objectName().isEmpty())
            GameWindow->setObjectName(QStringLiteral("GameWindow"));
        GameWindow->resize(1000, 600);
        centralwidget = new QWidget(GameWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        returnButton = new QPushButton(centralwidget);
        returnButton->setObjectName(QStringLiteral("returnButton"));
        returnButton->setGeometry(QRect(790, 300, 150, 70));
        stopButton = new QPushButton(centralwidget);
        stopButton->setObjectName(QStringLiteral("stopButton"));
        stopButton->setGeometry(QRect(790, 410, 150, 70));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(800, 170, 151, 81));
        QFont font;
        font.setPointSize(25);
        font.setBold(true);
        font.setItalic(true);
        font.setWeight(75);
        label->setFont(font);
        label_record = new QLabel(centralwidget);
        label_record->setObjectName(QStringLiteral("label_record"));
        label_record->setGeometry(QRect(790, 170, 161, 81));
        label_record->setFont(font);
        GameWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(GameWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1000, 26));
        GameWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(GameWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        GameWindow->setStatusBar(statusbar);

        retranslateUi(GameWindow);

        QMetaObject::connectSlotsByName(GameWindow);
    } // setupUi

    void retranslateUi(QMainWindow *GameWindow)
    {
        GameWindow->setWindowTitle(QApplication::translate("GameWindow", "MainWindow", Q_NULLPTR));
        returnButton->setText(QApplication::translate("GameWindow", "\350\277\224\345\233\236", Q_NULLPTR));
        stopButton->setText(QApplication::translate("GameWindow", "\346\232\202\345\201\234", Q_NULLPTR));
        label->setText(QApplication::translate("GameWindow", "\345\267\262\346\232\202\345\201\234", Q_NULLPTR));
        label_record->setText(QApplication::translate("GameWindow", "\346\226\260\350\256\260\345\275\225\357\274\201", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class GameWindow: public Ui_GameWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEWINDOW_H

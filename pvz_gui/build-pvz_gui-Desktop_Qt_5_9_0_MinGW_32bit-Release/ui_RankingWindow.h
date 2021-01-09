/********************************************************************************
** Form generated from reading UI file 'RankingWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RANKINGWINDOW_H
#define UI_RANKINGWINDOW_H

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

class Ui_RankingWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *RankingWindow)
    {
        if (RankingWindow->objectName().isEmpty())
            RankingWindow->setObjectName(QStringLiteral("RankingWindow"));
        RankingWindow->resize(1000, 600);
        centralwidget = new QWidget(RankingWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(440, 100, 120, 50));
        QFont font;
        font.setPointSize(35);
        font.setBold(true);
        font.setUnderline(true);
        font.setWeight(75);
        label->setFont(font);
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(450, 440, 100, 40));
        QFont font1;
        font1.setPointSize(15);
        pushButton->setFont(font1);
        RankingWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(RankingWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1000, 26));
        RankingWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(RankingWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        RankingWindow->setStatusBar(statusbar);

        retranslateUi(RankingWindow);

        QMetaObject::connectSlotsByName(RankingWindow);
    } // setupUi

    void retranslateUi(QMainWindow *RankingWindow)
    {
        RankingWindow->setWindowTitle(QApplication::translate("RankingWindow", "MainWindow", Q_NULLPTR));
        label->setText(QApplication::translate("RankingWindow", "\346\216\222\345\220\215", Q_NULLPTR));
        pushButton->setText(QApplication::translate("RankingWindow", "\350\277\224\345\233\236", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class RankingWindow: public Ui_RankingWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RANKINGWINDOW_H

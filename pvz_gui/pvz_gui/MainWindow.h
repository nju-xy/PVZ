#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSound>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_gameButton_clicked();

    void on_exitButton_clicked();

    void reshow();

    void on_gameButton_2_clicked();

    void on_rankingButton_clicked();

    void on_gameButton_3_clicked();

private:
    Ui::MainWindow *ui;
    QSound *bgm;
};

#endif // MAINWINDOW_H

#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include<QMouseEvent>
#include "game.h"
#include <QPixmap>
#include <QPaintEvent>
#include <QSound>

namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = 0);
    ~GameWindow();
    virtual void paintEvent(QPaintEvent* e);
    bool update_record();
    void set_difficulty(int difficulty);
    
private slots:
    void on_returnButton_clicked();

    void on_stopButton_clicked();

signals:
    void sendsignal(); //这个函数用户向主界面通知关闭的消息

protected:
    void timerEvent(QTimerEvent *e);
    void mousePressEvent(QMouseEvent *e);

private:
    int timer;
    QSound* bgm;
    Ui::GameWindow *ui;
    Game* game;
    bool write_record;
};

#endif // GAMEWINDOW_H

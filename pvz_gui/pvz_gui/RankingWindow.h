#ifndef RANKINGWINDOW_H
#define RANKINGWINDOW_H

#include <QMainWindow>
#include <QSound>

namespace Ui {
class RankingWindow;
}

class RankingWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RankingWindow(QWidget *parent = 0);
    ~RankingWindow();
    virtual void paintEvent(QPaintEvent* e);

signals:
    void sendsignal(); //这个函数用户向主界面通知关闭的消息

private slots:
    void on_pushButton_clicked();

private:
    Ui::RankingWindow *ui;
    QSound * bgm;
    int score[3];
};

#endif // RANKINGWINDOW_H

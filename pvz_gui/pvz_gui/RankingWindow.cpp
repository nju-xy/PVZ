#include "RankingWindow.h"
#include "ui_RankingWindow.h"
#include <QPainter>
#include <iostream>
#include <fstream>
using namespace std;

RankingWindow::RankingWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RankingWindow)
{
    ui->setupUi(this);

    ifstream in_file("..\\pvz_gui\\ranking.txt", ios::in);
    // ifstream in_file("D:\\Code\\pvz\\pvz_gui\\pvz_gui\\ranking.txt", ios::in);
    if(!in_file) { // 打开失败
        cout << "Cannot open this file" << endl;
        exit(-1);
    }
    in_file >> score[0];
    in_file >> score[1];
    in_file >> score[2];
    in_file.close();

    bgm = new QSound(":\\music\\game_end.wav",this);
    bgm->play();//
    bgm->setLoops(-1);//循环次数，-1代表一致循环
}

RankingWindow::~RankingWindow()
{
    delete ui;
}

void RankingWindow::on_pushButton_clicked()
{
    bgm->stop();
    emit sendsignal();
    this->close();
}

void RankingWindow::paintEvent(QPaintEvent* e) {
    QPainter painter(this);
    QFont font("Microsoft YaHei", 20, 75); //第一个属性是字体（微软雅黑），第二个是大小，第三个是加粗（权重是75）
    painter.setFont(font);
    painter.drawText(450, 220, QString::number(score[0]).prepend("1:    "));
    painter.drawText(450, 300, QString::number(score[1]).prepend("2:    "));
    painter.drawText(450, 380, QString::number(score[2]).prepend("3:    "));
}

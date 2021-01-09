#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "GameWindow.h"
#include "RankingWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    bgm = new QSound(":\\music\\menu.wav",this);
    bgm->play();//
    bgm->setLoops(-1);//循环次数，-1代表一致循环
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::reshow(){
    this->show();
    bgm->play();
}

void MainWindow::on_gameButton_clicked() // 普通难度
{
    this->hide();//主界面关闭
    bgm->stop();
    GameWindow *game_window = new GameWindow(this); //新建子界面
    game_window->set_difficulty(1);
    connect(game_window, SIGNAL(sendsignal()), this, SLOT(reshow())); //当点击子界面时，调用主界面的reshow()函数
    game_window->show(); //子界面出现
}

void MainWindow::on_exitButton_clicked()
{
    exit(0);
}

void MainWindow::on_gameButton_2_clicked() // 困难难度
{
    this->hide();//主界面关闭
    bgm->stop();
    GameWindow *game_window = new GameWindow(this); //新建子界面
    game_window->set_difficulty(2);
    connect(game_window, SIGNAL(sendsignal()), this, SLOT(reshow())); //当点击子界面时，调用主界面的reshow()函数
    game_window->show(); //子界面出现
}

void MainWindow::on_rankingButton_clicked() // 排行榜
{
    this->hide();//主界面关闭
    bgm->stop();
    RankingWindow *ranking_window = new RankingWindow(this); //新建子界面
    connect(ranking_window, SIGNAL(sendsignal()), this, SLOT(reshow())); //当点击子界面时，调用主界面的reshow()函数
    ranking_window->show(); //子界面出现
}

void MainWindow::on_gameButton_3_clicked() // 迷雾模式
{
    this->hide();//主界面关闭
    bgm->stop();
    GameWindow *game_window = new GameWindow(this); //新建子界面
    game_window->set_difficulty(3);
    connect(game_window, SIGNAL(sendsignal()), this, SLOT(reshow())); //当点击子界面时，调用主界面的reshow()函数
    game_window->show(); //子界面出现
}

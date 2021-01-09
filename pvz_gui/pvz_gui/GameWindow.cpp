#include "GameWindow.h"
#include "common.h"
#include "QtCore"
#include "ui_GameWindow.h"
#include <QPainter>
#include <algorithm>
#include <fstream>
using namespace std;

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose, 1);

    write_record = false;
    srand(time(0));
    ui->label->setVisible(false);
    ui->label_record->setVisible(false);
    ui->stopButton->setText("暂停");

    bgm = new QSound(":\\music\\background.wav",this);
    bgm->play();//
    bgm->setLoops(-1);//循环次数，-1代表一致循环


}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::set_difficulty(int difficulty) {
    game = new Game(difficulty);
    timer = startTimer(100);   //启动对象的定时器每隔0.1秒触发一次timerEvent事件
}

void GameWindow::paintEvent(QPaintEvent* e) {
    QPainter painter(this);

    vector<Zombie *> zombies = game->get_zombies();
    vector<Bullet *> bullets = game->get_bullets();
    vector<Ball *> balls = game->get_balls();
    vector<vector<Plant *>> plants = game->get_plants();
    int sun = game->get_sun();
    int score = game->get_score();
    Market* market = game->get_market();
    vector<pair<pair<int, int>, int>> booms = game->get_booms();

    // 商店栏
    painter.setBrush(QColor(165, 42, 42));
    painter.drawRect(15, 15, 970, 120);

    // 阳光
    QPixmap image;
    image.load(":\\figs\\plants\\Sun_0.png");
    painter.drawPixmap(20, 20, 75, 75, image);
    painter.setPen(QColor(255, 255, 0));
    painter.drawText(20, 115, QString::number(sun).prepend("阳光："));

    // 铲子
    if(market->get_shovel())
        painter.setBrush(QColor(154, 205, 50));
    else
        painter.setBrush(QColor(202, 255, 112));
    painter.drawRect(20 + 80 * 11, 20, 75, 75);
    image.load(":\\figs\\plants\\shovel.png");
    painter.drawPixmap(20 + 11 * 80, 20, 75, 75, image);

    // 商店
    for(int i = 0; i < market->get_number(); ++i) {
        if(market->get_chosen() && market->get_chosen()->get_no() == i)
            painter.setBrush(QColor(154, 205, 50));
        else
            painter.setBrush(QColor(202, 255, 112));
        painter.drawRect(20 + 80 * (i + 1), 20, 75, 75);

        Item* item = market->get_item_k(i);
        // painter.drawText(45 + 80 * (i + 1), 60, QString::number((item->get_timer() + 9) / 10));
        int cd = item->get_timer();
        int totol_cd = item->get_cd();
        if(cd > 0) {
            painter.setBrush(QColor(181, 181, 181));
            painter.drawRect(20 + 80 * (i + 1), 20, 75.0 * cd / totol_cd, 75);
        }
        painter.setPen(QColor(255, 255, 0));
        painter.drawText(50 + 80 * (i + 1), 115, QString::number(item->get_cost()));
        // painter.drawText(30 + 75 * (i + 1), 40, item->get_plant()->get_name());
        QPixmap image1;
        QString path = QString::fromStdString(item->get_plant()->get_path()).prepend(":\\figs\\plants\\");
        int flag = image1.load(path);
        // cout << item->get_plant()->get_name() << " : " << ret << endl;
        if(flag)
            painter.drawPixmap(20 + 80 * (i + 1), 20, 75, 75,image1);
        else {
            painter.setPen(QColor(0, 0, 0));
            painter.drawText(20 + 80 * (i + 1), 20 + 30, item->get_plant()->get_name());
            painter.setPen(QColor(255, 255, 0));
        }
    }

    // 草地
    for(int i = 0; i < nr_row; ++i) {
        for(int j = 0; j < nr_col; ++j) {
            if((i + j) % 2) {
                painter.setBrush(QColor(0, 139, 0));
            }
            else {
                painter.setBrush(QColor(0, 205, 0));
            }
            painter.drawRect(50 + j * 100, 200 + i * 100, 100, 100);
        }
    }
    painter.setPen(QColor(0, 0, 0));
    painter.drawText(800, 550, QString::number(score).prepend("分数："));

    // 植物
    for(int i = 0; i < nr_row; ++i) {
        for(int j = 0; j < nr_col; ++j) {
            if(plants[i][j]) {
                QPixmap image1;
                QString path = QString::fromStdString(plants[i][j]->get_path()).prepend(":\\figs\\plants\\");
                int flag = image1.load(path);
                if(flag) {
                    if(plants[i][j]->block_jump()) {
                        painter.drawPixmap(20 + j * 100, 150 + i * 100, 150, 150, image1);
                    }
                    else {
                        painter.drawPixmap(60 + j * 100, 200 + i * 100, 80, 80, image1);
                    }
                }
                else
                    painter.drawText(50 + j * 100 + 30, 200 + i * 100 + 50, plants[i][j]->get_name());
                if(plants[i][j]->check_pumpkin() > 0) {
                    image1.load(":\\figs\\plants\\Pumpkin_0.png");
                    painter.drawPixmap(50 + j * 100 - 10, 200 + i * 100 + 30, 120, 80, image1);
                }
            }
        }
    }

    // 僵尸
    for(Zombie* & zombie:zombies) {
        pair<int, int> pos = zombie->get_pos();
        // painter.drawText(50 + pos.second * 100 / 12, 200 + pos.first * 100 + 50, zombie->get_name());

        QPixmap image1;
        QString path = QString::fromStdString(zombie->get_path()).prepend(":\\figs\\zombies\\");
        int flag = image1.load(path);
        if(flag)
            painter.drawPixmap(50 + pos.second * 100 / 12 - 80, 200 + pos.first * 100 - 50, 150, 150, image1);
        else
            painter.drawText(50 + pos.second * 100 / 12, 200 + pos.first * 100 + 50, zombie->get_name());
    }


    // 子弹
    for(Bullet* & bullet:bullets) {
        pair<int, int> pos = bullet->get_pos();
        // painter.drawText(50 + pos.second * 100 / 12, 200 + pos.first * 100 + 50, "o");
        if(bullet->get_buff())
            painter.setBrush(QColor(175, 238, 238));
        else
            painter.setBrush(QColor(255, 255, 0));
        painter.drawEllipse(50 + pos.second * 100 / 12, 200 + pos.first * 100 + 15, 20, 20);
    }

    for(Ball* & ball: balls) {
        pair<double, double> pos = ball->get_pos_double();
        painter.setBrush(QColor(165, 42, 42));
        painter.drawEllipse(50 + int(pos.second * 100 / 12), 200 + int(pos.first * 100) + 15, 30, 30);
    }

    if(game->get_difficulty() == 3) { // 迷雾模式
        QPixmap image1;
        image1.load(":\\figs\\fog.png");
        painter.drawPixmap(450, 150, 320, 400, image1);
    }

    for(auto &boom : booms) {
        int x = boom.first.first;
        int y = boom.first.second;
        int d = boom.second;
        QPixmap image1;
        image1.load(":\\figs\\Boom.png");
        if(d == 3)
            painter.drawPixmap(50 + y * 100 / 12 - 125, 200 + x * 100 - 125, 300, 300, image1);
        else
            painter.drawPixmap(50 + y * 100 / 12 - 30, 200 + x * 100 - 30, 100, 100, image1);
    }
    game->delete_booms();

    if(timer == -1) {
        ui->label->setVisible(true);
    }
    else {
        ui->label->setVisible(false);
    }
    if(game->over()) {
        QPixmap image1;
        image1.load(":\\figs\\game_over.png");
        painter.drawPixmap(100, 100, 564, 468, image1);

        if(!write_record) {
            bool highest = update_record();
            if(highest) {
                ui->label_record->setVisible(true);
            }
        }
    }
}

bool GameWindow::update_record() {
    vector<int> score(3);
//    ifstream in_file("D:\\Code\\pvz\\pvz_gui\\pvz_gui\\ranking.txt", ios::in);
    ifstream in_file("..\\pvz_gui\\ranking.txt", ios::in);

    if(!in_file) { // 打开失败
        cout << "Cannot open this file" << endl;
        exit(-1);
    }
    in_file >> score[0];
    in_file >> score[1];
    in_file >> score[2];
    in_file.close();

    int temp = game->get_score();

    bool ret = false;
    if(temp > score[0]) {
        ret = true;
    }

    score.push_back(temp);
    sort(score.begin(), score.end(), greater<int>());



//    ofstream out_file("D:\\Code\\pvz\\pvz_gui\\pvz_gui\\ranking.txt", ios::out);
    ofstream out_file("..\\pvz_gui\\ranking.txt", ios::out);

    if(!out_file) { // 打开失败
        cout << "Cannot open this file" << endl;
        exit(-1);
    }
    out_file << score[0] << endl;
    out_file << score[1] << endl;
    out_file << score[2] << endl;
    out_file.close();
    write_record = true;
    return ret;
}

void GameWindow::mousePressEvent(QMouseEvent *e) {
    int x = e->x();
    int y = e->y();
    Market* market = game->get_market();

    if(x >= 900 && x < 980 && y >= 20 && y <= 100) { // 铲子
        market->cancel_choose();
        market->choose_shovel();
    }


    // 商店购买
    for(int i = 0; i < market->get_number(); ++i) {
        if(x >= 45 + 75 * (i + 1) && x < 45 + 75 * (i + 1) + 70 && y >= 20 && y < 90) {
            auto item = market->get_item_k(i);
            if (item->get_timer() == 0 && item->get_cost() <= game->get_sun()) {
                // sun -= item->get_cost();
                market->choose_item(i);
                market->cancel_choose_shovel();
            }
        }
    }

    // 种植
    vector<vector<Plant*>> plants = game->get_plants();
    Item *chosen_item = market->get_chosen();
    if(market->get_shovel()) {
        for(int i = 0; i < nr_row; ++i) {
            for(int j = 0; j < nr_col; ++j) {
                if(x >= 50 + j * 100 && x < 150 + j * 100 && y >= 200 + i * 100 && y < 300 + i * 100) {
                    game->delete_plant(i, j);
                    market->cancel_choose_shovel();
                }
            }
        }
    }
    if(chosen_item) {
        for(int i = 0; i < nr_row; ++i) {
            for(int j = 0; j < nr_col; ++j) {
                if(x >= 50 + j * 100 && x < 150 + j * 100 && y >= 200 + i * 100 && y < 300 + i * 100) {
                    if (chosen_item->get_no() == market->number_of_items() - 1) { // 南瓜头
                        Plant *plant = plants[i][j];
                        if (plant && plant->check_pumpkin() <= 0) {
                            // 南瓜头必须种在本来没有南瓜头的植物上
                            plant->add_pumpkin();
                            chosen_item->reset_timer();
                            market->cancel_choose();
                            game->minus_sun(chosen_item->get_cost());
                        }
                    }
                    else if (!plants[i][j]) {
                        Plant *plant = chosen_item->get_plant();
                        chosen_item->reset_timer();
                        plant->change_pos(i, j * 12 + 5);
                        game->add_plant(plant, i, j);
                        market->cancel_choose();
                        game->minus_sun(chosen_item->get_cost());
                    }
                }
            }
        }
    }

}

void GameWindow::timerEvent(QTimerEvent *e) { // 每一帧更新游戏
    if(!game->over()) {
        game->update();
        update();
    }
}

void GameWindow::on_returnButton_clicked()
{
    if(!write_record)
        update_record();
    bgm->stop();
    emit sendsignal();
    this->close();
}



void GameWindow::on_stopButton_clicked()
{
    if(!game->over()) {
        if(timer != -1) {
            killTimer(timer);
            timer = -1;
            ui->stopButton->setText("继续");
        }
        else {
            timer = startTimer(100);
            ui->stopButton->setText("暂停");
        }
    }
}

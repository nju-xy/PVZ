//
// Created by xy on 2020/10/5.
//

#include "game.h"

Board board;
Painter painter;

pair<int, int> Game::get_choose() {
    return choose;
}
int Game::get_sun() const {
    return sun;
}
int Game::get_score() const {
    return score;
}
int Game::get_game_time() const {
    return game_time;
}
int Game::get_chosen_plant() const {
    return chosen_plant;
}
void Game::add_timer() {
    game_time ++;
    for(auto &zombie : zombies) {
        if(zombie)
            zombie->add_timer();
    }
    for(auto &bullet : bullets) {
        if(bullet)
            bullet->add_timer();
    }
    for(auto &plant : plants) {
        if(plant)
            plant->add_timer();
    }
}

void Game::update() { // 游戏每一帧内做的所有事情
    add_timer();
    update_zombies(); // 更新僵尸状态
    update_bullets(); // 更新子弹
    gen_sun(); // 产生太阳

    update_board(); // 在地图上布置僵尸、子弹和植物
    painter.paint(board); // 将地图画出来
    listen_keyboard(); // 检测键盘
}

void Game::update_board() {
    board.clear();
    remove_dead();
    for(auto plant : plants) {
        board.add_plant(plant);
    }
    for(auto zombie : zombies) {
        board.add_zombie(zombie);
    }
    for(auto bullet : bullets) {
        board.add_bullet(bullet);
    }
}

void Game::remove_dead() {
    for(auto iter = plants.begin(); iter!=plants.end(); )
    {
        Plant* plant = *iter;
        if(!plant || plant->get_life() <= 0)
            iter = plants.erase(iter);
        else
            iter ++;
    }
    for(auto iter = zombies.begin(); iter!=zombies.end(); )
    {
        Zombie* zombie = *iter;
        if(!zombie || zombie->get_life() <= 0 || zombie->get_pos().second < 0)
            iter = zombies.erase(iter);
        else
            iter ++;
    }
    for(auto iter = bullets.begin(); iter!=bullets.end(); )
    {
        Bullet* bullet = *iter;
        if(!bullet || bullet->get_life() <= 0 || bullet->get_pos().second >= board_width)
            iter = bullets.erase(iter);
        else
            iter ++;
    }
}

void Game::check_zombie_hit_plant() {
    // 如果僵尸碰到了植物，就按照攻速进行攻击；如果植物没血了就死亡
    // 否则，僵尸继续前进
    for(auto & zombie : zombies)
    {
        bool flag = false;
        for(auto iter2 = plants.begin(); iter2 != plants.end(); iter2++) {
            Plant* plant = *iter2;
            if(plant->get_pos() == zombie->get_pos()) { // 僵尸所在格子有植物
                flag = true;
                if(zombie->get_timer() % zombie_attack_rate == 0) {
                    plant->minus_life(zombie->get_attack()); // 攻击植物
                    if(plant->get_life() <= 0) {
                        plant->~Plant();
                        plants.erase(iter2);
                        iter2--;
                        continue;
                    }
                }
            }
        }
        if(!flag) {
            zombie->update_pos();
            if(zombie->get_pos().second < 0)
                game_over();
        }
    }
}

void Game::update_zombies() {
    // 首先判断所有僵尸所在的格子有没有植物
    check_zombie_hit_plant();
    // 生成僵尸
    gen_zombies();
    // 再判断前进以后有没有撞到子弹
    check_bullet_hit_zombie();
}

void Game::check_bullet_hit_zombie() {
    // 如果僵尸撞到子弹，就子弹消失，且僵尸扣血
    // 如果僵尸没血了就死亡
    for(auto iter1 = zombies.begin(); iter1 !=zombies.end(); iter1++)
    {
        Zombie* zombie = *iter1;
        for(auto iter2 = bullets.begin(); iter2 != bullets.end(); iter2++) {
            Bullet* bullet = *iter2;
            if(bullet->get_pos() == zombie->get_pos()) { // 僵尸所在格子有子弹
                // 僵尸扣血
                zombie->minus_life(bullet->get_attack());
                if(zombie->get_life() <= 0) {
                    // 僵尸没血了就消失
                    zombie->~Zombie();
                    zombies.erase(iter1);
                    iter1--;
                    score += 100;
                    break;
                }
                // 子弹一定消失
                bullet->minus_life(1);
                bullet->~Bullet();
                bullets.erase(iter2);
                iter2--;
            }
        }
    }
}

void Game::update_bullets() {
    for(auto & bullet : bullets) {
        bullet->update_pos();
    }
    gen_bullets();
    // 检查新子弹刚发射或者老子弹移动后的位置有没有僵尸，如果有，直接造成伤害
    check_bullet_hit_zombie();
}
void Game::gen_zombies() {
    if(game_time % zombie_rate == 0) {
        Zombie* zom = new Zombie(rand() % board_height);
        zombies.push_back(zom);
    }
}

void Game::gen_bullets() {
    for(auto plant : plants) {
        Bullet* bul = plant->shot();
        if(bul)
            bullets.push_back(bul);
    }
};

void Game::gen_sun() {
    if(game_time % sun_rate == 0) {
        sun += one_sun;
    }
}

void Game::game_over() {
    painter.game_over();
    Sleep(5000);
    exit(0);
}

void Game::listen_keyboard() {
    char ch;
    if (_kbhit()){ //如果有按键按下，则_kbhit()函数返回真
        ch = _getch(); //使用_getch()函数获取按下的键值
        get_key(ch);
    }
}

void Game::get_key(char ch) {
    switch (ch) {
        case 'b': // 购买植物
            if(choose.first == board_height) {
                chosen_plant = choose.second + 1;
            }
            break;
        case 'x': // 取消购买植物
            chosen_plant = 0;
            break;
        case 'c': // 种植植物
            if(chosen_plant && sun >= plant_cost) {
                Plant* plant = new Plant(choose.first, choose.second);
                plants.push_back(plant);
                chosen_plant = 0;
                sun -= plant_cost;
            }
            break;
        case 72: //上
            choose.first = MAX(0, choose.first - 1);
            if(choose.first < board_height)
                choose.second = MIN(board_width - 1, choose.second);
            break;
        case 80: //下
            choose.first = MIN(board_height, choose.first + 1);
            if(choose.first == board_height)
                choose.second = MIN(plant_kinds - 1, choose.second);
            break;
        case 75: //左
            choose.second = MAX(0, choose.second - 1);
            break;
        case 77: //右
            if(choose.first != board_height)
                choose.second = MIN(board_width - 1, choose.second + 1);
            else
                choose.second = MIN(plant_kinds - 1, choose.second + 1);
            break;
    }
}

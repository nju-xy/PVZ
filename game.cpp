//
// Created by xy on 2020/10/5.
//

#include "game.h"

//pair<int, int> Game::get_choose() {
//    return choose;
//}
//int Game::get_sun() const {
//    return sun;
//}
//int Game::get_score() const {
//    return score;
//}
//int Game::get_game_time() const {
//    return game_time;
//}
//Market* Game::get_market() const {
//    return market;
//}

void Game::add_timer() {
    game_time ++;
    for(int i = 0; i < market->number_of_items(); ++i) {
        market->get_item_k(i)->update_timer();
    }
    for(auto &zombie : zombies) {
        assert(zombie);
        if(zombie)
            zombie->add_timer();
    }
    for(auto &bullet : bullets) {
        assert(bullet);
        if(bullet)
            bullet->add_timer();
    }
//    for(auto &plant : plants) {
//        if(plant)
//            plant->add_timer();
//    }
    for(int i = 0; i < nr_row; ++i) {
        for (int j = 0; j < nr_col; ++j) {
            if(plants[i][j])
                plants[i][j]->add_timer();
        }
    }
}

void Game::update() { // 游戏每一帧内做的所有事情
    painter->init();
    add_timer();
    update_zombies(); // 更新僵尸状态
    update_bullets(); // 更新子弹
    gen_sun(); // 产生太阳

    remove_dead();
    update_board(); // 在地图上布置僵尸、子弹和植物
    painter->paint(choose, sun, score, market); // 将地图画出来
    listen_keyboard(); // 检测键盘
}

void Game::update_board() {
    for(int i = 0; i < nr_row; ++i) {
        for (int j = 0; j < nr_col; ++j) {
            if(plants[i][j]) {
                painter->add_plant(plants[i][j]);
            }
        }
    }
    for(auto zombie : zombies) {
        assert(zombie);
        painter->add_zombie(zombie);
    }
    for(auto bullet : bullets) {
        assert(bullet);
        painter->add_bullet(bullet);
    }
}

void Game::remove_dead() {
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
        if(!bullet || bullet->get_life() <= 0 || bullet->get_pos().second >= nr_col * 12 + 1)
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
        assert(zombie);
        bool flag = false;
        auto pos = zombie->get_pos();
        pos.second = (pos.second - 1) / 12;
        if(pos.second < nr_col && plants[pos.first][pos.second]) { // 僵尸前进一步以后所在格子有植物
            Plant* plant = plants[pos.first][pos.second];
            if(strcmp(plant->get_name(), "Squash  ")) { // 窝瓜不阻挡
                flag = true;
                if(zombie->get_timer() % 10 == 0) {
                    plant->minus_life(zombie->get_attack()); // 攻击植物
                    if(strcmp(plant->get_name(), "Garlic  ") == 0 && plant->check_pumpkin() <= 0) {
                        zombie->random_change_pos();
                    }
                    if(plant->get_life() <= 0) {
                        plant->~Plant();
                        plants[pos.first][pos.second] = nullptr;
                    }
                }
            }
        }
        pos = zombie->get_pos();
        pos.second = (pos.second) / 12;
        if(pos.second < nr_col && plants[pos.first][pos.second]) { // 僵尸所在格子有窝瓜
            Plant* plant = plants[pos.first][pos.second];
            if(strcmp(plant->get_name(), "Squash  ") == 0) {
                auto pos2 = plant->get_pos();
                boom(pos2.first, pos2.second, 1);
                plants[pos.first][pos.second] = nullptr;
            }
            continue;
        }
        if(!flag) {
            assert(zombie);
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
                // 子弹一定消失
                bullet->minus_life(1);
                bullet->~Bullet();
                bullets.erase(iter2);
                iter2--;
                if(zombie->get_life() <= 0) {
                    // 僵尸没血了就消失
                    zombie->~Zombie();
                    zombies.erase(iter1);
                    iter1--;
                    score += 100;
                    break;
                }
                else if(bullet->get_buff()) {
                    zombie->add_buff(bullet->get_buff());
                }
            }
        }
    }
}

void Game::update_bullets() {
    for(auto & bullet : bullets) {
        assert(bullet);
        bullet->update_pos();
    }
    plant_shot();
    // 检查新子弹刚发射或者老子弹移动后的位置有没有僵尸，如果有，直接造成伤害
    check_bullet_hit_zombie();
}
void Game::gen_zombies() {
    if(game_time % zombie_rate == 0) {
        Zombie* zom = new Zombie(rand() % nr_row);
        zombies.push_back(zom);
    }
}

void Game::plant_shot() {
    for(int i = 0; i < nr_row; ++i) {
        for (int j = 0; j < nr_col; ++j) {
            if(plants[i][j]) {
                plants[i][j]->shot(bullets);
                if(strcmp(plants[i][j]->get_name(), "Cherry  ") == 0) {
                    auto pos = plants[i][j]->get_pos();
                    boom(pos.first, pos.second, 3);
                    plants[i][j] = nullptr;
                }
                else if(strcmp(plants[i][j]->get_name(), "Sun  ") == 0) {
                    ((Sunflower*)plants[i][j])->add_sun(sun);
                }
//                Bullet* bul = plants[i][j]->shot();
//                if(bul)
//                    bullets.push_back(bul);
            }
        }
    }
};

void Game::gen_sun() {
    if(game_time % sun_rate == 0) {
        sun += one_sun;
    }
}

void Game::game_over() {
    painter->game_over();
    Sleep(50000);
    exit(0);
}

void Game::boom(int x, int y, int d) {
    double r = d / 2.0;
    for(auto iter = zombies.begin(); iter !=zombies.end(); iter++) {
        Zombie* zombie = *iter;
        auto pos = zombie->get_pos();
        int x2 = pos.first, y2 = pos.second;
        if(x2 <= x + r && x2 >= x - r && y2 > y - r * 12 && y2 <= y + r * 12) {
            zombies.erase(iter);
            iter--;
        }
    }
    for(int i = (x + 0.5 - r) * 6 + 1; i < (x + 0.5 + r) * 6; ++i) {
        for (int j = y - 12 * r + 1; j <= y + 12 * r; ++j) {
            if(i < maps_height && i >= 0 && j >= 0 && j < maps_width)
                painter->add_boom(i, j);
        }
    }
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
        {
            if(choose.first >= nr_row) {
                // chosen_plant = choose.second + 1;
                auto item = market->get_item_k((choose.first - nr_row) * 3 + choose.second);
                if(item->get_timer() == 0 && item->get_cost() <= sun) {
                    sun -= item->get_cost();
                    market->choose_item((choose.first - nr_row) * 3 + choose.second);
                    choose.first = choose.second = 0;
                }
            }
            break;
        }
        case 'x': // 取消购买植物
        {
            if(market->get_chosen()) {
                sun += market->get_chosen()->get_cost();
                market->cancel_choose();
                choose.first = nr_row, choose.second = 0;
            }
            break;
        }
        case 'c': // 种植植物
        {
            Item* chosen_item = market->get_chosen();
            if(chosen_item) {
                if(chosen_item->get_no() == market->number_of_items() - 1) { // 南瓜头
                    Plant* plant = plants[choose.first][choose.second];
                    if(plant && plant->check_pumpkin() <= 0) {
                        // 南瓜头必须种在本来没有南瓜头的植物上
                        plant->add_pumpkin();
                        market->cancel_choose();
                        choose.first = nr_row, choose.second = 0;
                    }
                }
                if(!plants[choose.first][choose.second]) {
                    Plant* plant = chosen_item->get_plant();
                    chosen_item->reset_timer();
                    plant->change_pos(choose.first, choose.second * 12 + 5);
                    plants[choose.first][choose.second] = plant;
                    market->cancel_choose();
                    choose.first = nr_row, choose.second = 0;
                }
            }
            break;
        }
        case 72: //上
        {
            choose.first = MAX(0, choose.first - 1);
            if(choose.first < nr_row)
                choose.second = MIN(nr_col - 1, choose.second);
            break;
        }
        case 80: //下
        {
            if(market->get_chosen())
                choose.first = MIN(nr_row - 1, choose.first + 1);
            else {
                choose.first = MIN(nr_row + 3, choose.first + 1);
                if(choose.first == nr_row || choose.first == nr_row + 3)
                    choose.second = 0;
            }
            break;
        }
        case 75: //左
        {
            choose.second = MAX(0, choose.second - 1);
            break;
        }
        case 77: //右
        {
            if(choose.first < nr_row)
                choose.second = MIN(nr_col - 1, choose.second + 1);
            else if(choose.first == nr_row + 3)
                choose.second = 0;
            else
                choose.second = MIN(2, choose.second + 1);
            break;
        }
        default:
            break;
    }
}

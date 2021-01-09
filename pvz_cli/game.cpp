//
// Created by xy on 2020/10/5.
//

#include "game.h"

void Game::add_timer() {
    game_time++;
    for (int i = 0; i < market->number_of_items(); ++i) {
        market->get_item_k(i)->update_timer();
    }
    for (auto &zombie : zombies) {
        assert(zombie);
        if (zombie)
            zombie->add_timer();
    }
    for (auto &bullet : bullets) {
        assert(bullet);
        if (bullet)
            bullet->add_timer();
    }
//    for(auto &plant : plants) {
//        if(plant)
//            plant->add_timer();
//    }
    for (int i = 0; i < nr_row; ++i) {
        for (int j = 0; j < nr_col; ++j) {
            if (plants[i][j])
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

bool cmp(Zombie *a, Zombie *b) {
    auto pos1 = a->get_pos();
    auto pos2 = b->get_pos();
    return (pos1.first < pos2.first) || (pos1.first == pos2.first && pos1.second < pos2.second);
}

void Game::update_board() {
    for (int i = 0; i < nr_row; ++i) {
        for (int j = 0; j < nr_col; ++j) {
            if (plants[i][j]) {
                painter->add_plant(plants[i][j]);
            }
        }
    }
    sort(zombies.begin(), zombies.end(), cmp);
    for (auto zombie : zombies) {
        assert(zombie);
        painter->add_zombie(zombie);
    }
    for (auto bullet : bullets) {
        assert(bullet);
        painter->add_bullet(bullet);
    }
}

void Game::remove_dead() {
    for (auto iter = zombies.begin(); iter != zombies.end();) {
        Zombie *zombie = *iter;
        if (!zombie || zombie->get_life() <= 0 || zombie->get_pos().second < 0)
            iter = zombies.erase(iter);
        else
            iter++;
    }
    for (auto iter = bullets.begin(); iter != bullets.end();) {
        Bullet *bullet = *iter;
        if (!bullet || bullet->get_life() <= 0 || bullet->get_pos().second >= nr_col * 12 + 1)
            iter = bullets.erase(iter);
        else
            iter++;
    }
}

void Game::check_zombie_hit_plant() {
    // 如果僵尸碰到了植物，就按照攻速进行攻击；如果植物没血了就死亡
    // 否则，僵尸继续前进
    // for (auto &zombie : zombies) {
    for(auto iter = zombies.begin(); iter < zombies.end(); ++iter) {
        auto zombie = *iter;
        assert(zombie);
        bool flag = false;
        auto pos = zombie->get_pos();
        pos.second = (pos.second - 1) / 12;
        // 僵尸是投石僵尸
        if(zombie->boom_random()) {
            zombie_boom(zombie->get_pos().first, zombie->get_pos().second);
            zombie->~Zombie();
            zombies.erase(iter);
            iter--;
            score += 100;
            continue;
        }
        if (strcmp(zombie->get_name(), "catapult") == 0) {
            for (int i = 0; i < nr_col; ++i) {
                Plant *plant = plants[pos.first][i];
                if (plant) {
                    // int damage = ((Catapult *) zombie)->ball_damage();
                    int damage = zombie->ball_damage();
                    plant->minus_life(damage); // 攻击植物
                    if (damage) {
                        painter->add_boom(6 * pos.first + 3, 12 * i + 1);
                    }
                    flag = true;
                    if (plant->get_life() <= 0) {
                        plant->~Plant();
                        plants[pos.first][i] = nullptr;
                    }
                    break;
                }
            }
//            if(flag)
//                continue;
        }
        if (!flag && pos.second < nr_col && plants[pos.first][pos.second]) { // 僵尸已经被阻挡
            Plant *plant = plants[pos.first][pos.second];
            if (plant->if_block()) { // 窝瓜不阻挡
                flag = true;
                if (zombie->get_timer() % 10 == 0) {
                    if (!plant->block_jump() && zombie->jump()) {
                        zombie->change_pos(pos.first, pos.second * 12 - 1);
                    } else {
                        plant->minus_life(zombie->get_attack()); // 攻击植物
                        if (plant->change_zombie_line()) {
                            zombie->random_change_line();
                        }
                        if (plant->get_life() <= 0) {
                            plant->~Plant();
                            plants[pos.first][pos.second] = nullptr;
                        }
                    }
                }
            }
        }
        pos = zombie->get_pos();
        pos.second = (pos.second) / 12;
        if (pos.second < nr_col && plants[pos.first][pos.second]) { // 僵尸所在格子有窝瓜
            Plant *plant = plants[pos.first][pos.second];
            if (plant->boom_with_zombie()) {
                auto pos2 = plant->get_pos();
                plant_boom(pos2.first, pos2.second, 1);
                plants[pos.first][pos.second] = nullptr;
            }
            continue;
        }
        if (!flag) { // 僵尸没被阻挡，继续前进
            assert(zombie);
            zombie->update_pos();
            if (zombie->get_pos().second < 0)
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
    for (auto iter1 = zombies.begin(); iter1 != zombies.end(); iter1++) {
        Zombie *zombie = *iter1;
        for (auto iter2 = bullets.begin(); iter2 != bullets.end(); iter2++) {
            Bullet *bullet = *iter2;
            if (bullet->get_pos() == zombie->get_pos()) { // 僵尸所在格子有子弹
                // 僵尸扣血
                zombie->minus_life(bullet->get_attack());
                // 子弹一定消失
                bullet->minus_life(1);
                bullet->~Bullet();
                bullets.erase(iter2);
                iter2--;
                if (zombie->get_life() <= 0) {
                    // 僵尸没血了就消失
//                    if (zombie->boom_after_death()) { // 死后 3 * 3 爆炸
//                        zombie_boom(zombie->get_pos().first, zombie->get_pos().second);
//                    }
                    zombie->~Zombie();
                    zombies.erase(iter1);
                    iter1--;
                    score += 100;
                    break;
                } else if (bullet->get_buff()) {
                    zombie->add_buff(bullet->get_buff());
                }
            }
        }
    }
}

void Game::update_bullets() {
    for (auto &bullet : bullets) {
        assert(bullet);
        bullet->update_pos();
    }
    plant_shot();
    // 检查新子弹刚发射或者老子弹移动后的位置有没有僵尸，如果有，直接造成伤害
    check_bullet_hit_zombie();
}

void Game::gen_zombies() {
    if (game_time % 75 == 0) {
        int line = rand() % nr_row;
        Zombie *zom;
        if (game_time <= 300) { // 前30s
            zom = new Common();
        } else if (game_time >= 1000 && game_time % 300 == 0) {
            zom = new Catapult;
        } else { // 20 - 100s
            int r = rand() % 100;
            if (r < 45) {
                zom = new Common;
            } else if (r < 65) {
                zom = new Conehead;
            } else if (r < 80) {
                zom = new Newspaper;
            } else if (r < 93) {
                zom = new Pole_Vaunting;
            } else {
                zom = new Jack_in_the_Box;
            }
        }

//        line = 0;
//        zom = new Catapult;
        zom->change_pos(line, maps_width - 15);
        zombies.push_back(zom);
    }
}

void Game::plant_shot() {
    for (int i = 0; i < nr_row; ++i) {
        for (int j = 0; j < nr_col; ++j) {
            if (plants[i][j]) {
                auto ret_bullets = plants[i][j]->shot();
                for(auto & bullet : ret_bullets) {
                    bullets.push_back(bullet);
                }
                int add_sun = plants[i][j]->add_sun();
                sun += add_sun;
                if (plants[i][j]->boom_at_once()) {
                    auto pos = plants[i][j]->get_pos();
                    plant_boom(pos.first, pos.second, 3);
                    plants[i][j] = nullptr;
                }
            }
        }
    }
};

void Game::gen_sun() {
    if (game_time % sun_rate == 0) {
        sun += one_sun;
    }
}

void Game::game_over() {
    painter->game_over();
    system("pause");
    exit(0);
}

void Game::zombie_boom(int x, int y) { // 爆炸（僵尸）
    for (int i = 0; i < nr_row; ++i) {
        for (int j = 0; j < nr_col; ++j) {
            if (!plants[i][j])
                continue;
            auto pos = plants[i][j]->get_pos();
            if (abs(pos.first - x) <= 1 && abs(pos.second - y) <= 18) {
                plants[i][j]->~Plant();
                plants[i][j] = nullptr;
            }
        }
    }
    for (int i = (x - 1) * 6 + 1; i < (x + 2) * 6; ++i) {
        for (int j = y - 18; j <= y + 18; ++j) {
            if (i < maps_height && i >= 0 && j >= 0 && j < maps_width)
                painter->add_boom(i, j);
        }
    }
}

void Game::plant_boom(int x, int y, int d) { // 爆炸（植物）
    double r = d / 2.0;
    for (auto iter = zombies.begin(); iter != zombies.end(); iter++) {
        Zombie *zombie = *iter;
        auto pos = zombie->get_pos();
        int x2 = pos.first, y2 = pos.second;
        if (x2 <= x + r && x2 >= x - r && y2 > y - r * 12 && y2 <= y + r * 12) {
//            if (zombie->boom_after_death()) {
//                zombie_boom(x2, y2);
//            }
            zombies.erase(iter);
            iter--;
        }
    }
    for (int i = (x + 0.5 - r) * 6 + 1; i < (x + 0.5 + r) * 6; ++i) {
        for (int j = y - 12 * r + 1; j <= y + 12 * r; ++j) {
            if (i < maps_height && i >= 0 && j >= 0 && j < maps_width)
                painter->add_boom(i, j);
        }
    }
}

void Game::listen_keyboard() {
    char ch;
    if (_kbhit()) { //如果有按键按下，则_kbhit()函数返回真
        ch = _getch(); //使用_getch()函数获取按下的键值
        get_key(ch);
    }
}

extern HANDLE screen;

void Game::get_key(char ch) {
    switch (ch) {
        case 'b': // 购买植物
        {
            if (choose.first >= nr_row) {
                auto item = market->get_item_k((choose.first - nr_row) * 3 + choose.second);
                if (item->get_timer() == 0 && item->get_cost() <= sun) {
                    sun -= item->get_cost();
                    market->choose_item((choose.first - nr_row) * 3 + choose.second);
                    choose.first = choose.second = 0;
                }
            }
            break;
        }
        case 'x': // 取消购买植物
        {
            if (market->get_chosen()) {
                sun += market->get_chosen()->get_cost();
                market->cancel_choose();
                choose.first = nr_row, choose.second = 0;
            }
            break;
        }
        case 'c': // 种植植物
        {
            Item *chosen_item = market->get_chosen();
            if (chosen_item) {
                if (chosen_item->get_no() == market->number_of_items() - 1) { // 南瓜头
                    Plant *plant = plants[choose.first][choose.second];
                    if (plant && plant->check_pumpkin() <= 0) {
                        // 南瓜头必须种在本来没有南瓜头的植物上
                        plant->add_pumpkin();
                        chosen_item->reset_timer();
                        market->cancel_choose();
                        choose.first = nr_row, choose.second = 0;
                    }
                }
                else if (!plants[choose.first][choose.second]) {
                    Plant *plant = chosen_item->get_plant();
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
            if (choose.first < nr_row)
                choose.second = MIN(nr_col - 1, choose.second);
            break;
        }
        case 80: //下
        {
            if (market->get_chosen())
                choose.first = MIN(nr_row - 1, choose.first + 1);
            else {
                choose.first = MIN(nr_row + 3, choose.first + 1);
                if (choose.first == nr_row || choose.first == nr_row + 3)
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
            if (choose.first < nr_row)
                choose.second = MIN(nr_col - 1, choose.second + 1);
            else if (choose.first == nr_row + 3)
                choose.second = 0;
            else
                choose.second = MIN(2, choose.second + 1);
            break;
        }
        case 32: {
            system("pause");
            COORD position;
            position.X = 0, position.Y = 27;
            SetConsoleCursorPosition(screen, position);
            cout << "                        " << endl;
            break;
        }
        default:
            break;
    }
}

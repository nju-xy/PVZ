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
    for (int i = 0; i < nr_row; ++i) {
        for (int j = 0; j < nr_col; ++j) {
            if (plants[i][j])
                plants[i][j]->add_timer();
        }
    }
}

void Game::update() { // 游戏每一帧内做的所有事情
    // painter->init();
    add_timer();
    update_zombies(); // 更新僵尸状态
    update_bullets(); // 更新子弹
    gen_sun(); // 产生太阳

    remove_dead();

}

void Game::add_score() {
    if(difficulty == 1)
        score += 100;
    else if(difficulty == 2)
        score += 150;
    else
        score += 200;
}

bool cmp(Zombie *a, Zombie *b) {
    auto pos1 = a->get_pos();
    auto pos2 = b->get_pos();
    return (pos1.first > pos2.first) || (pos1.first == pos2.first && pos1.second < pos2.second);
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
            add_score();
            continue;
        }
        if (zombie->is_catapult()) {
            for (int i = 0; i < nr_col; ++i) {
                Plant *plant = plants[pos.first][i];
                if (plant) {
                    if(zombie->get_timer() % 20 == 0) {
                        int damage = zombie->ball_damage();
                        Ball* ball = new Ball(pos.first, i * 12 + 3, zombie->get_pos().second + 4, damage);
                        balls.push_back(ball);
                    }
                    flag = true;
                    break;
                }
            }
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
                game_over = true;
                // game_over();
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
                    zombie->~Zombie();
                    zombies.erase(iter1);
                    iter1--;
                    add_score();
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
    for (auto iter = balls.begin(); iter != balls.end(); iter++) {
        Ball *ball = *iter;
        assert(ball);
        ball->update_pos();
        pair<int, int> pos = ball->get_pos();
        int x0 = ball->get_x0();
        int y0 = (ball->get_y0() - 3) / 12;
        if(abs(pos.second - ball->get_y0()) <= 1) {
            if(plants[x0][y0]) {
                plants[x0][y0]->minus_life(ball->get_attack());
                if(plants[x0][y0]->get_life() <= 0) {
                    plants[x0][y0]->~Plant();
                    plants[x0][y0] = nullptr;
                }
            }
            ball->~Ball();
            balls.erase(iter);
            iter--;
        }
    }
    plant_shot();
    // 检查新子弹刚发射或者老子弹移动后的位置有没有僵尸，如果有，直接造成伤害
    check_bullet_hit_zombie();
}

void Game::gen_zombies() {
    if(difficulty == 1) {
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
            zom->change_pos(line, maps_width - 15);
            zombies.push_back(zom);
        }
    }
    else {
        if(game_time >= 300 && (game_time % 300 == 0 || game_time % 300 == 10)) {
            for(int line = 0; line < 3; ++line) {
                Zombie *zom;
                int t = game_time / 600;
                int r = rand() % 100;
                if (r < t) {
                    zom = new Jack_in_the_Box;
                } else if (r < 2 * t) {
                    zom = new Pole_Vaunting;
                } else if (r < 3 * t) {
                    zom = new Newspaper;
                } else if (r < 4 * t) {
                    zom = new Conehead;
                } else {
                    zom = new Common;
                }
                zom->change_pos(line, maps_width - 15);
                zombies.push_back(zom);
            }
        }
        else if(game_time >= 900 && game_time % 300 == 20) {
           for(int line = 0; line < 3; ++line) {
               Zombie *zom = new Catapult;
               zom->change_pos(line, maps_width - 15);
               zombies.push_back(zom);
           }
        }
        else if (game_time % 75 == 0) {
            int line = rand() % nr_row;
            Zombie *zom;
            if (game_time <= 300) { // 前30s
                zom = new Common();
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
            zom->change_pos(line, maps_width - 15);
            zombies.push_back(zom);
        }
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
    booms.push_back(make_pair(make_pair(x,y), 3));
}

void Game::plant_boom(int x, int y, int d) { // 爆炸（植物）
    double r = d / 2.0;
    for (auto iter = zombies.begin(); iter != zombies.end(); iter++) {
        Zombie *zombie = *iter;
        auto pos = zombie->get_pos();
        int x2 = pos.first, y2 = pos.second;
        if (x2 <= x + r && x2 >= x - r && y2 > y - r * 12 && y2 <= y + r * 12) {
            zombies.erase(iter);
            iter--;
            add_score();
        }
    }
    booms.push_back(make_pair(make_pair(x,y), d));
}

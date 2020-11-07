//
// Created by xy on 2020/10/5.
//

#ifndef SOURCE_GAME_H
#define SOURCE_GAME_H

#include "object.h"
#include "painter.h"
#include "board.h"
#include "plants.h"
#include "market.h"

class Game {
public:
    Market* market;
    Board* board;
    vector<Zombie*> zombies; // 存储所有僵尸
    vector<Bullet*> bullets; // 存储所有子弹
    // vector<Plant*> plants; // 存储所有植物
    Plant* plants[nr_row][nr_col]; // 存储所有植物
    pair<int, int> choose; // 当前选中的位置
    // int chosen_plant; // 选中的植物标号
    int sun, score; // 现有阳光和分数
    int game_time; // 游戏开始的时间
public:
    Game() {
        market = new Market;
        board = new Board;
        choose.first = 0;
        choose.second = 0;
        sun = 250;
        score = 0;
        game_time = 1;
        memset(plants, 0, sizeof(plants));
    }
    int get_sun() const;
    int get_game_time() const;
    int get_score() const;
    int get_chosen_plant() const;
    pair<int, int> get_choose();
    void add_timer();
    void get_key(char ch);
    void listen_keyboard(); // 检测键盘按键并且做出相应反应
    void update(); // 更新游戏状态（即每一帧内游戏做的所有事情）
    void update_zombies(); // 更新所有僵尸的状态
    void update_bullets(); // 更新所有的子弹的状态
    void check_bullet_hit_zombie(); // 检测是否子弹碰到僵尸，并且进行处理
    void check_zombie_hit_plant(); // 检测是否僵尸碰到植物，并且进行处理
    void gen_zombies(); // 生成新的僵尸
    void gen_bullets(); // 生成新的子弹
    void gen_sun(); // 产生阳光
    void remove_dead(); // 删除越界或者死亡的僵尸、子弹、植物
    void game_over(); // 失败，游戏结束
    void update_board(); // 更新地图
};

#endif //SOURCE_GAME_H

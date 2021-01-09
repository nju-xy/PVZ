//
// Created by xy on 2020/10/5.
//

#ifndef SOURCE_GAME_H
#define SOURCE_GAME_H

//#include "object.h"
#include "painter.h"
#include "plants.h"
#include "zombie.h"
#include "market.h"

class Game {
private:
    int difficulty;
    Market *market;
    bool game_over;
    // Painter *painter;
    vector<Zombie *> zombies; // 存储所有僵尸
    vector<Bullet *> bullets; // 存储所有子弹
    // Plant *plants[nr_row][nr_col]; // 存储所有植物
    vector<vector<Plant *>> plants;
    vector<Ball *> balls; // 投石僵尸的球
    vector<pair<pair<int, int>, int>> booms;
    pair<int, int> choose; // 当前选中的位置
    int sun, score; // 现有阳光和分数
    int game_time; // 游戏开始的时间
    void add_timer();
    void update_zombies(); // 更新所有僵尸的状态
    void update_bullets(); // 更新所有的子弹的状态
    void check_bullet_hit_zombie(); // 检测是否子弹碰到僵尸，并且进行处理
    void check_zombie_hit_plant(); // 检测是否僵尸碰到植物，并且进行处理
    void gen_zombies(); // 生成新的僵尸
    void plant_shot(); // 植物攻击，生成子弹或者其他效果
    void gen_sun(); // 产生阳光
    void plant_boom(int x, int y, int d); // 爆炸（窝瓜和樱桃）
    void zombie_boom(int x, int y); // 爆炸（小丑）
    void remove_dead(); // 删除越界或者死亡的僵尸、子弹、植物
    void add_score();
public:
    Game(int _difficulty) {
        difficulty = _difficulty;
        market = new Market;
        // painter = new Painter;
        choose.first = nr_row, choose.second = 0;
        sun = 250;
        score = 0;
        game_time = 1;

        vector<Plant *> temp(nr_col);
        plants.resize(nr_col, temp);
        game_over = false;
    }
    int get_difficulty() const {
        return difficulty;
    }
    bool over() const {
        return game_over;
    }
    void update(); // 更新游戏状态（即每一帧内游戏做的所有事情）
    vector<Zombie *> get_zombies() const {
        return zombies;
    }
    vector<Bullet *> get_bullets() const {
        return bullets;
    }
    vector<Ball *> get_balls() const {
        return balls;
    }
    vector<vector<Plant *>> get_plants() const {
        return plants;
    }
    vector<pair<pair<int, int>, int>> get_booms() const {
        return booms;
    }
    void delete_booms() {
        booms.clear();
    }
    void delete_plant(int i, int j) {
        plants[i][j] = nullptr;
    }
    int get_sun() const {
        return sun;
    }
    int get_score() const {
        return score;
    }
    int get_time() const {
        return game_time;
    }
    Market* get_market() const {
        return market;
    }
    void minus_sun(int k) {
        sun -= k;
    }
    void add_plant(Plant* plant, int i, int j) {
        plants[i][j] = plant;
    }
};

#endif //SOURCE_GAME_H

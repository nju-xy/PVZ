//
// Created by xy on 2020/10/5.
//

#ifndef SOURCE_OBJECT_H
#define SOURCE_OBJECT_H

#include "common.h"

class Object {
protected:
    int life, attack;
    double speed; // 生命值、攻击力、速度
    pair<double, double> pos; // 当前位置（浮点数），显示的时候再取整
    int timer; // 计时器，用于记录出生以来的时间
public:
    pair<int, int> get_pos() const; // 获取当前位置
    void update_pos(); // 更新当前位置（根据速度前进）
    // void change_pos(double x, double y);
    void add_timer(); // 计时器增加
    void minus_life(int damage); // 收到量为damage的伤害，因此扣血
    int get_life() const; // 获得生命值
    int get_attack() const; // 获取攻击力
    int get_timer() const; // 获取计时器
};

class Zombie: public Object {
public:
    Zombie(int line) {
        pos.first = line, pos.second = board_width - zombie_speed;
        life = zombie_life, attack = zombie_attack, speed = - zombie_speed, timer = 1;
    }
};

class Bullet: public Object {
public:
    Bullet(int x, int y) {
        pos.first = x, pos.second = y;
        life = 1, attack = plant_attack, speed = bullet_speed, timer = 1;
    }
};

class Plant: public Object {
private:
    int sun_cost;
public:
    Plant(int x, int y) {
        sun_cost = plant_cost, life = plant_life, attack = plant_attack, speed = 0, timer = 1;
        pos.first = x, pos.second = y;
    }
    int get_cost() const;
    Bullet* shot() const;
};



#endif //SOURCE_OBJECT_H

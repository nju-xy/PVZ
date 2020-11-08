//
// Created by xy on 2020/10/5.
//

#ifndef SOURCE_OBJECT_H
#define SOURCE_OBJECT_H

#include "common.h"

class Object {
protected:
    int life, attack, attack_interval;
    int buff; // 0：无buff；1：寒冰buff
    double speed; // 生命值、攻击力、攻击间隔s、速度
    pair<int, double> pos; // 当前位置（浮点数），显示的时候再取整
    int timer; // 计时器，用于记录出生以来的时间
    int buff_timer;
    const char* name;
public:
    Object() {
        pos.first = timer = life = attack = attack_interval = buff = buff_timer = 0;
        name = nullptr;
        speed = pos.second = 0;

    }
    pair<int, int> get_pos() const; // 获取当前位置
    virtual void update_pos(); // 更新当前位置（根据速度前进）
    void change_pos(int x, double y) {
        pos.first = x, pos.second = y;
    }
    void add_timer(); // 计时器增加
    virtual void minus_life(int damage); // 收到量为damage的伤害，因此扣血
    int get_life() const; // 获得生命值
    int get_attack() const; // 获取攻击力
    int get_timer() const; // 获取计时器
    const char* get_name() const; // 获取名字
    int get_buff();
    void add_buff(int _buff);
};

class Bullet: public Object {
public:
    Bullet(int x, double y, int _attack, int _buff = 0) {
        pos.first = x, pos.second = y;
        life = 1, attack = _attack, speed = 1, timer = 1;
        buff = _buff, buff_timer = INF;
    }
};

#endif //SOURCE_OBJECT_H

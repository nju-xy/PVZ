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
    pair<double, double> pos; // 当前位置（浮点数），显示的时候再取整 // 刚改，int改为double
    int timer; // 计时器，用于记录出生以来的时间
    int buff_timer;
    const char *name;
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
    const char *get_name() const; // 获取名字
    int get_buff();

    void add_buff(int _buff);
};

class Bullet : public Object {
public:
    Bullet(int x, double y, int _attack, int _buff = 0) {
        pos.first = x, pos.second = y;
        life = 1, attack = _attack, speed = 1, timer = 1;
        buff = _buff, buff_timer = INF;
    }
    int get_buff() const {
        return buff;
    }
};

class Ball : public Object {
private:
    double a, b, c, x0, y0; // x = (y - b) ^ 2 + c
    int damage, speed;
public:
    Ball(double x, double y1, double y2, int _damage) {
        a = 4 / ((y1 - y2) * (y1 - y2));
        b = (y1 + y2) / 2;
        c = x - 1;
        attack = _damage, speed = 2, life = 1;
        pos.first = x, pos.second = y2, y0 = y1, x0 = x;
    }
    void update_pos() {
        pos.second -= speed;
        pos.first = a * (pos.second - b) * (pos.second - b) + c;
    }
    pair<double, double> get_pos_double () const {
        return pos;
    }
    int get_y0() const {
        return y0;
    }
    int get_x0() const {
        return x0;
    }
};

#endif //SOURCE_OBJECT_H

//
// Created by xy on 2020/11/7.
//

#ifndef PVZ_PLANTS_H
#define PVZ_PLANTS_H

#include "object.h"

class Plant: public Object {
private:
    int pumpkin;
public:
    void minus_life(int damage);
    Plant(const char* _name, int _life, int _attack, int _attack_interval) { // 名字，生命值，攻击力，攻击间隔(单位是0.1s)
        life = _life, attack = _attack, speed = 0, timer = 1, name = _name, attack_interval = _attack_interval;
        pumpkin = 0;
        // pos.first = x, pos.second = y;
    }
    void add_pumpkin() {
        assert(pumpkin <= 0);
        pumpkin = 4000;
    }
    int check_pumpkin() {
        return pumpkin;
    }
    virtual void shot(vector<Bullet*> &bullets);
};

class Sunflower : public Plant {
public:
    Sunflower() : Plant("Sun     ", 300, 0, 25) {}
    void shot(vector<Bullet*> &bullets);
    void add_sun(int &sun);
};

class Peashooter : public Plant {
public:
    Peashooter() : Plant("Pea     ", 300, 15, 20) {}
};

class Repeater : public Plant {
public:
    Repeater() : Plant("Repeater", 300, 15, 20) {}
    void shot(vector<Bullet*> &bullets);
};

class Snow_Pea : public Plant {
public:
    Snow_Pea() : Plant("Snow-pea", 300, 15, 20) {}
    void shot(vector<Bullet*> &bullets);
};

class Wall_nut : public Plant {
public:
    Wall_nut() : Plant("Wall-nut", 4000, 0, -1) {}
};

class Tall_nut : public Plant {
public:
    Tall_nut() : Plant("Tall-nut", 8000, 0, -1) {}
};

class Squash : public Plant {
public:
    Squash() : Plant("Squash  ", 9999, INF, -1) {}
};

class Cherry : public Plant {
public:
    Cherry() : Plant("Cherry  ", 9999, INF, -1) {}
};

class Garlic : public Plant {
public:
    Garlic() : Plant("Garlic  ", 400, 0, -1) {}
};

class Pumpkin : public Plant {
public:
    Pumpkin() : Plant("Pumpkin ", 4000, 0, -1) {}
};

#endif //PVZ_PLANTS_H

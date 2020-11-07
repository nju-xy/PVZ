//
// Created by xy on 2020/11/7.
//

#ifndef PVZ_PLANTS_H
#define PVZ_PLANTS_H

#include "object.h"

class Plant: public Object {
public:
    Plant(string _name, int _life, int _attack, int _attack_interval) {
        life = _life, attack = _attack, speed = 0, timer = 1, name = _name;
        // pos.first = x, pos.second = y;
    }
    void change_pos(int x, int y) {
        pos.first = x, pos.second = y;
    }
    Bullet* shot() const;
};

class Peashooter : public Plant {
public:
    Peashooter() : Plant("Pea     ", 300, 1.5, 20) {}
};

class Repeater : public Plant {
public:
    Repeater() : Plant("Repeater", 300, 1.5, 40) {}
};

class Snow_Pea : public Plant {
public:
    Snow_Pea() : Plant("Snow-pea", 300, 1.5, 20) {}
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
    Squash() : Plant("Squash  ", INF, INF, 1) {}
};

class Cherry : public Plant {
public:
    Cherry() : Plant("Cherry  ", INF, INF, 1) {}
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

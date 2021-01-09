//
// Created by xy on 2020/11/7.
//

#ifndef PVZ_PLANTS_H
#define PVZ_PLANTS_H

#include "object.h"

class Plant : public Object {
private:
    int pumpkin;
protected:
    string path;
public:
    void minus_life(int damage);

    Plant(const char *_name, int _life, int _attack, int _attack_interval, string _path) { // 名字，生命值，攻击力，攻击间隔(单位是0.1s)，图片路径
        life = _life, attack = _attack, speed = 0, timer = 1, name = _name, attack_interval = _attack_interval;
        pumpkin = 0;
        path = _path;
    }

    virtual string get_path() const {
        return path;
    }

    void add_pumpkin() {
        assert(pumpkin <= 0);
        pumpkin = 4000;
    }

    int check_pumpkin() {
        return pumpkin;
    }

    virtual vector<Bullet *> shot();

    virtual int add_sun();

    virtual bool change_zombie_line() {
        return false;
    }

    virtual bool if_block() {
        return true;
    }

    virtual bool block_jump() {
        return false;
    }

    virtual bool boom_at_once() {
        return false;
    }

    virtual bool boom_with_zombie() {
        return false;
    }
};

class Sunflower : public Plant {
public:
    Sunflower() : Plant("向日葵", 300, 0, -1, "SunFlower_0.png") {}

    int add_sun();
};

class Peashooter : public Plant {
public:
    Peashooter() : Plant("豌豆射手", 300, 20, 15, "Peashooter_0.png") {}
};

class Repeater : public Plant {
public:
    Repeater() : Plant("双发射手", 300, 20, 15, "RepeaterPea_0.png") {}

    vector<Bullet *> shot();
};

class Snow_Pea : public Plant {
public:
    Snow_Pea() : Plant("寒冰射手", 300, 20, 15, "SnowPea_0.png") {}

    vector<Bullet *> shot();
};

class Wall_nut : public Plant {
public:
    Wall_nut() : Plant("坚果墙", 4000, 0, -1, "WallNut_0.png") {}
    string get_path() const {
        if(life <= 1000)
            return "WallNut_cracked2_0.png";
        else if(life <= 2000)
            return "WallNut_cracked1_0.png";
        else
            return path;
    }
};

class Tall_nut : public Plant {
public:
    Tall_nut() : Plant("高坚果", 8000, 0, -1, "TallNut.png") {}

    bool block_jump() {
        return true;
    }
};

class Squash : public Plant {
public:
    Squash() : Plant("窝瓜", 9999, INF, -1, "Squash.png") {}

    bool if_block() {
        return false;
    }

    bool boom_with_zombie() {
        return true;
    }
};

class Cherry : public Plant {
public:
    Cherry() : Plant("樱桃炸弹", 9999, INF, -1, "CherryBomb_0.png") {}
    bool boom_at_once() {
        return true;
    }
};

class Garlic : public Plant {
public:
    Garlic() : Plant("大蒜", 400, 0, -1, "Garlic.png") {}

    bool change_zombie_line() {
        if(check_pumpkin() > 0)
            return false;
        return true;
    }
};

class Pumpkin : public Plant {
public:
    Pumpkin() : Plant("南瓜头", 4000, 0, -1, "Pumpkin.png") {}
};

#endif //PVZ_PLANTS_H

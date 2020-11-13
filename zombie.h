//
// Created by xy on 2020/11/8.
//

#ifndef PVZ_ZOMBIE_H
#define PVZ_ZOMBIE_H

#include "object.h"

class Zombie : public Object {
public:
    Zombie() {
        name = nullptr;
        life = 270, attack = 100, speed = -0.2, timer = 1;
    }

    void update_pos();

    void random_change_line();

    virtual bool boom_after_death() {
        return false;
    }

    virtual bool jump() {
        return false;
    }
};

class Common : public Zombie {
public:
    Common() {
        name = "zombie";
        life = 270, attack = 100, speed = -0.2, timer = 1;
    }
};

class Conehead : public Zombie { // 路障僵尸
public:
    Conehead() {
        name = "conehead";
        life = 270 + 370, attack = 100, speed = -0.2, timer = 1;
    }

    void minus_life(int damage) {
        life -= damage;
        if (life <= 270)
            change();
    }

    void change() {
        name = "CONEHEAD";
    }
};

class Newspaper : public Zombie { // 读报僵尸
public:
    Newspaper() {
        name = "paper";
        life = 270 + 150, attack = 100, speed = -0.2, timer = 1;
    }

    void minus_life(int damage) {
        life -= damage;
        if (life <= 270)
            change();
    }

    void change() {
        name = "PAPER";
        speed = -0.67;
    }
};

class Pole_Vaunting : public Zombie { // 撑杆僵尸
private:
    int skill_cnt;
public:
    Pole_Vaunting() {
        name = "pole";
        skill_cnt = 1;
        life = 500, attack = 100, speed = -0.48, timer = 1;
    }

    bool jump() {
        if (skill_cnt) {
            skill_cnt--;
            change();
            return true;
        }
        return false;
    }

    void change() {
        name = "POLE", speed = -0.2;
    }
};

class Jack_in_the_Box : public Zombie { // 小丑僵尸，死了就爆炸3 * 3
public:
    Jack_in_the_Box() {
        name = "jack";
        life = 500, attack = 100, speed = -0.82, timer = 1;
    }

    bool boom_after_death() {
        return true;
    }
};

class Catapult : public Zombie { // 投石僵尸
private:
    int skill_cnt;
public:
    Catapult() { // 第一状态，用篮球远程攻击植物（最左），攻击力75（另外结算伤害）
        name = "catapult";
        skill_cnt = 20;
        life = 850, attack = 0, speed = -0.72, timer = 1;
    }

    int ball_damage() {
        if (timer % 10 != 0)
            return 0;
        if (skill_cnt > 0) {
            skill_cnt--;
            if (skill_cnt == 0)
                change();
            return 75; // 75伤害
        }
        return 0;
    }

    void change() {
        name = "CATAPULT", attack = 1000000, speed = -0.2;
    }
};


#endif //PVZ_ZOMBIE_H

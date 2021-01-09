//
// Created by xy on 2020/11/8.
//

#ifndef PVZ_ZOMBIE_H
#define PVZ_ZOMBIE_H

#include "object.h"

class Zombie : public Object {
protected:
    string path;
public:
    Zombie() {
        name = nullptr, path = "";
        life = 270, attack = 100, speed = -0.2, timer = 1;
    }

    string get_path() const {
        return path;
    }

    void update_pos();

    void random_change_line();

    virtual bool boom_random() {
        return false;
    }

    virtual bool jump() {
        return false;
    }

    virtual int ball_damage() {
        return 0;
    }

    virtual bool is_catapult() {
        return false;
    }
};

class Common : public Zombie {
public:
    Common() {
        name = "普通僵尸";
        life = 270, attack = 100, speed = -0.2, timer = 1;
        path = "Zombie_0.png";
    }
};

class Conehead : public Zombie { // 路障僵尸
public:
    Conehead() {
        name = "路障僵尸";
        life = 270 + 370, attack = 100, speed = -0.2, timer = 1;
        path = "ConeheadZombie_0.png";
    }

    void minus_life(int damage) {
        life -= damage;
        if (life <= 270)
            change();
    }

    void change() {
        name = "CONEHEAD";
        path = "Zombie_0.png";
    }
};

class Newspaper : public Zombie { // 读报僵尸
public:
    Newspaper() {
        name = "读报僵尸";
        life = 270 + 150, attack = 100, speed = -0.2, timer = 1;
        path = "NewspaperZombie_0";
    }

    void minus_life(int damage) {
        life -= damage;
        if (life <= 270)
            change();
    }

    void change() {
        name = "PAPER";
        path = "NewspaperZombieNoPaper_0";
        speed = -0.67;
    }
};

class Pole_Vaunting : public Zombie { // 撑杆僵尸
private:
    int skill_cnt;
public:
    Pole_Vaunting() {
        name = "撑杆僵尸";
        skill_cnt = 1;
        life = 500, attack = 100, speed = -0.48, timer = 1;
        path = "Pole_0.png";
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
        path = "Pole_1.png";
    }
};

class Jack_in_the_Box : public Zombie { // 小丑僵尸，每次按照概率爆炸3 * 3
public:
    Jack_in_the_Box() {
        name = "小丑僵尸";
        life = 500, attack = 100, speed = -0.82, timer = 1;
        path = "Jack_0.png";
    }

    bool boom_random() {
        int temp = rand() % 100;
        if(timer >= 50 && temp >= 97)
            return true;
        return false;
    }
};

class Catapult : public Zombie { // 投石僵尸
private:
    int skill_cnt;
    bool has_changed;
public:
    Catapult() { // 第一状态，用篮球远程攻击植物（最左），攻击力75（另外结算伤害）
        name = "投石僵尸";
        skill_cnt = 8;
        life = 850, attack = 0, speed = -0.72, timer = 1;
        path = "Catapult_0.png";
        has_changed = false;
    }

    int ball_damage() {
        if (timer % 10 != 0)
            return 0;
        if (skill_cnt > 0) {
            skill_cnt--;
            if (skill_cnt == 0)
                change();
            return 150; // 150伤害
        }
        return 0;
    }

    void change() {
        name = "CATAPULT", attack = 1000000, speed = -0.2;
        has_changed = true;
    }

    virtual bool is_catapult() {
        return !has_changed;
    }
};


#endif //PVZ_ZOMBIE_H

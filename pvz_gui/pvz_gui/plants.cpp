//
// Created by xy on 2020/11/7.
//

#include "plants.h"

vector<Bullet *> Plant::shot() { // 正常的植物攻击就是发出子弹
    vector<Bullet*> vec;
    if (attack_interval > 0 && timer % attack_interval == 0) {
        Bullet *bul = new Bullet(pos.first, pos.second + 6, attack);
        vec.push_back(bul);
    }
    return vec;
}

int Plant::add_sun() {
    return 0;
}

void Plant::minus_life(int damage) {
    if (pumpkin > 0)
        pumpkin -= damage;
    else
        life -= damage;
}

vector<Bullet *> Repeater::shot() { // 双发射手发出发出子弹
    vector<Bullet*> vec;
    if (attack_interval > 0 && timer % attack_interval == 0) {
        Bullet *bul = new Bullet(pos.first, pos.second + 5, attack);
        vec.push_back(bul);
        bul = new Bullet(pos.first, pos.second + 7, attack);
        vec.push_back(bul);
    }
    return vec;
}

vector<Bullet *> Snow_Pea::shot() { // 寒冰射手发出发出子弹
    vector<Bullet*> vec;
    if (attack_interval > 0 && timer % attack_interval == 0) {
        Bullet *bul = new Bullet(pos.first, pos.second + 6, attack, 1);
        vec.push_back(bul);
    }
    return vec;
}

int Sunflower::add_sun() {
    if (timer % 100 == 0) {
        return 25;
    }
    return 0;
}

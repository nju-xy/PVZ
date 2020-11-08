//
// Created by xy on 2020/11/7.
//

#include "plants.h"

void Plant::shot(vector<Bullet*> &bullets) { // 正常的植物攻击就是发出子弹
    if(attack_interval > 0 && timer % attack_interval == 0) {
        Bullet* bul = new Bullet(pos.first, pos.second + 6, attack);
        bullets.push_back(bul);
    }
}

void Plant::minus_life(int damage) {
    if(pumpkin > 0)
        pumpkin -= damage;
    else
        life -= damage;
}

void Repeater::shot(vector<Bullet*> &bullets) { // 双发射手发出发出子弹
    if(attack_interval > 0 && timer % attack_interval == 0) {
        Bullet* bul = new Bullet(pos.first, pos.second + 6, attack);
        bullets.push_back(bul);
        bul = new Bullet(pos.first, pos.second + 7, attack);
        bullets.push_back(bul);
    }
}

void Snow_Pea::shot(vector<Bullet*> &bullets) { // 双发射手发出发出子弹
    if(attack_interval > 0 && timer % attack_interval == 0) {
        Bullet* bul = new Bullet(pos.first, pos.second + 6, attack, 1);
        bullets.push_back(bul);
    }
}

void Sunflower::shot(vector<Bullet*> &bullets) { // 向日葵不发射子弹
}

void Sunflower::add_sun(int &sun) {
    if(attack_interval > 0 && timer % attack_interval == 0) {
        sun += 25;
    }
}

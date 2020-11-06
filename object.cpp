//
// Created by xy on 2020/10/5.
//

#include "object.h"

// Object
pair<int, int> Object::get_pos() const {
    if(pos.second >= 0)
        return make_pair(int(pos.first), int(pos.second));
    else
        return make_pair(int(pos.first), -1);
}
//void Object::change_pos(double x, double y) {
//    pos.first = x;
//    pos.second = y;
//}
void Object::update_pos() {
    pos.second = pos.second + speed;
}
void Object::minus_life(int damage) {
    life = life - damage;
}
int Object::get_life() const {
    return life;
}
int Object::get_attack() const {
    return attack;
}
int Object::get_timer() const {
    return timer;
}
void Object::add_timer() {
    timer++;
}

// Plant
int Plant::get_cost() const {
    return sun_cost;
}
Bullet* Plant::shot() const {
    if(timer % shot_cd == 0)
        return new Bullet(pos.first, pos.second + 1);
    return nullptr;
}

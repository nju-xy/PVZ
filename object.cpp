//
// Created by xy on 2020/10/5.
//

#include "object.h"

// Object
pair<int, double> Object::get_pos() const {
    if(pos.second >= 0)
        return make_pair(pos.first, pos.second);
    else
        return make_pair(pos.first, -1);
}
string Object::get_name() const {
    return name;
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



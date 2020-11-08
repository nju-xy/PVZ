//
// Created by xy on 2020/10/5.
//

#include "object.h"

// Object
pair<int, int> Object::get_pos() const {
    if(pos.second >= 0)
        return make_pair(pos.first, int(pos.second));
    else
        return make_pair(pos.first, -1);
}
const char* Object::get_name() const {
    return name;
}
//void Object::change_pos(double x, double y) {
//    pos.first = x;
//    pos.second = y;
//}
int Object::get_buff() {
    return buff;
}
void Object::add_buff(int _buff) {
    buff = _buff, buff_timer = 10;
}
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
    buff_timer--;
    if(buff_timer == 0)
        buff = 0;
}
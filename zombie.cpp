//
// Created by xy on 2020/11/8.
//

#include "zombie.h"

void Zombie::update_pos() {
    if (buff == 1)
        pos.second = pos.second + speed / 2;
    else
        pos.second = pos.second + speed;
}

void Zombie::random_change_line() {
    if (pos.first == 0)
        pos.first++;
    else if (pos.first == nr_row - 1)
        pos.first--;
    else {
        if (rand() % 2)
            pos.first++;
        else
            pos.first--;
    }
}
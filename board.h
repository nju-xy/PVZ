//
// Created by xy on 2020/10/2.
//

#ifndef SOURCE_BOARD_H
#define SOURCE_BOARD_H

#include "common.h"
#include "object.h"
#include "plants.h"

class Board {
private:
    vector<Zombie*> zombie_board[board_height][board_width];
    Plant* plant_board[board_height][board_width];
    vector<Bullet*> bullet_board[board_height][board_width];
public:
    Board();
    void clear();
    vector<Zombie*> get_zombie(int i, int j);
    Plant* get_plant(int i, int j);
    vector<Bullet*> get_bullet(int i, int j);
    void add_zombie(Zombie* zom);
    void add_plant(Plant* plant);
    void add_bullet(Bullet* bul);
};

#endif //SOURCE_BOARD_H

//
// Created by xy on 2020/10/2.
//

#include "board.h"
extern int game_time;

Board::Board() {
    clear();
}
void Board::clear() {
    memset(plant_board, 0, board_height * board_width * sizeof(void*));
    for(int i = 0; i < board_height; ++i) {
        for(int j = 0; j < board_width; ++j) {
            bullet_board[i][j].clear();
            zombie_board[i][j].clear();
        }
    }
}
vector<Zombie*> Board::get_zombie(int i, int j) {
    return zombie_board[i][j];
}
Plant* Board::get_plant(int i, int j) {
    return plant_board[i][j];
}
vector<Bullet*> Board::get_bullet(int i, int j) {
    return bullet_board[i][j];
}

void Board::add_zombie(Zombie* zom) {
    auto pos = zom->get_pos();
    zombie_board[pos.first][pos.second].push_back(zom);
}
void Board::add_bullet(Bullet* bul) {
     auto pos = bul->get_pos();
     bullet_board[pos.first][pos.second].push_back(bul);
}
void Board::add_plant(Plant* plant) {
    auto pos = plant->get_pos();
    plant_board[pos.first][pos.second] = plant;
}


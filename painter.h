//
// Created by xy on 2020/10/2.
//

#ifndef SOURCE_PAINTER_H
#define SOURCE_PAINTER_H

#include <iostream>
#include <windows.h>
#include "board.h"
#include "market.h"
#include "common.h"
using namespace std;

class Painter{
private:
    char pixels[maps_height][maps_width];
    bool boom[maps_height][maps_width];
    void paint_market(Market* market, int x, int y) const;
public:
    void init();
    void paint(pair<int, int> choose, int sun, int score, Market* market);
    void game_over() const;
    void add_zombie(Zombie* zom);
    void add_plant(Plant* plant);
    void add_bullet(Bullet* bul);
    void add_boom(int x, int y);
};

#endif //SOURCE_PAINTER_H

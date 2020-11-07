//
// Created by xy on 2020/10/2.
//

#ifndef SOURCE_PAINTER_H
#define SOURCE_PAINTER_H

#include <iostream>
#include <windows.h>
#include "board.h"
#include "market.h"
#include "game.h"
#include "common.h"
using namespace std;

class Painter{
private:
    void paint_market(Market* market, int x, int y) const;
public:
    void paint(Board* board, Market* market) const;
    void game_over() const;
};

#endif //SOURCE_PAINTER_H

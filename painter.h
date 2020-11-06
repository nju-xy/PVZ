//
// Created by xy on 2020/10/2.
//

#ifndef SOURCE_PAINTER_H
#define SOURCE_PAINTER_H

#include <iostream>
#include <windows.h>
#include "board.h"
using namespace std;

class Painter{
public:
    void paint(Board& board) const;
    void game_over() const;
};

#endif //SOURCE_PAINTER_H

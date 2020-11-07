//
// Created by xy on 2020/10/2.
//

#ifndef SOURCE_COMMON_H
#define SOURCE_COMMON_H

#include <iostream>
#include <assert.h>
#include <iomanip>
#include <conio.h>
#include <windows.h>
#include <stack>
#include <queue>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <string>
#include <ctime>

using namespace std;

#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a < b ? a : b)
#define INF 0x3f3f3f3f

const int board_width = 7, board_height = 3;
const int nr_row = 3, nr_col = 7;

const int zombie_rate = 20;
const int zombie_attack_rate = 10;
const int zombie_life = 30, zombie_attack = 4;
const double zombie_speed = 0.05;
const double bullet_speed = 0.2;

const int sun_rate = 20;
const int one_sun = 25;
// const int plant_kinds = 1;
// const int shot_cd = 10;
// const int plant_cost = 100, plant_life = 10, plant_attack = 10;

#endif //SOURCE_COMMON_H

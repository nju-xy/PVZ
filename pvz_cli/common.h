//
// Created by xy on 2020/10/2.
//

#ifndef SOURCE_COMMON_H
#define SOURCE_COMMON_H

#include <iostream>
#include <algorithm>
#include <cassert>
#include <cmath>
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

const int nr_row = 3, nr_col = 7;
const int maps_height = nr_row * 6 + 1, maps_width = (nr_col + 1) * 12 + 1;

const int sun_rate = 20;
const int one_sun = 25;

#endif //SOURCE_COMMON_H

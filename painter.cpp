//
// Created by xy on 2020/10/2.
//

#include "painter.h"

HANDLE screen = GetStdHandle(STD_OUTPUT_HANDLE);

void Painter::init() {
    for(int i = 0; i < maps_height; ++i) {
        for(int j = 0; j < maps_width; ++j) {
            pixels[i][j] = ' ';
            boom[i][j] = false;
        }
    }
}

void Painter::paint(pair<int, int> choose, int sun, int score, Market* market) {
    // 画格子
    for(int i = 0; i < maps_height; i += 6) {
        for(int j = 0; j < maps_width - 12; ++j) {
            pixels[i][j] = '#';
        }
        for(int j = maps_width - 12; j < maps_width; ++j) {
            pixels[i][j] = '-';
        }
    }
    for(int i = 0; i < maps_height; ++i) {
        for (int j = 0; j < maps_width; ++j) {
            if(boom[i][j])
                pixels[i][j] = 'x';
        }
    }
    if(choose.first < nr_row) {
        for(int i = 0; i < 5; ++i) {
            pixels[1 + 6 * choose.first + i][12 * choose.second] = '|';
            pixels[1 + 6 * choose.first + i][12 * choose.second + 12] = '|';
        }
    }
    COORD position;    // position 是一个 COORD 结构
    position.X = position.Y = 0;
    SetConsoleCursorPosition(screen, position);
    for(int i = 0; i < maps_height; ++i) {
        for(int j = 0; j < maps_width; ++j) {
            cout << pixels[i][j];
        }
        cout << endl;
    }
    cout << "[shop] sun: "<< sun;
    cout << "                   [score]:" << score << endl;
    paint_market(market, choose.first, choose.second);
}

void Painter::add_zombie(Zombie* zom) {
    auto pos = zom->get_pos();
    int x = pos.first * 6 + 1;
    int y = pos.second;
    sprintf(&pixels[x][y], "%s", zom->get_name());
    sprintf(&pixels[x + 1][y], "[%d]", zom->get_life());
}
void Painter::add_plant(Plant* plant) {
    auto pos = plant->get_pos();
    int x = pos.first * 6 + 4;
    int y = pos.second - 4;
    int pumpkin = plant->check_pumpkin();
    if(pumpkin > 0) {
        sprintf(&pixels[x][y], "{%s}", plant->get_name());
        sprintf(&pixels[x + 1][y], "[%d]%d", plant->get_life(), pumpkin);
    }
    else {
        sprintf(&pixels[x][y], "%s", plant->get_name());
        sprintf(&pixels[x + 1][y], "[%d]", plant->get_life());
    }
}
void Painter::add_boom(int x, int y) {
    boom[x][y] = true;
}

void Painter::add_bullet(Bullet* bul) {
    auto pos = bul->get_pos();
    int x = pos.first * 6 + 3;
    int y = pos.second;
    pixels[x][y] = 'o';
}

void Painter::paint_market(Market* market, int x, int y) const {
    cout << "------------------------------------------------------------------------------" << endl;
    for(int i = 0; i < market->number_of_items(); ++i) {
        if(market->get_chosen() && market->get_chosen()->get_no() == i) {
            cout << "[*] ";
        }
        else if(x >= nr_row && (x - nr_row) * 3 + y == i) {
            cout << "[+] ";
        }
        else {
            cout << "[ ] ";
        }

        auto item = market->get_item_k(i);
        cout << item->get_plant()->get_name() << " ";
        cout << setw(3) << setfill(' ') << item->get_cost() << " ";
        cout << setw(4) << setfill(' ') << item->get_timer() / 10 << "s";
        if(i % 3 == 2)
            cout << endl;
        else
            cout << "     ";
    }
    cout << endl << "==============================================================================" << endl;
    cout << "Select plant: b; Cancel selection: x; Grow plant: c; " << endl;
}

void Painter::game_over() const {
    cout << "GAME OVER!!!" << endl;
}
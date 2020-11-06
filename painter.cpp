//
// Created by xy on 2020/10/2.
//

#include "common.h"
#include "painter.h"
#include "game.h"
extern Game game;

HANDLE screen = GetStdHandle(STD_OUTPUT_HANDLE);

void Painter::paint(Board& board) const {
    // system("cls"); // 这样会闪，效果太差了
    COORD position;    // position 是一个 COORD 结构
    position.X = position.Y = 0;
    SetConsoleCursorPosition(screen, position);

    auto choose = game.get_choose();
    for(int i = 0; i <= board_height; ++i) { // 3行
        for (int j = 0; j < board_width; ++j) {
            if(choose.first == board_height)
                cout << "###########";
            else if(choose.first >= 0 && (i == choose.first || i == choose.first + 1) && j == choose.second)
                cout << "-----------";
            else
                cout << "###########";
        }
        cout << "#" << endl;
        if(i == board_height)
            continue;
        for (int k = 0; k < 3; ++k) {
            for (int j = 0; j <= board_width; ++j) {
                if(choose.first >= 0 && i == choose.first && (j == choose.second || j == choose.second + 1))
                    cout << "|";
                else
                    cout << "#";
                if(j == board_width)
                    continue;
                if(k == 0) { // 僵尸
                    vector<Zombie*> zombies = board.get_zombie(i, j);
//                    if(zombies.size()) {
//                        cout << " zombie   ";
//                    }
//                    else {
//                        cout << "          ";
//                    }
                    if(zombies.empty()) {
                        cout << "          ";
                        continue;
                    }
                    int s = MIN(5, zombies.size());
                    for(int t = 0; t < s; ++t) {
                        cout << "z";
                    }
                    cout << "ombie";
                    for(int t = 0; t + s < 5; ++t) {
                        cout << " ";
                    }
                }
                else if(k == 2) { // 植物
                    Plant* plant = board.get_plant(i, j);
                    if(plant) {
                        cout << "Peashooter";
                    }
                    else {
                        cout << "          ";
                    }
                }
                else { // 子弹
                    auto bullets = board.get_bullet(i, j);
                    int s = MIN(10, bullets.size());
                    for(int t = 0; t < s; ++t) {
                        cout << "O";
                    }
                    for(int t = 0; t + s < 10; ++t) {
                        cout << " ";
                    }
                }
            }
            cout << endl;
        }
    }
    cout << "==============================================================================" << endl;
    cout << "[shop] sun: "<< game.get_sun() << "               [score]:" << game.get_score() << endl;
    cout << "------------------------------------------------------------------------------" << endl;

    if(choose.first == board_height && choose.second == 0 && game.get_game_time() % 4 <= 1)
        cout << "[+]";
    else if(game.get_chosen_plant())
        cout << "[+]";
    else
        cout << "[ ]";
    cout << " Peashooter 100" << endl;

//    if(choose.first == board_height && choose.second == 1)
//        cout << "[-]";
//    else
//        cout << "[ ]";
//    cout << " Sunflower 50 ";

    cout << "==============================================================================" << endl;
    cout << "Select plant: b; Cancel selection: x; Grow plant: c; " << endl;
}

void Painter::game_over() const {
    cout << "GAME OVER!!!" << endl;
}
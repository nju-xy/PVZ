#include "common.h"
#include "game.h"

Game game;

int main() {


    srand((unsigned) time(nullptr));
    clock_t last = clock();
    while (true) {
        clock_t cur = clock();
        double diff = (double)(cur - last) / CLOCKS_PER_SEC;
        if(diff >= 0.1) {
            last = cur;
            game.update();
            // cout << diff << endl;
        }
    }
//    while(true) {
//        game.update();
//        Sleep(100);
//    }
}
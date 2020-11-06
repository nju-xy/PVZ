#include "common.h"
#include "game.h"

Game game;

int main()
{
    srand((unsigned)time(nullptr));
    while(true) {
        game.update();
        Sleep(100);
    }
}
#include<iostream>
#include"Game.h"
using namespace sf;

#pragma warning(disable : 4996)

int main()
{
    time_t t;
    srand((unsigned)time(&t));
    Game game;

    game.run();

    return 0;

}
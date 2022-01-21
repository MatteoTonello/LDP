#include "Board.cpp"
#include "Pawn.cpp"
#include "Rock.cpp"
#include "Knight.cpp"
#include "Queen.cpp"
#include "King.cpp"
#include "Bishop.cpp"
#include "Game.cpp"
#include "Player.cpp"
#include "GameReplay.cpp"
#include <iostream>
using namespace std;
int main(int args,char *argv[])
{
    Game* g=new Game(*argv[1]);
    g->startgame();
    return 0;
}
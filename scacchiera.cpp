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
    if(*argv[1]=='p')
    {
        Player* p1 = new Player('p');
        Player* p2 = new Player('c');
        Game* g=new Game(p1,p2);
        g->startgame();
    }
    if(*argv[1]=='c')
    {
        Player* p1 = new Player('c');
        Player* p2 = new Player('c');
        Game* g=new Game(p1,p2);
        g->startgame();
    }
    return 0;
}
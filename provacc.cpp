#include "Board.cpp"
#include "Pawn.cpp"
#include "Rock.cpp"
#include "Knight.cpp"
#include "Queen.cpp"
#include "King.cpp"
#include "Bishop.cpp"
#include "Game.cpp"
#include "Player.cpp"
#include <iostream>
using namespace std;
int main()
{
    
    Player* p1 = new Player('c');
    Player* p2 = new Player('p');
    Game* g=new Game(p1,p2);
    cout<<"INIZIO"<<endl;
    g->startgame();
    cout<<"FINITO";

    
    
    return 0;
}
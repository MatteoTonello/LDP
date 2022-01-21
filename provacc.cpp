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
    Game* g=new Game('p');
    cout<<"INIZIO"<<endl;
    g->startgame();
    cout<<"FINITO";
    delete g;
    if(g->game_result()=="VINCITORE NERO") return 0;
    if(g->game_result()=="VINCITORE BIANCO") return 0;
    
    return 0;
}

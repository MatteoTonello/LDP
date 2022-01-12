#include "Board.cpp"
#include "Pawn.cpp"
#include "Rock.cpp"
#include "Knight.cpp"
#include "Queen.cpp"
#include "King.cpp"
#include "Bishop.cpp"
#include "Game.cpp"
#include "Player.cpp"
#include "Replay.cpp"
#include <iostream>
using namespace std;
int main()
{
    Replay* r=new Replay("replay.txt");
    r->replay();
    cout<<"ok";
    
    return 0;
}
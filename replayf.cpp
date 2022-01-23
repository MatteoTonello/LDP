#include "Piece.h"
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
int main()
{ 
        string file_input="log.txt";
        GameReplay* games = new GameReplay(file_input);
        games->replayv();
        delete games;
        cout<<"finito";
    return 0;
}
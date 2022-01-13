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
    if(*argv[1]=='v')
    {
        string file_input=argv[2];
        GameReplay* game = new GameReplay(file_input);
        game->replayv();
    }
    if(*argv[1]=='f')
    {
        string file_output=argv[3];
        string file_input=argv[2];
        GameReplay* game = new GameReplay(file_input,file_output);
        game->replayf();
    }
    return 0;
}
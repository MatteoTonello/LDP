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
        string file_output="logg.txt";
        string file_input="replay.txt";
        GameReplay* games = new GameReplay(file_input,file_output);
        games->replayf();
        cout<<games->game->mainboard->is_check_mate('b');
    return 0;
}
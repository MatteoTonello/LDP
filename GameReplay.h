#include "Game.h"
#include "Player.h"
class GameReplay
{
    public:
    string file_input;
    string file_output;
    Game* game;
    GameReplay(string in);
    GameReplay(string in, string out);
    void replayf();
    void replayv();
};
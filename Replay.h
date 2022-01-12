#include "Game.h"
#include "Player.h"
class Replay
{
    public:
    string file_name;
    Game* game;
    Replay(string filename);
    void replay();
};
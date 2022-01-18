#ifndef GAMEREPLAY_H
#define GAMEREPLAY_H
#include "Game.h"
#include "Player.h"
//classe che gestisce i replay
class GameReplay
{
    public:
    string file_input;              //nome file di input
    string file_output;             //nome file di output
    Game* game;                        //puntatore alla partita
    GameReplay(string in);              //costruttore per replay a monitor
    GameReplay(string in, string out);  //costruttore per replay su file
    void replayf();             //avvia il replay su file
    void replayv();             //avvia il replay su monitor
};
#endif
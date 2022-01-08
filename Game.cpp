#ifndef GAME_CPP
#define GAME_CPP
#include "Game.h"
#include "Player.h"
#include <stdlib.h>    
#include <time.h>
Game::Game(Player* n1,Player* n2)
{
    srand (time(NULL));
    if(n1->is_human || n2->is_human)
    {
        int rand = rand() % 2;
        if(rand==0)
        {
            white_player=n1;
            black_player=n2;
        }
        else
        {
            white_player=n2;
            black_player=n1;
        }
    }
	mainboard=new Board();
	is_turn=white_player;
    result="";
}
void Game::startgame()
{
    while(!(is_finished()))
    {
        move();
        change_turn();
    }
}
void Game::change_turn()
{
    if(is_turn==white_player)
        is_turn=black_player;
    else
        is_turn=white_player;
}
void Game::player_move()
{
    is_turn->move();
}
bool Game::is_finished()
{
    bool mate=0;
    if(is_draw())
    {
        result="PATTA";
        return true;
    }
    if(is_turn==white_player)
    {
        mate=mainboard.is_check_mate('w');
        if(mate==1)
        {
            result="VINCITORE NERO";
            return true;
        }
    }
    else
    {
        mate=mainboard.is_check_mate('b');
        if(mate==1)
        {
            result="VINCITORE BIANCO";
            return true;
        }
    }
    return false;
}
#endif
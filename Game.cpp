#ifndef GAME_CPP
#define GAME_CPP
#include "Game.h"
#include "Player.h"
#include "Illegal_move.cpp"
#include <stdio.h>
#include <stdlib.h>    
#include <time.h>
using namespace std;
Game::Game(Player* n1,Player* n2)
{
    srand (time(NULL));
    if(n1->is_human || n2->is_human)
    {
        int r = rand() % 2;
        if(r==0)
        {
            white_player=n1;
            black_player=n2;
        }
        else
        {
            white_player=n2;
            black_player=n1;
        }
        white_player->color='w';
        black_player->color='b';
    }
    white_player->boardgame=black_player->boardgame;
	mainboard=white_player->boardgame;
	is_turn=white_player;
    result="";
}
void Game::startgame()
{
    while(!(is_finished()))
    {
        player_move();
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
    bool flag=true;
    while(flag)
    {
        try
        {
            is_turn->move();
            flag=false;
        }
        catch(const Illegal_move& e)
        {
            flag=true;
        }
    }
    
    
}
bool Game::is_finished()
{
    bool mate=0;
    if(mainboard->is_draw())
    {
        result="PATTA";
        return true;
    }
    if(is_turn==white_player)
    {
        mate=mainboard->is_check_mate('w');
        if(mate==1)
        {
            result="VINCITORE NERO";
            return true;
        }
    }
    else
    {
        mate=mainboard->is_check_mate('b');
        if(mate==1)
        {
            result="VINCITORE BIANCO";
            return true;
        }
    }
    return false;
}
#endif
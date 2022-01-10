#ifndef GAME_CPP
#define GAME_CPP
#include <iostream>
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
        
    }
    else
    {
        white_player=n1;
        black_player=n2;
    }
    white_player->color='w';
    black_player->color='b';
	mainboard=new Board();
    white_player->boardgame=mainboard;
    black_player->boardgame=mainboard;
	is_turn=white_player;
    result="";
    nmosse=0;
	last_bs={mainboard->to_string()};
}
void Game::startgame()
{
    cout<<*mainboard<<endl;
    while(!(is_finished()))
    {
        player_move();
        change_turn();
        for(int i=0;i<8;i++)
        {
            for(int j=0;j<8;j++)
            
                if(mainboard->gameboard[i][j]!=nullptr)
                    cout<<mainboard->gameboard[i][j]->color;
                else
                    cout<<" ";
                    cout<<endl;
        }
    }
    cout<<result<<endl;
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
        catch(Illegal_move* e)
        {
            cout<<"illegal move"<<endl;
            flag=true;
        }
    }
    nmosse++;
	last_bs.push_back(mainboard->to_string());
    cout<<*mainboard<<endl;
}
bool Game:: draw_for_ripetition()
{
	int counter=0;
	for(int i=0;i<last_bs.size();i++)
	{
		if(mainboard->to_string==last_bs[i])
		{
				counter++;
		}
	}
	if(counter>=3) return true;
	return false;
}
bool Game::is_finished()
{
    bool mate=0;
    if(nmosse>50 && (!white_player->is_human) && (!black_player->is_human))
    {
        result="PATTA, 50 MOSSE";
        return true;
    }
    if(mainboard->is_draw(is_turn->color))
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
	if(draw_for_ripetition())
	{
		cout<<"PATTA PER RIPETIZIONE DI MOSSE";
		return true;
	}
    return false;
}
#endif
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
	last_bs={mainboard->to_String()};
    pawns="PPPPPPPP                                pppppppp";
    fmcount=0;
    npieces=16;
    
}
void Game::startgame()
{
    cout<<*mainboard<<endl;
    srand(time(NULL));
    while(!(is_finished()))
    {
        player_move();
        change_turn();
        for(int i=0;i<mainboard->whites.size();i++)
            cout<<mainboard->whites[i]->piece;
        cout<<endl;
        for(int i=0;i<mainboard->blacks.size();i++)
            cout<<mainboard->blacks[i]->piece;
        cout<<endl;
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
            if(is_turn->is_human==true)
                cout<<"illegal move"<<endl;
            flag=true;
        }
    }
    nmosse++;
	last_bs.push_back(mainboard->to_String());
    cout<<*mainboard<<endl;
}
bool Game:: draw_for_ripetition()
{
	int counter=0;
	for(int i=0;i<last_bs.size();i++)
	{
		if((mainboard->to_String()).compare(last_bs[i])==0)
		{
				counter++;
		}
	}
	if(counter>=3) return true;
	return false;
}


bool Game::fifty_moves(){
	string s="";
    if(fmcount==50) return true;
    for(int i=1;i<7;i++){
        for(int j=0;j<8;j++){
            if(mainboard->gameboard[i][j]!=nullptr){
                if(mainboard->gameboard[i][j]->piece=='p' || mainboard->gameboard[i][j]->piece=='P'){
                    s=s+mainboard->gameboard[i][j]->piece;
                }
                else{
                    s=s+" ";
                }
            }
        }
    }
    int n=mainboard->whites.size()+mainboard->blacks.size();
    if(s.compare(pawns) && n==npieces){
        fmcount++;
    }
    else{
        pawns=s;
        npieces=n;
        fmcount=0;
    }
    return false;
}

bool Game::is_finished()
{
    bool mate=0;
    if(nmosse>=50 && (!white_player->is_human) && (!black_player->is_human))
    {
        result="PATTA,LIMITE 50 MOSSE";
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

		result="PATTA PER RIPETIZIONE DI MOSSE";
		return true;
	}
    if(fifty_moves())
    {
        result="PATTA, 50 MOSSE SENZA MUOVERE PEDONE O CATTURARE PEZZI";
        return true;
    }
    return false;
}
#endif
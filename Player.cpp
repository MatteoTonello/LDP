#ifndef PLAYER_CPP
#define PLAYER_CPP
#include <stdlib.h>
#include <time.h>
#include "Player.h"
#include <iostream>
#include "Board.cpp"
using namespace std;
Player::Player(char c)
{
	if(c!='c' || c!='p') cout<<"sbagliati giocatori";
	if(c=='p')is_human=true;
	if(c=='c')is_human=false;
	boardgame=new Board();
};
void Player::move()
{
	srand(time(NULL));
	if(is_human)
	{
		int ni,li,nf,lf;
		char i_letter,f_letter;
		int i_number,f_number;
		string mossa="";
		cin>>mossa;
		if(mossa=="XX XX")
		{
			cout<<*boardgame<<endl;
			move();
			return;
		}
		/*i_letter=mossa[0];	//ancora da convertire
		f_letter=mossa[3];
		i_number=mossa[1]-48;
		f_number=mossa[4]-48;
		if(mossa[2]!=' ') throw new Illegal_move();
		if(i_number<0 || i_number>=8)
		if(f_number)*/
		//da finire
	}
	else
	{
		int random_letter=0,random_number=0,random_piece=0;
		if(color=='w')
		{
			do
			{
				random_piece=rand()%boardgame->whites.size();
				random_number=rand()%8;
				random_letter=rand()%8;
			}while(!(boardgame->whites[random_piece]->try_move(random_number,random_letter)));
			boardgame->whites[random_piece]->move(random_number,random_letter);
		}
		if(color=='b')
		{
			do
			{
				random_piece=rand()%boardgame->blacks.size();
				random_number=rand()%8;
				random_letter=rand()%8;
			}while(!(boardgame->blacks[random_piece]->try_move(random_number,random_letter)));
			boardgame->blacks[random_piece]->move(random_number,random_letter);
		}
		
	}
	
}
#endif
	

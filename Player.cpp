#ifndef PLAYER_CPP
#define PLAYER_CPP
#include <stdlib.h>
#include <time.h>
#include "Player.h"
#include <iostream>
#include "Board.cpp"
#include "Illegal_move.cpp"
using namespace std;
Player::Player(char c)
{
	if(c!='c' && c!='p') cout<<"sbagliati giocatori";
	if(c=='p')is_human=true;
	if(c=='c')is_human=false;
	color='n';
	boardgame=new Board();
};
void Player::move()
{
	srand(time(NULL));
	if(is_human)
	{
		int i_letter,f_letter;
		char chari_letter,charf_letter;
		int i_number,f_number;
		string mossa="";
		cin>>mossa;
		if(mossa=="XX XX")
		{
			cout<<*boardgame<<endl;
			move();
			return;
		}
		chari_letter=mossa[0];	//convertiti
		charf_letter=mossa[3];
		i_number=mossa[1]-'0';	//da convertire
		f_number=mossa[4]-'0';
		if(mossa[2]!=' ') throw new Illegal_move();
		if(i_number<0 || i_number>=8) throw new Illegal_move();
		if(f_number<0 || f_number>=8) throw new Illegal_move();
		if(chari_letter<'A' || chari_letter>'z') throw new Illegal_move();
		if(charf_letter>'Z' || charf_letter<'a') throw new Illegal_move();
		if(chari_letter>='A' && chari_letter<'Z') i_letter=chari_letter-'A';
		if(chari_letter>='a' && chari_letter<'z') i_letter=chari_letter-'a';
		i_number=7-i_number+1; //conversione numeri per la matrice
		f_number=7-f_number+1;
		if(!(boardgame->gameboard[i_number][i_letter]->try_move(f_number,f_letter)))
		{
			cout<<"Illegal move"<<endl;
			move();
		}
		boardgame->gameboard[i_number][i_letter]->move(f_number,f_letter);
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
			cout<<boardgame->whites[random_piece]->number<<boardgame->whites[random_piece]->letter<<" "<<random_number<<random_letter<<endl<<endl;
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
			cout<<boardgame->blacks[random_piece]->number<<boardgame->blacks[random_piece]->letter<<" "<<random_number<<random_letter<<endl<<endl;
			boardgame->blacks[random_piece]->move(random_number,random_letter);
		}
		
	}
	
}
#endif
	

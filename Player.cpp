#include <stdlib.h>
#include <time.h
#include <iostream>
#include "Board.cpp"
#ifndef PLAYER_H
#def PLAYER_H

class Player
{
	public:
		Player(char col, char c )
		{
			if(c!='c' || c!='p')throw Illegal_move();
			if(c=='p')is_human=true;
			if(c=='c') is_human=false;
			color=c;
		};
		void move()
		{
			srand(time(NULL));
			String mossa;
			if(is_human)cin>>mossa;
			else random_move();
			{
				if(color=='w')
				{
					int chose_index_random=rand()%whites.size();
					
					
				}
			}
		}
		char computer_or_human;
		char color;
		bool is_human;
}
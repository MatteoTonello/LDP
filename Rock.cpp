#ifndef ROCK_CPP
#define ROCK_CPP
#include "Illegal_move.cpp"
#include "Rock.h"
#include "Board.cpp"
using namespace std;

Rock::Rock(int n, int l, char col, Board& myBoard )
{
	number=n;
	letter=l;
	color=col;
	b=myBoard;
	if(color=='w') piece='t';
	else piece='T';
}

bool Rock:: can_move()
{
	b.gameboard[letter][number]=nullptr;
	if(b.is_check(color)) return false;
	b.gameboard[letter][number]=this;
	for(int i=-1; i<=1; i++)
	{
			if(b.gameboard[letter][number+i]==nullptr || b.gameboard[letter+i][number]==nullptr) return true;
			if(b.gameboard[letter][number+i]->color!=color || b.gameboard[letter+i][number]->color!=color) return true;
	}
	return false;
}

void Rock:: move(int l, int n)
{
	if(!can_move()) throw new Illegal_move();
	if(letter!=l && number!=n) throw new Illegal_move();
	int vertical=number, horizontal=letter ;
	if(number!=n && letter==l)
	{
		if(n>number)
		{
			vertical++;
			while(vertical<n && b.gameboard[letter][vertical]==nullptr)
			{
				vertical++;
			}
			if(vertical!=n) throw new Illegal_move();
		}
		else
		{
			vertical--;
			while(vertical>=n && b.gameboard[letter][vertical]==nullptr)
			{
				vertical--;
			}
			if(vertical!=n) throw new Illegal_move();
		}
	}
	if(letter!=l && number==n)
	{
		if(l>letter)
		{
			horizontal++;
			while(horizontal<l && b.gameboard[horizontal][n]==nullptr)
			{
				horizontal++;
			}
			if(horizontal!=l) throw new Illegal_move();
		}
		else
		{
			horizontal--;
			while(horizontal>=n && b.gameboard[horizontal][n]==nullptr)
			{
				horizontal--;
			}
			if(horizontal!=l) throw new Illegal_move();
		}
	}
	#endif
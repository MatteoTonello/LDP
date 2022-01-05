#ifndef ROCK_CPP
#define ROCK_CPP
#include "Illegal_move.cpp"
#include "Rock.h"
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
	if(b.is_check()) return false;
	b.gameboard[letter][number]=this;
	for(int i=-1; i<=1; i++)
	{
		for(int j=-1;j<=1;j++)
		{
			if(b.gameboard[letter+i][number+j]==nullptr) return true;
			if(b.gameboard[letter+i][number+j]->color!=color) return true;
		}
	}
	return false;
}
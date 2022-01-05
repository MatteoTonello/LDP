#ifndef KING_CPP
#define KING_CPP
#include "Illegal_move.cpp"
#include "King.h"
#include <cstdlib>
using namespace std;
King::King(int l, int n, char col, Board& myBoard)
{
	number=n;
	letter=l;
	color=col;
	b=myBoard;
	if(color=='w') piece='r';
	else piece='R';
};

bool King:: can_move()
{
	if(b.is_check()) return false;
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
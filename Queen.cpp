#ifndef QUEEN_CPP
#define QUEEN_CPP
#include "Illegal_move.cpp"
#include "Queen.h"
#include "Board.cpp"
using namespace std;

Queen::Queen(int n, int l, char col, Board* myBoard )
{
	number=n;
	letter=l;
	color=col;
	b=myBoard;
	if(color=='w') piece='d';
	else piece='D';
}
bool Queen:: can_move()
{
	b->gameboard[number][letter]=nullptr;
	if(b->is_check(color)) return false;
	b->gameboard[number][letter]=this;
	for(int i=-1; i<=1; i++)
	{
		for(int j=-1;j<=1;j++)
		{
			if(b->gameboard[number+i][letter+j]==nullptr) return true;
			if(b->gameboard[number+i][letter+j]->color!=color) return true;
		}
	}
	return false;
}
int abs_value(int j)
{
	if(j>0) return j;return -j;
}
void Queen:: move(int n, int l)
{
	if(!can_move()) throw new Illegal_move();
	if((letter!=l && number!=n)&&(abs_value(number-n)!=abs_value(letter-l))) throw new Illegal_move();
	int vertical=number, horizontal=letter ;
	if(number!=n && letter==l)
	{
		if(n>number)
		{
			vertical++;
			while(vertical<n && b->gameboard[vertical][letter]==nullptr)
			{
				vertical++;
			}
			if(vertical!=n) throw new Illegal_move();
		}
		else
		{
			vertical--;
			while(vertical>=n && b->gameboard[vertical][letter]==nullptr)
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
			while(horizontal<l && b->gameboard[n][horizontal]==nullptr)
			{
				horizontal++;
			}
			if(horizontal!=l) throw new Illegal_move();
		}
		else
		{
			horizontal--;
			while(horizontal>=n && b->gameboard[n][horizontal]==nullptr)
			{
				horizontal--;
			}
			if(horizontal!=l) throw new Illegal_move();
		}
	}
	if(n>number)
	{
		if(l>letter)
		{
			for(int i=number, j=letter; i<=n; i++, j++)
			{
				if(b->gameboard[i][j]!=nullptr) throw new Illegal_move();
			}
		}
		else
		{
			for(int i=number, j=letter; i<=n; i++, j--)
			{
				if(b->gameboard[i][j]!=nullptr) throw new Illegal_move();
			}
		}
	}
	else
	{
		if(l>letter)
		{
			for(int i=number, j=letter; i<=n; i--, j++)
			{
				if(b->gameboard[i][j]!=nullptr) throw new Illegal_move();
			}
		}
		else
		{
			for(int i=number, j=letter; i<=n; i--, j--)
			{
				if(b->gameboard[i][j]!=nullptr) throw new Illegal_move();
			}
		}
	}
	if(b->gameboard[n][l]!=nullptr)
	{
		if(b->gameboard[n][l]->color==color)throw new Illegal_move();
	}
	b->gameboard[number][letter]=nullptr;
	letter=l; number=n;
	b->gameboard[n][l]=this;
}
#endif

#ifndef QUEEN_CPP
#define QUEEN_CPP
#include "Illegal_move.cpp"
#include "Queen.h"
using namespace std;

Queen::Queen(int n, int l, char col, Board& myBoard )
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
int abs_value(int j)
{
	if(j>0) return j;return -j;
}
void Queen:: move(int l, int n)
{
	if(b.is_check()) throw invalid_move();
	if((letter!=l && number!=n)&&(abs_value(number-n)!=abs_value(letter-l))) throw invalid_move();
	int vertical=number, horizontal=letter ;
	if(number!=n && letter=l)
	{
		if(n>number)
		{
			vertical++;
			while(vertical<n && b.gameboard[letter][vertical]==nullptr)
			{
				vertical++;
			}
			if(vertical!=n) throw invalid_move();
		}
		else
		{
			vertical--;
			while(vertical>=n && b.gameboard[letter][vertical]==nullptr)
			{
				vertical--;
			}
			if(vertical!=n) throw invalid_move();
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
			if(horizontal!=l) throw invalid_move();
		}
		else
		{
			horizontal--;
			while(horizontal>=n && b.gameboard[horizontal][n]==nullptr)
			{
				horizontal--;
			}
			if(horizontal!=l) throw invalid_move();
		}
	}
	if(n>number)
	{
		if(l>letter)
		{
			for(int i=number, j=letter; i<=n; i++, j++)
			{
				if(b.gameboard[i][j]!=nullptr) throw invalid_move();
			}
		}
		else
		{
			for(int i=number, j=letter; i<=n; i++, j--)
			{
				if(b.gameboard[i][j]!=nullptr) throw invalid_move();
			}
		}
	}
	else
	{
		if(l>letter)
		{
			for(int i=number, j=letter; i<=n; i--, j++)
			{
				if(b.gameboard[i][j]!=nullptr) throw invalid_move();
			}
		}
		else
		{
			for(int i=number, j=letter; i<=n; i--, j--)
			{
				if(b.gameboard[i][j]!=nullptr) throw invalid_move();
			}
		}
	}
	if(b.gameboard[l][n]!=nullptr)
	{
		if(b.gameboard[l][n]->color==color)throw invalid_move();
	}
	b.gameboard[letter][number]=nullptr;
	letter=l; number=n;
	b.gameboard[l][n]=this;
}

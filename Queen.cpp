#include "Queen.h"
using namespace std;

Queen::Queen(int n, int l, char col, Board& myBoard )
{
	number=n;
	letter=l;
	color=col;
	b=myBoard;
	if(color=='w') piece='D';
	else piece='d';
}
bool Queen:: can_move()
{
	*(b.gameboard[letter][number])=nullptr;
	if(b.is_check()) return false;
	*(b.gameboard[letter][number])=this;
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
	int vertical, horizontal ;
	if(number!=n && letter=l)
	{
		if(n>number)
		{
			vertical++;
			while(vertical<=n && b.gameboard[letter][vertical]==nullptr)
			{
				vertical++;
			}
			if(vertical!=n && b.gameboard[letter][vertical]==nullptr) throw invalid_move();
		}
		else
		{
			vertical--;
			while(vertical>=n && b.gameboard[letter][vertical]==nullptr)
			{
				vertical--;
			}
			if(vertical!=n || b.gameboard[letter][vertical]!=nullptr) throw invalid_move();
		}
	}
	if(letter!=l && number==n)
	{
		if(n>number)
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
				if(b.gameboard[i][j]) throw invalid_move();
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
				if(b.gameboard[i][j]) throw invalid_move();
			}
		}
	}
	if(b.gameboard[l][n]!=nullptr)
	{
		if(b.gameboard[l][n]->color==color)throw invalid_move();
	}
	b.gameboard[letter][number]=null;
	letter=l; number=n;
	*(b.gameboard[l][n])=this;
}

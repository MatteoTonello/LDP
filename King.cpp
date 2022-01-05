#ifndef KING_H
#define KING_H
#include "King.h"
#include "Board.cpp"
using namespace std;

King::King(int n, int l, char col, Board* myBoard)
{
    number=n;
	letter=l;
	color=col;
	b=myBoard;
	if(color=='w') piece='r';
	else piece='R';
	is_already_move=false;
}
bool King::can_move()
{
	int j=-1; int i=-1;
	int save_letter=letter, save_number=number;
	while(i<=1)
		{
			while(j<=1)
			{
				if(b->gameboard[i][j]==nullptr)
				{
					b->gameboard[i][j]=this;
					b->gameboard[letter][number]=nullptr;
					letter=i; number=j;
					if(!b->is_check(color))
					{
						b->gameboard[i][j]=nullptr;
						b->gameboard[save_letter][save_number]=this;
						letter=save_letter; number=save_number;
						return true;
					}
					b->gameboard[i][j]=nullptr;
					b->gameboard[save_letter][save_number]=this;
					letter=save_letter; number=save_number;
				}
				if(b->gameboard[i][j]->color!=color)
				{
					Piece* p=b->gameboard[i][j];
					b->gameboard[i][j]=this;
					b->gameboard[letter][number]=nullptr;
					letter=i; number=j;
					if(!b->is_check(color))
					{
						b->gameboard[i][j]=p;
						b->gameboard[save_letter][save_number]=this;
						letter=save_letter; number=save_number
						return true;
					}
					b->gameboard[i][j]=p;
					b->gameboard[save_letter][save_number]=this;
					letter=save_letter; number=save_number;
				}
				j++;
			}
			i++;
		}
	return false;
}
void King::move(int n, int l)
{
	if(abs_value(n-number)!=1 || abs_value(l-letter)!=1) throw new Illegal_move();
	int save_letter=letter, save_number=number;
	if(b->gameboard[l][n]==nullptr)
				{
					b->gameboard[l][n]=this;
					b->gameboard[letter][number]=nullptr;
					letter=l; number=n;
					if(b->is_check(color))
					{
						b->gameboard[l][n]=nullptr;
						b->gameboard[save_letter][save_number]=this;
						letter=save_letter; number=save_number;
						throw new Illegal_move();
					}
					b->gameboard[l][n]=nullptr;
					b->gameboard[save_letter][save_number]=this;
					letter=save_letter; number=save_number;
				}
				if(b->gameboard[l][n]->color!=color)
				{
					Piece* p=b->gameboard[l][n];
					b->gameboard[l][n]=this;
					b->gameboard[letter][number]=nullptr;
					letter=l; number=n;
					if(b->is_check(color))
					{
						b->gameboard[l][n]=p;
						b->gameboard[save_letter][save_number]=this;
						letter=save_letter; number=save_number;
						throw new Illegal_move();
					}
					b->gameboard[l][n]=p;
					b->gameboard[save_letter][save_number]=this;
					letter=save_letter; number=save_number;
				}
	if(b->gameboard[l][n]->color==color)
	{
		throw new Illegal_move();
	}
	b->gameboard[letter][number]=nullptr;
	number=n;
	letter=l;
	
	b->gameboard[l][n]=this;
	is_already_move=true;
	return;
	
}
#endif
#ifndef KING_CPP
#define KING_CPP
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
bool King::try_move(int n,int l)
{
	return 0;
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
					b->gameboard[number][letter]=nullptr;
					number=i; letter=j;
					if(!b->is_check(color))
					{
						b->gameboard[i][j]=nullptr;
						b->gameboard[save_number][save_letter]=this;
						letter=save_letter; number=save_number;
						return false;
					}
					b->gameboard[i][j]=nullptr;
					b->gameboard[save_number][save_letter]=this;
					letter=save_letter; number=save_number;
				}
				if(b->gameboard[i][j]->color!=color)
				{
					Piece* p=b->gameboard[i][j];
					b->gameboard[i][j]=this;
					b->gameboard[number][letter]=nullptr;
					number=i; letter=j;
					if(!b->is_check(color))
					{
						b->gameboard[i][j]=p;
						b->gameboard[save_number][save_letter]=this;
						letter=save_letter; number=save_number;
						return false;
					}
					b->gameboard[i][j]=p;
					b->gameboard[save_number][save_letter]=this;
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
	if(n==number && (l==letter+2 || l==letter-2) )
	{
		if(b->is_check(color)) throw new Illegal_move();
		if(l==6) short_castling();
		if(l==2) long_castling();
		return;
	}
	if(abs_value(n-number)!=1 || abs_value(l-letter)!=1) throw new Illegal_move();
	int save_letter=letter, save_number=number;
	if(b->gameboard[n][l]==nullptr)
				{
					b->gameboard[n][l]=this;
					b->gameboard[number][letter]=nullptr;
					letter=l; number=n;
					if(b->is_check(color))
					{
						b->gameboard[n][l]=nullptr;
						b->gameboard[save_number][save_letter]=this;
						letter=save_letter; number=save_number;
						throw new Illegal_move();
					}
				}
				if(b->gameboard[n][l]->color!=color)
				{
					Piece* p=b->gameboard[n][l];
					b->gameboard[n][l]=this;
					b->gameboard[number][letter]=nullptr;
					letter=l; number=n;
					if(b->is_check(color))
					{
						b->gameboard[n][l]=p;
						b->gameboard[save_number][save_letter]=this;
						letter=save_letter; number=save_number;
						throw new Illegal_move();
					}
					if(color=='w')
					{
						for(int i=0;i<b->blacks.size();i++)
						{
							if(b->blacks[i]==p){ b->blacks.erase(b->blacks.begin()+i); break;}
						}
					}
					if(color=='b')
					{
						for(int i=0;i<b->whites.size();i++)
						{
							if(b->whites[i]==p){ b->whites.erase(b->whites.begin()+i); break;}
						}
					}
				}
	if(b->gameboard[n][l]->color==color)
	{
		throw new Illegal_move();
	}
	is_already_move=true;
	remove_en_passant();
	return;
}
void King::short_castling()
{
		if((!is_already_move) && b->gameboard[number][7]->piece=='t' && !(((Rock*)(b->gameboard[number][7]))->is_already_move))
		{
			if(b->gameboard[number][5]==nullptr && b->gameboard[number][6]== nullptr)
			{
				    b->gameboard[number][5]=this;
					b->gameboard[number][letter]=nullptr;
					letter=5;
					if(b->is_check(color))
					{
						b->gameboard[number][5]=nullptr;
						b->gameboard[number][4]=this;
						letter=4;
						throw new Illegal_move();
					}
					b->gameboard[number][5]=nullptr;
					b->gameboard[number][4]=this;
					letter=4;
					b->gameboard[number][6]=this;
					b->gameboard[number][letter]=nullptr;
					letter=6; 
					if(b->is_check(color))
					{
						b->gameboard[number][6]=nullptr;
						b->gameboard[number][4]=this;
						letter=4; 
						throw new Illegal_move();
					}
					b->gameboard[number][5]=b->gameboard[number][7];
					b->gameboard[number][7]=nullptr;
					b->gameboard[number][5]->letter=5;
			}
		}
}
void King::long_castling()
{
	if((!is_already_move) && b->gameboard[number][0]->piece=='t' && !(((Rock*)(b->gameboard[number][0]))->is_already_move))
		{
			if(b->gameboard[number][1]==nullptr && b->gameboard[number][2]== nullptr && b->gameboard[number][3]==nullptr)
			{
				   b->gameboard[number][3]=this;
					b->gameboard[number][letter]=nullptr;
					letter=3;
					if(b->is_check(color))
					{
						b->gameboard[number][3]=nullptr;
						b->gameboard[number][4]=this;
						letter=4;
						throw new Illegal_move();
					}
					b->gameboard[number][3]=nullptr;
					b->gameboard[number][4]=this;
					letter=4;
					b->gameboard[number][2]=this;
					b->gameboard[number][letter]=nullptr;
					letter=2; 
					if(b->is_check(color))
					{
						b->gameboard[number][2]=nullptr;
						b->gameboard[number][4]=this;
						letter=4; 
						throw new Illegal_move();
					}
					b->gameboard[number][3]=b->gameboard[number][0];
					b->gameboard[number][0]=nullptr;
					b->gameboard[number][3]->letter=3;
			}
		}
}
#endif
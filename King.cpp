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
	is_not_check=false;
}
bool King::try_move(int n,int l)
{
	return true;
}
bool King::can_move()
{
	int save_letter=letter;
	int save_number=number;
	for(int i=-1; i<=1; i++)
	{
		if(number+i>=0 && number+i<=7){
			for(int j=-1;j<=1;j++)
			{
				if(letter+j>=0 && letter+j<=7)
				{
					if(b->gameboard[number+i][letter+j]==nullptr || b->gameboard[number+i][letter+j]->color!=color)
					{
						Piece* p=b->gameboard[number+i][letter+j];
						b->gameboard[number+i][letter+j]=this;
						b->gameboard[number][letter]=nullptr;
						number=number+i; letter=letter+j;
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
						if(!(b->is_check(color)))
						{
							b->gameboard[number][letter]=p;
							b->gameboard[save_number][save_letter]=this;
							letter=save_letter; number=save_number;
							if(p!=nullptr)
							if(color=='w') b->blacks.push_back(p);
							else b->whites.push_back(p);
							return true;
						}
						if(p!=nullptr)
						if(color=='w') b->blacks.push_back(p);
							else b->whites.push_back(p);
						b->gameboard[number][letter]=p;
						b->gameboard[save_number][save_letter]=this;
						letter=save_letter; number=save_number;
					
					}
				}
			}
		}
	}
	return false;
	/*int j=-1; int i=-1;
	int save_letter=letter, save_number=number;
	while(i<=1)
		{
			while(j<=1)
			{
				if(b->gameboard[i][j]==nullptr)
				{
					b->gameboard[number+i][j]=this;
					b->gameboard[number][letter]=nullptr;
					number=number+i; letter=letter+j;
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
	*/
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
	if(abs_value(n-number)>1 || abs_value(l-letter)>1) throw new Illegal_move();
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
	else
	{
		if(b->gameboard[n][l]->color!=color)
		{
			Piece* p=b->gameboard[n][l];
			b->gameboard[n][l]=this;
			b->gameboard[number][letter]=nullptr;
			letter=l; number=n;
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
			if(b->is_check(color))
			{
				b->gameboard[n][l]=p;
				b->gameboard[save_number][save_letter]=this;
				letter=save_letter; number=save_number;
				if(color=='w') b->blacks.push_back(p);
					else b->whites.push_back(p);
				throw new Illegal_move();
			}
					
	    }
		else
			throw new Illegal_move();

	}
	is_already_move=true;
	remove_en_passant();
	return;
}
void King::short_castling()
{
		if((!is_already_move) && (b->gameboard[number][7]!=nullptr) && (b->gameboard[number][7]->piece=='t' || b->gameboard[number][7]->piece=='T') && !(((Rock*)(b->gameboard[number][7]))->is_already_move))
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
					return;
			}
			
		}
		throw new Illegal_move();
}
void King::long_castling()
{
	if((!is_already_move) && (b->gameboard[number][0]!=nullptr) && (b->gameboard[number][0]->piece=='t' || b->gameboard[number][0]->piece=='T') && !(((Rock*)(b->gameboard[number][0]))->is_already_move))
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
					return;
			}
		}
		throw new Illegal_move();
}
#endif
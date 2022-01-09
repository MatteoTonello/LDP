#ifndef ROCK_CPP
#define ROCK_CPP
#include "Illegal_move.cpp"
#include "Rock.h"
using namespace std;

Rock::Rock(int n, int l, char col, Board* myBoard )
{
	number=n;
	letter=l;
	color=col;
	b=myBoard;
	if(color=='w') piece='t';
	else piece='T';
	is_already_move=false;
};

bool Rock:: can_move()
{
	for(int i=-1; i<=1; i=i+2)
	{
		if(letter+i>=0 && letter+i<=7 ){
			if(b->gameboard[number][letter+i]==nullptr || b->gameboard[number][letter+i]->color!=color) return true;
		}
		if(number+i>=0 && number+i<=7){
			if(b->gameboard[number+i][letter]==nullptr || b->gameboard[number+i][letter]->color!=color) return true;
		}			
	}
	return false;
};

void Rock:: move(int n, int l)
{
	if(try_move(n, l))
	{
		int save_number=number, save_letter=letter;
		Piece* temp=b->gameboard[n][l];
		b->gameboard[number][letter]=nullptr;
		letter=l;number=n;
		b->gameboard[n][l]=this;
		if(b->is_check(color))
		{
			b->gameboard[n][l]=temp;
			b->gameboard[save_number][save_letter]=this;
			number=save_number; letter=save_letter;
			throw new Illegal_move();
		}
		else
		{
			if(temp!=nullptr)
			{
				if(color=='w')
				{
					for(int i=0;i<b->blacks.size();i++)
					{
						if(b->blacks[i]==temp){ b->blacks.erase(b->blacks.begin()+i); break;}
					}
				}
				if(color=='b')
				{
					for(int i=0;i<b->whites.size();i++)
					{
						if(b->whites[i]==temp){ b->whites.erase(b->whites.begin()+i); break;}
					}
				}
			}
			is_already_move=true;
			remove_en_passant();
			return;
		}	
	}
	throw new Illegal_move();
}


bool Rock::try_move(int n, int l){
	
	if(!can_move()) return false;
	if(letter!=l && number!=n) return false;
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
			if(vertical!=n) return false;
		}
		else
		{
			vertical--;
			while(vertical>n && b->gameboard[vertical][letter]==nullptr)
			{
				vertical--;
			}
			if(vertical!=n) return false;
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
			if(horizontal!=l) return false;
		}
		else
		{
			horizontal--;
			while(horizontal>l && b->gameboard[n][horizontal]==nullptr)
			{
				horizontal--;
			}
			if(horizontal!=l) return false;
		}
	}
	if(b->gameboard[n][l]!=nullptr)
    {
        if(b->gameboard[n][l]->color==color)return false;
    }
	return true;
}
	#endif
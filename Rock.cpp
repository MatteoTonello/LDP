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
};

bool Rock:: can_move()
{
	b->gameboard[number][letter]=nullptr;
	if(b->is_check(color)) return false;
	b->gameboard[number][letter]=this;
	for(int i=-1; i<=1; i+2)
	{
		if(letter+i>=0 && letter+i<=7 ){
			if(b->gameboard[number][letter+i]==nullptr || b->gameboard[number][letter+i]->color!=color) return true;
		}else if(number+i>=0 && number+i<=7){
			if(b->gameboard[number+i][letter]==nullptr || b->gameboard[number+i][letter]->color!=color) return true;
		}			
	}
	return false;
};

void Rock:: move(int n, int l)
{
	if(try_move(n,l)){
		b->gameboard[number][letter]=nullptr;
		letter=l; number=n;
		b->gameboard[n][l]=this;
	};
}

bool Rock::try_move(int n, int l){
	try{
		if(!can_move()) throw new Illegal_move();
		if(letter!=l && number!=n) throw new Illegal_move();
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
		return true;
	}catch(new Illegal_move())
	{return false;}
	return false;
}
	#endif
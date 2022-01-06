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
		return;
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
			while(vertical>=n && b->gameboard[vertical][letter]==nullptr)
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
			while(horizontal>=n && b->gameboard[n][horizontal]==nullptr)
			{
				horizontal--;
			}
			if(horizontal!=l) return false;
		}
	}
	return true;
}
	#endif
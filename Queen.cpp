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
	//Controllo le 8 caselle circostanti
	for(int i=-1; i<=1; i++)
	{
		if(number+i>=0 && number+i<=7){
			for(int j=-1;j<=1;j++)
			{
				if(letter+j>=0 && letter+j<=7){
					if(b->gameboard[number+i][letter+j]==nullptr) return true; //
					if(b->gameboard[number+i][letter+j]->color!=color) return true;
				}
			}
		}
	}
	return false;
}
bool Queen::try_move(int n, int l)
{
	if(!can_move()) return false;
	if((letter!=l && number!=n)&&(abs(number-n)!=abs(letter-l))) return false;
	int vertical=number, horizontal=letter;
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
	if(n>number)
	{
		if(l>letter)
		{
			for(int i=number+1, j=letter+1; i<n; i++, j++)
			{
				if(b->gameboard[i][j]!=nullptr) return false;
			}
		}
		if(l<letter)
		{
			for(int i=number+1, j=letter-1; i<n; i++, j--)
			{
				if(b->gameboard[i][j]!=nullptr) return false;
			}
		}
	}
	else
	{
		if(l>letter)
		{
			for(int i=number-1, j=letter+1; i>n; i--, j++)
			{
				if(b->gameboard[i][j]!=nullptr) return false;
			}
		}
		if(l<letter)
		{
			for(int i=number-1, j=letter-1; i>n; i--, j--)
			{
				if(b->gameboard[i][j]!=nullptr) return false;
			}
		}
	}
	if(b->gameboard[n][l]!=nullptr)
	{
		if(b->gameboard[n][l]->color==color)return false;
	}
	return !diventa_scacco(n,l,n,l);
}
void Queen:: move(int n, int l)
{
	if(try_move(n, l))
	{
		int save_number=number, save_letter=letter;
		Piece* temp=b->gameboard[n][l];
		b->gameboard[number][letter]=nullptr;
		letter=l;number=n;
		b->gameboard[n][l]=this;
		if(color=='w')
			for(int i=0;i<b->blacks.size();i++)
				if(b->blacks[i]==temp){ b->blacks.erase(b->blacks.begin()+i); break;}
		if(color=='b')
			for(int i=0;i<b->whites.size();i++)
				if(b->whites[i]==temp){ b->whites.erase(b->whites.begin()+i); break;}
			remove_en_passant();
			return;
		}	
	
	throw new Illegal_move();
}
#endif

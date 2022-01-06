#ifndef KNIGHT_CPP
#define KNIGHT_CPP
#include "Illegal_move.cpp"
#include "Knight.h"
#include <cstdlib>
using namespace std;
Knight::Knight(int n, int l, char col, Board* myBoard)
{
	number=n;
	letter=l;
	color=col;
	b=myBoard;
	if(color=='w') piece='c';
	else piece='C';
}

bool Knight::can_move()
	{
		b->gameboard[number][letter]=nullptr;
		if(b->is_check(color))return false;	//controllo scacco
		b->gameboard[number][letter]=this;
		return 0;
	};
	
void Knight::move(int n, int l)
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
		return;
	}
	throw new Illegal_move();
	}

bool Knight::try_move(int n, int l){

		if(!can_move()) return false;
		if((abs(l-letter)==2 && abs(n-number)==1) || (abs(l-letter)==1 && abs(n-number)==2)){ //controllo se non è una delle 8 caselle possibili
			if(b->gameboard[n][l]==nullptr) if(b->gameboard[n][l]->color==color) return false;	//controllo se è lo stesso colore
				return true;
		}
		else return false;
}
#endif

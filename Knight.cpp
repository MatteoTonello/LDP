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
		if(!can_move()) throw new Illegal_move();
		if((abs(l-letter)==2 && abs(n-number)==1) || (abs(l-letter)==1 && abs(n-number)==2)){ //controllo se non è una delle 8 caselle possibili
			if(b->gameboard[n][l]==nullptr) if(b->gameboard[n][l]->color==color) throw new Illegal_move();	//controllo se è lo stesso colore
			b->gameboard[number][letter]=nullptr;	//Se non è uguale effettuo la modifica
			number=n;
			letter=l;
			b->gameboard[n][l]=this;
			return;
		}
		else throw new Illegal_move();
	}
#endif

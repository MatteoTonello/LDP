#ifndef KNIGHT_CPP
#define KNIGHT_CPP
#include "Illegal_move.cpp"
#include "Knight.h"
using namespace std;
Knight::Knight(int l, int n, char col, Board& myBoard)
{
	number=n;
	letter=l;
	color=col;
	b=myBoard;
	if(color=='w') piece='c';
	else piece='C';
};

bool Knight::can_move()
		{
			b.gameboard[letter][number]=nullptr;
			if(b.is_check(color))return false;
			b.gameboard[letter][number+1]=this;
		};
void Knight::move(int n, int l)
		{
         if(l-letter>3 || l-letter<-3 || n-number>3 || n-number<-3) throw new Illegal_move();
         
		}
#endif

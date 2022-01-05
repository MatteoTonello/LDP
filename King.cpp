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
}
void King::move(int n, int l)
{
    return;
}
bool King::can_move()
{
    return 0;
}
#endif
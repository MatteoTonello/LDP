#ifndef KING_H
#define KING_H
#include <iostream>
#include "Piece.h"
using namespace std;
class King:public Piece
{
	
	public:
		King(int n, int l, char col, Board* myBoard);
		void move(int n, int l);
		bool can_move();
      bool is_already_move;
};
#endif
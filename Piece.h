#ifndef PIECE_H
#define PIECE_H
#include "Board.h"
class Piece
{
	public:
		char piece;
		int number;
		int letter;
		Board* b;
		char color;
		virtual void move(int n, int l) =0;
		virtual bool try_move(int n,int l)=0;
		virtual bool can_move() =0;
		void remove_en_passant();
};
#endif
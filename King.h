//FRANCESCATO DANIELE 2000167

#ifndef KING_H
#define KING_H
#include <iostream>
#include "Piece.h"
using namespace std;
//classe che rappresenta il re
class King:public Piece
{
	public:
		King(int n, int l, char col, Board* myBoard);
		void move(int n, int l);
		bool can_move();
		bool try_move(int n,int l);
		bool is_already_move;    //true se si è già mosso,false altrimenti
		bool is_not_check;		//true se è impossibile che sia scacco, false altrimenti, utile per casi particolari
		void short_castling();  //arrocco corto
		void long_castling();	//arrocco lungo
};
#endif
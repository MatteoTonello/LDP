#ifndef PAWN_H
#define PAWN_H
#include <iostream>
#include "Piece.h"
using namespace std;
//classe che rappresenta il pedone
class Pawn : public Piece
{
    public:
	    bool en_passant;   //true se è possibile catturarlo con la mossa speciale en passant, false negli altri casi
        Pawn(int l, int n, char col, Board* myBoard);
        void move(int n, int l);
        bool try_move(int n, int l);
        bool can_move();
};
#endif
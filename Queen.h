//FRANCESCATO DANIELE 2000167

#ifndef QUEEN_H
#define QUEEN_H
#include <iostream>
#include "Piece.h"
//classe che rappresenta la regina
class Queen:public Piece
{
    public:
        Queen(int n, int l, char col, Board* myBoard );
        void move(int n, int l);
        bool try_move(int n, int l);
        bool can_move();
};
#endif
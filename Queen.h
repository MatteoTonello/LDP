#ifndef QUEEN_H
#define QUEEN_H
#include <iostream>
#include "Piece.h"
class Queen:public Piece
{
    Queen(int n, int l, char col, Board& myBoard );
    void move(int n, int l);
    bool can_move();
};
#endif
#ifndef KNIGHT_H
#define KNIGHT_H
#include <iostream>
#include "Piece.h"
using namespace std;
class Knight:public Piece
{
    Knight(int l, int n, char col, Board& myBoard);
    void move(int n, int l);
    bool can_move();
};
#endif
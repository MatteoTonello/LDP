#ifndef KNIGHT_H
#define KNIGHT_H
#include <iostream>
#include "Piece.h"
using namespace std;
class Knight:public Piece
{
    public:
    Knight(int l, int n, char col, Board* myBoard);
    void move(int n, int l);
    bool try_move(int n, int l);
    bool can_move();
    void random_move();
};
#endif
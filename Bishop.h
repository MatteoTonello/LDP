#ifndef BISHOP_H
#define BISHOP_H
#include <iostream>
#include "Piece.h"
using namespace std;
class Bishop:public Piece
{
    public:
    Bishop(int l, int n, char col, Board* myBoard);
    void move(int n, int l);
    bool try_move(int n, int l);
    bool can_move();
    void random_move();
};
#endif
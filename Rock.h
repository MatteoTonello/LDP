#ifndef ROCK_H
#define ROCK_H
#include <iostream>
#include "Piece.h"
class Rock:public Piece
{
    Rock(int n, int l, char col, Board& myBoard );
    void move(int n, int l);
    bool can_move();
};
#endif
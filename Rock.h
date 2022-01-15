#ifndef ROCK_H
#define ROCK_H
#include <iostream>
#include "Piece.h"
class Rock:public Piece
{
    public:
    Rock(int n, int l, char col, Board* myBoard );
    void move(int n, int l);
    bool try_move(int n, int l);
    bool can_move();
	bool is_already_move;
};
#endif
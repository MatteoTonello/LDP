#ifndef PAWN_H
#define PAWN_H
#include <iostream>
#include "Piece.h"
using namespace std;
class Pawn : public Piece
{
    public:
	bool en_passant;
    Pawn(int l, int n, char col, Board* myBoard);
    void move(int n, int l);
    bool try_move(int n, int l);
    bool can_move();
    void promotion();
    void random_move();
};
#endif
#ifndef PAWN_H
#define PAWN_H
#include <iostream>
#include "Piece.h"
using namespace std;
class Pawn : public Piece
{
    public:
    Pawn(int l, int n, char col, Board& myBoard);
    void move(int n, int l);
    bool can_move();

};
#endif
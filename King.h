#ifndef KING_H
#define KING_H
class King::public Piece
{
    King(int n, int l, char col, Board& myBoard);
    void move(int n, int l);
    bool can_move();
};
#endif
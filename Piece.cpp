#ifndef PIECE_CPP
#define PIECE_CPP
#include "Piece.h"
#include <fstream>
using namespace std;

void Piece::remove_en_passant()
{
    for(int i=0;i<b->whites.size();i++)
    {
        if(b->whites[i]->piece=='p')
            ((Pawn*)b->whites[i])->en_passant=false;
    }
    for(int i=0;i<b->blacks.size();i++)
    {
        if(b->blacks[i]->piece=='P')
                ((Pawn*) b->blacks[i])->en_passant=false;
    }

}

#endif
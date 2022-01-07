#ifndef PIECE_CPP
#define PIECE_CPP
#include "Piece.h"
using namespace std;

void Piece::remove_en_passant()
{
    for(int i=0;i<b->whites.size();i++)
    {
        if(whites[i]->piece=='p')
            whites[i]->en_passant=false;
    }
    for(int i=0;i<b->blacks.size();i++)
    {
        if(blacks[i]->piece=='P')
                    blacks[i]->en_passant=false;
    }

}
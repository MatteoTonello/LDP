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
bool Piece::diventa_scacco(int number_elim, int letter_elim, int number_mov,int letter_mov)
   {
         int save_number = number, save_letter=letter;
         Piece* tmp=b->gameboard[number_elim][letter_elim];
         b->gameboard[number_elim][letter_elim]=nullptr;
         b->gameboard[number][letter]=nullptr;
         letter=letter_mov;number=number_mov;
         b->gameboard[number_mov][letter_mov]=this;
         if(color=='w')
            for(int i=0;i<b->blacks.size();i++)
               if(b->blacks[i]==tmp){ b->blacks.erase(b->blacks.begin()+i); break;}
         if(color=='b')
            for(int i=0;i<b->whites.size();i++)
               if(b->whites[i]==tmp){ b->whites.erase(b->whites.begin()+i); break;}
         if(color=='b') b->white_king->is_not_check=true;
         else b->black_king->is_not_check=true;
         if(b->is_check(color))
         {
            b->gameboard[number_elim][letter_elim]=tmp;
            b->gameboard[save_number][save_letter]=this;
            if(number_elim!=number_mov || letter_elim!=letter_mov)
               b->gameboard[number_mov][letter_mov]=nullptr;
            number=save_number; letter=save_letter;
            if(tmp!=nullptr)
            {
               if(color=='w') b->blacks.push_back(tmp);
                        else b->whites.push_back(tmp);
            }
            if(color=='b') b->white_king->is_not_check=false;
            else b->black_king->is_not_check=false;
            return true;
		   }
      
      b->gameboard[number_elim][letter_elim]=tmp;
		b->gameboard[save_number][save_letter]=this;
      if(number_elim!=number_mov || letter_elim!=letter_mov)
               b->gameboard[number_mov][letter_mov]=nullptr;
		number=save_number, letter=save_letter;
      if(tmp!=nullptr)
		{
		   if(color=='w') b->blacks.push_back(tmp);
				else b->whites.push_back(tmp);
		}
      if(color=='b') b->white_king->is_not_check=false;
         else b->black_king->is_not_check=false;
      return false;
   }
#endif
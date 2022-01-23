//FRANCESCATO DANIELE 2000167

#ifndef PIECE_CPP
#define PIECE_CPP
#include "Piece.h"
#include "Pawn.h"
#include "King.h"
#include <fstream>
using namespace std;

char Piece::col()
{return color;}
char Piece::cpiece()
{return piece;}
int Piece::num()
{return number;}
int Piece::let()
{return letter;}
void Piece::remove_en_passant()
{
    for(int i=0;i<b->whites.size();i++)   //Controllo tutti i pezzi bianchi
    {
        if(b->whites[i]->cpiece()=='p')   //Se è un pedone, setto "en_passant" a falso
            ((Pawn*)b->whites[i])->en_passant=false;
    }
    for(int i=0;i<b->blacks.size();i++)   //Controllo tutti i pezzi neri
    {
        if(b->blacks[i]->cpiece()=='P')   //Se è un pedone, setto "en_passant" a falso
                ((Pawn*) b->blacks[i])->en_passant=false;
    }

}
bool Piece::diventa_scacco(int number_elim, int letter_elim, int number_mov,int letter_mov)
   {
         int save_number = number, save_letter=letter;
         Piece* tmp=b->gameboard[number_elim][letter_elim];  //salvo il puntatore alla casella col pezzo da eliminare (potrebbe essere anche nullptr)
         b->gameboard[number_elim][letter_elim]=nullptr;    //pongo il puntatore della casella che potrebbe contenere il pezzo eliminato uguale a nullptr
         b->gameboard[number][letter]=nullptr;        //pongo a nullptr il pezzo che si muove
         letter=letter_mov;number=number_mov;      
         b->gameboard[number_mov][letter_mov]=this;      //sposto il pezzo che si muove nella casella in cui deve muoversi
         //elimino il pezzo eventualmente mangiato
         if(color=='w')
            for(int i=0;i<b->blacks.size();i++)
               if(b->blacks[i]==tmp){ b->blacks.erase(b->blacks.begin()+i); break;}
         if(color=='b')
            for(int i=0;i<b->whites.size();i++)
               if(b->whites[i]==tmp){ b->whites.erase(b->whites.begin()+i); break;}
         //modifico la variabile is_not_check in modo tale da impedire scacchi all'altro re
         if(color=='b') b->white_king->is_not_check=true;
         else b->black_king->is_not_check=true;
         if(b->is_check(color))
         {
            //ritorno alla posizione iniziale
            b->gameboard[number_elim][letter_elim]=tmp;
            b->gameboard[save_number][save_letter]=this;
            if(number_elim!=number_mov || letter_elim!=letter_mov)
               b->gameboard[number_mov][letter_mov]=nullptr;
            number=save_number; letter=save_letter;
            //reinserisco il pezzo mangiato
            if(tmp!=nullptr)
            {
               if(color=='w') b->blacks.push_back(tmp);
                        else b->whites.push_back(tmp);
            }
            if(color=='b') b->white_king->is_not_check=false;
            else b->black_king->is_not_check=false;
            return true;
		   }
      //ritorno alla posione iniziale
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
#ifndef BISHOP_CPP
#define BISHOP_CPP
#include "Illegal_move.cpp"
#include "Bishop.h"
#include "Board.cpp"
#include <cstdlib>
using namespace std;
   Bishop::Bishop(int n, int l, char col, Board* myBoard)
   {
      number=n;
      letter=l;
      color=col;
      b=myBoard;
      if(color=='w') piece='a';  //Assegno la lettera da visualizzare a schermo in base al colore
      else piece='A';
   };

   bool Bishop::can_move()
   {
      //Controllo se si può muovere nelle 4 caselle diagonali
      for(int i=-1; i<=1; i=i+2)
      {
         for(int j=-1;j<=1;j=j+2)
         {
            if(number+i>=0 && number+i<8 && letter+j>=0 && letter+j<8)
            {
               if(b->gameboard[number+i][letter+j]==nullptr || b->gameboard[number+i][letter+j]->color!=color) //Se la casella è vuota o contiene una pedina avversaria
                  if(!diventa_scacco(number+i,letter+j,number+i,letter+j)) return true; //Se il movimento non porta uno scacco allora true
            }
         }
      }
      return false; //Non ha nessuna possibilità di movimento
   }

   void Bishop::move(int n, int l){
      if(try_move(n, l))
      {
         Piece* temp=b->gameboard[n][l];  //Salvo il contenuto della casella di arrivo
         //Sposto il pezzo nella casella di arrivo
         b->gameboard[number][letter]=nullptr;
         letter=l;number=n;
         b->gameboard[n][l]=this;

         //Se c'era un pezzo lo elimino dalla casella di arrivo
         if(color=='w')
            for(int i=0;i<b->blacks.size();i++)
               if(b->blacks[i]==temp){ 
                  b->blacks.erase(b->blacks.begin()+i);
                  break;
               }
         if(color=='b')
            for(int i=0;i<b->whites.size();i++)
               if(b->whites[i]==temp){
                  b->whites.erase(b->whites.begin()+i);
                  break;
               }
            remove_en_passant(); //Rimuovo la possibilità di fare l'en passant da tutti i pedoni, perché ho fatto una mossa
            return;
      }	
      throw new Illegal_move(); //Se la mossa non era possibile lancio l'eccezione
   }

   bool Bishop::try_move(int n, int l){
      if((abs(l-letter))!=(abs(n-number))) return false; //Se gli indici non sono uguali non è in diagonale

      if(n>number) // Controllo se la diagonale è verso il basso
      {
         if(l>letter)   // Controllo se la diagonale è verso destra
         {
            for(int i=number+1, j=letter+1; i<n; i++, j++) //Controllo progressivamente tutta la diagonale che attraversa nel movimento
            {
               if(b->gameboard[i][j]!=nullptr) return false; //Se c'è un pezzo nel mezzo è false
            }
         }
         else  // La diagonale è verso sinistra
         {
            for(int i=number+1, j=letter-1; i<n; i++, j--) //Controllo progressivamente tutta la diagonale che attraversa nel movimento
            {
               if(b->gameboard[i][j]!=nullptr) return false; //Se c'è un pezzo nel mezzo è false
            }
         }
      }
      else //La diagonale è verso l'alto
      {
         if(l>letter) // Controllo se la diagonale è verso destra
         {
            for(int i=number-1, j=letter+1; i>n; i--, j++) //Controllo progressivamente tutta la diagonale che attraversa nel movimento
            {
               if(b->gameboard[i][j]!=nullptr) return false; //Se c'è un pezzo nel mezzo è false
            }
         }
         else // La diagonale è verso sinistra
         {
            for(int i=number-1, j=letter-1; i>n; i--, j--) //Controllo progressivamente tutta la diagonale che attraversa nel movimento
            {
               if(b->gameboard[i][j]!=nullptr) return false; //Se c'è un pezzo nel mezzo è false
            }
         }
      }

      //Se il movimento è lecito, controllo che la casella di arrivo sia valida
      if(b->gameboard[n][l]!=nullptr) //Se è vuota procedo, altrimenti controllo
      {
         if(b->gameboard[n][l]->color==color)return false; //Se non è vuota e il pezzo non è avversario, false
      }
      return !diventa_scacco(n,l,n,l);
   }
   

#endif
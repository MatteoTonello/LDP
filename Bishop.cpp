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
      if(color=='w') piece='a';
      else piece='A';
   };

   bool Bishop::can_move()
   {
      for(int i=-1; i<=1; i=i+2)
      {
         for(int j=-1;j<=1;j=j+2)
         {
            if(number+i>=0 && number+i<8 && letter+j>=0 && letter+j<8)
            {
               if(b->gameboard[number+i][letter+j]==nullptr) return true;
               if(b->gameboard[number+i][letter+j]->color!=color) return true;
            }
         }
      }
      return false;
   }

   void Bishop::move(int n, int l)
   {
	if(try_move(n, l))
	{
		int save_number=number, save_letter=letter;
		Piece* temp=b->gameboard[n][l];
		b->gameboard[number][letter]=nullptr;
		letter=l;number=n;
		b->gameboard[n][l]=this;
      if(color=='w')
			for(int i=0;i<b->blacks.size();i++)
				if(b->blacks[i]==temp){ b->blacks.erase(b->blacks.begin()+i); break;}
		if(color=='b')
			for(int i=0;i<b->whites.size();i++)
				if(b->whites[i]==temp){ b->whites.erase(b->whites.begin()+i); break;}
            
         remove_en_passant();
			return;
	}	
	
   throw new Illegal_move();
}

   bool Bishop::try_move(int n, int l){
         if(!can_move()) return false;
         if((abs(l-letter))!=(abs(n-number))) return false;
               if(n>number)
            {
            if(l>letter)
            {
               for(int i=number+1, j=letter+1; i<n; i++, j++)
               {
                  if(b->gameboard[i][j]!=nullptr) return false;
               }
            }
            else
            {
               for(int i=number+1, j=letter-1; i<n; i++, j--)
               {
                  if(b->gameboard[i][j]!=nullptr) return false;
               }
            }
         }
         else
         {
            if(l>letter)
            {
               for(int i=number-1, j=letter+1; i>n; i--, j++)
               {
                  if(b->gameboard[i][j]!=nullptr) return false;
               }
            }
            else
            {
               for(int i=number-1, j=letter-1; i>n; i--, j--)
               {
                  if(b->gameboard[i][j]!=nullptr) return false;
               }
            }
         }
         if(b->gameboard[n][l]!=nullptr)
         {
            if(b->gameboard[n][l]->color==color)return false;
         }
         return !diventa_scacco(n,l,n,l);
   }
   

#endif
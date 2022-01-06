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
      b->gameboard[number][letter]=nullptr;
      if(b->is_check(color)) return false;
      b->gameboard[number][letter]=this;
      for(int i=-1; i<=1; i+2)
      {
         for(int j=-1;j<=1;j+2)
         {
            if(b->gameboard[number+i][letter+j]==nullptr) return true;
            if(b->gameboard[number+i][letter+j]->color!=color) return true;
         }
      }
      return false;
   }

   void Bishop::move(int n, int l)
   {
      if(try_move(n,l)){
         b->gameboard[number][letter]=nullptr;
         letter=l; number=n;
         b->gameboard[n][l]=this;
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
               for(int i=number, j=letter; i<=n; i++, j++)
               {
                  if(b->gameboard[i][j]!=nullptr) return false;  //secondo me (DAN) qui bisogna partire
               }                                                           //da posizioni +1
            }
            else
            {
               for(int i=number, j=letter; i<=n; i++, j--)
               {
                  if(b->gameboard[i][j]!=nullptr) return false;
               }
            }
         }
         else
         {
            if(l>letter)
            {
               for(int i=number, j=letter; i<=n; i--, j++)
               {
                  if(b->gameboard[i][j]!=nullptr) return false;
               }
            }
            else
            {
               for(int i=number, j=letter; i<=n; i--, j--)
               {
                  if(b->gameboard[i][j]!=nullptr) return false;
               }
            }
         }
         if(b->gameboard[n][l]!=nullptr)
         {
            if(b->gameboard[n][l]->color==color)return false;
         }
         return true;
   }

#endif
#ifndef BISHOP_CPP
#define BISHOP_CPP
#include "Illegal_move.cpp"
#include "Bishop.h"
#include <cstdlib>
using namespace std;
   Bishop::Bishop(int l, int n, char col, Board& myBoard)
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
      b.gameboard[letter][number]=nullptr;
      if(b.is_check()) return false;
      b.gameboard[letter][number]=this;
      for(int i=-1; i<=1; i+2)
      {
         for(int j=-1;j<=1;j+2)
         {
            if(b.gameboard[letter+i][number+j]==nullptr) return true;
            if(b.gameboard[letter+i][number+j]->color!=color) return true;
         }
      }
      return false;
   }

   void Bishop::move(int l, int n)
   {
      if(b.is_check()) throw new Illegal_move();
      if((abs(l-letter))!=(abs(n-number))) throw new Illegal_move();
      
      if(n>number)
      {
         if(l>letter)
         {
            for(int i=number, j=letter; i<=n; i++, j++)
            {
               if(b.gameboard[i][j]!=nullptr) throw new Illegal_move();
            }
         }
         else
         {
            for(int i=number, j=letter; i<=n; i++, j--)
            {
               if(b.gameboard[i][j]!=nullptr) throw new Illegal_move();
            }
         }
      }
      else
      {
         if(l>letter)
         {
            for(int i=number, j=letter; i<=n; i--, j++)
            {
               if(b.gameboard[i][j]!=nullptr) throw new Illegal_move();
            }
         }
         else
         {
            for(int i=number, j=letter; i<=n; i--, j--)
            {
               if(b.gameboard[i][j]!=nullptr) throw new Illegal_move();
            }
         }
      }
      if(b.gameboard[l][n]!=nullptr)
      {
         if(b.gameboard[l][n]->color==color)throw new Illegal_move();
      }
      b.gameboard[letter][number]=nullptr;
      letter=l; number=n;
      b.gameboard[l][n]=this;
      }

}
#endif
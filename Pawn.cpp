#ifndef PAWN_CPP
#define PAWN_CPP
#include "Illegal_move.cpp"
#include "Pawn.h"
#include "Board.cpp"
using namespace std;
Pawn::Pawn(int n, int l, char col, Board* myBoard)
{
	number=n;
	letter=l;
	color=col;
	b=myBoard;
	if(color=='w') piece='p';
	else piece='P';
};
bool Pawn::can_move()
		{
			b->gameboard[letter][number]=nullptr;
			if(b->is_check(color))return false;
			b->gameboard[letter][number+1]=this;
			if(color=='b')
			{
				if(b->gameboard[letter][number+1]==nullptr) return true;
				if(b->gameboard[letter+1][number+1]==nullptr||(b->gameboard[letter-1][number+1]==nullptr)) return false;
				if(b->gameboard[letter+1][number+1]->color=='b'||b->gameboard[letter-1][number+1]->color=='b') return true;
				return false;
			}
			if(color=='w')
			{
				if(b->gameboard[letter][number-1]==nullptr) return true;
				if(b->gameboard[letter+1][number-1]==nullptr|| b->gameboard[letter-1][number-1]==nullptr) return false;
				if(b->gameboard[letter+1][number-1]->color=='w'|| b->gameboard[letter-1][number-1]->color=='w') return true;
				return false;
			}
			return false;
		};
void Pawn::move(int n, int l)
		{
			/*if(!can_move()) throw new Illegal_move();
			if(color=='b')
			{
				if(n-number>2 || l-letter<-1 || l-letter>1) throw new Illegal_move();
				if(n-number==2 && number!=2) throw new Illegal_move();
				if((l-letter==1 || l-letter==-1)&& n-number==1)
				{
					if(b->gameboard[l][n]->color=='w')
					{
						b->gameboard[letter][number]=nullptr;
						number=n;
						letter=l;
						b->gameboard[l][n]=this;
						return;
					}
					else
					{
						throw new Illegal_move();
					}
				}
				if((l-letter==1||l-letter==-1)&& n-number==2) throw new Illegal_move();
				if(b->gameboard[l][n]==nullptr) throw new Illegal_move();
				if(b->gameboard[l][n]->color=='b') throw new Illegal_move();
				b->gameboard[letter][number]=nullptr;
				letter=l;number=n;
				b->gameboard[l][n]=this;
			}
			if(color=='w')
			{
				//controllo casella non raggiugibili
				if(n-number<-2 || l-letter<-1 || l-letter>1) throw new Illegal_move();
				if(n-number==-2 && number!=7) throw new Illegal_move();
				//controllo movimento diagonale
				if((l-letter==1 || l-letter==-1)&& n-number==-1)
				{
					if(b->gameboard[l][n]->color=='b')
					{
						b->gameboard[letter][number]=nullptr;
						number=n;
						letter=l;
						b->gameboard[l][n]=this;
						return;
					}
					else
					{
						throw new Illegal_move();
					}
				}
				//controllo movimento in avanti di 2 e diagonale
				if((l-letter==1||l-letter==-1)&& n-number==-2) throw new Illegal_move();
				//
				if(b->gameboard[l][n]==nullptr) throw new Illegal_move();
				//controllo stesso colore
				if(b->gameboard[l][n]->color=='w') throw new Illegal_move();
				b->gameboard[letter][number]=nullptr;
				letter=l;number=n;
				b->gameboard[l][n]=this;
				
			}*/
			b->gameboard[letter][number]=nullptr;
			
			b->gameboard[n][l]=this;
		
		};
#endif

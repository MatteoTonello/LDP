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
			b->gameboard[number][letter]=nullptr;
			if(b->is_check(color))return false;
			b->gameboard[number][letter]=this;
			if(color=='b')
			{
				if(number+1<=7){
					if(b->gameboard[number+1][letter]==nullptr) return true;
					if(letter+1<=7){
						if(b->gameboard[number+1][letter+1]==nullptr) return false;
						if(b->gameboard[number+1][letter+1]->color=='b') return true;
					}
					else if(letter-1>=0)){
						if(b->gameboard[number+1][letter-1]==nullptr) return false;
						if(b->gameboard[number+1][letter-1]->color=='b') return true;
					}
					return false;
				}
			}
			if(color=='w')
			{
				if(number-1>=0){
					if(b->gameboard[number-1][letter]==nullptr) return true;
					if(letter+1<=7){
						if(b->gameboard[number-1][letter+1]==nullptr) return false;
						if(b->gameboard[number-1][letter+1]->color=='w') return true;
					}
					else if(letter-1>=0){
						if(b->gameboard[number-1][letter-1]==nullptr) return false;
						if(b->gameboard[number-1][letter-1]->color=='w') return true;
					}
				}				
				return false;
			}
			return false;
		};
void Pawn::move(int n, int l)
		{
			if(!can_move()) throw new Illegal_move();
			if(color=='b')
			{
				if(n-number>2 || l-letter<-1 || l-letter>1) throw new Illegal_move();
				if(n-number==2 && number!=1) throw new Illegal_move();
				if((l-letter==1 || l-letter==-1)&& n-number==1)
				{
					if(b->gameboard[n][l]->color=='w')
					{
						b->gameboard[number][letter]=nullptr;
						number=n;
						letter=l;
						b->gameboard[n][l]=this;
						return;
					}
					else
					{
						throw new Illegal_move();
					}
				}
				if((l-letter==1||l-letter==-1)&& n-number==2) throw new Illegal_move();
				if(b->gameboard[n][l]!=nullptr)
					if(b->gameboard[n][l]->color=='b') throw new Illegal_move();
				b->gameboard[number][letter]=nullptr;
				letter=l;number=n;
				b->gameboard[n][l]=this;
			}
			if(color=='w')
			{
				//controllo casella non raggiugibili
				if(n-number<-2 || l-letter<-1 || l-letter>1) throw new Illegal_move();
			
				if(n-number==-2 && number!=6) throw new Illegal_move();
				//controllo movimento diagonale
				if((l-letter==1 || l-letter==-1)&& n-number==-1)
				{
					if(b->gameboard[n][l]->color=='b')
					{
						b->gameboard[number][letter]=nullptr;
						number=n;
						letter=l;
						b->gameboard[n][l]=this;
						return;
					}
					else
					{
						throw new Illegal_move();
					}
				}
				//controllo movimento in avanti di 2 e diagonale
				if((l-letter==1||l-letter==-1)&& n-number==-2) throw new Illegal_move();
				
				
				//controllo stesso colore
				if(b->gameboard[n][l]!=nullptr)
					if(b->gameboard[n][l]->color=='w') throw new Illegal_move();
				b->gameboard[number][letter]=nullptr;
				letter=l;number=n;
				b->gameboard[n][l]=this;
				
			}
		
		};
#endif

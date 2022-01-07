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
	en_passant=false;
	if(color=='w') piece='p';
	else piece='P';
};
bool Pawn::can_move()
 {
	if(color=='b')
	{
		if(number+1<=7){
			if(b->gameboard[number+1][letter]==nullptr) return true;
			if(letter+1<=7){
				if(b->gameboard[number+1][letter+1]==nullptr) return false;
				if(b->gameboard[number+1][letter+1]->color=='b') return true;
			}
			else if(letter-1>=0){
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
}
bool Pawn:: try_move(int n, int l)
{
	if(!can_move()) return false;
	if(color=='b')
	{
		if(n-number==1 && l-letter==1 && b->gameboard[number][letter+1]->en_passant==true) return true;
		if(n-number==1 && l-letter==-1 && b->gameboard[number][letter-1]->en_passant==true) return true;
		if(n-number>2 || l-letter<-1 || l-letter>1) return false;
		if(n-number==2 && number!=1) return false;
		if((l-letter==1 || l-letter==-1)&& n-number==1)
		{
			if(b->gameboard[n][l]->color=='w')
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		if((l-letter==1||l-letter==-1)&& n-number==2) return false;
		if(b->gameboard[n][l]!=nullptr)
			if(b->gameboard[n][l]->color=='b') return false;
		return true;
	}
	if(color=='w')
	{
		//controllo casella non raggiugibili
		if(n-number<-2 || l-letter<-1 || l-letter>1) return false;
		if(n-number==-2 && number!=6) return false;
		//controllo movimento diagonale
		
		if((l-letter==1 || l-letter==-1)&& n-number==-1)
		{
			if(b->gameboard[n][l]->color=='b')
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		//controllo movimento in avanti di 2 e diagonale
		if((l-letter==1||l-letter==-1)&& n-number==-2) return false;
		
		
		//controllo stesso colore
		if(b->gameboard[n][l]!=nullptr)
			if(b->gameboard[n][l]->color=='w') return false;
		return true;	
	}		
	return false;	
}
void Pawn::move(int n, int l)
{
	if(try_move(n, l))
	{
		Piece* temp;
		if(color='b')
		{
			if(n-number==1 && ((l-letter==1 && b->gameboard[number][letter+1]->en_passant==true
			) || (l-letter==-1 && b->gameboard[number][letter-1]->en_passant==true)))
			{
				int save_number=number, save_letter=letter;
				temp=b->gameboard[n-1][l];
				b->gameboard[number][letter]=nullptr;
				letter=l;number=n;
				b->gameboard[n][l]=this;
				b->gameboard[n-1][l]=nullptr;
				if(b->is_check(color))
				{
					b->gameboard[n-1][l]=temp;
					b->gameboard[save_number][save_letter]=this;
					b->gameboard[n][l]=nullptr;
					number=save_number; letter=save_letter;
					throw new Illegal_move();
				}
			}
		}
		if(color='w')
		{
			if(n-number==-1 && ((l-letter==1 && b->gameboard[number][letter+1]->en_passant==true
			) || (l-letter==-1 && b->gameboard[number][letter-1]->en_passant==true)))
			{
				int save_number=number, save_letter=letter;
				temp=b->gameboard[n+1][l];
				b->gameboard[number][letter]=nullptr;
				letter=l;number=n;
				b->gameboard[n][l]=this;
				b->gameboard[n+1][l]=nullptr;
				if(b->is_check(color))
				{
					b->gameboard[n+1][l]=temp;
					b->gameboard[save_number][save_letter]=this;
					b->gameboard[n][l]=nullptr;
					number=save_number; letter=save_letter;
					throw new Illegal_move();
				}
			}
			
		}
		
		int save_number=number, save_letter=letter;
		temp=b->gameboard[n][l];
		b->gameboard[number][letter]=nullptr;
		letter=l;number=n;
		b->gameboard[n][l]=this;
		if(b->is_check(color))
		{
			b->gameboard[n][l]=temp;
			b->gameboard[save_number][save_letter]=this;
			number=save_number; letter=save_letter;
			throw new Illegal_move();
		}
		else
		{
			if(temp!=nullptr)
			{
				if(color=='w')
				{
					for(int i=0;i<b->blacks.size();i++)
					{
						if(b->blacks[i]==temp){ b->blacks.erase(b->blacks.begin()+i); break;}
					}
				}
				if(color=='b')
				{
					for(int i=0;i<b->whites.size();i++)
					{
						if(b->whites[i]==temp){ b->whites.erase(b->whites.begin()+i); break;}
					}
				}
			}
		}	
		remove_en_passant();
		if(color=='w' && n-save_number==-2)
		{
			if(b->gameboard[number][letter+1]!=nullptr && b->gameboard[number][letter+1]->piece=='P')
				this->en_passant=true;
			if(b->gameboard[number][letter-1]!=nullptr && b->gameboard[number][letter-1]->piece=='P')
				this->en_passant=true;
		}
		if(color=='b' && n-save_number==+2)
		{
			if(b->gameboard[number][letter+1]!=nullptr && b->gameboard[number][letter+1]->piece=='p')
				this->en_passant=true;
			if(b->gameboard[number][letter-1]!=nullptr && b->gameboard[number][letter-1]->piece=='p')
				this->en_passant=true;
		}
	}
}
#endif

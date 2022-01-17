#ifndef PAWN_CPP
#define PAWN_CPP
#include "Illegal_move.cpp"
#include "Pawn.h"
#include "Piece.cpp"
#include "Board.cpp"
#include <iostream>
#include "Promotion.cpp"
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
	int i=0;
	if(color=='w') i=-1;     
	else i=+1;
	if(b->gameboard[number+i][letter]==nullptr) return true;
	if(letter+1<=7 && b->gameboard[number+i][letter+1]!=nullptr)
		if(b->gameboard[number+i][letter+1]->color!=color) return true;
	if(letter-1>=0 && b->gameboard[number+i][letter-1]!=nullptr)
		if(b->gameboard[number+i][letter-1]->color!=color) return true;
	if(color=='w')
	{
		if(letter-1>=0 && b->gameboard[number][letter-1]!=nullptr)
	 		if(b->gameboard[number][letter-1]->piece=='P' && ((Pawn*)b->gameboard[number][letter-1])->en_passant==true) return true;
		if(letter-1<=7 && b->gameboard[number][letter+1]!=nullptr)
	 		if(b->gameboard[number][letter+1]->piece=='P' && ((Pawn*)b->gameboard[number][letter+1])->en_passant==true) return true;
	}
	if(color=='b')
	{
		if(letter-1>=0 && b->gameboard[number][letter-1]!=nullptr)
	 		if(b->gameboard[number][letter-1]->piece=='p' && ((Pawn*)b->gameboard[number][letter-1])->en_passant==true) return true;
		if(letter-1<=7 && b->gameboard[number][letter+1]!=nullptr)
	 		if(b->gameboard[number][letter+1]->piece=='p' && ((Pawn*)b->gameboard[number][letter+1])->en_passant==true) return true;
	}
	return false;
}
bool Pawn:: try_move(int n, int l)
{
	if(!can_move()) return false;
	if(color=='b')
	{
		//controllo en passant
		if(b->gameboard[number][letter+1]!=nullptr)
			if(n-number==1 && l-letter==1 && b->gameboard[number][letter+1]->piece=='p' && ((Pawn*)b->gameboard[number][letter+1])->en_passant==true) return !diventa_scacco(number,letter+1,n,l);
		if(b->gameboard[number][letter-1]!=nullptr)
			if(n-number==1 && l-letter==-1 && b->gameboard[number][letter-1]->piece=='p' && ((Pawn*)b->gameboard[number][letter-1])->en_passant==true) return !diventa_scacco(number,letter-1,n,l);
		//controllo caselle in avanti
		if(n-number==1 && l==letter && b->gameboard[n][l]==nullptr) return !diventa_scacco(n,l,n,l);
		if(n-number==2 && number==1 && l==letter && b->gameboard[n][l]==nullptr && b->gameboard[n-1][l]==nullptr) return !diventa_scacco(n,l,n,l);
		//controllo mangiare diagonale
		if(n-number==1 && l-letter==1 && b->gameboard[n][l]!=nullptr && b->gameboard[n][l]->color!=color) return !diventa_scacco(n,l,n,l);
		if(n-number==1 && l-letter==-1 && b->gameboard[n][l]!=nullptr && b->gameboard[n][l]->color!=color) return !diventa_scacco(n,l,n,l);
		
	}
	if(color=='w')
	{
		//controllo en passant
		if(b->gameboard[number][letter+1]!=nullptr)
			if(n-number==-1 && l-letter==1 && b->gameboard[number][letter+1]->piece=='P' && ((Pawn*)b->gameboard[number][letter+1])->en_passant==true) return !diventa_scacco(number,letter+1,n,l);
		if(b->gameboard[number][letter-1]!=nullptr)
			if(n-number==-1 && l-letter==-1 && b->gameboard[number][letter-1]->piece=='P' && ((Pawn*)b->gameboard[number][letter-1])->en_passant==true) return !diventa_scacco(number,letter-1,n,l);
		//controllo caselle in avanti
		if(n-number==-1 && l==letter && b->gameboard[n][l]==nullptr) return !diventa_scacco(n,l,n,l);
		if(n-number==-2 && number==6 && l==letter && b->gameboard[n][l]==nullptr && b->gameboard[n+1][l]==nullptr) return !diventa_scacco(n,l,n,l);
		//controllo mangiare diagonale
		if(n-number==-1 && l-letter==1 && b->gameboard[n][l]!=nullptr && b->gameboard[n][l]->color!=color) return !diventa_scacco(n,l,n,l);
		if(n-number==-1 && l-letter==-1 && b->gameboard[n][l]!=nullptr && b->gameboard[n][l]->color!=color) return !diventa_scacco(n,l,n,l);
	}
	return false;
		
}
void Pawn::move(int n, int l)
{
	if(try_move(n, l))
	{
		Piece* temp;
		if(color=='b')
		{
			if(n-number==1 && ((l-letter==1 && b->gameboard[number][letter+1]!=nullptr && ((Pawn*)b->gameboard[number][letter+1])->en_passant==true
			) || (l-letter==-1 && b->gameboard[number][letter-1]!=nullptr && ((Pawn*)b->gameboard[number][letter-1])->en_passant==true)))
			{
				int save_number=number, save_letter=letter;
				temp=b->gameboard[n-1][l];
				b->gameboard[number][letter]=nullptr;
				letter=l;number=n;
				b->gameboard[n][l]=this;
				b->gameboard[n-1][l]=nullptr;
				
				for(int i=0;i<b->whites.size();i++)
					if(b->whites[i]==temp){ b->whites.erase(b->whites.begin()+i); break;}
				if(b->is_check(color))
				{
					b->gameboard[n-1][l]=temp;
					b->gameboard[save_number][save_letter]=this;
					b->gameboard[n][l]=nullptr;
					b->whites.push_back(temp);
					number=save_number; letter=save_letter;
					throw new Illegal_move();
				}
				return;
			}
		}
		if(color=='w')
		{
			if(n-number==-1 && ((l-letter==1 && b->gameboard[number][letter+1]!=nullptr && ((Pawn*)b->gameboard[number][letter+1])->en_passant==true
			) || (l-letter==-1 && b->gameboard[number][letter-1]!=nullptr && ((Pawn*)b->gameboard[number][letter-1])->en_passant==true)))
			{
				int save_number=number, save_letter=letter;
				temp=b->gameboard[n+1][l];
				b->gameboard[number][letter]=nullptr;
				letter=l;number=n;
				b->gameboard[n][l]=this;
				b->gameboard[n+1][l]=nullptr;
				
				for(int i=0;i<b->blacks.size();i++)
					if(b->blacks[i]==temp){ b->blacks.erase(b->blacks.begin()+i); break;}
				
				if(b->is_check(color))
				{
					b->gameboard[n+1][l]=temp;
					b->gameboard[save_number][save_letter]=this;
					b->gameboard[n][l]=nullptr;
					b->blacks.push_back(temp);
					number=save_number; letter=save_letter;
					throw new Illegal_move();
				}
				return;
			}
			
			
		}
		int save_number=number, save_letter=letter;
		temp=b->gameboard[n][l];
		b->gameboard[number][letter]=nullptr;
		b->gameboard[n][l]=this;
		letter=l;number=n;
		
		if(color=='w')
			for(int i=0;i<b->blacks.size();i++)
				if(b->blacks[i]==temp){ b->blacks.erase(b->blacks.begin()+i); break;}
		if(color=='b')
			for(int i=0;i<b->whites.size();i++)
				if(b->whites[i]==temp){ b->whites.erase(b->whites.begin()+i); break;}
		if(b->is_check(color))
		{
			b->gameboard[n][l]=temp;
			b->gameboard[save_number][save_letter]=this;
			number=save_number; letter=save_letter;
			if(temp!=nullptr)
			{
				if(color=='w') b->blacks.push_back(temp);
							else b->whites.push_back(temp);
			}
			throw new Illegal_move();
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
		if(number==0 || number==7)
		{
			throw new Promotion();
		}
		return;
	}
	throw new Illegal_move();
}


#endif

#ifndef KNIGHT_CPP
#define KNIGHT_CPP
#include "Illegal_move.cpp"
#include "Knight.h"
#include <cstdlib>
using namespace std;
Knight::Knight(int n, int l, char col, Board* myBoard)
{
	number=n;
	letter=l;
	color=col;
	b=myBoard;
	if(color=='w') piece='c';
	else piece='C';
}

bool Knight::can_move()
	{
		if(b->gameboard[number+1][letter+2]==nullptr || b->gameboard[number+1][letter+2]->color!=color || number+1<0 || number+1>7 || letter+2<0 || letter+2>7) return true;
		if(b->gameboard[number+1][letter-2]==nullptr || b->gameboard[number+1][letter-2]->color!=color || number+1<0 || number+1>7 || letter-2<0 || letter-2>7) return true;
		if(b->gameboard[number-1][letter+2]==nullptr || b->gameboard[number-1][letter+2]->color!=color || number-1<0 || number-1>7 || letter+2<0 || letter+2>7) return true;
		if(b->gameboard[number-1][letter-2]==nullptr || b->gameboard[number-1][letter-2]->color!=color || number-1<0 || number-1>7 || letter-2<0 || letter-2>7) return true;
		if(b->gameboard[number+2][letter+1]==nullptr || b->gameboard[number+2][letter+1]->color!=color || number+2<0 || number+2>7 || letter+1<0 || letter+1>7) return true;
		if(b->gameboard[number+2][letter-1]==nullptr || b->gameboard[number+2][letter-1]->color!=color || number+2<0 || number+2>7 || letter-1<0 || letter-1>7) return true;
		if(b->gameboard[number-2][letter+1]==nullptr || b->gameboard[number-2][letter+1]->color!=color || number-2<0 || number-2>7 || letter+1<0 || letter+1>7) return true;
		if(b->gameboard[number-2][letter-1]==nullptr || b->gameboard[number-2][letter-1]->color!=color || number-2<0 || number-2>7 || letter-1<0 || letter-1>7) return true;
		
		return true;
	};
	
void Knight::move(int n, int l)
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
		if(b->is_check(color))
		{
			b->gameboard[n][l]=temp;
			b->gameboard[save_number][save_letter]=this;
			number=save_number; letter=save_letter;
			if(color=='w') b->blacks.push_back(temp);
							else b->whites.push_back(temp);
			throw new Illegal_move();
		}
		
			remove_en_passant();
			return;
		}	
	
	throw new Illegal_move();
}

bool Knight::try_move(int n, int l){
	
		//if(!can_move()) return false;
		if((abs(l-letter)==2 && abs(n-number)==1) || (abs(l-letter)==1 && abs(n-number)==2)){ //controllo se non è una delle 8 caselle possibili
			if(b->gameboard[n][l]==nullptr) return true;
			if(b->gameboard[n][l]->color==color) return false;	//controllo se è lo stesso colore
				return true;
		}
		else return false;
}

void Knight::random_move()
{
	int m=rand()%8;
	if(number+1>7 || letter+2>7) throw new Illegal_move();
	if(m==0) if(try_move(number+1,letter+2)) move(number+1,letter+2); else throw new Illegal_move();
	if(number+1>7 || letter-2<0) throw new Illegal_move();
	if(m==1) if(try_move(number+1,letter-2)) move(number+1,letter-2); else throw new Illegal_move();
	if(number-1<0 || letter+2>7) throw new Illegal_move();
	if(m==2) if(try_move(number-1,letter+2)) move(number-1,letter+2); else throw new Illegal_move();
	if(number-1<0 || letter-2<0) throw new Illegal_move();
	if(m==3) if(try_move(number-1,letter-2)) move(number-1,letter-2); else throw new Illegal_move();
	if(number+2>7 || letter+2>7) throw new Illegal_move();
	if(m==4) if(try_move(number+2,letter+2)) move(number+2,letter+2); else throw new Illegal_move();
	if(number+2>7 || letter-2<0) throw new Illegal_move();
	if(m==5) if(try_move(number+2,letter-2)) move(number+2,letter-2); else throw new Illegal_move();
	if(number-2<0 || letter+2>7) throw new Illegal_move();
	if(m==6) if(try_move(number-2,letter+2)) move(number-2,letter+2); else throw new Illegal_move();
	if(number-2<0 || letter-2<0) throw new Illegal_move();
	if(m==7) if(try_move(number-2,letter-2)) move(number-2,letter-2); else throw new Illegal_move();
}
#endif

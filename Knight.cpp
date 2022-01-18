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
		//controllo tutte le mosse del cavallo
		if((b->gameboard[number+1][letter+2]==nullptr || b->gameboard[number+1][letter+2]->color!=color) && (number+1<=7 && letter+2<=7))
			if(!diventa_scacco(number+1,letter+2,number+1,letter+2)) return true;
		if((b->gameboard[number+1][letter-2]==nullptr || b->gameboard[number+1][letter-2]->color!=color) && (number+1>=7 && letter-2>=0))
			if(!diventa_scacco(number+1,letter-2,number+1,letter-2)) return true;
		if((b->gameboard[number-1][letter+2]==nullptr || b->gameboard[number-1][letter+2]->color!=color) && (number-1>=0 && letter+2<=7))
			if(!diventa_scacco(number-1,letter+2,number-1,letter+2)) return true;
		if((b->gameboard[number-1][letter-2]==nullptr || b->gameboard[number-1][letter-2]->color!=color) && (number-1>=0 && letter-2>=0))
			if(!diventa_scacco(number-1,letter-2,number-1,letter-2)) return true;
		if((b->gameboard[number+2][letter+1]==nullptr || b->gameboard[number+2][letter+1]->color!=color) && (number+2<=7 && letter+1<=7))
			if(!diventa_scacco(number+2,letter+1,number+2,letter+1)) return true;
		if((b->gameboard[number+2][letter-1]==nullptr || b->gameboard[number+2][letter-1]->color!=color) && (number+2<=7 && letter-1>=0))
			if(!diventa_scacco(number+2,letter-1,number+2,letter-1)) return true;
		if((b->gameboard[number-2][letter+1]==nullptr || b->gameboard[number-2][letter+1]->color!=color) && (number-2>=0 && letter+1<=7))
			if(!diventa_scacco(number-2,letter+1,number-2,letter+1)) return true;
		if((b->gameboard[number-2][letter-1]==nullptr || b->gameboard[number-2][letter-1]->color!=color) && (number-2>=0 && letter-1>=0))
			if(!diventa_scacco(number-2,letter-1,number-2,letter-1)) return true;
		
		return false;  //nessuna mossa è possibile
	};
	
void Knight::move(int n, int l)
{
	if(try_move(n, l))
	{
		//salva il puntatore al pezzo eliminato/nullptr se casella vuota
		Piece* temp=b->gameboard[n][l];
		//completamento mossa
		b->gameboard[number][letter]=nullptr;
		letter=l;number=n;
		b->gameboard[n][l]=this;
		//rimuove eventuale pedina mangiata
		if(color=='w')
			for(int i=0;i<b->blacks.size();i++)
				if(b->blacks[i]==temp){ b->blacks.erase(b->blacks.begin()+i); break;}
		if(color=='b')
			for(int i=0;i<b->whites.size();i++)
				if(b->whites[i]==temp){ b->whites.erase(b->whites.begin()+i); break;}
		
		remove_en_passant();	//rimuovo eventuali en passant
		return;
	}	
	//se mossa non possibile, illegal move
	throw new Illegal_move();
}

bool Knight::try_move(int n, int l)
{
		
		if((abs(l-letter)==2 && abs(n-number)==1) || (abs(l-letter)==1 && abs(n-number)==2)){ //controllo se è una delle 8 caselle possibili
			if(b->gameboard[n][l]==nullptr) return !diventa_scacco(n,l,n,l);
			if(b->gameboard[n][l]->color==color) return false;	//controllo se è lo stesso colore
				return !diventa_scacco(n,l,n,l);
		}
		else return false;
}


#endif

#ifndef ROCK_CPP
#define ROCK_CPP
#include "Illegal_move.cpp"
#include "Rock.h"
using namespace std;

Rock::Rock(int n, int l, char col, Board* myBoard )
{
	number=n;
	letter=l;
	color=col;
	b=myBoard;
	if(color=='w') piece='t';
	else piece='T';
	is_already_move=false;
};

bool Rock:: can_move()
{
	//controllo se si può muovere nelle 4 caselle intorno a lui
	for(int i=-1; i<=1; i=i+2)
	{
		if(letter+i>=0 && letter+i<=7 ){
			if(b->gameboard[number][letter+i]==nullptr || b->gameboard[number][letter+i]->color!=color) return true;
		}
		if(number+i>=0 && number+i<=7){
			if(b->gameboard[number+i][letter]==nullptr || b->gameboard[number+i][letter]->color!=color) return true;
		}			
	}
	//se non si può muovere su quelle caselle è bloccato
	return false;
};

void Rock:: move(int n, int l)
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
		is_already_move=true; 	//si è appena mosso
		remove_en_passant();	//rimuovo eventuali en passant
		return;
	}	
	//se mossa non possibile, illegal move
	throw new Illegal_move();
}


bool Rock::try_move(int n, int l){
	
	if(!can_move()) return false;
	if(letter!=l && number!=n) return false;  //se la casella non è tra quelle della riga o colonna della torre
	int vertical=number, horizontal=letter ;
	//controllo movimento sulla colonna
	if(number!=n && letter==l)
	{
		
		if(n>number) 		//la posizione indicata è più in giù di quella attuale
		{
			vertical++;
			while(vertical<n && b->gameboard[vertical][letter]==nullptr)
			{
				vertical++;
			}
			if(vertical!=n) return false;  //se non ha raggiunto la posizione
		}
		else				//la posizione indicata è più in sù di quella attuale
		{
			vertical--;
			while(vertical>n && b->gameboard[vertical][letter]==nullptr)
			{
				vertical--;
			}
			if(vertical!=n) return false;  //se non ha raggiunto la posizione
		}
	}
	//controllo movimento sulla riga
	if(letter!=l && number==n)		
	{
		if(l>letter)       //la posizione indicata è più a destra di quella attuale
		{
			horizontal++;
			while(horizontal<l && b->gameboard[n][horizontal]==nullptr)
			{
				horizontal++;
			}
			if(horizontal!=l) return false;  //se non ha raggiunto la posizione
		}
		else				//la posizione indicata è più a sinistra di quella attuale
		{
			horizontal--;
			while(horizontal>l && b->gameboard[n][horizontal]==nullptr)
			{
				horizontal--;
			}
			if(horizontal!=l) return false;   //se non ha raggiunto la posizione
		}
	}
	
	if(b->gameboard[n][l]!=nullptr)
    {
        if(b->gameboard[n][l]->color==color)return false;	//controllo che la pedina nella casella non sia dello stesso colore
    }
	return !diventa_scacco(n, l,n,l);
}

	#endif
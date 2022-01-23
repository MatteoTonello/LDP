//FRANCESCATO DANIELE 2000167

#ifndef QUEEN_CPP
#define QUEEN_CPP
#include "Illegal_move.cpp"
#include "Queen.h"
#include "Board.cpp"

using namespace std;

Queen::Queen(int n, int l, char col, Board* myBoard )
{
	number=n;
	letter=l;
	color=col;
	b=myBoard;
	if(color=='w') piece='d';
	else piece='D';
}

bool Queen:: can_move()
{
	//Controllo le 8 caselle circostanti
	for(int i=-1; i<=1; i++)
	{
		if(number+i>=0 && number+i<=7){
			for(int j=-1;j<=1;j++)
			{
				if(letter+j>=0 && letter+j<=7){
					if(b->gameboard[number+i][letter+j]==nullptr || b->gameboard[number+i][letter+j]->col()!=color) //Se la casella è vuota o contiene una pedina avversaria
						if(!diventa_scacco(number+i,letter+j,number+i,letter+j)) return true; //Se il movimento non porta uno scacco allora true
				}
			}
		}
	}
	return false; //Non ha nessuna possibilità di movimento 
}
bool Queen::try_move(int n, int l)
{
	if((letter!=l && number!=n)&&(abs(number-n)!=abs(letter-l))) return false; //false se non sono su una traiettoria possibile
	int vertical=number, horizontal=letter;
	if(number!=n && letter==l) //Se mi muovo in verticale
	{
		if(n>number) //Se vado verso il basso
		{	//Controllo che tutte le caselle che devo attraversare siano vuote
			vertical++;
			while(vertical<n && b->gameboard[vertical][letter]==nullptr)
			{
				vertical++;
			}
			if(vertical!=n) return false;
			
		}
		else //Se vado verso l'alto
		{	//Controllo che tutte le caselle che devo attraversare siano vuote
			vertical--;
			while(vertical>n && b->gameboard[vertical][letter]==nullptr)
			{
				vertical--;
			}
			if(vertical!=n) return false;
		}
	}
	if(letter!=l && number==n) //Se mi muovo in orizzontale
	{
		if(l>letter)//Se vado verso destra
		{	//Controllo che tutte le caselle che devo attraversare siano vuote
			horizontal++;
			while(horizontal<l && b->gameboard[n][horizontal]==nullptr)
			{
				horizontal++;
			}
			if(horizontal!=l) return false;
		}
		else //Se vado verso sinistra
		{	//Controllo che tutte le caselle che devo attraversare siano vuote
			horizontal--;
			while(horizontal>l && b->gameboard[n][horizontal]==nullptr)
			{
				horizontal--;
			}
			if(horizontal!=l) return false;
		}
	}
	if(n>number) // Controllo se la diagonale è verso il basso
	{
		if(l>letter)   // Controllo se la diagonale è verso destra
		{
			for(int i=number+1, j=letter+1; i<n; i++, j++) //Controllo progressivamente tutta la diagonale che attraversa nel movimento
			{
				if(b->gameboard[i][j]!=nullptr) return false; //Se c'è un pezzo nel mezzo è false
			}
		}
		else  // La diagonale è verso sinistra
		{
			for(int i=number+1, j=letter-1; i<n; i++, j--) //Controllo progressivamente tutta la diagonale che attraversa nel movimento
			{
				if(b->gameboard[i][j]!=nullptr) return false; //Se c'è un pezzo nel mezzo è false
			}
		}
	}
   else //La diagonale è verso l'alto
	{
		if(l>letter) // Controllo se la diagonale è verso destra
		{
			for(int i=number-1, j=letter+1; i>n; i--, j++) //Controllo progressivamente tutta la diagonale che attraversa nel movimento
			{
				if(b->gameboard[i][j]!=nullptr) return false; //Se c'è un pezzo nel mezzo è false
			}
		}
		else // La diagonale è verso sinistra
		{
			for(int i=number-1, j=letter-1; i>n; i--, j--) //Controllo progressivamente tutta la diagonale che attraversa nel movimento
			{
				if(b->gameboard[i][j]!=nullptr) return false; //Se c'è un pezzo nel mezzo è false
			}
		}
	}
	//Se il movimento è lecito, controllo che la casella di arrivo sia valida
	if(b->gameboard[n][l]!=nullptr) //Se è non è vuota controllo
	{
		if(b->gameboard[n][l]->col()==color)return false; //Se il pezzo non è avversario, false
	}
	return !diventa_scacco(n,l,n,l);
}
void Queen:: move(int n, int l)
{
	if(try_move(n, l))
	{
		//Salvo il contenuto della casella di arrivo
		Piece* temp=b->gameboard[n][l];
		//Sposto il pezzo nella casella di arrivo
		b->gameboard[number][letter]=nullptr;
		letter=l;number=n;
		b->gameboard[n][l]=this;

		//Se c'era un pezzo lo elimino dalla casella di arrivo
		if(color=='w')
			for(int i=0;i<b->blacks.size();i++)
				if(b->blacks[i]==temp){
					b->blacks.erase(b->blacks.begin()+i);
					break;
				}
		if(color=='b')
			for(int i=0;i<b->whites.size();i++)
				if(b->whites[i]==temp){
					b->whites.erase(b->whites.begin()+i);
					break;
				}
			remove_en_passant(); //Rimuovo la possibilità di fare l'en passant da tutti i pedoni, perché ho fatto una mossa
			return;
		}	
	
	throw new Illegal_move();
}
#endif

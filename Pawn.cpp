#ifndef PAWN_CPP
#define PAWN_CPP
#include "Illegal_move.cpp"
#include "Pawn.h"
#include "Piece.cpp"
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
	int i=0;
	if(color=='w') i=-1;
	else i=+1;
	if(b->gameboard[number+i][letter]==nullptr) return true;
	if(letter-1<=7 && b->gameboard[number+i][letter+1]!=nullptr)
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
		/*if(b->gameboard[number][letter+1]!=nullptr)
			if(n-number==1 && l-letter==1 && b->gameboard[number][letter+1]->piece=='p' && ((Pawn*)b->gameboard[number][letter+1])->en_passant==true) return true;
		if(b->gameboard[number][letter-1]!=nullptr)
			if(n-number==1 && l-letter==-1 && b->gameboard[number][letter-1]->piece=='p' && ((Pawn*)b->gameboard[number][letter-1])->en_passant==true) return true;
		if(number+1<=7){
			if(b->gameboard[number+1][letter]==nullptr) return true;
			if(letter+1<=7){
				if(b->gameboard[number+1][letter+1]==nullptr) return false;
				if(b->gameboard[number+1][letter+1]->color=='w') return true;
			}
			else if(letter-1>=0){
				if(b->gameboard[number+1][letter-1]==nullptr) return false;
				if(b->gameboard[number+1][letter-1]->color=='w') return true;
			}
			return false;
		}
	}
	if(color=='w')
	{
		/*if(b->gameboard[number][letter+1]!=nullptr)
			if(b->gameboard[number+1][letter+1]==nullptr) && b->gameboard[number][letter+1]->piece=='P' && ((Pawn*)b->gameboard[number][letter+1])->en_passant==true) return true;
		if(b->gameboard[number][letter-1]!=nullptr)
			if(n-number==-1 && l-letter==-1 && b->gameboard[number][letter-1]->piece=='P' && ((Pawn*)b->gameboard[number][letter-1])->en_passant==true) return true;
		if(number-1>=0){
			if(b->gameboard[number-1][letter]==nullptr) return true;
			if(letter+1<=7){
				if(b->gameboard[number-1][letter+1]==nullptr) return false; 
				if(b->gameboard[number-1][letter+1]->color=='b') return true;
			}
			else if(letter-1>=0){
				if(b->gameboard[number-1][letter-1]==nullptr) return false;
				if(b->gameboard[number-1][letter-1]->color=='b') return true;
			}
		}				
		return false;*/
	
	return false;
}
bool Pawn:: try_move(int n, int l)
{
	if(!can_move()) return false;
	if(color=='b')
	{
		//controllo en passant
		if(b->gameboard[number][letter+1]!=nullptr)
			if(n-number==1 && l-letter==1 && b->gameboard[number][letter+1]->piece=='p' && ((Pawn*)b->gameboard[number][letter+1])->en_passant==true) return true;
		if(b->gameboard[number][letter-1]!=nullptr)
			if(n-number==1 && l-letter==-1 && b->gameboard[number][letter-1]->piece=='p' && ((Pawn*)b->gameboard[number][letter-1])->en_passant==true) return true;
		//controllo caselle in avanti
		if(n-number==1 && l==letter && b->gameboard[n][l]==nullptr) return true;
		if(n-number==2 && number==1 && l==letter && b->gameboard[n][l]==nullptr && b->gameboard[n+1][l]==nullptr) return true;
		//controllo mangiare diagonale
		if(n-number==1 && l-letter==1 && b->gameboard[n][l]!=nullptr && b->gameboard[n][l]->color!=color) return true;
		if(n-number==1 && l-letter==-1 && b->gameboard[n][l]!=nullptr && b->gameboard[n][l]->color!=color) return true;
		//if(n-number>2 || l-letter<-1 || l-letter>1) return false;
		//if(n-number==2 && number!=1) return false;
		/*if((l-letter==1 || l-letter==-1)&& n-number==1)
		{
			if(b->gameboard[n][l]==nullptr) return false;
			if(b->gameboard[n][l]->color=='w')
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		if(b->gameboard[n][l]==nullptr && (n==number+1 || n==number+2) && l==letter) return true;
		if((l-letter==1||l-letter==-1)&& n-number==2) return false;
		if(b->gameboard[n][l]!=nullptr)
			if(b->gameboard[n][l]->color=='b') return false;
		if(n==number && (l==letter-1 || l==letter+1)) return false;
		return true;*/
	}
	if(color=='w')
	{
		//controllo en passant
		if(b->gameboard[number][letter+1]!=nullptr)
			if(n-number==-1 && l-letter==1 && b->gameboard[number][letter+1]->piece=='P' && ((Pawn*)b->gameboard[number][letter+1])->en_passant==true) return true;
		if(b->gameboard[number][letter-1]!=nullptr)
			if(n-number==-1 && l-letter==-1 && b->gameboard[number][letter-1]->piece=='P' && ((Pawn*)b->gameboard[number][letter-1])->en_passant==true) return true;
		//controllo caselle in avanti
		if(n-number==-1 && l==letter && b->gameboard[n][l]==nullptr) return true;
		if(n-number==-2 && number==6 && l==letter && b->gameboard[n][l]==nullptr && b->gameboard[n-1][l]==nullptr) return true;
		//controllo mangiare diagonale
		if(n-number==-1 && l-letter==1 && b->gameboard[n][l]!=nullptr && b->gameboard[n][l]->color!=color) return true;
		if(n-number==-1 && l-letter==-1 && b->gameboard[n][l]!=nullptr && b->gameboard[n][l]->color!=color) return true;
	}
	return false;
		/*
		if(b->gameboard[number][letter+1]!=nullptr)
			if(n-number==-1 && l-letter==1 && b->gameboard[number][letter+1]->piece=='P' && ((Pawn*)b->gameboard[number][letter+1])->en_passant==true) return true;
		if(b->gameboard[number][letter-1]!=nullptr)
			if(n-number==-1 && l-letter==-1 && b->gameboard[number][letter-1]->piece=='P' && ((Pawn*)b->gameboard[number][letter-1])->en_passant==true) return true;
		//controllo casella non raggiugibili
		if(n-number<-2 || l-letter<-1 || l-letter>1) return false;
		if(n-number==-2 && number!=6) return false;
		//controllo movimento diagonale
		
		if((l-letter==1 || l-letter==-1)&& n-number==-1)
		{
			if(b->gameboard[n][l]==nullptr) return false;
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
		if(b->gameboard[n][l]==nullptr && (n==number-1 || n==number-2) && l==letter) return true;
		//controllo stesso colore
		if(b->gameboard[n][l]!=nullptr)
			if(b->gameboard[n][l]->color=='w') return false;
		if(n==number && (l==letter-1 || l==letter+1)) return false;
		return false;	
	}		
	return false;*/	
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
		if(number==0 || number==7)
		{
			promotion();
		}
		return;
	}
	throw new Illegal_move();
}
void Pawn:: promotion()
{
	if(color=='b')
	{
		char c;
		cout<<"hai promosso il pedone, scegli il pezzo: scrivi l'iniziale maiuscola del pezzo che vuoi scegliere"<<endl;
		while(true)
		{
			cin>>c;
			if(c=='A' || c=='T' || c=='D' || c=='C') break;
			cout<<"pezzo non valido"<<endl;
		}
		Piece* tmp=b->gameboard[number][letter];
		if(c=='A') b->gameboard[number][letter]=new Bishop(number, letter, 'b',b );
		if(c=='T') b->gameboard[number][letter]=new Rock(number, letter, 'b', b);
		if(c=='D') b->gameboard[number][letter]=new Queen(number, letter, 'b', b);	
		if(c=='C') b->gameboard[number][letter]=new Knight(number, letter, 'b', b);
        for(int i=0;i<b->blacks.size();i++)
		{
			if(b->blacks[i]==tmp)
			{
				b->blacks.erase(b->blacks.begin()+i);
				b->blacks.push_back(b->gameboard[number][letter]);
				break;
			}
		}
	}
	else
	{
		char c;
		cout<<"hai promosso il pedone, scegli il pezzo: scrivi l'iniziale minuscola del pezzo che vuoi scegliere"<<endl;
		while(true)
		{
			cin>>c;
			if(c=='a' || c=='t' || c=='d' || c=='c') break;
			cout<<"pezzo non valido"<<endl;
		}
		Piece* tmp=b->gameboard[number][letter];
		if(c=='a') b->gameboard[number][letter]=new Bishop(number, letter, 'w', b);
		if(c=='t') b->gameboard[number][letter]=new Rock(number, letter, 'w', b);
		if(c=='d') b->gameboard[number][letter]=new Queen(number, letter, 'w', b);	
		if(c=='c') b->gameboard[number][letter]=new Knight(number, letter, 'w', b);
		
		for(int i=0;i<b->whites.size();i++)
		{
			if(b->whites[i]==tmp)
			{
				b->whites.erase(b->whites.begin()+i);
				b->whites.push_back(b->gameboard[number][letter]);
				break;
			}
		}
		//bisogna rimuovere pedone e aggiungere pedina nuova al vector
	}
	
}
#endif

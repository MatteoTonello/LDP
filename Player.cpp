#ifndef PLAYER_CPP
#define PLAYER_CPP
#include <stdlib.h>
#include <time.h>
#include "Player.h"
#include <iostream>
#include <fstream>
#include "Board.cpp"
#include "Illegal_move.cpp"
using namespace std;
Player::Player(char c)
{
	if(c!='c' && c!='p') cout<<"sbagliati giocatori";
	if(c=='p')is_human=true;
	if(c=='c')is_human=false;
	color='n';
	replay=false;
	output_file=OFILE_DEFAULT;
	
};

char Player::col()
{return color;}

bool Player::human()
{return is_human;}

void Player::setcol(char c)
{color=c;}

void Player::move(string mossa)
{
		int i_letter,f_letter;
		char chari_letter,charf_letter;
		int i_number,f_number;
		chari_letter=mossa[0];	//convertiti
		charf_letter=mossa[3];
		i_number=mossa[1]-'0';	//da convertire
		f_number=mossa[4]-'0';
		i_number--;
		f_number--;
		//Conversione del sistema di riferimento degli indici da matrice a scacchiera (numeri in ordine opposto)
		if(mossa[2]!=' ') throw new Illegal_move();
		if(i_number<0 || i_number>=8) throw new Illegal_move();
		if(f_number<0 || f_number>=8) throw new Illegal_move();
		if(chari_letter<'A' || chari_letter>'h') throw new Illegal_move();
		if(chari_letter>'H' && chari_letter<'a') throw new Illegal_move();
		if(charf_letter<'A' || charf_letter>'h') throw new Illegal_move();
		if(charf_letter>'H' && charf_letter<'a') throw new Illegal_move();
		if(chari_letter>='A' && chari_letter<='H') i_letter=chari_letter-'A';
		if(chari_letter>='a' && chari_letter<='h') i_letter=chari_letter-'a';
		if(charf_letter>='A' && charf_letter<='H') f_letter=charf_letter-'A';
		if(charf_letter>='a' && charf_letter<='h') f_letter=charf_letter-'a';
		i_number=7-i_number; //conversione numeri per la matrice
		f_number=7-f_number;

		//Condizioni per il movimento
		if(boardgame->gameboard[i_number][i_letter]==nullptr) throw new Illegal_move();
		if(boardgame->gameboard[i_number][i_letter]->col()!=color) throw new Illegal_move();
		if(!(boardgame->gameboard[i_number][i_letter]->try_move(f_number,f_letter)))
		{
			cout<<"MOSSA ILLEGALE"<<endl;
         	throw new Illegal_move();
		}
		try
		{
			try{
			boardgame->gameboard[i_number][i_letter]->move(f_number,f_letter);
			}
			catch(Promotion* e)
			{
				promotion((Pawn*)(boardgame->gameboard[f_number][f_letter]),' ');
				return;
			}
		}
		catch(Illegal_move* e)
		{
			throw new Illegal_move();
		}
}

void Player::move()
{
	if(is_human)
	{
		int i_letter,f_letter;
		char chari_letter,charf_letter;
		int i_number,f_number;
		string mossa="";
		cout<<"inserisci mossa"<<endl;
		getline(cin,mossa);
		if(mossa=="XX XX")
		{
			cout<<*boardgame<<endl<<endl;
			move();
			return;
		}
		if(mossa=="PATTA")
		{
			int patta=rand()%2;
			if(patta==0)
			{
				cout<<"PATTA RIFIUTATA"<<endl;
				move();
				return;
			}
				
			if(patta==1)
			{
				boardgame->set_draw();
				ofstream file(output_file,ios::app);
				file<<mossa<<"\n";
				file.close();
				return;
			}
		}
		chari_letter=mossa[0];	//convertiti
		charf_letter=mossa[3];
		i_number=mossa[1]-'0';	//da convertire
		f_number=mossa[4]-'0';
		i_number--;
		f_number--;
		if(mossa[2]!=' ') throw new Illegal_move();
		if(i_number<0 || i_number>=8) throw new Illegal_move();
		if(f_number<0 || f_number>=8) throw new Illegal_move();
		if(chari_letter<'A' || chari_letter>'h') throw new Illegal_move();
		if(chari_letter>'H' && chari_letter<'a') throw new Illegal_move();
		if(charf_letter<'A' || charf_letter>'h') throw new Illegal_move();
		if(charf_letter>'H' && charf_letter<'a') throw new Illegal_move();
		if(chari_letter>='A' && chari_letter<='H') i_letter=chari_letter-'A';
		if(chari_letter>='a' && chari_letter<='h') i_letter=chari_letter-'a';
		if(charf_letter>='A' && charf_letter<='H') f_letter=charf_letter-'A';
		if(charf_letter>='a' && charf_letter<='h') f_letter=charf_letter-'a';
		i_number=7-i_number; //conversione numeri per la matrice
		f_number=7-f_number;
		if(boardgame->gameboard[i_number][i_letter]==nullptr) throw new Illegal_move();
		if(boardgame->gameboard[i_number][i_letter]->col()!=color) throw new Illegal_move();
		if(!(boardgame->gameboard[i_number][i_letter]->try_move(f_number,f_letter)))
		{
			cout<<"MOSSA INVALIDA"<<endl;
			move();
			return;
		}
		try
		{
			try{
			boardgame->gameboard[i_number][i_letter]->move(f_number,f_letter);
			}
			catch(Promotion* e)
			{
				ofstream file(output_file,ios::app);
				file<<mossa;
				file.close();
				promotion((Pawn*)(boardgame->gameboard[f_number][f_letter]),' ');
				file.close();
				return;
			}
			ofstream file(output_file,ios::app);
			file<<mossa<<"\n";
			file.close();
		}
		catch(Illegal_move* e)
		{
			throw new Illegal_move();
		}
		
	}
	else
	{
		int random_letter=0,random_number=0,random_piece=0;
		if(color=='w')
		{
			Piece* t;
			do
			{
				random_piece=rand()%boardgame->whites.size();
				random_number=rand()%8;
				random_letter=rand()%8;
				t=boardgame->whites[random_piece];
			}while(!(boardgame->whites[random_piece]->try_move(random_number,random_letter)));
			
			int n=boardgame->whites[random_piece]->num(),l=boardgame->whites[random_piece]->let();
			try{
				try{
					boardgame->whites[random_piece]->move(random_number,random_letter);
				}
				catch(Illegal_move* i)
				{
					move();
					return;
				}
				
			}
			catch(Promotion* e)
			{
				ofstream file(output_file,ios::app);
				file<<output_random_move(n,l,random_number,random_letter)<<"\n";
				file.close();
				promotion((Pawn*)(boardgame->gameboard[random_number][random_letter]),' ');
				return;
			}
			ofstream file(output_file,ios::app);
			file<<output_random_move(n,l,random_number,random_letter)<<"\n";
			file.close();
		}
		if(color=='b')
		{
			Piece* t;
			do
			{
				random_piece=rand()%boardgame->blacks.size();
				random_number=rand()%8;
				random_letter=rand()%8;
				t=boardgame->blacks[random_piece];
			}while(!(boardgame->blacks[random_piece]->try_move(random_number,random_letter)));
			
			int n=boardgame->blacks[random_piece]->num(),l=boardgame->blacks[random_piece]->let();
			try{
				try{
					boardgame->blacks[random_piece]->move(random_number,random_letter);
				}
				catch(Illegal_move* i)
				{
					move();
					return;
				}
			}
			catch(Promotion* e)
			{
				ofstream file(output_file,ios::app);
				file<<output_random_move(n,l,random_number,random_letter)<<"\n";
				file.close();
				promotion((Pawn*)(boardgame->gameboard[random_number][random_letter]),' ');
				return;
			}
			ofstream file(output_file,ios::app);
			file<<output_random_move(n,l,random_number,random_letter)<<"\n";
			file.close();
		}
		
	}
	
}

string Player::output_random_move(int num,int let,int n,int l)
{
    char fl='a'+l;
    char il='a'+let;
    int fn=7-n+1;
    int in=7-num+1;
    return il+to_string(in)+" "+fl+to_string(fn);
}

void Player::set_output_file(string file)
{
	output_file=file;
}

void Player:: promotion(Pawn* p,char pezzo)
{
	if(is_human)
	{
		if(pezzo!=' ')
		{
			Piece* tmp=p->b->gameboard[p->num()][p->let()];
			if(pezzo=='A') p->b->gameboard[p->num()][p->let()]=new Bishop(p->num(),p->let(), 'b',p->b );
			if(pezzo=='T') p->b->gameboard[p->num()][p->let()]=new Rock(p->num(), p->let(), 'b', p->b);
			if(pezzo=='D') p->b->gameboard[p->num()][p->let()]=new Queen(p->num(), p->let(), 'b', p->b);	
			if(pezzo=='C') p->b->gameboard[p->num()][p->let()]=new Knight(p->num(), p->let(), 'b',p-> b);
			if(pezzo=='a') p->b->gameboard[p->num()][p->let()]=new Bishop(p->num(), p->let(), 'w', p->b);
			if(pezzo=='t') p->b->gameboard[p->num()][p->let()]=new Rock(p->num(), p->let(), 'w', p->b);
			if(pezzo=='d') p->b->gameboard[p->num()][p->let()]=new Queen(p->num(), p->let(), 'w', p->b);	
			if(pezzo=='c') p->b->gameboard[p->num()][p->let()]=new Knight(p->num(), p->let(), 'w', p->b);
			if(pezzo!='A' && pezzo!='C' && pezzo!='D' && pezzo!='T' && pezzo!='a' && pezzo!='c' && pezzo!='t' && pezzo!='d')
				throw new Illegal_move();
			if(p->col()=='w')
			{
			for(int i=0;i<p->b->whites.size();i++)
			{
				if(p->b->whites[i]==tmp)
				{
					p->b->whites.erase(p->b->whites.begin()+i);
					p->b->whites.push_back(p->b->gameboard[p->num()][p->let()]);
					break;
				}
			}
			}
			else
			{
				for(int i=0;i<p->b->blacks.size();i++)
			{
				if(p->b->blacks[i]==tmp)
				{
					p->b->blacks.erase(p->b->blacks.begin()+i);
					p->b->blacks.push_back(p->b->gameboard[p->num()][p->let()]);
					break;
				}
			}
			}
			return;
		}
		if(replay)
		{
			throw p;
		}
		if(p->col()=='b')
		{
			char c;
			string prom;
			cout<<"hai promosso il pedone, scegli il pezzo: scrivi l'iniziale maiuscola del pezzo che vuoi scegliere"<<endl;
			while(true)
			{
				getline(cin,prom);
				c=prom[0];
				if(c=='A' || c=='T' || c=='D' || c=='C') break;
				cout<<"pezzo non valido"<<endl;
				throw new Illegal_move();
			}
			ofstream file(output_file,ios::app);
			file<<prom<<"\n";
			file.close();
			Piece* tmp=p->b->gameboard[p->num()][p->let()];
			if(c=='A') p->b->gameboard[p->num()][p->let()]=new Bishop(p->num(),p->let(), 'b',p->b );
			if(c=='T') p->b->gameboard[p->num()][p->let()]=new Rock(p->num(), p->let(), 'b', p->b);
			if(c=='D') p->b->gameboard[p->num()][p->let()]=new Queen(p->num(), p->let(), 'b', p->b);	
			if(c=='C') p->b->gameboard[p->num()][p->let()]=new Knight(p->num(), p->let(), 'b',p-> b);
			
			for(int i=0;i<p->b->blacks.size();i++)
			{
				if(p->b->blacks[i]==tmp)
				{
					p->b->blacks.erase(p->b->blacks.begin()+i);
					p->b->blacks.push_back(p->b->gameboard[p->num()][p->let()]);
					break;
				}
			}
		}
		else
		{
			char c;
			string prom;
			cout<<"hai promosso il pedone, scegli il pezzo: scrivi l'iniziale minuscola del pezzo che vuoi scegliere"<<endl;
			while(true)
			{
				getline(cin, prom);
				c=prom[0];
				if(c=='a' || c=='t' || c=='d' || c=='c') break;
				cout<<"pezzo non valido"<<endl;
			}
			ofstream file(output_file,ios::app);
			file<<prom<<"\n";
			file.close();
			Piece* tmp=p->b->gameboard[p->num()][p->let()];
			if(c=='a') p->b->gameboard[p->num()][p->let()]=new Bishop(p->num(), p->let(), 'w', p->b);
			if(c=='t') p->b->gameboard[p->num()][p->let()]=new Rock(p->num(), p->let(), 'w', p->b);
			if(c=='d') p->b->gameboard[p->num()][p->let()]=new Queen(p->num(), p->let(), 'w', p->b);	
			if(c=='c') p->b->gameboard[p->num()][p->let()]=new Knight(p->num(), p->let(), 'w', p->b);
			
			for(int i=0;i<p->b->whites.size();i++)
			{
				if(p->b->whites[i]==tmp)
				{
					p->b->whites.erase(p->b->whites.begin()+i);
					p->b->whites.push_back(p->b->gameboard[p->num()][p->let()]);
					break;
				}
			}
		}
	}
	else
	{
		int random_piece=rand()%4;
		Piece* tmp=p->b->gameboard[p->num()][p->let()];
			if(random_piece==0) p->b->gameboard[p->num()][p->let()]=new Bishop(p->num(), p->let(), p->col(), p->b);
			if(random_piece==1) p->b->gameboard[p->num()][p->let()]=new Rock(p->num(), p->let(), p->col(), p->b);
			if(random_piece==2) p->b->gameboard[p->num()][p->let()]=new Queen(p->num(), p->let(), p->col(), p->b);	
			if(random_piece==3) p->b->gameboard[p->num()][p->let()]=new Knight(p->num(), p->let(), p->col(), p->b);
			
			if(p->col()=='w')
			{
			for(int i=0;i<p->b->whites.size();i++)
			{
				if(p->b->whites[i]==tmp)
				{
					p->b->whites.erase(p->b->whites.begin()+i);
					p->b->whites.push_back(p->b->gameboard[p->num()][p->let()]);
					break;
				}
			}
			}
			else
			{
				for(int i=0;i<p->b->blacks.size();i++)
			{
				if(p->b->blacks[i]==tmp)
				{
					p->b->blacks.erase(p->b->blacks.begin()+i);
					p->b->blacks.push_back(p->b->gameboard[p->num()][p->let()]);
					break;
				}
			}
			}
		ofstream file(output_file,ios::app);
		string pezzo;
      	pezzo.push_back(p->b->gameboard[p->num()][p->let()]->cpiece());
		file<<pezzo<<"\n";
		file.close();
			
	}
}
#endif
	

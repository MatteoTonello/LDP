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
	output_file="log.txt";
	ofstream file(output_file);
	file.clear();
	file.close();
};
void Player::move(string mossa)
{
		ofstream file(output_file,ios::app);
		int i_letter,f_letter;
		char chari_letter,charf_letter;
		int i_number,f_number;
		if(mossa=="XX XX")
		{
			cout<<*boardgame<<endl;
			return;
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
		cout<<i_number<<" "<<i_letter<<endl;
		cout<<f_number<<" "<<f_letter<<endl;
		cout<<"superati controlli limiti"<<endl;
		if(boardgame->gameboard[i_number][i_letter]==nullptr) throw new Illegal_move();
		cout<<"controllo null"<<endl;
		cout<<color<<" "<<boardgame->gameboard[i_number][i_letter]->color<<endl;
		if(boardgame->gameboard[i_number][i_letter]->color!=color) throw new Illegal_move();
		cout<<"controllo colore"<<endl;
		if(!(boardgame->gameboard[i_number][i_letter]->try_move(f_number,f_letter)))
		{
			cout<<"Illegal move"<<endl;
		}
		try
		{
			cout<<"inizio mossa"<<endl;
			try{
			boardgame->gameboard[i_number][i_letter]->move(f_number,f_letter);
			}
			catch(Promotion* e)
			{
				file<<mossa<<"\n";
				promotion((Pawn*)(boardgame->gameboard[f_number][f_letter]),' ');
				file.close();
				return;
			}
			

			file<<mossa<<"\n";
			file.close();
			cout<<"fine mossa"<<endl;
		}
		catch(Illegal_move* e)
		{
			cout<<"errore nella mossa"<<boardgame->gameboard[i_number][i_letter]->piece<<endl;
			throw new Illegal_move();
		}
}
void Player::move()
{
	//srand(time(NULL));
	ofstream file(output_file,ios::app);
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
			cout<<*boardgame<<endl;
			move();
			return;
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
		cout<<i_number<<" "<<i_letter<<endl;
		cout<<f_number<<" "<<f_letter<<endl;
		cout<<"superati controlli limiti"<<endl;
		if(boardgame->gameboard[i_number][i_letter]==nullptr) throw new Illegal_move();
		cout<<"controllo null"<<endl;
		cout<<color<<" "<<boardgame->gameboard[i_number][i_letter]->color<<endl;
		if(boardgame->gameboard[i_number][i_letter]->color!=color) throw new Illegal_move();
		cout<<"controllo colore"<<endl;
		if(!(boardgame->gameboard[i_number][i_letter]->try_move(f_number,f_letter)))
		{
			cout<<"Illegal move"<<endl;
			move();
			return;
		}
		try
		{
			cout<<"inizio mossa"<<endl;
			try{
			boardgame->gameboard[i_number][i_letter]->move(f_number,f_letter);
			}
			catch(Promotion* e)
			{
				file<<mossa<<"\n";
				promotion((Pawn*)(boardgame->gameboard[f_number][f_letter]),' ');
				file.close();
				return;
			}
			file<<mossa<<"\n";
			file.close();
			cout<<"fine mossa"<<endl;
		}
		catch(Illegal_move* e)
		{
			cout<<"errore nella mossa"<<boardgame->gameboard[i_number][i_letter]->piece<<endl;
			throw new Illegal_move();
		}
		
	}
	else
	{
		int random_letter=0,random_number=0,random_piece=0;
		if(color=='w')
		{
			do
			{
				random_piece=rand()%boardgame->whites.size();
				random_number=rand()%8;
				random_letter=rand()%8;
			}while(!(boardgame->whites[random_piece]->try_move(random_number,random_letter)));
			//cout<<boardgame->whites[random_piece]->number<<boardgame->whites[random_piece]->letter<<" "<<random_number<<random_letter<<endl<<endl;
			int n=boardgame->whites[random_piece]->number,l=boardgame->whites[random_piece]->letter;
			boardgame->whites[random_piece]->move(random_number,random_letter);
			cout<<boardgame->whites[random_piece]->number<<boardgame->whites[random_piece]->letter;
			cout<<endl<<random_number<<random_letter<<endl;
			file<<output_random_move(n,l,random_number,random_letter)<<"\n";
			file.close();
			/*random_piece=rand()%boardgame->whites.size();
			boardgame->whites[random_piece]->random_move();*/
		}
		if(color=='b')
		{
			do
			{
				random_piece=rand()%boardgame->blacks.size();
				random_number=rand()%8;
				random_letter=rand()%8;
			}while(!(boardgame->blacks[random_piece]->try_move(random_number,random_letter)));
			//cout<<boardgame->blacks[random_piece]->number<<boardgame->blacks[random_piece]->letter<<" "<<random_number<<random_letter<<endl<<endl;
			int n=boardgame->blacks[random_piece]->number,l=boardgame->blacks[random_piece]->letter;
			boardgame->blacks[random_piece]->move(random_number,random_letter);
			cout<<boardgame->blacks[random_piece]->number<<boardgame->blacks[random_piece]->letter;
			cout<<endl<<random_number<<random_letter<<endl;
			file<<output_random_move(n,l,random_number,random_letter)<<"\n";
			file.close();
			/*random_piece=rand()%boardgame->blacks.size();
			boardgame->blacks[random_piece]->random_move();*/
		}
		
	}
	
}
string Player::output_random_move(int num,int let,int n,int l)
{
    char fl='A'+l;
    char il='A'+let;
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
			Piece* tmp=p->b->gameboard[p->number][p->letter];
			if(pezzo=='A') p->b->gameboard[p->number][p->letter]=new Bishop(p->number,p-> letter, 'b',p->b );
			if(pezzo=='T') p->b->gameboard[p->number][p->letter]=new Rock(p->number, p->letter, 'b', p->b);
			if(pezzo=='D') p->b->gameboard[p->number][p->letter]=new Queen(p->number, p->letter, 'b', p->b);	
			if(pezzo=='C') p->b->gameboard[p->number][p->letter]=new Knight(p->number, p->letter, 'b',p-> b);
			if(pezzo=='a') p->b->gameboard[p->number][p->letter]=new Bishop(p->number, p->letter, 'w', p->b);
			if(pezzo=='t') p->b->gameboard[p->number][p->letter]=new Rock(p->number, p->letter, 'w', p->b);
			if(pezzo=='d') p->b->gameboard[p->number][p->letter]=new Queen(p->number, p->letter, 'w', p->b);	
			if(pezzo=='c') p->b->gameboard[p->number][p->letter]=new Knight(p->number, p->letter, 'w', p->b);
			if(p->color=='w')
			{
			for(int i=0;i<p->b->whites.size();i++)
			{
				if(p->b->whites[i]==tmp)
				{
					p->b->whites.erase(p->b->whites.begin()+i);
					p->b->whites.push_back(p->b->gameboard[p->number][p->letter]);
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
					p->b->blacks.push_back(p->b->gameboard[p->number][p->letter]);
					break;
				}
			}
			}
			ofstream file(output_file,ios::app);
			file<<pezzo<<"\n";
			file.close();
			return;
		}
		if(replay)
		{
			throw p;
		}
			if(p->color=='b')
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
			}
			Piece* tmp=p->b->gameboard[p->number][p->letter];
			if(c=='A') p->b->gameboard[p->number][p->letter]=new Bishop(p->number,p-> letter, 'b',p->b );
			if(c=='T') p->b->gameboard[p->number][p->letter]=new Rock(p->number, p->letter, 'b', p->b);
			if(c=='D') p->b->gameboard[p->number][p->letter]=new Queen(p->number, p->letter, 'b', p->b);	
			if(c=='C') p->b->gameboard[p->number][p->letter]=new Knight(p->number, p->letter, 'b',p-> b);
			
			for(int i=0;i<p->b->blacks.size();i++)
			{
				if(p->b->blacks[i]==tmp)
				{
					p->b->blacks.erase(p->b->blacks.begin()+i);
					p->b->blacks.push_back(p->b->gameboard[p->number][p->letter]);
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
			Piece* tmp=p->b->gameboard[p->number][p->letter];
			if(c=='a') p->b->gameboard[p->number][p->letter]=new Bishop(p->number, p->letter, 'w', p->b);
			if(c=='t') p->b->gameboard[p->number][p->letter]=new Rock(p->number, p->letter, 'w', p->b);
			if(c=='d') p->b->gameboard[p->number][p->letter]=new Queen(p->number, p->letter, 'w', p->b);	
			if(c=='c') p->b->gameboard[p->number][p->letter]=new Knight(p->number, p->letter, 'w', p->b);
			
			for(int i=0;i<p->b->whites.size();i++)
			{
				if(p->b->whites[i]==tmp)
				{
					p->b->whites.erase(p->b->whites.begin()+i);
					p->b->whites.push_back(p->b->gameboard[p->number][p->letter]);
					break;
				}
			}
		}
	}
	else
	{
		int random_piece=rand()%4;
		Piece* tmp=p->b->gameboard[p->number][p->letter];
			if(random_piece==0) p->b->gameboard[p->number][p->letter]=new Bishop(p->number, p->letter, p->color, p->b);
			if(random_piece==1) p->b->gameboard[p->number][p->letter]=new Rock(p->number, p->letter, p->color, p->b);
			if(random_piece==2) p->b->gameboard[p->number][p->letter]=new Queen(p->number, p->letter, p->color, p->b);	
			if(random_piece==3) p->b->gameboard[p->number][p->letter]=new Knight(p->number, p->letter, p->color, p->b);
			
			if(p->color=='w')
			{
			for(int i=0;i<p->b->whites.size();i++)
			{
				if(p->b->whites[i]==tmp)
				{
					p->b->whites.erase(p->b->whites.begin()+i);
					p->b->whites.push_back(p->b->gameboard[p->number][p->letter]);
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
					p->b->blacks.push_back(p->b->gameboard[p->number][p->letter]);
					break;
				}
			}
			}
	}
}
#endif
	

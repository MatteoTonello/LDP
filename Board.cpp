#ifndef BOARD_CPP
#define BOARD_CPP
#include "Board.h"
#include "Pawn.h"
#include "Rock.h"
#include "Knight.h"
#include "Queen.h"
#include "King.h"
#include "Bishop.h"
#include <vector>
#include <string>
using namespace std;
Board::Board()
{
	draw=false;
	//Inizializzazione della matrice vuota
	Piece* matrix[8][8];
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			gameboard[i][j]=matrix[i][j];
			gameboard[i][j]=nullptr;
		}
	}
	//Inizializzazione dei vettori di pezzi e di ogni pedina posta sulla scacchiera
	vector<Piece*> first;
	whites=first;
	vector<Piece*> second;
	blacks=second;
	gameboard[0][0]=new Rock(0,0,'b',this);
	gameboard[0][1]=new Knight(0,1,'b',this);
	gameboard[0][2]=new Bishop(0,2,'b',this);
	gameboard[0][3]=new Queen(0,3,'b',this);
	black_king=new King(0,4,'b',this);         //evita conversioni da Piece a King
	gameboard[0][5]=new Bishop(0,5,'b',this);
	gameboard[0][6]=new Knight(0,6,'b',this);
	gameboard[0][7]=new Rock(0,7,'b',this);
	gameboard[7][0]=new Rock(7,0,'w',this);
	gameboard[7][1]=new Knight(7,1,'w',this);
	gameboard[7][2]=new Bishop(7,2,'w',this);
	gameboard[7][3]=new Queen(7,3,'w',this);
	white_king=new King(7,4,'w',this);
	gameboard[7][5]=new Bishop(7,5,'w',this);
	gameboard[7][6]=new Knight(7,6,'w',this);
	gameboard[7][7]=new Rock(7,7,'w',this);
	gameboard[7][4]=white_king;   
	gameboard[0][4]=black_king;
	for(int i=0;i<=7;i++)
		gameboard[1][i]=new Pawn(1,i,'b',this);
	for(int i=0;i<=7;i++)
		gameboard[6][i]=new Pawn(6,i,'w',this);

	//Inserimento dei pezzi di ogni colore nei rispettivi vettori
	for(int j=0;j<2;j++){
		for(int i=0;i<=7;i++){
			whites.push_back(gameboard[7-j][i]);
			blacks.push_back(gameboard[j][i]);
		}
    }
	
}
//Distruttore
Board::~Board()
{
   for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            delete gameboard[i][j];
        }
            
    }
   for(int i=0;i<blacks.size();i++)
	{
			delete blacks[i];
	}
   for(int i=0;i<whites.size();i++)
	{
			delete whites[i];
	}
}

bool Board::is_check_mate(char c)
{

	int piece_check=0;
	Piece* p;
   if(c=='w')
	{
		//Se il Re è sotto scacco e non si può muovere, conto i pezzi neri che lo tengono in scacco
		if(is_check(c) && (!(white_king->can_move())))
		{
			for(int i=0;i<blacks.size();i++)
			{
				if(blacks[i]->try_move(white_king->num(), white_king->let()))
				{
					p=blacks[i];	//Salvo il pezzo che tiene sotto scacco il Re per i controlli successivi
					piece_check++;
				}
			}
			if(piece_check>=2) return true;	//Con un doppio scacco è scacco matto
			
			/*
			Se c'è solo uno scacco, in base a quale pezzo è responsabile, controllo che una tra le pedine bianche
			possa interporsi nella linea di movimento o eventualmente mangiare la pedina nera
			*/
			if(p->cpiece()=='P')
			{
				for(int i=0;i<whites.size();i++)
				{
					if(whites[i]->try_move(p->num(), p->let()))return false;
				}
				return true;
			}
			if(p->cpiece()=='T')
			{
				if(p->num()==white_king->num())
				{
					if(p->let()<white_king->let())
					{
						for(int i=p->let();i<white_king->let();i++)
						{
							for(int j=0;j<whites.size();j++)
							{
								if(whites[j]->try_move(white_king->num(), i)) return false;
							}
						}
					}
					else
					{
						for(int i=p->let();i>white_king->let();i--)
						{
							for(int j=0;j<whites.size();j++)
							{
								if(whites[j]->try_move(white_king->num(), i)) return false;
							}
						}
					}
					return true;
				}
				else
				{
					if(p->num()<white_king->num())
					{
						for(int i=p->num();i<white_king->num();i++)
						{
							for(int j=0;j<whites.size();j++)
							{
								if(whites[j]->try_move(i, white_king->let())) return false;
							}
						}
					}
					else
					{
						for(int i=p->num();i>white_king->num();i--)
						{
							for(int j=0;j<whites.size();j++)
							{
								if(whites[j]->try_move(i, white_king->let())) return false;
							}
						}
					}
				}
				return true;
			}
			if(p->cpiece()=='A')
			{
				if(p->num()>white_king->num())
				{
					if(p->let()>white_king->let())
					{
						for(int i=p->num(), j=p->let();j>white_king->let();i--, j--)
						{
							for(int k=0;k<whites.size();k++)
							{
								if(whites[k]->try_move(i, j)) return false;
							}
						}
					}
					else
					{
						for(int i=p->num(), j=p->let();j>white_king->let();i++, j--)
						{
							for(int k=0;k<whites.size();k++)
							{
								if(whites[k]->try_move(i, j)) return false;
							}
						}
					}
				}
				else
				{
					if(p->let()>white_king->let())
					{
						for(int i=p->num(), j=p->let();j<white_king->let();i--, j++)
						{
							for(int k=0;k<whites.size();k++)
							{
								if(whites[k]->try_move(i, j)) return false;
							}
						}
					}
					else
					{
						for(int i=p->num(), j=p->let();j<white_king->let();i++, j++)
						{
							for(int k=0;k<whites.size();k++)
							{
								if(whites[k]->try_move(i, j)) return false;
							}
						}
					}
				}
				return true;
			}
			if(p->cpiece()=='D')
			{
				if(p->num()==white_king->num())
				{
					if(p->let()<white_king->let())
					{
						for(int i=p->let();i<white_king->let();i++)
						{
							for(int j=0;j<whites.size();j++)
							{
								if(whites[j]->try_move(white_king->num(), i)) return false;
							}
						}
					}
					else
					{
						for(int i=p->let();i>white_king->let();i--)
						{
							for(int j=0;j<whites.size();j++)
							{
								if(whites[j]->try_move(white_king->num(), i)) return false;
							}
						}
					}
					return true;
				}
				if(p->let()==white_king->let())
				{
					if(p->num()<white_king->num())
					{
						for(int i=p->num();i<white_king->num();i++)
						{
							for(int j=0;j<whites.size();j++)
							{
									if(whites[j]->try_move(i, white_king->let())) return false;
							}
						}
					}
					else
					{
						for(int i=p->num();i>white_king->num();i--)
						{
							for(int j=0;j<whites.size();j++)
							{
								if(whites[j]->try_move(i, white_king->let())) return false;
							}
						}
					}
					return true;
				}
				if(p->num()>white_king->num())
				{
					if(p->let()>white_king->let())
					{
						for(int i=p->num(), j=p->let();j>white_king->let();i--, j--)
						{
							for(int k=0;k<whites.size();k++)
							{
								if(whites[k]->try_move(i, j)) return false;
							}
						}
					}
					else
					{
						for(int i=p->num(), j=p->let();j>white_king->let();i--, j++)
						{
							for(int k=0;k<whites.size();k++)
							{
								if(whites[k]->try_move(i, j)) return false;
							}
						}
					}
				}
				else
				{
					if(p->let()>white_king->let())
					{
						for(int i=p->num(), j=p->let();j>white_king->let();i++, j--)
						{
							for(int k=0;k<whites.size();k++)
							{
									if(whites[k]->try_move(i, j)) 
										return false;
							}
						}
					}
					else
					{
						for(int i=p->num(), j=p->let();j<white_king->let();i++, j++)
						{
							for(int k=0;k<whites.size();k++)
							{
								if(whites[k]->try_move(i, j)) return false;
							}
						}
					}
				}
				return true;
			}
			if(p->cpiece()=='C')
			{
				for(int i=0;i<whites.size();i++)
				{
					if(whites[i]->try_move(p->num(), p->let())) return false;
				}
				return true;
			}
		}
	}
	if(c=='b')
	{
		//Se il Re è sotto scacco e non si può muovere, conto i pezzi bianchi che lo tengono in scacco
		if(is_check(c) && !(black_king->can_move()))
		{
			for(int i=0;i<whites.size();i++)
			{
				if(whites[i]->try_move(black_king->num(), black_king->let()))
				{
					p=whites[i];
					piece_check++;
				}
			}
			if(piece_check>=2) return true;	//Con un doppio scacco è scacco matto

			/*
			Se c'è solo uno scacco, in base a quale pezzo è responsabile, controllo che una tra le pedine nere
			possa interporsi nella linea di movimento o eventualmente mangiare la pedina nera
			*/
			if(p->cpiece()=='p')
			{
				for(int i=0;i<blacks.size();i++)
				{
					if(blacks[i]->try_move(p->num(), p->let()))return false;
				}
				return true;
			}
			if(p->cpiece()=='t')
			{
				if(p->num()==black_king->num())
				{
					if(p->let()<black_king->let())
					{
						for(int i=p->let();i<black_king->let();i++)
						{
							for(int j=0;j<blacks.size();j++)
							{
								if(blacks[j]->try_move(black_king->num(), i)) return false;
							}
						}
					}
					else
					{
						for(int i=p->let();i>black_king->let();i--)
						{
							for(int j=0;j<blacks.size();j++)
							{
								if(blacks[j]->try_move(black_king->num(), i)) return false;
							}
						}
					}
				}
				else
				{
					if(p->num()<black_king->num())
					{
						for(int i=p->num();i<black_king->num();i++)
						{
							for(int j=0;j<blacks.size();j++)
							{
								if(blacks[j]->try_move(i, black_king->let())) return false;
							}
						}
					}
					else
					{
						for(int i=p->num();i>black_king->num();i--)
						{
							for(int j=0;j<blacks.size();j++)
							{
								if(blacks[j]->try_move(i, black_king->let())) return false;
							}
						}
					}
				}
				return true;
			}
		if(p->cpiece()=='a')
		{
			if(p->num()>black_king->num())
			{
				if(p->let()>black_king->let())
				{
					for(int i=p->num(), j=p->let();j>black_king->let();i--, j--)
					{
						for(int k=0;k<blacks.size();k++)
						{
							if(blacks[k]->try_move(i, j)) return false;
						}
					}
				}
				else
				{
					for(int i=p->num(), j=p->let();j<black_king->let();i--, j++)
					{
						for(int k=0;k<blacks.size();k++)
						{
							if(blacks[k]->try_move(i, j)) return false;
						}
					}
				}
			}
			else
			{
				if(p->let()>black_king->let())
				{
					for(int i=p->num(), j=p->let();j>black_king->let();i++, j--)
					{
						for(int k=0;k<blacks.size();k++)
						{
							if(blacks[k]->try_move(i, j)) return false;
						}
					}
				}
				else
				{
					for(int i=p->num(), j=p->let();j<black_king->let();i++, j++)
					{
						for(int k=0;k<blacks.size();k++)
						{
							if(blacks[k]->try_move(i, j)) return false;
						}
					}
				}
			}
			return true;
		}
		if(p->cpiece()=='d')
		{
			if(p->num()==black_king->num())
			{
				if(p->let()<black_king->let())
				{
					for(int i=p->let();i<black_king->let();i++)
					{
						for(int j=0;j<blacks.size();j++)
						{
							if(blacks[j]->try_move(black_king->num(), i)) return false;
						}
					}
				}
				else
				{
					for(int i=p->let();i>black_king->let();i--)
					{
						for(int j=0;j<blacks.size();j++)
						{
							if(blacks[j]->try_move(black_king->num(), i))
								return false;
						}
					}
				}
			}
			if(p->let()==black_king->let())
			{
				if(p->num()<black_king->num())
				{
					for(int i=p->num();i<black_king->num();i++)
					{
						for(int j=0;j<blacks.size();j++)
						{
							if(blacks[j]->try_move(i, black_king->let())) return false;
						}
					}
				}
				else
				{
					for(int i=p->num();i>black_king->num();i--)
					{
						for(int j=0;j<blacks.size();j++)
						{
							if(blacks[j]->try_move(i, black_king->let())) return false;
						}
					}
				}
			}
			if(p->num()>black_king->num())
			{
				if(p->let()>black_king->let())
				{
					for(int i=p->num(), j=p->let();j>black_king->let();i--, j--)
					{
						for(int k=0;k<blacks.size();k++)
						{
							if(blacks[k]->try_move(i, j)) return false;
						}
					}
				}
				else
				{
					for(int i=p->num(), j=p->let();j<black_king->let();i--, j++) 
					{
						for(int k=0;k<blacks.size();k++)
						{
							if(blacks[k]->try_move(i, j)) return false;
						}
					}
				}
			}
			else
			{
				if(p->let()>black_king->let())
				{
					for(int i=p->num(), j=p->let();j>black_king->let();i++, j--)
					{
						for(int k=0;k<blacks.size();k++)
						{
							if(blacks[k]->try_move(i, j)) return false;
						}
					}
				}
				else
				{
					for(int i=p->num(), j=p->let();j<black_king->let();i++, j++)
					{
						for(int k=0;k<blacks.size();k++)
						{
							if(blacks[k]->try_move(i, j)) return false;
						}
					}
				}
			}
			return true;
			}
			if(p->cpiece()=='c')
			{
				for(int i=0;i<blacks.size();i++)
				{
					if(blacks[i]->try_move(p->num(), p->let())) return false;
				}
				return true;
			}
		}
	}
	return false;
}

bool Board::is_check(char c)
{
	if(c=='w')
	{
		if(white_king->is_not_check) return false;
		//Controllo se un qualche pezzo nero può muoversi sulla casella del re bianco
		for(int i=0;i<blacks.size();i++)
		{
			if(blacks[i]->try_move(white_king->num(), white_king->let())) return true;
		}
		return false;
	}
	if(c=='b')
	{
		if(black_king->is_not_check) return false;
		//Controllo se un qualche pezzo bianco può muoversi sulla casella del re nero
		for(int i=0;i<whites.size();i++)
		{
			if(whites[i]->try_move(black_king->num(), black_king->let())) return true;
		}
		return false;
	}
	return false;
}

bool Board::is_draw(char c)
{
	if(c=='w'){
		//Controllo che il re bianco non sia sotto scacco
		if(is_check('w')) return false;

		//Creo un vector temporaneo di pezzi bianchi
		vector<Piece*> whites_copy;
		for(int i=0;i<whites.size();i++)
			whites_copy.push_back(whites[i]);
		
		//Controllo che nessuna pedina possa muoversi (in caso contrario non è stallo)
		for(int i=0;i<whites_copy.size();i++){
			if(whites_copy[i]->can_move())
				return false;
		}
	
	}
	if(c=='b'){
		//Controllo che il re bianco non sia sotto scacco
		if(is_check('b')) return false;

		//Creo un vector temporaneo di pezzi neri
		vector<Piece*> blacks_copy;
		for(int i=0;i<blacks.size();i++)
			blacks_copy.push_back(blacks[i]);
		
		//Controllo che nessuna pedina possa muoversi (in caso contrario non è stallo)
		for(int i=0;i<blacks.size();i++){
			if(blacks[i]->can_move())
				return false;
		}
	}
	//Se il Re non è sotto scacco e nessuna pedina può muoversi, è stallo
	return true;
}

bool Board::cant_be_mate()
{
	//Se sono rimasti solo i due Re non può essere scacco
	if(blacks.size()==1 && whites.size()==1) return true;

	//Se è rimasta un'altra pedina, controllo se è un alfiere o un cavallo. In tal caso, non potrà mai essere scacco
	if(whites.size()==1 && blacks.size()==2){
		for(int i=0;i<2;i++){
			if(blacks[i]->cpiece()=='A' || blacks[i]->cpiece()=='C') return true;
		}
		
	}
	if(blacks.size()==1 && whites.size()==2){
		for(int i=0;i<2;i++){
			if(whites[i]->cpiece()=='a' || whites[i]->cpiece()=='c') return true;
		}
	}
	if(blacks.size()==2 && whites.size()==2){
		for(int i=0;i<2;i++){
			if(whites[i]->cpiece()=='a' || whites[i]->cpiece()=='c')
			{
				for(int j=0;j<2;j++){
					if(blacks[i]->cpiece()=='A' || blacks[i]->cpiece()=='C') return true;
				}
			}
		}
	}
	return false;
}
bool Board::get_draw()
{
	return draw;
}

void Board::set_draw()
{
	draw=true;

}
string Board::to_String()
{
	//Controllo tutta la scacchiera e la scrivo su una stringa
	string out="";
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            if(gameboard[i][j]==nullptr)
                out=out+" ";
            else
                out=out+gameboard[i][j]->cpiece();
        }
        out=out+"\n";
    }
	return out;
}

ostream& operator<<(ostream& os, Board& b)
{
    string out="";
    for(int i=0;i<8;i++)
    {
        out=out+" "+to_string(8-i)+" ";
        for(int j=0;j<8;j++)
        {
            if(b.gameboard[i][j]==nullptr)
                out=out+" ";
            else
                out=out+b.gameboard[i][j]->cpiece();
        }
        out=out+"\n";
    }
    out=out+"   ABCDEFGH\n";
    os<<out;
    return os ;
}
#endif
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
using namespace std;
Board::Board()
{
    
    Piece* matrix[8][8];
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            gameboard[i][j]=matrix[i][j];
            gameboard[i][j]=nullptr;
        }
            
    }
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
    for(int j=0;j<2;j++){
        for(int i=0;i<=7;i++){
            whites.push_back(gameboard[7-j][i]);
            blacks.push_back(gameboard[j][i]);
        }
    }
	
}
int Board::check_draw_for_ripetions()
{
    return 0;
}

bool Board::is_check(char c)
{
	if(c=='w')
	{
		for(int i=0;i<blacks.size();i++)
		{
			
			if(blacks[i]->try_move(white_king->number, white_king->letter)) {
				cout<<blacks[i]->piece;
				return true;}
			
			
		}
		return false;
	}
	if(c=='b')
	{
		for(int i=0;i<whites.size();i++)
		{
			if(whites[i]->try_move(black_king->number, black_king->letter)) return true;
		}
		return false;
	}
    return false;
}

bool Board::is_check_mate(char c)
{
	Piece* p;
   if(c=='w')
	{
		if(is_check(c) && (!(white_king->can_move())))
		{
			for(int i=0;i<blacks.size();i++)
			{
				if(blacks[i]->try_move(white_king->number, white_king->letter))
				{
					p=blacks[i];
					break;
				}
			}
			if(p->piece=='P')
			{
				for(int i=0;i<whites.size();i++)
				{
					if(whites[i]->piece!='r') if(whites[i]->try_move(p->number, p->letter))return false;
				}
				return true;
			}
			if(p->piece=='T')
			{
				if(p->number==white_king->number)
				{
					if(p->letter<white_king->letter)
					{
						for(int i=p->letter;i<white_king->letter;i++)
						{
							for(int j=0;j<whites.size();j++)
							{
								if(whites[j]->piece=='r')continue;
								if(whites[j]->try_move(white_king->number, i)) return false;
							}
						}
					}
					else
					{
						for(int i=p->letter;i>white_king->letter;i--)
						{
							for(int j=0;j<whites.size();j++)
							{
								if(whites[j]->piece=='r')continue;
								if(whites[j]->try_move(white_king->number, i)) return false;
							}
						}
					}
					return true;
				}
				else
				{
					if(p->number<white_king->number)
					{
						for(int i=p->number;i<white_king->number;i++)
						{
							for(int j=0;j<whites.size();j++)
							{
								if(whites[j]->piece=='r')continue;
								if(whites[j]->try_move(i, white_king->letter)) return false;
							}
						}
					}
					else
					{
						for(int i=p->number;i>white_king->number;i--)
						{
							for(int j=0;j<whites.size();j++)
							{
								if(whites[j]->piece=='r')continue;
								if(whites[j]->try_move(i, white_king->letter)) return false;
							}
						}
					}
				}
				return true;
			}
			if(p->piece=='A')
			{
				if(p->number>white_king->number)
				{
					if(p->letter>white_king->letter)
					{
						for(int i=p->number, j=p->letter;j>white_king->number;i--, j--)
						{
							for(int k=0;k<whites.size();k++)
							{
								if(whites[k]->piece=='r')continue;
								if(whites[k]->try_move(i, j)) return false;
							}
						}
					}
					else
					{
						for(int i=p->number, j=p->letter;j>white_king->number;i++, j--)
						{
							for(int k=0;k<whites.size();k++)
							{
								if(whites[k]->piece=='r')continue;
								if(whites[k]->try_move(i, j)) return false;
							}
						}
					}
				}
				else
				{
					if(p->letter>white_king->letter)
					{
						for(int i=p->number, j=p->letter;j<white_king->number;i--, j++)
						{
							for(int k=0;k<whites.size();k++)
							{
								if(whites[k]->piece=='r')continue;
								if(whites[k]->try_move(i, j)) return false;
							}
						}
					}
					else
					{
						for(int i=p->number, j=p->letter;j<white_king->number;i++, j++)
						{
							for(int k=0;k<whites.size();k++)
							{
								if(whites[k]->piece=='r')continue;
								if(whites[k]->try_move(i, j)) return false;
							}
						}
					}
				}
				return true;
			}
			if(p->piece=='D')
			{
				if(p->number==white_king->number)
				{
					if(p->letter<white_king->letter)
					{
						for(int i=p->letter;i<white_king->letter;i++)
						{
							for(int j=0;j<whites.size();j++)
							{
								if(whites[j]->piece=='r')continue;
								if(whites[j]->try_move(white_king->number, i)) return false;
							}
						}
					}
					else
					{
						for(int i=p->letter;i>white_king->letter;i--)
						{
							for(int j=0;j<whites.size();j++)
							{
								if(whites[j]->piece=='r')continue;
								if(whites[j]->try_move(white_king->number, i)) return false;
							}
						}
					}
				}
				if(p->letter==white_king->letter)
				{
					if(p->number<white_king->number)
					{
						for(int i=p->number;i<white_king->number;i++)
						{
							for(int j=0;j<whites.size();j++)
							{
								if(whites[j]->piece=='r')continue;
								if(whites[j]->try_move(i, white_king->letter)) return false;
							}
						}
					}
					else
					{
						for(int i=p->number;i>white_king->number;i--)
						{
							for(int j=0;j<whites.size();j++)
							{
								if(whites[j]->piece=='r')continue;
								if(whites[j]->try_move(i, white_king->letter)) return false;
							}
						}
					}
				}
				if(p->number>white_king->number)
				{
					if(p->letter>white_king->letter)
					{
						for(int i=p->number, j=p->letter;j>white_king->number;i--, j--)
						{
							for(int k=0;k<whites.size();k++)
							{
								if(whites[k]->piece=='r')continue;
								if(whites[k]->try_move(i, j)) return false;
							}
						}
					}
					else
					{
						for(int i=p->number, j=p->letter;j>white_king->number;i--, j++)
						{
							for(int k=0;k<whites.size();k++)
							{
								if(whites[k]->piece=='r')continue;
								if(whites[k]->try_move(i, j)) return false;
							}
						}
					}
				}
				else
				{
					if(p->letter>white_king->letter)
					{
						for(int i=p->number, j=p->letter;j<white_king->number;i++, j--)
						{
							for(int k=0;k<whites.size();k++)
							{
								if(whites[k]->piece!='r') if(whites[k]->try_move(i, j)) return false;
							}
						}
					}
					else
					{
						for(int i=p->number, j=p->letter;j<white_king->number;i++, j++)
						{
							for(int k=0;k<whites.size();k++)
							{
								if(whites[k]->piece!='r')	if(whites[k]->try_move(i, j)) return false;
							}
						}
					}
				}
				return true;
			}
			if(p->piece=='C')
			  {
				  for(int i=0;i<whites.size();i++)
				  {
					  if(whites[i]->piece=='r')continue;
					  if(whites[i]->try_move(p->number, p->letter)) return false;
				  }
				  return true;
			  }
			}
	}
	if(c=='b')
		{
			
			if(is_check(c) && !(black_king->can_move()))
				{
					for(int i=0;i<blacks.size();i++)
						{
								if(blacks[i]->try_move(black_king->number, black_king->letter))
						{
								p=blacks[i];
								break;
						}
					}
			if(p->piece=='p')
			{
				for(int i=0;i<blacks.size();i++)
				{
					if(blacks[i]->piece=='R')continue;
					if(blacks[i]->try_move(p->number, p->letter))return false;
				}
				return true;
			}
			if(p->piece=='t')
			{
				if(p->number==black_king->number)
				{
					if(p->letter<black_king->letter)
					{
						for(int i=p->letter;i<black_king->letter;i++)
						{
							for(int j=0;j<blacks.size();j++)
							{
								if(blacks[j]->piece=='R')continue;
								if(blacks[j]->try_move(black_king->number, i)) return false;
							}
						}
					}
					else
					{
						for(int i=p->letter;i>black_king->letter;i--)
						{
							for(int j=0;j<blacks.size();j++)
							{
								if(blacks[j]->piece=='R')continue;
								if(blacks[j]->try_move(black_king->number, i)) return false;
							}
						}
					}
				}
				else
				{
					if(p->number<black_king->number)
					{
						for(int i=p->number;i<black_king->number;i++)
						{
							for(int j=0;j<blacks.size();j++)
							{
								if(blacks[j]->piece=='R')continue;
								if(blacks[j]->try_move(i, black_king->letter)) return false;
							}
						}
					}
					else
					{
						for(int i=p->number;i>black_king->number;i--)
						{
							for(int j=0;j<blacks.size();j++)
							{
								if(blacks[j]->piece=='R')continue;
								if(blacks[j]->try_move(i, black_king->letter)) return false;
							}
						}
					}
				}
				return true;
			}
			if(p->piece=='a')
			{
				if(p->number>black_king->number)
				{
					if(p->letter>black_king->letter)
					{
						for(int i=p->number, j=p->letter;j>black_king->number;i--, j--)
						{
							for(int k=0;k<blacks.size();k++)
							{
								if(blacks[k]->piece=='R')continue;
								if(blacks[k]->try_move(i, j)) return false;
							}
						}
					}
					else
					{
						for(int i=p->number, j=p->letter;j>black_king->number;i++, j--)
						{
							for(int k=0;k<blacks.size();k++)
							{
								if(blacks[k]->piece=='R')continue;
								if(blacks[k]->try_move(i, j)) return false;
							}
						}
					}
				}
				else
				{
					if(p->letter>black_king->letter)
					{
						for(int i=p->number, j=p->letter;j<black_king->number;i--, j++)
						{
							for(int k=0;k<blacks.size();k++)
							{
								if(blacks[k]->piece=='R')continue;
								if(blacks[k]->try_move(i, j)) return false;
							}
						}
					}
					else
					{
						for(int i=p->number, j=p->letter;j<black_king->number;i++, j++)
						{
							for(int k=0;k<blacks.size();k++)
							{
								if(blacks[k]->piece=='R')continue;
								if(blacks[k]->try_move(i, j)) return false;
							}
						}
					}
				}
				return true;
			}
			if(p->piece=='d')
			{
				if(p->number==black_king->number)
				{
					if(p->letter<black_king->letter)
					{
						for(int i=p->letter;i<black_king->letter;i++)
						{
							for(int j=0;j<blacks.size();j++)
							{
								if(blacks[j]->piece=='R')continue;
								if(blacks[j]->try_move(black_king->number, i)) return false;
							}
						}
					}
					else
					{
						for(int i=p->letter;i>black_king->letter;i--)
						{
							for(int j=0;j<blacks.size();j++)
							{
								if(blacks[j]->piece=='R')continue;
								if(blacks[j]->try_move(black_king->number, i)) return false;
							}
						}
					}
				}
				if(p->letter==black_king->letter)
				{
					if(p->number<black_king->number)
					{
						
						for(int i=p->number;i<black_king->number;i++)
						{
							for(int j=0;j<blacks.size();j++)
							{
								if(blacks[j]->piece!='R')
									if(blacks[j]->try_move(i, black_king->letter)) return false;
							}
						}
					}
					else
					{
						for(int i=p->number;i>black_king->number;i--)
						{
							for(int j=0;j<blacks.size();j++)
							{
								if(blacks[j]->piece=='R')continue;
								if(blacks[j]->try_move(i, black_king->letter)) return false;
							}
						}
					}
				}
				if(p->number>black_king->number)
				{
					if(p->letter>black_king->letter)
					{
						for(int i=p->number, j=p->letter;j>black_king->number;i--, j--)
						{
							for(int k=0;k<blacks.size();k++)
							{
								if(blacks[k]->piece=='R')continue;
								if(blacks[k]->try_move(i, j)) return false;
							}
						}
					}
					else
					{
						for(int i=p->number, j=p->letter;j>black_king->number;i++, j--)
						{
							for(int k=0;k<blacks.size();k++)
							{
								if(blacks[k]->piece=='R')continue;
								if(blacks[k]->try_move(i, j)) return false;
							}
						}
					}
				}
				else
				{
					if(p->letter>black_king->letter)
					{
						for(int i=p->number, j=p->letter;j<black_king->number;i--, j++)
						{
							for(int k=0;k<blacks.size();k++)
							{
								if(blacks[k]->piece=='R')continue;
								if(blacks[k]->try_move(i, j)) return false;
							}
						}
					}
					else
					{
						for(int i=p->number, j=p->letter;j<black_king->number;i++, j++)
						{
							for(int k=0;k<blacks.size();k++)
							{
								if(blacks[k]->piece=='R')continue;
								if(blacks[k]->try_move(i, j)) return false;
							}
						}
					}
				}
				return true;
			  }
			  if(p->piece=='c')
			  {
				  for(int i=0;i<blacks.size();i++)
				  {
					  if(blacks[i]->piece=='R')continue;
					  if(blacks[i]->try_move(p->number, p->letter)) return false;
				  }
				  return true;
			  }
		   }
		}
		return false;
}

bool Board::is_draw()
{
	return false;
}
ostream& operator<<(ostream& os, Board& b)
{
    string out="";
    for(int i=0;i<8;i++)
    {
        out=out+to_string(i)+to_string(8-i)+" ";
        for(int j=0;j<8;j++)
        {
            if(b.gameboard[i][j]==nullptr)
                out=out+" ";
            else
                out=out+b.gameboard[i][j]->piece;
        }
        out=out+"\n";
    }
    out=out+"   ABCDEFGH\n";
    out=out+"   01234567\n";
    os<<out;
    return os ;
}
#endif
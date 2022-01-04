#include "Pawn.h"
using namespace std;
Pawn::Pawn(int n, int l, char col, Board& myBoard)
{
	number=n;
	letter=l;
	color=col;
	b=myBoard;
}
Pawn::bool can_move()
		{
			char tmp=color;
			color='0';
			if(is_check(tmp))return false;
			color=tmp;
			if(color=='w')
			{
				if((b.gameboard[l][n+1]->color=='0') return true;
				if(b.gameboard[l+1][n+1]->color=='b'||(b.gameboard[l-1][n+1]->color=='b') return true;
				return false;
			}
			if(color=='b')
			{
				if((b.gameboard[l][n-1]->color=='0') return true;
				if(b.gameboard[l+1][n-1]->color=='w'||(b.gameboard[l-1][n-1]->color=='w') return true;
				return false;
			}
		}
Pawn::void move(int n, int l)
		{
			if(!can_move()) throw illegal_move();
			if(color=='w')
			{
				if(n-number>2 || l-letter<-1 || l-letter>1) throw illegal_move();
				if(n-number==2 && number!=2) throw illegal_move;
				if((l-letter==1 || l-letter==-1)&& n-number==1)
				{
					if(b.gameboard[l][n]->color=='b')
					{
						number=n;
						letter=l;
						return;
					}
					else
					{
						throw illegal_move();
					}
				}
				if((l-letter==1||l-letter==-1)&& n-number==2) throw illegal_move();
				if(b.gameboard[l][n]->color=='w') throw illegal_move();
				letter=l;number=n;
			}
			if(color=='b')
			{
				if(n-number<-2 || l-letter<-1 || l-letter>1) throw illegal_move();
				if(n-number==-2 && number!=7) throw illegal_move;
				if((l-letter==1 || l-letter==-1)&& n-number==-1)
				{
					if(b.gameboard[l][n]->color=='w')
					{
						number=n;
						letter=l;
						return;
					}
					else
					{
						throw illegal_move();
					}
				}
				if((l-letter==1||l-letter==-1)&& n-number==-2) throw illegal_move();
				if(b.gameboard[l][n]->color=='b') throw illegal_move();
				letter=l;number=n;
			}
		}
}


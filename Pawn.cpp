#include "Pawn.h"
using namespace std;
Pawn::Pawn(int n, int l, char col, Board& myBoard)
{
	number=n;
	letter=l;
	color=col;
	b=myBoard;
	if(color=='w') piece='p';
	else piece='P';
};
bool Pawn::can_move()
		{
			*(b.gameboard[letter][number])==nullptr;
			if(b.is_check(color))return false;
			*(b.gameboard[l][n+1])==this;
			if(color=='w')
			{
				if((*(b.gameboard[l][n+1])==nullptr) return true;
				if(*(b.gameboard[l+1][n+1])==nullptr||(*(b.gameboard[l-1][n+1])==nullptr) return false;
				if(b.gameboard[l+1][n+1]->color=='b'||(b.gameboard[l-1][n+1]->color=='b') return true;
				return false;
			}
			if(color=='b')
			{
				if((*(b.gameboard[l][n-1])==nullptr) return true;
				if(*(b.gameboard[l+1][n-1])==nullptr||(*(b.gameboard[l-1][n-1])==nullptr) return false;
				if(b.gameboard[l+1][n-1]->color=='w'||(b.gameboard[l-1][n-1]->color=='w') return true;
				return false;
			}
		};
void Pawn::move(int n, int l)
		{
			if(!can_move()) throw illegal_move();
			if(color=='b')
			{
				if(n-number>2 || l-letter<-1 || l-letter>1) throw illegal_move();
				if(n-number==2 && number!=2) throw illegal_move;
				if((l-letter==1 || l-letter==-1)&& n-number==1)
				{
					if(b.gameboard[l][n]->color=='w')
					{
						*(b.gameboard[letter][number])=nullptr;
						number=n;
						letter=l;
						*(b.gameboard[l][n])=this;
						return;
					}
					else
					{
						throw illegal_move();
					}
				}
				if((l-letter==1||l-letter==-1)&& n-number==2) throw illegal_move();
				if(*(b.gameboard[l][n])==nullptr) throw illegal_move();
				if(b.gameboard[l][n]->color=='b') throw illegal_move();
				*(b.gameboard[letter][number])=nullptr;
				letter=l;number=n;
				*(b.gameboard[l][n])=this;
			}
			if(color=='w')
			{
				if(n-number<-2 || l-letter<-1 || l-letter>1) throw illegal_move();
				if(n-number==-2 && number!=7) throw illegal_move;
				if((l-letter==1 || l-letter==-1)&& n-number==-1)
				{
					if(b.gameboard[l][n]->color=='b')
					{
						*(b.gameboard[letter][number])=nullptr;
						number=n;
						letter=l;
						*(b.gameboard[l][n])=this;
						return;
					}
					else
					{
						throw illegal_move();
					}
				}
				if((l-letter==1||l-letter==-1)&& n-number==-2) throw illegal_move();
				if(*(b.gameboard[l][n])==nullptr) throw illegal_move();
				if(b.gameboard[l][n]->color=='w') throw illegal_move();
				*(b.gameboard[letter][number])=nullptr;
				letter=l;number=n;
				*(b.gameboard[l][n])=this;
			}
		}
};


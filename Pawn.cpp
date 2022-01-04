#include<Pawn.h>
class Pawn:: public Piece
{
	//   ciao mici
	public:
		Pawn(int n, int l, char color, Board myBoard);
		bool can_move()
		{
			if(color=='w')
			{
				if((*b[l][n+1]).color=='0') return true;
				if((*b[l+1][n+1]).color=='b'||(*b[l-1][n+1]).color=='b') return true;
				return false;
			}
		}
		void move(int n, int l)
		{
			
			if(color=='w')
			{
				if(n-number>2 || l-letter<-1 || l-letter>1) throw illegal_move();
				if(n-number==2 && number!=2) throw illegal_move;
				if((l-letter==1 || l-letter==-1)&& n-number==1)
				{
					if((*b[l][n]).color=='b')
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
				if((*b[l][n]).color=='w') throw illegal_move();
				letter=l;number=n;
			}
			if(color=='b')
			{
				if(n-number<-2 || l-letter<-1 || l-letter>1) throw illegal_move();
				if(n-number==-2 && number!=7) throw illegal_move;
				if((l-letter==1 || l-letter==-1)&& n-number==-1)
				{
					if((*b[l][n]).color=='w')
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
				if((*b[l][n]).color=='b') throw illegal_move();
				letter=l;number=n;
			}
		}
}


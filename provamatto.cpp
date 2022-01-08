#include "Board.cpp"
#include "Pawn.cpp"
#include "Rock.cpp"
#include "Knight.cpp"
#include "Queen.cpp"
#include "King.cpp"
#include "Bishop.cpp"
using namespace std;
int main()
{
    
    Board* b=new Board();
	b->gameboard[6][5]->move(4,5);
	b->gameboard[6][6]->move(4,6);
	b->gameboard[1][4]->move(3,4);
	b->gameboard[0][3]->move(4,7);
	cout<<*b<<endl;
	//for(int i=0;i<10;i++)
	//{
		if(b->is_check('w'))
		{
			cout<<"be dai1"<<endl;
		}
		if(!(b->white_king->can_move())){
			cout<<"be dai2"<<endl;
		}
		if(b->is_check_mate('w'))
		{
			cout<<"be dai3"<<endl;
		}
	//}
    return 0;
}

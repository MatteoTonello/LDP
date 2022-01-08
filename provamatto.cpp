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
	b->gameboard[6][4]->move(4,4);
	b->gameboard[7][5]->move(4,2);
	b->gameboard[7][3]->move(5,5);
	cout<<b->gameboard[5][5]->try_move(1,5);
	cout<<*b<<endl;
	if(b->is_check_mate('w'))cout<<"scacco matto"<<endl;
	//}
    return 0;
}

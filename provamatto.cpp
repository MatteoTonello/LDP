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
	cout<<b->is_check_mate('w');
    return 0;
}

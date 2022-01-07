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
    b->gameboard[6][4]->move(5,4);
    b->gameboard[1][7]->move(2,7);
    b->gameboard[1][6]->move(2,6);
    b->gameboard[7][5]->move(4,2);
    b->gameboard[7][3]->move(5,5);
    b->gameboard[5][5]->move(2,5);
	cout<<*b<<endl;
    cout<<(b->is_check_mate('b'));
    return 0;
}

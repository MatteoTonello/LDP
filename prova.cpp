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
    //Piece* piece=new King(1,2,'o',b);
    Pawn p(1,2,'b',b);
    cout<<*b;
    b->gameboard[6][0]->move(4,0);
    cout<<*b;
    b->gameboard[1][1]->move(2,1);
    cout<<*b;
    b->gameboard[4][0]->move(3,0);
    cout<<*b;
    b->gameboard[2][1]->move(3,0);
    cout<<*b;
    return 0;
}

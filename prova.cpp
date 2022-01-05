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
    b->gameboard[0][6]->move(0,4);
    cout<<*b;
    return 0;
}

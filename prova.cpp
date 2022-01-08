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
    b->gameboard[7][0]->move(3,0);
    cout<<*b;
    b->gameboard[0][2]->move(1,1);
    cout<<*b;
    b->gameboard[7][1]->move(5,2);
    cout<<*b;
    b->gameboard[6][4]=nullptr;
    cout<<*b;
    b->gameboard[2][4]=b->gameboard[0][3];
    cout<<*b;
    b->gameboard[0][3]->number=2;
    b->gameboard[0][3]->letter=4;
    b->gameboard[0][3]=nullptr;
    cout<<*b;
    
    cout<<b->is_check('w')<<endl<<b->is_check_mate('w')<<endl;
    b->gameboard[5][5]=b->gameboard[0][6];
    b->gameboard[5][5]->number=5;
    b->gameboard[5][5]->letter=5;
    b->gameboard[0][1]->move(2,2);
    b->gameboard[0][4]->move(0,2);
    cout<<*b;
    cout<<b->is_check_mate('w');
    
    return 0;
}

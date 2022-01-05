#include "Board.cpp"
#include "Pawn.cpp"
#include "Pawn.cpp"
#include "Rock.cpp"
#include "Knight.cpp"
#include "Queen.cpp"
#include "King.cpp"
#include "Bishop.cpp"
using namespace std;
int main()
{
    cout<<"1";
    Board b;
    cout<<"2";
    Pawn p(1,2,'b',b);
    cout<<"3";
    b.print();
    cout<<"4";
    return 0;
}

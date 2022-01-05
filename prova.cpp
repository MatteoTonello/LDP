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
    Board* b=new Board();
    Pawn p(1,2,'b',b);
    cout<<*b;
    return 0;
}

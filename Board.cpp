#ifndef BOARD_CPP
#define BOARD_CPP
#include "Board.h"
using namespace std;
//Board::Board()
//{
   /* gameboard=new Piece*[8][8];
    whites(16);
    blacks(16);
    gameboard[0][0]=new Rock();
    gameboard[1][0]=new Knight();
    gameboard[2][0]=new Bishop();
    gameboard[3][0]=new Queen();
    gameboard[4][0]=new King();
    gameboard[5][0]=new Bishop();
    gameboard[6][0]=new Knight();
    gameboard[7][0]=new Rock();
    gameboard[0][7]=new Rock();
    gameboard[1][7]=new Knight();
    gameboard[2][7]=new Bishop();
    gameboard[3][7]=new Queen();
    gameboard[4][7]=new King();
    gameboard[5][7]=new Bishop();
    gameboard[6][7]=new Knight();
    gameboard[7][7]=new Rock();

    for(int i=0;i<7;i++)
     gameboard[i][1]=new Pawn(i,1,'b',this);
    for(int i=0;i<7;i++)
     gameboard[i][6]=new Pawn(i,6,'w',this);

    for(int j=0;j<2;j++){
        for(int i=0;i<7;i++){
            whites.push_back(gameboard[i][7-j]);
            blacks.push_back(gameboard[i][0+j]);
        }
    }
*/
//}
int Board::check_draw_for_ripetions()
{
    return 0;
}
bool Board::is_check_mate(char c)
{
    if(is_check(c))
    {
        
    }
    return 0;
}
bool Board::is_check(char c)
{
    return 0;
}
bool Board::is_draw()
{
    return 0;
}
#endif
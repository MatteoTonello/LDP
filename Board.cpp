#ifndef BOARD_CPP
#define BOARD_CPP
#include "Board.h"
#include "Pawn.h"
#include "Rock.h"
#include "Knight.h"
#include "Queen.h"
#include "King.h"
#include "Bishop.h"
#include <vector>
using namespace std;
Board::Board()
{
    
    Piece* matrix[8][8];
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            gameboard[i][j]=matrix[i][j];
            gameboard[i][j]=nullptr;
        }
            
    }
    vector<Piece*> first(16);
    whites=first;
    vector<Piece*> second(16);
    blacks=second;
    gameboard[0][0]=new Rock(0,0,'b',this);
    gameboard[1][0]=new Knight(1,0,'b',this);
    gameboard[2][0]=new Bishop(2,0,'b',this);
    gameboard[3][0]=new Queen(3,0,'b',this);
    gameboard[4][0]=new Queen(4,0,'b',this);
    gameboard[5][0]=new Bishop(5,0,'b',this);
    gameboard[6][0]=new Knight(6,0,'b',this);
    gameboard[7][0]=new Rock(7,0,'b',this);
    gameboard[0][7]=new Rock(0,7,'w',this);
    gameboard[1][7]=new Knight(1,7,'w',this);
    gameboard[2][7]=new Bishop(2,7,'w',this);
    gameboard[3][7]=new Queen(3,7,'w',this);
    gameboard[4][7]=new Queen(4,7,'w',this);
    gameboard[5][7]=new Bishop(5,7,'w',this);
    gameboard[6][7]=new Knight(6,7,'w',this);
    gameboard[7][7]=new Rock(7,7,'w',this);
    for(int i=0;i<=7;i++)
     gameboard[i][1]=new Pawn(i,1,'b',this);
    for(int i=0;i<=7;i++)
     gameboard[i][6]=new Pawn(i,6,'w',this);
    for(int j=0;j<2;j++){
        for(int i=0;i<=7;i++){
            whites.push_back(gameboard[i][7-j]);
            blacks.push_back(gameboard[i][0+j]);
        }
    }

}
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
ostream& operator<<(ostream& os, Board& b)
{
    string out="";
    for(int i=0;i<8;i++)
    {
        out=out+to_string(8-i)+" ";
        for(int j=0;j<8;j++)
        {
            if(b.gameboard[j][i]==nullptr)
                out=out+" ";
            else
                out=out+b.gameboard[j][i]->piece;
        }
        out=out+"\n";
    }
    out=out+"  ABCDEFGH\n";
    os<<out;
    return os ;
}
#endif
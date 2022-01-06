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
    gameboard[0][1]=new Knight(0,1,'b',this);
    gameboard[0][2]=new Bishop(0,2,'b',this);
    gameboard[0][3]=new Queen(0,3,'b',this);
    gameboard[0][4]=new King(0,4,'b',this);
    gameboard[0][5]=new Bishop(0,5,'b',this);
    gameboard[0][6]=new Knight(0,6,'b',this);
    gameboard[0][7]=new Rock(0,7,'b',this);
    gameboard[7][0]=new Rock(7,0,'w',this);
    gameboard[7][1]=new Knight(7,1,'w',this);
    gameboard[7][2]=new Bishop(7,2,'w',this);
    gameboard[7][3]=new Queen(7,3,'w',this);
    gameboard[7][4]=new King(7,4,'w',this);
    gameboard[7][5]=new Bishop(7,5,'w',this);
    gameboard[7][6]=new Knight(7,6,'w',this);
    gameboard[7][7]=new Rock(7,7,'w',this);
    for(int i=0;i<=7;i++)
        gameboard[1][i]=new Pawn(1,i,'b',this);
    for(int i=0;i<=7;i++)
        gameboard[6][i]=new Pawn(6,i,'w',this);
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
    return 0; //per lo scacco secondo me bisogna convertire tutti i move in "try_move" e poi se non dà eccezioni
            //si muove. Poi si applica il try_move a tutte le caselle del colore opposto e se ce n'è una che non fa eccezioni
            //allora è scacco
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
        out=out+to_string(i)+to_string(8-i)+" ";
        for(int j=0;j<8;j++)
        {
            if(b.gameboard[i][j]==nullptr)
                out=out+" ";
            else
                out=out+b.gameboard[i][j]->piece;
        }
        out=out+"\n";
    }
    out=out+"   ABCDEFGH\n";
    out=out+"   01234567\n";
    os<<out;
    return os ;
}
#endif
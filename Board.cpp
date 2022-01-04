Board::Board()
{
    gameboard=new Piece*[8][8];
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
     gameboard[i][1]=new Pawn();
    for(int i=0;i<7;i++)
     gameboard[i][6]=new Pawn();

}
int Board::check_draw_for_ripetions();
bool Board::is_check_mate(char c)
{
    if(is_check(c))
    {
        
    }
}
bool Board::is_check(char c);
bool Board::is_draw();
int Board::white_pieces;
int Board::black_pieces;
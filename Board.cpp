Board::Board()
{
    gameboard=new Piece*[8][8];
    gameboard[0][0]=new Rock();
    gameboard[][]=new Knight();
    gameboard[][]=new Bishop();
    gameboard[][]=new Queen();
    gameboard[][]=new King();
    gameboard[][]=new Bishop();
    gameboard[][]=new Knight();
    gameboard[][]=new Rock();
    gameboard[0][0]=new Rock();
    gameboard[][]=new Knight();
    gameboard[][]=new Bishop();
    gameboard[][]=new Queen();
    gameboard[][]=new King();
    gameboard[][]=new Bishop();
    gameboard[][]=new Knight();
    gameboard[][]=new Rock();

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
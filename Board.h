class Board
{
	private:
		Piece* gameboard[8][8];
		vector<b> last_bs;
	public:
		int check_draw_for_ripetions();
		bool is_check_mate();
		bool is_check(char c);
		bool is_draw();
		int white_pieces;
		int black_pieces;
		
}
class Board
{
	private:
		Piece* gameboard[8][8];
		vector<b> last_bs;
	public:
		int check_draw_for_ripetions;
		bool is_check_mate();
		bool is_check();
		bool is_draw();
		int white_pieces;
		int black_pieces;
		
};
class Game
{
	board mainb();
	bool player;
	bool is_finished();
	
};
class Piece
{
	public:
		int number;
		int letter;
		Board b;
		const char color;
		virtual void move(int n, int l) =0;
		virtual bool can_move() =0;
	};
class Pawn
{
};
class Rock
{
};
class Knight
{
};
class Bishop
{
};
class Queen
{
};
class King
{
};


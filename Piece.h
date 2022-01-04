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
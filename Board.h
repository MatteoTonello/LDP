#ifndef BOARD_H
#define BOARD_H
#include <vector>
using namespace std;
class Piece;
class King;
class Board
{
	public:
		Board();
		Piece* gameboard[8][8];
		vector<Board> last_bs;
		vector<Piece*> whites;
		vector<Piece*> blacks;
		int check_draw_for_ripetions();
		bool is_check_mate(char c);
		bool is_check(char c);
		bool is_draw();
		King* white_king;
		King* black_king;
		void print();
		
};
#endif
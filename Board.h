#ifndef BOARD_H
#define BOARD_H
#include <vector>
using namespace std;
class Piece;

class Board
{
	public:
		Piece* gameboard[8][8];
		vector<Board> last_bs;
		vector<Piece*> whites;
		vector<Piece*> blacks;
	public:
		int check_draw_for_ripetions();
		bool is_check_mate(char c);
		bool is_check(char c);
		bool is_draw();
		int white_pieces;
		int black_pieces;
		
};
#endif
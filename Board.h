#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>
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
		bool is_check_mate(char c);
		bool is_check(char c);
		bool is_draw(char c);
		bool cant_be_mate();
		King* white_king;
		King* black_king;
		void print();
		string to_String();
		
};
#endif
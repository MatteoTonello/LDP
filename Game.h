#ifndef GAME_H
#define GAME_H
#include "Board.h"
#include "Player.h"
class Game
{
	public:
		Game(Player* n1,Player* n2);
		void startgame();
		void change_turn();
		void player_move();
		Player* white_player;
		Player* black_player;
		Board* mainboard;
		Player* is_turn;
		bool is_finished();
		string result;
}
#endif
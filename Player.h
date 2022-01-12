#ifndef PLAYER_H
#define PLAYER_H
#include "Board.h"
class Player
{
    public:
	char color;
    Board* boardgame;
	bool is_human;
    Player(char c);
    void move();
    void move(string mossa);
};
#endif
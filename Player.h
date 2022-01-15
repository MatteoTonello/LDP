#ifndef PLAYER_H
#define PLAYER_H
#include "Board.h"
#include "Pawn.h"
#include "Promotion.cpp"
class Player
{
    public:
	char color;
    Board* boardgame;
	bool is_human;
    string output_file;
    bool replay;
    Player(char c);
    void move();
    void move(string mossa);
    string output_random_move(int num,int let,int n,int l);
    void set_output_file(string file);
    void promotion(Pawn* p,char pezzo);
};
#endif
//PRIOLI GIACOMO 2016259
#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;
class Piece;
class King;
//classe che rappresenta la scacchiera
class Board
{
		bool draw;       		//true se è patta
	public:
		Board();       				//costruttore scacchiera iniziale
      ~Board();
		Piece* gameboard[8][8];   	//matrice di puntatori a pezzi
		vector<Piece*> whites;		//vettore contenente tutti i pezzi bianchi
		vector<Piece*> blacks;		//vettore contenente tutti i pezzi neri
		bool is_check_mate(char c);	//true se è scacco matto, false altrimenti
		bool is_check(char c);	//true se è scacco, false altrimenti
		bool is_draw(char c);	//true se è patta, false altrimenti
		bool cant_be_mate();	//true se non è possibile fare scacco, false altrimenti
		King* white_king;		//puntatore al re bianco
		King* black_king;		//puntatore al re nero
		string to_String();		//restituisce la scacchiera come stringa
		void set_draw();		//draw diventa true
		bool get_draw();		//restituisce draw
};
#endif
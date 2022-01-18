#ifndef GAME_H
#define GAME_H
#include "Board.h"
#include "Player.h"
#include <iostream>
//classe che gestisce le partite
class Game
{
	public:
		Game(Player* n1,Player* n2);   	//costruttore per partita giocatore n1 contro n2
		Player* white_player;			//puntatore a giocatore bianco
		Player* black_player;			//puntatore a giocatore bianco
		Board* mainboard;				//puntatore alla scacchiera della partita	
		Player* is_turn;				//puntatore al giocatore che deve fare la mossa
		string result;					//descrive il risultato della partita
		int nmosse;						//numero mosse della partita
		vector<string> last_bs;			//vettore contenente tutte le disposizioni delle scacchiere durante la partita
		string pawns;					//stringa che rappresenta i pedoni nella scacchiera, utile nel metodo fifty_moves()
		int fmcount;					//contatore per fifty_moves()
		int npieces;					//contatore pezzi della scacchiera, per fifty_moves()
		bool is_finished();		//true se la partita è finita(aggiorna il risultato), false altrimenti
		void startgame();     	//inizio partita
		void change_turn();		//se il turno è del nero, passa al bianco, e viceversa
		void player_move();		//mossa del giocatore
		bool draw_for_ripetition();  	//true se è patta per ripetizione, false altrimenti
		bool fifty_moves(); 			//true se è patta, 50 mosse senza cattura di pezzi o muovere pedoni
};
#endif
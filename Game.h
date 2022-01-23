#ifndef GAME_H
#define GAME_H
#include "Board.h"
#include "Player.h"
#include <iostream>
//classe che gestisce le partite
class Game
{
      Player* white_player;			//puntatore a giocatore bianco
		Player* black_player;			//puntatore a giocatore bianco
      int nmosse;						//numero mosse della partita
      int fmcount;					//contatore per fifty_moves()
		int npieces;					//contatore pezzi della scacchiera, per fifty_moves()
      string result;					//descrive il risultato della partita
      string pawns;					//stringa che rappresenta i pedoni nella scacchiera, utile nel metodo fifty_moves()
	
   public:
		Game(char type);   	//costruttore per partita giocatore n1 contro n2
      ~Game();
		void addMove();		//Incrementa il numero di mosse
      string game_result();
		Board* mainboard;				//puntatore alla scacchiera della partita	
		Player* is_turn;				//puntatore al giocatore che deve fare la mossa
		vector<string> last_bs;			//vettore contenente tutte le disposizioni delle scacchiere durante la partita
		bool is_finished();		//true se la partita è finita(aggiorna il risultato), false altrimenti
		void startgame();     	//inizio partita
		void change_turn();		//se il turno è del nero, passa al bianco, e viceversa
		void player_move();		//mossa del giocatore
		bool draw_for_ripetition();  	//true se è patta per ripetizione, false altrimenti
		bool fifty_moves(); 			//true se è patta, 50 mosse senza cattura di pezzi o muovere pedoni
};
#endif
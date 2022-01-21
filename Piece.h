#ifndef PIECE_H
#define PIECE_H
#include "Board.h"
//classe astratta che definisce un pezzo
class Piece
{
	protected:
		bool diventa_scacco(int number_eliminated, int letter_eliminated, int number_moved,int letter_moved);
		/*true se la mossa "scopre" uno scacco, false altrimenti, quindi è permessa
		number_eliminated,letter_eliminated indicano la posizione nella quale se c'è un pezzo dovrebbe essere eliminato
		number_moved,letter_moved indicano la posizione dove si dovrebbe muovere il pezzo
		questa distione è stata fatta per adattare il codice all'en passant*/

		void remove_en_passant();      //mette a false tutti gli en passant dei pedoni quando finisce una mossa
      char piece;     //carattere che distingue il tipo del pezzo
		int number;		//numero della riga nella matrice della scacchiera del pezzo
		int letter;    //numero della colonna nella matrice della scacchiera del pezzo
      char color;		//colore del pezzo
      
	public:
				 
		Board* b;		//scacchiera nel quale si trova il pezzo
		int num();
      int let();
      char col();
      char cpiece();
		virtual void move(int n, int l) =0;   //permette al pezzo di muoversi nella matrice alla riga n e colonna l
		virtual bool try_move(int n,int l)=0;  //true se il pezzo può muoversi in quella posizione, false altrimenti
		virtual bool can_move() =0;    //true se il pezzo ha mosse disponibili, false altrimenti
};
#endif
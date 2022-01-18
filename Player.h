#ifndef PLAYER_H
#define PLAYER_H
#include "Board.h"
#include "Pawn.h"
#include "Promotion.cpp"
//classe che rappresenta i giocatori sia umani che computer
class Player
{
        string output_file;      //nome file di output
        string output_random_move(int num,int let,int n,int l);    //restituisce la mossa con la notazione corretta per la scacchiera
    public:
        char color;       //colore dei pezzi del giocatore
        Board* boardgame; //scacchiera su cui giocano i giocatori
        bool is_human;    //true se è umano, false se è computer
        bool replay;            //true se si sta facendo un replay, false se è una partita
        Player(char c);         //costruttore di un giocatore con pezzi di colore c
        void move();            //mossa del giocatore
        void move(string mossa);  //mossa del giocatore descitta dalla stringa "mossa"
        void set_output_file(string file);         //imposta il file di output
        void promotion(Pawn* p,char pezzo);        //promozione del pedone p in pezzo
};
#endif
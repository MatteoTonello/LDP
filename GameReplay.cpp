//TONELLO MATTEO 2008596
#ifndef GAMEREPLAY_CPP
#define GAMEREPLAY_CPP
#include "GameReplay.h"
#include "Piece.h"
#include <chrono>
#include <thread>
#include "Board.cpp"
#include <iostream>
#include <fstream>
#include "Illegal_move.cpp"
using namespace std;

GameReplay::GameReplay(string in)   //Costruttore per solo file in input
{
    game=new Game('r');         //nuova partita con parametro replay
    file_input=in;
    file_output="";
}

GameReplay::GameReplay(string in,string out)    //Costruttore per input e output
{
    game=new Game('r');         //nuova partita con parametro replay
    file_input=in;
    file_output=out;
}

GameReplay::~GameReplay()
{
   delete game;
}

void GameReplay::replayf()
{
    string mossa;
    ofstream fileo(file_output);
    ifstream filei (file_input);
    if (filei.is_open())
    {
        fileo<<*(game->mainboard)<<"\n";            //stampa la scacchiera nel file
        while ( getline (filei,mossa))
        {
            string piece="";
            if(mossa=="PATTA")
            {
                game->mainboard->set_draw();        //variabile draw diventa true
            }
            else
            {
                try
                {
                    try
                    {
                        game->is_turn->move(mossa);
                    }
                    catch(Illegal_move* i)
                    {
                        cout<<"MODIFICARE IL FILE DI INPUT"<<endl;  //messaggio di errore in output
                    }
                        
                }
                catch(Pawn* e)                      //se viene lanciato un Pawn* vuol dire che bisogna ricevere in input il carattere del pedone
                {
                    getline (filei,piece);                      
                    game->is_turn->promotion(e,piece[0]);       //richiamato la funzione promozione con il pedone e il carattere ricevuto in input
                }
                fileo<<*(game->mainboard)<<"\n";            //stampa la scacchiera nel file
                if(piece!="")                   //se c'è stata promozione
                    fileo<<piece[0]<<endl<<endl;        //stampa del carattere della pedina promossa nel file
                piece="";                   //imposta nuovamente piece a ""
                game->change_turn();
            }  
            game->addMove();            //incrementato il contatore delle mosse
            game->last_bs.push_back(game->mainboard->to_String());          //inserita la scacchiera nel vettore delle vecchie scacchiere
            if(game->is_finished()) break;              //se è finita la partita esce dal ciclo
        }
        fileo<<game->game_result()<<"\n";           //stampa il risultato nel file
        fileo.close();
        filei.close();
     }
}

void GameReplay::replayv()
{
    string mossa;
    string piece="";
    ifstream filei (file_input);
    if (filei.is_open())
    {
        while ( getline (filei,mossa) )
        {
            if(mossa=="PATTA")
            {
                game->mainboard->set_draw();            //variabile draw diventa true
                break;
            }
            try
            {
                try
                    {
                        game->is_turn->move(mossa);
                    }
                    catch(Illegal_move* i)
                    {
                        cout<<"MODIFICARE IL FILE DI INPUT"<<endl;  //messaggio di errore in output
                    }
            }
            catch(Pawn* e)      //se viene lanciato un Pawn* vuol dire che bisogna ricevere in input il carattere del pedone
            {
                getline (filei,piece);
                game->is_turn->promotion(e,piece[0]);       //richiamato la funzione promozione con il pedone e il carattere ricevuto in input
            }
            cout<<*(game->mainboard)<<endl;     //stampata in output la scacchiera
            if(piece!="")                      //se c'è stata promozione
                cout<<"\n"<<piece[0]<<"\n\n";        //stampa del carattere della pedina promossa
            piece="";                   //imposta nuovamente piece a ""
            this_thread::sleep_for(1000ms);
            game->change_turn();
            game->addMove();            //incrementato il contatore delle mosse
            game->last_bs.push_back(game->mainboard->to_String());          //inserita la scacchiera nel vettore delle vecchie scacchiere
            if(game->is_finished()) break;          //se è finita la partita esce dal ciclo
        }
        cout<<game->game_result()<<"\n";            //stampa in output il risultato
        filei.close();
     }
}
#endif
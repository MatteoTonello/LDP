//TONELLO MATTEO 2008596
#ifndef GAME_CPP
#define GAME_CPP
#include <iostream>
#include "Game.h"
#include "Player.h"
#include "Board.cpp"
#include "Illegal_move.cpp"
#include <stdio.h>
#include <fstream>
#include <stdlib.h>    
#include <time.h>
using namespace std;
Game::Game(char type)
{
    if(type=='p')   //Se la partita viene fatta da un giocatore
    {
        srand (time(NULL));
        //Scelta randomica del colore e assegnazione al giocatore e al computer
        int r = rand() % 2;
        if(r==0)
        {
            white_player=new Player('p');
            black_player=new Player('c');
        }
        else
        {
            white_player=new Player('c');
            black_player=new Player('p');
        }
        ofstream file(white_player->OFILE_DEFAULT);
        file.clear();
        file.close();
    }
    if(type=='c')   //Se la partita viene fatta dal computer
    {
        white_player=new Player('c');
        black_player=new Player('c');
        ofstream file(white_player->OFILE_DEFAULT);
	    file.clear();
	    file.close();
    }
    if(type=='r')   //Se la partita è un replay
    {
       white_player=new Player('p');
       white_player->replay=true;
       black_player=new Player('p');
       black_player->replay=true;
    }
    
    //Inizializzo le caratteristiche dei giocatori e del campo di gioco
    white_player->setcol('w');
    black_player->setcol('b');
	mainboard=new Board();
    white_player->boardgame=mainboard;
    black_player->boardgame=mainboard;
	is_turn=white_player;
    result="";
    nmosse=0;
	last_bs={mainboard->to_String()};
    pawns="PPPPPPPP                                pppppppp"; //Stringa che servirà per un controllo successivo
    fmcount=0;
    npieces=32;
    
}


Game::~Game()
{
   delete white_player;
   delete black_player;
   delete mainboard;
}
void Game::addMove()
{
   nmosse++;
}
string Game::game_result()
{
   return result;
}
void Game::startgame()
{
    
    if(white_player->human() || black_player->human())
        cout<<*mainboard<<endl;                 //Stampa la scacchiera
    if(white_player->human())
        cout<<"SEI IL GIOCATORE BIANCO"<<endl<<endl;
    if(black_player->human())
        cout<<"SEI IL GIOCATORE NERO"<<endl<<endl;
    srand(time(NULL));
    //Se la partita può continuare, fa eseguire la mossa e cambia il turno
    while(!(is_finished()))
    {
        player_move();
        change_turn();
    }
    cout<<*mainboard<<endl;
    cout<<result<<endl;
}
void Game::change_turn()
{
    if(is_turn==white_player)
        is_turn=black_player;
    else
        is_turn=white_player;
}
void Game::player_move()
{
    bool flag=true;
    while(flag)
    {
        //Prova a far eseguire una mossa finchè non è valida
        try
        {
            is_turn->move();
            flag=false;
        }
        catch(Illegal_move* e)  //Lancia l'eccezione se la mossa non è valida, stampa "MOSSA INVALIDA" e ricomincia il tentativo
        {
            if(is_turn->human()==true)
                cout<<"MOSSA INVALIDA"<<endl;
            flag=true;
        }
    }
    //Fatta la mossa, aggiorna i dati
    nmosse++;
	last_bs.push_back(mainboard->to_String());
    //cout<<*mainboard<<endl;
}
bool Game:: draw_for_ripetition()
{
	int counter=0;
    //Conta nell'array, il numero di caselle uguali all'attuale configurazione della scacchiera
	for(int i=0;i<last_bs.size();i++)
	{
		if((mainboard->to_String()).compare(last_bs[i])==0)
		{
				counter++;
		}
	}

    if(counter>=5) return true; //Patta obbligata a 5 corrispondenze
	if(counter>=3)  //A tre, il gioco chiede al giocatore se vuole imporre la patta
    {
        string decision;
        if(is_turn->human()==true && (white_player->human()==false || black_player->human()==false))
        {
            cout<<"POSIZIONE RIPETUTA "+counter<<" VOLTE\nVUOI DICHIARARE PATTA?";
            getline(cin,decision);
            if(decision=="SI")
                return true;
            else
                return false;
        }
    }
	return false;
}


bool Game::fifty_moves(){
	string s="";
    if(fmcount==50) return true;

    //Scorro tutta la scacchiera e ne estraggo il carattere delle pedine pedone. Altrimenti falso
    for(int i=1;i<7;i++)
    {
        for(int j=0;j<8;j++)
        {
            if(mainboard->gameboard[i][j]!=nullptr)
            {
                if(mainboard->gameboard[i][j]->cpiece()=='p' || mainboard->gameboard[i][j]->cpiece()=='P')
                {
                    s=s+mainboard->gameboard[i][j]->cpiece();
                }
                else
                {
                    s=s+" ";
                }
            }
            else
            {
                s=s+" ";
            }
        }
    }

    int n=mainboard->whites.size()+mainboard->blacks.size();
    //Se nessuna mossa è stata mangiata e nessun pedone è stato mosso, aumenta i counter
    if(s.compare(pawns)==0 && n==npieces){
        fmcount++;
    }
    else{
        //Azzero i counter
        pawns=s;
        npieces=n;
        fmcount=0;
    }
    return false;
}

bool Game::is_finished()
{
    //Controllo tutti i metodi decretanti la fine della partita
    bool mate=0;
    if(mainboard->get_draw())
    {
        result="PATTA PER DECISIONE";
        return true;
    }
    if(nmosse>=150)
    {
        result="PATTA,LIMITE 150 MOSSE";
        return true;
    }
    if(mainboard->cant_be_mate())
    {
        result="PATTA PER PEZZI INSUFFICIENTI";
        return true;
    }
    if(mainboard->is_draw(is_turn->col()))
    {
        result="PATTA PER STALLO";
        return true;
    }
    if(is_turn==white_player)
    {
        mate=mainboard->is_check_mate('w');
        if(mate==1)
        {
            result="VINCITORE NERO";
            return true;
        }
    }
    else
    {
        mate=mainboard->is_check_mate('b');
        if(mate==1)
        {
            result="VINCITORE BIANCO";
            return true;
        }
        
    }
	if(draw_for_ripetition())
	{
		result="PATTA PER RIPETIZIONE DI MOSSE";
		return true;
	}
    if(fifty_moves())
    {
        result="PATTA, 50 MOSSE SENZA MUOVERE PEDONE O CATTURARE PEZZI";
        return true;
    }
    return false;
}
#endif
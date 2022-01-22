#ifndef GAMEREPLAY_CPP
#define GAMEREPLAY_CPP
#include "GameReplay.h"
#include "Piece.h"
#include "windows.h"
#include "Board.cpp"
#include <iostream>
#include <fstream>
using namespace std;

GameReplay::GameReplay(string in)
{
    game=new Game('r');
    file_input=in;
    file_output="";
}
GameReplay::GameReplay(string in,string out)
{
    game=new Game('r');
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
    bool flag=false;
    ofstream fileo(file_output);
    ifstream filei (file_input);
    if (filei.is_open())
    {
        fileo<<*(game->mainboard)<<"\n";
        while ( getline (filei,mossa))
        {
            string piece;
            if(mossa=="XX XX")  fileo<<*(game->mainboard);
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
                      cout<<"MODIFICARE IL FILE DI INPUT"<<endl;
                      cout<<mossa;
                   }
                     
                }
                catch(Pawn* e)
                {
                    getline (filei,piece);
                    game->is_turn->promotion(e,piece[0]);
                    flag=true;
                }
                fileo<<*(game->mainboard)<<"\n";
                flag=false;
                game->change_turn();
            }
            game->addMove();
            game->last_bs.push_back(game->mainboard->to_String());
            if(game->is_finished()) break;
        }
        fileo<<game->game_result()<<"\n";
        fileo.close();
        filei.close();
     }
}
void GameReplay::replayv()
{
    string mossa;
    string piece;
    bool flag;
    ifstream filei (file_input);
    if (filei.is_open())
    {
        while ( getline (filei,mossa) )
        {
            if(mossa=="-") break;
            if(mossa=="XX XX")  cout<<*(game->mainboard);
            else
            {
                try
                {
                    game->is_turn->move(mossa);
                }
                catch(Pawn* e)
                {
                    getline (filei,piece);
                    game->is_turn->promotion(e,piece[0]);
                    flag=true;
                }
                cout<<*(game->mainboard)<<endl;
                if(flag)
                    cout<<piece[0]<<"\n\n";
                flag=false;
                //Sleep(1000);
                game->change_turn();
            }
            game->addMove();
            game->last_bs.push_back(game->mainboard->to_String());
            if(game->is_finished()) break;
        }
        cout<<game->game_result()<<"\n";
        filei.close();
     }
}
#endif
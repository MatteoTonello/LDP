#include "GameReplay.h"
#include "Piece.h"
#include <iostream>
#include <fstream>
using namespace std;

GameReplay::GameReplay(string in)
{
    Player* p1=new Player('p');
    Player* p2=new Player('p');
    p1->replay=true;
    p2->replay=true;
    game=new Game(p1,p2);
    file_input=in;
    file_output="";
}
GameReplay::GameReplay(string in,string out)
{
    Player* p1=new Player('p');
    Player* p2=new Player('p');
    p1->replay=true;
    p2->replay=true;
    game=new Game(p1,p2);
    file_input=in;
    file_output=out;
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
            if(mossa=="-") break;
            if(mossa=="XX XX")  fileo<<*(game->mainboard);
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
                fileo<<*(game->mainboard)<<"\n";
                if(flag)
                    fileo<<piece[0]<<"\n\n";
                flag=false;
                game->change_turn();
            }
            game->nmosse++;
            game->last_bs.push_back(game->mainboard->to_String());
            if(game->is_finished()) break;
        }
        fileo<<game->result<<"\n";
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
                if(flag)
                    cout<<piece[0]<<"\n\n";
                flag=false;
                game->change_turn();
            }
            game->nmosse++;
            game->last_bs.push_back(game->mainboard->to_String());
            if(game->is_finished()) break;
        }
        cout<<game->result<<"\n";
        filei.close();
     }
}
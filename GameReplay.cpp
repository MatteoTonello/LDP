#include "GameReplay.h"
#include "Piece.h"
#include <iostream>
#include <fstream>
using namespace std;

GameReplay::GameReplay(string in)
{
    Player* p1=new Player('p');
    Player* p2=new Player('p');
    game=new Game(p1,p2);
    file_input=in;
    file_output="";
}
GameReplay::GameReplay(string in,string out)
{
    Player* p1=new Player('p');
    Player* p2=new Player('p');
    game=new Game(p1,p2);
    file_input=in;
    file_output=out;
}
void GameReplay::replayf()
{
    string mossa;
    ofstream fileo(file_output);
    ifstream filei (file_input);
    if (filei.is_open())
    {
        fileo<<*(game->mainboard)<<"\n";
        while ( getline (filei,mossa) )
        {
            if(mossa=="-") break;
            if(mossa=="XX XX")  cout<<*(game->mainboard);
            else
            {
                game->is_turn->move(mossa);
                fileo<<*(game->mainboard)<<"\n";
                game->change_turn();
            }
        }
        fileo.close();
        filei.close();
     }
}
void GameReplay::replayv()
{
    string mossa;
    ifstream filei (file_input);
    if (filei.is_open())
    {
        while ( getline (filei,mossa) )
        {
            if(mossa=="-") break;
            if(mossa=="XX XX")  cout<<*(game->mainboard);
            else
            {
                game->is_turn->move(mossa);
                cout<<*(game->mainboard);
                game->change_turn();
            }
        }
        filei.close();
     }
}
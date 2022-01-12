#include "Replay.h"
#include "Piece.h"
#include <iostream>
#include <fstream>
using namespace std;

Replay::Replay(string filename)
{
    Player* p1=new Player('p');
    Player* p2=new Player('p');
    game=new Game(p1,p2);
    file_name=filename;
}
void Replay::replay()
{
    string mossa;
    ifstream myfile (file_name);
    if (myfile.is_open())
    {
        while ( getline (myfile,mossa) )
        {
            if(mossa=="XX XX")  cout<<*(game->mainboard);
            else
            {
            game->is_turn->move(mossa);
            cout<<*(game->mainboard);
            game->change_turn();
            for(int i=0;i<game->mainboard->whites.size();i++)
                cout<<game->mainboard->whites[i]->piece;
            cout<<endl;
            for(int i=0;i<game->mainboard->blacks.size();i++)
                 cout<<game->mainboard->blacks[i]->piece;
            cout<<endl;
            }
        }
    myfile.close();
     }
}
#include <vector>
#include <array>
enum PlayerPiece
{
    Empty = 0,
    PlayerOne = 1,
    PlayerTwo = 2,
};

using namespace std;
struct Board
{
    array<PlayerPiece, 42> Board = {Empty}; // Board as a 1d array
    array<short int, 7> BoardTop = {5,5,5,5,5,5,5};

    //Insert Piece. Return True if success. Else return false
    bool DropPiece(int x, PlayerPiece player)     
    {
        if(BoardTop[x]!= -1){
            Board[Conv2dTo1d(x, BoardTop[x])] = player;
            BoardTop[x]--;
            return true;
        }
        else return false;
    } 

    int Conv2dTo1d(int x, int y)
    {
        return x + y*7 ; 
    }

    bool CheckWin()
    {
        return false;
    }

    void DisplayBoard()
    {
        return;
    }


};

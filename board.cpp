#include <vector>
#include <array>
#include <iostream>

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

    bool CheckWin(int xPos, PlayerPiece player)
    {
        int yPos = BoardTop[xPos];

        // horizontal
        for(int i = xPos>=4?xPos-3:0; i!= 7 || i!= (xPos + 1); ++i )
        {
            if(Board[Conv2dTo1d(i,yPos)] == Board[Conv2dTo1d(i+1,yPos)] && Board[Conv2dTo1d(i+1,yPos)] == Board[Conv2dTo1d(i+2,yPos)] 
            && Board[Conv2dTo1d(i+2,yPos)] == Board[Conv2dTo1d(i+3,yPos)] && Board[Conv2dTo1d(i+3,yPos)] == Board[Conv2dTo1d(i+4,yPos)])
            {
                return true;
            } 
        }

        // verticle
        if(yPos <=2) //if smaller than 2, than it cant be a complete verticle line of 4
        {
            if(Board[Conv2dTo1d(xPos,yPos)] ==Board[Conv2dTo1d(xPos,yPos+1)] && Board[Conv2dTo1d(xPos,yPos+1)] ==Board[Conv2dTo1d(xPos,yPos+2)] 
            && Board[Conv2dTo1d(xPos+2,yPos)] ==Board[Conv2dTo1d(xPos,yPos+3)] && Board[Conv2dTo1d(xPos,yPos+3)] ==Board[Conv2dTo1d(xPos,yPos+4)])
            {
                return true;
            }
        }
        // diag upwards
        
        // diag downwards 


        return false;
    }

    void DisplayBoard()
    {
        for (int y = 0; y != 6; ++y)
        {
            for (int x = 0; x != 7; x++)
            {
                cout << Board[Conv2dTo1d(x,y)] << " ";
            }
            cout << endl;
        }
    }


};

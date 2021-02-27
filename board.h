#pragma once

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
    array<PlayerPiece, 42> Board;
    array<short int, 7> BoardTop;

    //Insert Piece. Return True if success. Else return false
    bool DropPiece(int x, PlayerPiece player);

    int Conv2dTo1d(int x, int y);

    bool CheckWin(){}

    void DisplayBoard(){}


};


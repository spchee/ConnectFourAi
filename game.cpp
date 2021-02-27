#pragma once
#include "board.h"

class ConnectFourGame
{
    bool ai;
    Board board;
    ConnectFourGame(bool AI)
    {
        ai = AI;
    }

    bool PlayerTurn(PlayerPiece player)
    {
        return true;
    }

    void End(PlayerPiece player)
    {
        return;
    }


};


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

    bool player_turn(PlayerPiece player)
    {
        return true;
    }

    void end_game(PlayerPiece player)
    {
        return;
    }


};


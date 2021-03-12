#pragma once

#include <array>
#include <vector>
enum PlayerPiece
{
  Empty = 0,
  PlayerOne = 1,
  PlayerTwo = 2,
};

using namespace std;
struct Board
{
  array<PlayerPiece, 42> board;
  array<short int, 7> BoardTop;

  // Insert Piece. Return True if success. Else return false
  bool drop_piece(int x, PlayerPiece player);

  int flatten(int x, int y);

  bool check_win(int xPos, PlayerPiece player);

  void display_board();

  Board *deep_copy();
};

using namespace std;

#include "board.h"

#include <random>

class ZorbistHashing
{

  array<array<unsigned int, 2>, 42> ZorbistTable;

public:
  ZorbistHashing();

  unsigned int get_zorbist_hash(PlayerPiece player, int x, int y, unsigned int hash);
};
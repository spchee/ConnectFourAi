using namespace std;

#include "board.h"

#include <random>

class ZorbistHashing
{

  array<array<unsigned int, 2>, 42> ZorbistTable = {};

public:
  ZorbistHashing()
  {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(1, 4294967295);

    // generates a random number for each piece in each position
    for(int i = 0; i != 42; ++i)
    {
      ZorbistTable[i][0] = distrib(gen);
      ZorbistTable[i][1] = distrib(gen);
    }
  }
  unsigned int get_zorbist_hash(PlayerPiece player, int x, int y, unsigned int hash)
  {

    return ZorbistTable[x + y * 7][player] ^ hash;
  }
};
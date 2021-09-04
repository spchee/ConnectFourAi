#include "board.h"

struct Node
{

  // TODO
  // change ChildNodes to a set or map rather than a vector
  vector<Node *> ChildNodes = {};  // Pointers to each child node
  vector<Node *> ParentNodes = {}; // Pointers to all parent nodes
  unsigned int Hash;

  short int wins = 0;
  short int visits = 0;
  bool expanded = false;
  short int depth;
  char move;
  PlayerPiece PlayerTurn;

  Node(Node *parent, int move)
  {
    ParentNodes.push_back(parent);
    depth = parent->depth + 1;
    PlayerTurn = ((parent->PlayerTurn) == PlayerOne) ? PlayerTwo : PlayerOne;
  }
  /*
  Node* deep_copy()
  {
      Node copy = Node(ParentNodes[0]);

      for(int i = 1; i != ParentNodes.size(); ++i)
          copy.ParentNodes.push_back(ParentNodes[i]);

      for(int i = 0; i != ChildNodes.size(); ++i)
          copy.ChildNodes.push_back(ChildNodes[i]);

      copy.wins = wins;
      copy.visits = visits;
      copy.Hash = Hash;

  }
  */
};
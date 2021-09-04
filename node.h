#include "board.h"
#pragma once

struct Node
{

  // TODO
  // change ChildNodes to a set or map rather than a vector
  vector<Node *> ChildNodes;
  vector<Node *> ParentNodes;
  unsigned int Hash;

  short int wins;
  short int visits;
  bool expanded;
  short int depth;
  char move;
  PlayerPiece PlayerTurn;

  Node(Node *parent, int move);
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
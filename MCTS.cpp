using namespace std;
#include "TranspositionTable.h"
#include "ZorbistHashing.h"
#include "board.h"
#include "node.h"

#include <algorithm>
#include <array>
#include <random>
#include <unordered_map>
#include <vector>

#define EXPLORATIONCONST 1.414214

class MCTS
{
  Node RootNode = Node(nullptr, 0);
  Board RootBoard = Board();

  Node CurrentNode = RootNode;
  Board CurrentBoard = *RootBoard.deep_copy();

  TranspositionTable TransTable = TranspositionTable();

  ZorbistHashing HashGen = ZorbistHashing();
  MCTS()
  {
    RootNode.Hash = 0;
  }

  vector<int> get_moves()
  {
    vector<int> ValidMoves = {};
    for(int i = 0; i != 7; ++i)
    {
      if(CurrentBoard.BoardTop[i] != -1)
      {
        ValidMoves.push_back(i);
      }
    }
    return ValidMoves;
  }

  // calculates the UCT score of a particular node
  double calc_UCT(Node node)
  {
    /*  UCT normally only works for trees where nodes have a single parent,
        so I'm not sure if totally all of the parent visits up will work    */

    int ParentVisits = 0;
    for(int i = 0; i != node.ParentNodes.size(); ++i)
    {
      ParentVisits += node.ParentNodes[i]->visits;
    }

    double UCT = node.wins / node.visits + EXPLORATIONCONST * sqrt(log(ParentVisits) / node.visits);

    return UCT;
  }

  void selection()
  {
    double MaxUCT;
    double uct;
    Node *NextNode;

    while(CurrentNode.expanded = true)
    {
      MaxUCT = 0;

      for(Node *pNode: CurrentNode.ChildNodes)
      {
        uct = calc_UCT(*pNode);
        if(uct > MaxUCT)
        {
          NextNode = pNode;
          MaxUCT = uct;
        }
      }

      CurrentBoard.drop_piece(NextNode->move, NextNode->PlayerTurn);
      CurrentNode = *NextNode;
    }

    /*
   double max_uct = 0;
   double uct;
   Node* node;
   for(pair<unsigned int, Node*> NodePair: TransTable.table)
   {
       uct = calc_UCT((*NodePair.second));
       if ( uct > max_uct)
       {
           node = NodePair.second;
           max_uct = uct;
       }
   }

   return node;
    */
  }

  // will get all valid movies and expand each of them
  void explansion()
  {

    vector<int> ValidMoves = get_moves();
    unsigned int NewHash;
    Node *pNewChild;

    // Loops through each valid move and adds it to ChildNodes attribute
    for(int move: ValidMoves)
    {
      NewHash = HashGen.get_zorbist_hash((CurrentNode.PlayerTurn == PlayerOne) ? PlayerTwo : PlayerOne, move, CurrentBoard.BoardTop[move],
                                         CurrentNode.Hash);
      pNewChild = TransTable.create_node(NewHash, &CurrentNode, (char) move);

      // Check if the node already exists as a child node before adding.
      if(find(CurrentNode.ChildNodes.begin(), CurrentNode.ChildNodes.end(), pNewChild) == CurrentNode.ChildNodes.end())
      {
        CurrentNode.ChildNodes.push_back(pNewChild);
      }
    }

    CurrentNode.expanded = true;
  }

  PlayerPiece simulation()
  {

    bool complete;
    int move;
    unsigned int NewHash;
    Node *pNewChild;
    Board SelectedNodeBoard = *CurrentBoard.deep_copy();

    // TODO
    // Make it so it changes the board state after changing current node
    // Implement backpropagation after each child finishes exploring
    for(Node *pChildNode: CurrentNode.ChildNodes) // not sure if this will work.
    {
      CurrentNode = *pChildNode;
      complete = false;
      while(!complete)
      {
        vector<int> ValidMoves = get_moves();

        // if there are no valid moves, complete
        if(ValidMoves.size() == 0)
        {
          complete = true;
        }

        else
        {

          // randomly selects a valid move
          random_device rd;
          mt19937 gen(rd());
          uniform_int_distribution<> distrib(0, ValidMoves.size() - 1);
          move = distrib(gen);

          // Gens zorbist hash to adds it to the transposition table
          NewHash = HashGen.get_zorbist_hash((CurrentNode.PlayerTurn == PlayerOne) ? PlayerTwo : PlayerOne, move,
                                             CurrentBoard.BoardTop[move], CurrentNode.Hash);
          pNewChild = TransTable.create_node(NewHash, &CurrentNode, (char) move);

          // Add to ChildNodes if it isn't already there.
          if(find(CurrentNode.ChildNodes.begin(), CurrentNode.ChildNodes.end(), pNewChild) == CurrentNode.ChildNodes.end())
          {
            CurrentNode.ChildNodes.push_back(pNewChild);
          }

          CurrentNode = *pNewChild;
          CurrentBoard.drop_piece(CurrentNode.move, CurrentNode.PlayerTurn);

          if(CurrentBoard.check_win(CurrentNode.move, CurrentNode.PlayerTurn) ||
             equal(CurrentBoard.BoardTop.begin() + 1, CurrentBoard.BoardTop.end(), CurrentBoard.BoardTop.begin()))
            complete = true;
        }
      }
      // will randomly play until game is complete
    }
  }
  bool backpropagation(Node *pLeafNode, PlayerPiece winner)
  {
    while(pLeafNode != &RootNode)
    {
    }
  }

  void play_move()
  {
    // change root node
    // players turn
    // delete all nodes with a depth less than root to free up memory.
  }
};
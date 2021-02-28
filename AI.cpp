using namespace std;
#include <array>
#include <vector>
#include <unordered_map>
#include <random>
#include "board.h"

#define EXPLORATIONCONST = 1.414214
struct Node
{
    Board NodeBoard;
    vector<Node*> ChildNodes; // Pointer to each child node
    vector<Node*> ParentNodes; //pointer to all parent nodes
    unsigned int Hash;

    int wins = 0;
    int simulations = 0;
    
    Node(Node* parent/*, PlayerPiece player, int dropPos*/)
    {
        ParentNodes.push_back(parent);
        //NodeBoard = clone Need to figure out how to do a deep copy.
    }
};

struct NodeMap // contains map of all nodes which have been explored
{
    unordered_map<unsigned int, Node*> NodeMap = {};

    //Creates new node if hasn't been explored.
    Node* CreateNewNode(unsigned int hash, Node* parent)
    {
        if (NodeMap.find(hash) == NodeMap.end())
        {
            NodeMap[hash] = new Node(parent);
        }
        return NodeMap[hash];
    }
};

class ZorbistHashing
{
    
    array<array<unsigned int,2>,42> ZorbistTable = {};
    ZorbistHashing()
    {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distrib(1,4294967295);
        
        //generates a random number for each piece in each position
        for(int i = 0; i!= 42; ++i) 
        {
             ZorbistTable[i][0] = distrib(gen);
             ZorbistTable[i][1] = distrib(gen);
        }
    }

    unsigned int ReturnZorbistHash(PlayerPiece player, int x, int y, unsigned int hash)
    {
        
        return ZorbistTable[x + y*7][player]^hash;
    }
};


class MCTS
{
    Node RootNode = Node(nullptr);
    MCTS()
    {
        RootNode.Hash = 0;
    }

    int GetPossibleMoves()
    {

    }

    Node* Selection()
    {

    }

    PlayerPiece Simulation()
    {

    }

    bool Backpropagation()
    {

    }

};
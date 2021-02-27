using namespace std;
#include <array>
#include <vector>
#include <unordered_map>
#include <random>
#include "board.h"
struct Node
{
    vector<Node*> ChildNodes; // Pointer to each child node
    vector<Node*> ParentNodes; //pointer to all parent nodes
    unsigned int Hash;
    Node(Node* parent)
    {
        ParentNodes.push_back(parent);
    }
};

struct NodeMap
{
    unordered_map<unsigned int, Node*> NodeMap = {};

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
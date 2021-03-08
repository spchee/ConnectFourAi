using namespace std;
#include <array>
#include <vector>
#include <unordered_map>
#include <random>
#include "board.h"

#define EXPLORATIONCONST 1.414214
struct Node
{
    Board NodeBoard;
    vector<Node*> ChildNodes; // Pointers to each child node
    vector<Node*> ParentNodes; // Pointers to all parent nodes
    unsigned int Hash;

    int wins = 0;
    int visits = 0;
    PlayerPiece PlayerTurn;
    
    Node(Node* parent)
    {
        ParentNodes.push_back(parent);
        PlayerTurn = (parent->PlayerTurn)==PlayerOne?PlayerTwo:PlayerOne;

    }
};

struct TranspositionTable // contains map of all nodes which have been explored
{
    unordered_map<unsigned int, Node*> table = {};

    //Creates new node if hasn't been explored.
    Node* create_node(unsigned int hash, Node* parent)
    {
        if (table.find(hash) == table.end())
        {
            table[hash] = new Node(parent);
        }
        return table[hash];
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
    public:
    unsigned int get_zorbist_hash(PlayerPiece player, int x, int y, unsigned int hash)
    {
        
        return ZorbistTable[x + y*7][player]^hash;
    }
};


class MCTS
{
    Node RootNode = Node(nullptr);
    Board RootBoard = Board();

    Node CurrentNode = RootNode;
    Board CurrentBoard = RootBoard;
    
    MCTS()
    {
        RootNode.Hash = 0;
    }

    

    vector<int> get_moves()
    {
        vector<int> ValidMoves = {};
        for(int i = 0; i!=7; ++i)
        {
            if(CurrentBoard.BoardTop[i] != -1)
            {
                ValidMoves.push_back(i);
            }
        }
        return ValidMoves;

    }

    double calc_UCT(Node node)
    {
        /*  UCT normally only works for trees where nodes have a single parent, 
            so I'm not sure if totally all of the parent visits up will work    */

        int ParentVisits = 0; 
        for(int i = 0; i != node.ParentNodes.size(); ++i) 
        {
            ParentVisits += node.ParentNodes[i] -> visits;
        }

        double UCT = node.wins / node.visits + EXPLORATIONCONST * sqrt(log(ParentVisits)/ node.visits);

        return UCT;
    }

    Node* selection()
    {


    }


    PlayerPiece simulation()
    {

    }

    bool backpropagation()
    {

    }

    void play_move()
    {
        //change root node
        //playesr turn
    }

};
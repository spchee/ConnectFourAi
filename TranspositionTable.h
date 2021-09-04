#include "node.h"

#include <unordered_map>
using namespace std;

struct TranspositionTable // contains map of all nodes which have been explored
{
  unordered_map<unsigned int, Node *> table;

  // Creates new node if hasn't been explored.
  Node *create_node(unsigned int hash, Node *parent, char move);
};
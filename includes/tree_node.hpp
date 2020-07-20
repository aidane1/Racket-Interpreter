#ifndef TREE_NODE
#define TREE_NODE

#include "token.hpp"

class ASTTreeNode
{

private:
public:

Token *token;
std::vector<ASTTreeNode *> children;
ASTTreeNode *parent;

};

#endif
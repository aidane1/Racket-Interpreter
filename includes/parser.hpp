#ifndef PARSER
#define PARSER

#include "token.hpp"
#include <vector>
#include <string>

class ASTTreeNode
{
private:
public:
	Token *token;
	std::vector<ASTTreeNode *> children;
	ASTTreeNode *parent;

	ASTTreeNode();
};

class Parser
{
private:
public:
	ASTTreeNode *parse(std::vector<Token *> tokens);
	void dump(ASTTreeNode *root, int depth = 0);
};

#endif
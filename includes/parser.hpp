#ifndef PARSER
#define PARSER

#include <vector>
#include "token.hpp"
#include "tree_node.hpp"

class Parser
{
private:
public:
	std::vector<Token *> generate_reverse_polish_notion(std::vector<Token *> tokens);

	ASTTreeNode *generate_abstract_syntax_tree(std::vector<Token *> tokens);

	void dump(ASTTreeNode *node, int depth = 0);
};

#endif
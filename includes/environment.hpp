#ifndef ENVIRONMENT
#define ENVIRONMENT

#include <vector>
#include <map>
// #include <hash_map>

#include "parser.hpp"
#include "token.hpp"

class Environment
{
private:
	std::map<std::string, ASTTreeNode *> definitions;
	std::map<std::string, Token *> arg_map;

	bool verbose = true;

public:
	Environment(bool verbose = true);

	void evaluate(ASTTreeNode *root);

	Token *evaluate_node(ASTTreeNode *node);
	Token *evaluate_variable(Token *token);

	std::vector<Token *> get_rest(std::vector<ASTTreeNode *> rest);
	std::vector<Token *> get_all(std::vector<ASTTreeNode *> all);
};

#endif
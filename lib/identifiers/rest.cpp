#include "ast_evaluation.hpp"

Token *ASTEvaluation::evaluate_rest(ASTTreeNode *node, std::vector<Token *> args)
{
	LinkedList<Token *> *new_list = args[0]->stored_value.list.rest();
	Token *new_token = new Token("list", 5, list);
	new_token->stored_value.list = *new_list;
	return new_token;
}
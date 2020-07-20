#include "ast_evaluation.hpp"

Token *ASTEvaluation::evaluate_first(ASTTreeNode *node, std::vector<Token *> args)
{
	Token **new_token = args[0]->stored_value.list.first();
	if (new_token == nullptr)
	{
		return node->token;
	}
	else
	{
		return *new_token;
	}
}
#include "ast_evaluation.hpp"

Token *ASTEvaluation::evaluate_empty_q(ASTTreeNode *node, std::vector<Token *> args)
{
	if (args[0]->stored_value.list.get_length() == 0)
	{
		return new Token("#t", 1, boolean);
	}
	return new Token("#f", 1, boolean);
}
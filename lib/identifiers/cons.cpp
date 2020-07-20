#include "ast_evaluation.hpp"

Token *ASTEvaluation::evaluate_cons(ASTTreeNode *node, std::vector<Token *> args)
{
	Token *new_token = new Token("list", 5, list);

	new_token->stored_value.list = args[1]->stored_value.list.prepend(args[0]);

	return new_token;
}
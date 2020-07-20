#include "ast_evaluation.hpp"

Token *ASTEvaluation::evaluate_list(ASTTreeNode *node, std::vector<Token *> args)
{
	Token *new_token = new Token("list", 5, list);
	for (int i = 0; i < args.size(); i++)
	{
		new_token->stored_value.list.append(args[i]);
	}
	return new_token;
}
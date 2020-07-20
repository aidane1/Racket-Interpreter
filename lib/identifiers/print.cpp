#include "ast_evaluation.hpp"

Token *ASTEvaluation::evaluate_print(ASTTreeNode *node, std::vector<Token *> args)
{
	for (int i = 0; i < args.size(); i++)
	{
		std::cout << Token::get_value(args[i]) << " ";
	}
	std::cout << "\n";
	return node->token;
}
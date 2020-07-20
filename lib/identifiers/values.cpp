#include "ast_evaluation.hpp"

Token *ASTEvaluation::evaluate_values(ASTTreeNode *node, std::vector<Token *> args, Environment *enviroment, std::map<std::string, Token *> arg_map)
{
	for (int i = 0; i < node->children.size(); i++)
	{
		if (i == node->children.size() - 1)
		{
			return enviroment->evaluate_ast(node->children[i], arg_map);
		}
		else
		{
			enviroment->evaluate_ast(node->children[i], arg_map);
		}
	}
	return node->token;
}

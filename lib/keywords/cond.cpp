#include "ast_evaluation.hpp"

Token *ASTEvaluation::evaluate_cond(ASTTreeNode *node, Environment *environment, std::map<std::string, Token *> arg_map)
{
	for (int i = 0; i < node->children.size(); i++)
	{

		ASTTreeNode *first = node->children[i]->children[0];
		ASTTreeNode *second = node->children[i]->children[1];

		if (first->token->value == "else")
		{
			return environment->evaluate_ast(second, arg_map);
		}
		else
		{

			Token *current_expression = environment->evaluate_ast(first, arg_map);

			switch (current_expression->type)
			{
			case boolean:
				if (current_expression->stored_value.boolean)
				{
					return environment->evaluate_ast(second, arg_map);
				}
				break;
			case lang_int:
				if (current_expression->stored_value.lang_int)
				{
					return environment->evaluate_ast(second, arg_map);
				}
			default:
				break;
			}
		}
	}
	return node->token;
}
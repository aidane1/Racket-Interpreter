#include "ast_evaluation.hpp"

Token *ASTEvaluation::evaluate_and(ASTTreeNode *node, Environment *environment, std::map<std::string, Token *> arg_map)
{
	for (int i = 0; i < node->children.size(); i++)
	{
		Token *current_val = environment->evaluate_ast(node->children[i], arg_map);
		bool evaluation = true;

		switch (current_val->type)
		{
		case boolean:
			if (!current_val->stored_value.boolean)
			{
				evaluation = false;
			}
			break;
		case lang_int:
			if (!current_val->stored_value.lang_int)
			{
				evaluation = false;
			}
		default:
			break;
		}
		if (!evaluation)
		{
			Token *new_token = new Token("#f", 1, boolean);
			return new_token;
		}
	}
	Token *new_token = new Token("#t", 1, boolean);
	return new_token;
}
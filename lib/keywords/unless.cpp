#include "ast_evaluation.hpp"

Token *ASTEvaluation::evaluate_unless(ASTTreeNode *node, Environment *environment, std::map<std::string, Token *> arg_map)
{
	Token *test_expression = environment->evaluate_ast(node->children[0], arg_map);

	switch (test_expression->type)
	{
	case boolean:
		if (test_expression->stored_value.boolean)
		{
			return environment->evaluate_ast(node->children[2], arg_map);
		}
		else
		{
			return environment->evaluate_ast(node->children[1], arg_map);
		}
		break;
	case lang_int:
		if (test_expression->stored_value.lang_int)
		{
			return environment->evaluate_ast(node->children[2], arg_map);
		}
		else
		{
			return environment->evaluate_ast(node->children[1], arg_map);
		}
	default:
		return environment->evaluate_ast(node->children[2], arg_map);
		break;
	}
}
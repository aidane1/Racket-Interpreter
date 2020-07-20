#include "ast_evaluation.hpp"

Token *ASTEvaluation::evaluate_greater_than(ASTTreeNode *node,std::vector<Token *> args)
{
	if (args.size() == 2)
	{

		if (
			((args[0]->type == lang_int) || (args[0]->type == lang_float)) &&
			((args[1]->type == lang_int) || (args[1]->type == lang_float)))
		{

			bool comparison = (args[0]->type == lang_float ? args[0]->stored_value.lang_float : args[0]->stored_value.lang_int) > (args[1]->type == lang_float ? args[1]->stored_value.lang_float : args[1]->stored_value.lang_int);

			Token *new_token = new Token(comparison ? "#t" : "#f",
										 4, boolean);

			return new_token;
		}
		else
		{
			// type error
			return node->token;
		}
	}
	else
	{
		// argument error
		return node->token;
	}
}
#include "ast_evaluation.hpp"
#include "environment.hpp"

Token *ASTEvaluation::evaluate_plus(ASTTreeNode *node, std::vector<Token *> args)
{
	TokenType type = lang_int;
	float accumulator = 0;
	int precedence = -1;
	for (int i = 0; i < args.size(); i++)
	{
		if (ASTEvaluation::check_type(args[i], std::vector<TokenType>{lang_int, lang_float}))
		{
			if (args[i]->precedence > precedence)
			{
				precedence = args[i]->precedence;
			}

			if (args[i]->type == lang_int)
			{
				accumulator += args[i]->stored_value.lang_int;
			}
			else if (args[i]->type == lang_float)
			{
				type = lang_float;
				accumulator += args[i]->stored_value.lang_float;
			}
		}
		else
		{
			Environment::error_message(type_error, Environment::construct_type_error(TokenTypes::get(args[i]->type), args[i]->value, "number"), args[i]->line, args[i]->character);
		}
	}

	std::string new_value;

	if (type == lang_int)
	{
		int new_int = static_cast<int>(accumulator);
		new_value = std::to_string(new_int);
	}
	else
	{
		new_value = std::to_string(accumulator);
	}

	Token *new_token = new Token(new_value,
								 precedence, type);
	new_token->line = node->token->line;
	new_token->character = node->token->character;
	return new_token;
}
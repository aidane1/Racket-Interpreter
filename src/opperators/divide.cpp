#include "evaluation.hpp"

#include "token.hpp"
#include <iostream>

Token *Evaluation::evaluate_divide(std::vector<Token *> args)
{
	float value = 0;

	if (args[0]->type == lang_int)
	{
		value = args[0]->stored_value.lang_int;
	}
	else
	{
		value = args[0]->stored_value.lang_float;
	}

	for (int i = 1; i < args.size(); i++)
	{
		if (args[i]->type == lang_int)
		{
			value /= args[i]->stored_value.lang_int;
		}
		else
		{
			value /= args[i]->stored_value.lang_float;
		}
	}

	TokenType type = lang_int;

	for (int i = 0; i < args.size(); i++)
	{
		if (args[i]->type == lang_float)
		{
			type = lang_float;
		}
	}

	return new Token(type == lang_int ? std::to_string((int)value) : std::to_string(value), type);
}
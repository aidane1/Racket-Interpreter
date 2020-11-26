#include "evaluation.hpp"

#include "token.hpp"
#include <iostream>

Token *Evaluation::evaluate_string_equal_q(std::vector<Token *> args)
{
	bool return_val = true;

	std::string current = args[0]->stored_value.string;

	for (int i = 1; i < args.size(); i++)
	{
		if (!(current == args[i]->stored_value.string))
		{
			return_val = false;
		}
	}

	return new Token(return_val ? "#t" : "#f", boolean);
}
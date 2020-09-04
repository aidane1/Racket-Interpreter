#include "evaluation.hpp"

#include "token.hpp"
#include <iostream>

Token *Evaluation::evaluate_equal_q(std::vector<Token *> args)
{
	bool equal = true;

	for (int i = 0; i < args.size() - 1; i++)
	{
		if (Token::get_value(args[i]) == Token::get_value(args[i + 1]))
		{
		}
		else
		{
			equal = false;
		}
	}
	return new Token(equal ? "#t" : "#f", boolean);
}
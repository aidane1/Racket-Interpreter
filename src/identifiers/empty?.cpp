#include "evaluation.hpp"

#include "token.hpp"
#include <iostream>

Token *Evaluation::evaluate_empty_q(std::vector<Token *> args)
{
	if (args[0]->stored_value.list.get_length() == 0)
	{
		return new Token("#t", boolean);
	}
	return new Token("#f", boolean);
}
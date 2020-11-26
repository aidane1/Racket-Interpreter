#include "evaluation.hpp"

#include "token.hpp"
#include <iostream>
#include <math.h>

Token *Evaluation::evaluate_sqr(std::vector<Token *> args)
{

	float start_val;

	TokenType type = args[0]->type;

	if (args[0]->type == lang_int)
	{
		start_val = (float)args[0]->stored_value.lang_int;
	}
	else
	{
		start_val = (float)args[0]->stored_value.lang_float;
	}

	start_val = start_val * start_val;

	return new Token(type == lang_int ? std::to_string((int)start_val) : std::to_string(start_val), type);
}
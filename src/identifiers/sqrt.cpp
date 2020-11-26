#include "evaluation.hpp"

#include "token.hpp"
#include <iostream>
#include <math.h>

Token *Evaluation::evaluate_sqrt(std::vector<Token *> args)
{

	float start_val;

	if (args[0]->type == lang_int)
	{
		start_val = (float)args[0]->stored_value.lang_int;
	}
	else
	{
		start_val = (float)args[0]->stored_value.lang_float;
	}

	start_val = sqrt(start_val);

	return new Token(std::to_string(start_val), lang_float);
}
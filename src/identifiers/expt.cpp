#include "evaluation.hpp"

#include "token.hpp"
#include <iostream>
#include <math.h>

Token *Evaluation::evaluate_expt(std::vector<Token *> args)
{

	float base;

	float exponent;

	TokenType final_type = lang_int;

	if (args[0]->type == lang_int)
	{
		base = (float)args[0]->stored_value.lang_int;
	}
	else
	{
		base = (float)args[0]->stored_value.lang_float;
		final_type = lang_float;
	}

	if (args[1]->type == lang_int)
	{
		exponent = (float)args[1]->stored_value.lang_int;
	}
	else
	{
		exponent = (float)args[1]->stored_value.lang_float;
		final_type = lang_float;
	}

	float final = pow(base, exponent);

	
	return new Token(final_type == lang_int ? std::to_string((int)final) : std::to_string(final), final_type);
}
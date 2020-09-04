#include "evaluation.hpp"

#include "token.hpp"
#include <iostream>

Token *Evaluation::evaluate_minus(std::vector<Token *> args)
{
	if (Evaluation::check_type(args, {lang_int, lang_float}))
	{
	}
	else
	{
	}
	int value = args[0]->stored_value.lang_int;
	for (int i = 1; i < args.size(); i++)
	{
		value -= args[i]->stored_value.lang_int;
	}
	return new Token(std::to_string(value), lang_int);
}
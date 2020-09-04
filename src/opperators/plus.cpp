#include "evaluation.hpp"

#include "token.hpp"

Token *Evaluation::evaluate_plus(std::vector<Token *> args)
{
	if (Evaluation::check_type(args, {lang_int, lang_float}))
	{
	}
	else
	{
	}
	int value = 0;
	for (int i = 0; i < args.size(); i++)
	{
		value += args[i]->stored_value.lang_int;
	}
	return new Token(std::to_string(value), lang_int);
}
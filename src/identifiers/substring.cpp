#include "evaluation.hpp"

#include "token.hpp"
#include <iostream>

Token *Evaluation::evaluate_substring(std::vector<Token *> args)
{
	std::string return_val;

	int index_1;
	int index_2;

	// Two numbers
	if (args.size() == 3)
	{
		index_1 = args[1]->stored_value.lang_int;
		index_2 = args[2]->stored_value.lang_int;
		}
	// One number
	else
	{
		index_1 = args[1]->stored_value.lang_int;
		index_2 = args[0]->stored_value.string.length();
	}

	return_val = args[0]->stored_value.string.substr(index_1, index_2 - index_1);

	return new Token(return_val, string);
}
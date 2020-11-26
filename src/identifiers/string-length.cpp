#include "evaluation.hpp"

#include "token.hpp"
#include <iostream>

Token *Evaluation::evaluate_string_length(std::vector<Token *> args)
{
	int return_val = args[0]->stored_value.string.size();

	return new Token(std::to_string(return_val), lang_int);
}
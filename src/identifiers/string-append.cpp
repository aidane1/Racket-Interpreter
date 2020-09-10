#include "evaluation.hpp"

#include "token.hpp"
#include <iostream>

Token *Evaluation::evaluate_string_append(std::vector<Token *> args)
{
	std::string return_val;

	for (int i = 0; i < args.size(); i++) {
		return_val += args[i]->stored_value.string;
	}

	Token *new_token = new Token(return_val, string);

	return new_token;
}
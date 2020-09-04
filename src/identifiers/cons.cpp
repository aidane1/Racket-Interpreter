#include "evaluation.hpp"

#include "token.hpp"
#include <iostream>

Token *Evaluation::evaluate_cons(std::vector<Token *> args)
{
	Token *new_token = new Token("list", list);

	new_token->stored_value.list = args[1]->stored_value.list.prepend(args[0]);

	return new_token;
}
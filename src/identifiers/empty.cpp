#include "evaluation.hpp"

#include "token.hpp"
#include <iostream>

Token *Evaluation::evaluate_empty(std::vector<Token *> args)
{
	Token *new_token = new Token("list", list);
	return new_token;
}
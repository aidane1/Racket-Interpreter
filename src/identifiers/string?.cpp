#include "evaluation.hpp"

#include "token.hpp"
#include <iostream>

Token *Evaluation::evaluate_string_q(std::vector<Token *> args)
{
	return new Token(args[0]->type == string ? "#t" : "#f", boolean);
}
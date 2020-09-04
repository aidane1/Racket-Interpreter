#include "evaluation.hpp"

#include "token.hpp"
#include <iostream>

Token *Evaluation::evaluate_rest(std::vector<Token *> args)
{
	LinkedList<Token *> *new_list = args[0]->stored_value.list.rest();
	Token *new_token = new Token("list", list);
	new_token->stored_value.list = *new_list;
	return new_token;
}
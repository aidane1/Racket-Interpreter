#include "evaluation.hpp"

#include "token.hpp"
#include <iostream>

Token *Evaluation::evaluate_empty(std::vector<Token *> args)
{
	Token *new_token = new Token("list", list);
	return new_token;

	// std::cout << "hey" << "\n";

	// Token *new_token = new Token("list", list);
	// for (int i = 0; i < args.size(); i++)
	// {
	// 	new_token->stored_value.list.append(args[i]);
	// }
	// return new_token;
}
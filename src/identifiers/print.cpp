#include "evaluation.hpp"

#include "token.hpp"
#include <iostream>

Token *Evaluation::evaluate_display(std::vector<Token *> args)
{
	for (int i = 0; i < args.size(); i++)
	{
		std::cout << Token::get_value(args[i]) << " ";
	}
	std::cout << "\n";
	return args[0];
}
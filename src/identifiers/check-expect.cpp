#include "evaluation.hpp"
#include "colors.hpp"

#include "token.hpp"
#include <iostream>

Token *Evaluation::evaluate_check_expect(std::vector<Token *> args)
{
	bool equal = true;

	for (int i = 0; i < args.size() - 1; i++)
	{
		if (Token::get_value(args[i]) == Token::get_value(args[i + 1]))
		{
		}
		else
		{
			equal = false;
		}
	}

	if (equal) {
		std::cout << KGRN << BOLD("Check Expect Passed") << RST << std::endl;
	} else {
		std::cout << KRED << BOLD("Check Expect Failed") << RST << std::endl;
	}

	return new Token(equal ? "#t" : "#f", boolean);
}
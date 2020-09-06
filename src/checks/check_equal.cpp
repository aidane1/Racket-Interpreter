#include "evaluation.hpp"

#include "token.hpp"

Token *Evaluation::check_equal(std::vector<Token *> args)
{

	if (args.size() == 0)
	{
		auto error_text = Environment::construct_argument_error("equal?", 2, 0);

		Token *error = Environment::error_message(arguments_error, error_text, 0, 0);

		return error;
	}
	else
	{
		return nullptr;
	}
}
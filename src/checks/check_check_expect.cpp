#include "evaluation.hpp"

#include "token.hpp"

Token *Evaluation::check_check_expect(std::vector<Token *> args)
{

	if (args.size() != 2)
	{
		auto error_text = Environment::construct_argument_error("check-expect", 2, 0);

		Token *error = Environment::error_message(arguments_error, error_text, 0, 0);

		return error;
	}
	else
	{
		return nullptr;
	}
}
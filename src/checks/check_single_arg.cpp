#include "evaluation.hpp"

#include "token.hpp"

Token *Evaluation::check_single_arg(std::vector<Token *> args)
{

	if (args.size() != 1)
	{
		auto error_text = Environment::construct_argument_error("String Opperator", 1, 0);

		Token *error = Environment::error_message(arguments_error, error_text, 0, 0);

		return error;
	}

	return nullptr;
}
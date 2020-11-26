#include "evaluation.hpp"

#include "token.hpp"

Token *Evaluation::check_expt(std::vector<Token *> args)
{

	if (args.size() != 2)
	{
		auto error_text = Environment::construct_argument_error("expt", 2, args.size());

		Token *error = Environment::error_message(arguments_error, error_text, 0, 0);

		return error;
	}
	else if (!Evaluation::check_type(args, {lang_int, lang_float}))
	{

		for (int i = 0; i < args.size(); i++)
		{
			if (args[i]->type != lang_int && args[i]->type != lang_float)
			{
				auto error_text = Environment::construct_type_error(TokenTypes::get(args[i]->type), Token::get_value(args[i]), "Int, Float");

				Token *error = Environment::error_message(type_error, error_text, 0, 0);

				return error;
			}
		}

		auto error_text = Environment::construct_argument_error("expt", 2, 0);

		Token *error = Environment::error_message(arguments_error, error_text, 0, 0);

		return error;
	}
	else
	{
		return nullptr;
	}
}
#include "evaluation.hpp"

#include "token.hpp"
#include <iostream>

Token *Evaluation::evaluate_minus(std::vector<Token *> args)
{
	if (args.size() == 0)
	{
		auto error_text = Environment::construct_argument_error("-", 2, 0);

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

		auto error_text = Environment::construct_argument_error("+", 2, 0);

		Token *error = Environment::error_message(arguments_error, error_text, 0, 0);

		return error;
	}
	else
	{
		float value = 0;

		if (args[0]->type == lang_int)
		{
			value = args[0]->stored_value.lang_int;
		}
		else
		{
			value = args[0]->stored_value.lang_float;
		}

		for (int i = 1; i < args.size(); i++)
		{
			if (args[i]->type == lang_int)
			{
				value -= args[i]->stored_value.lang_int;
			}
			else
			{
				value -= args[i]->stored_value.lang_float;
			}
		}

		TokenType type = lang_int;

		for (int i = 0; i < args.size(); i++)
		{
			if (args[i]->type == lang_float)
			{
				type = lang_float;
			}
		}

		return new Token(type == lang_int ? std::to_string((int)value) : std::to_string(value), type);
	}
}
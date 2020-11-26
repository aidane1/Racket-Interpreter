#include "evaluation.hpp"

#include "token.hpp"

Token *Evaluation::check_substring(std::vector<Token *> args)
{

	if (args.size() != 2 && args.size() != 3)
	{
		auto error_text = Environment::construct_argument_error("String Opperator", 2, args.size());

		Token *error = Environment::error_message(arguments_error, error_text, 0, 0);

		return error;
	}

	if (args[0]->type != string)
	{
		auto error_text = Environment::construct_type_error(TokenTypes::get(args[0]->type), Token::get_value(args[0]), "String");

		Token *error = Environment::error_message(type_error, error_text, 0, 0);

		return error;
	}

	if (args[1]->type != lang_int)
	{
		auto error_text = Environment::construct_type_error(TokenTypes::get(args[1]->type), Token::get_value(args[1]), "Int");

		Token *error = Environment::error_message(type_error, error_text, 0, 0);

		return error;
	}

	if (args.size() == 3)
	{
		if (args[2]->type != lang_int)
		{
			auto error_text = Environment::construct_type_error(TokenTypes::get(args[2]->type), Token::get_value(args[2]), "Int");

			Token *error = Environment::error_message(type_error, error_text, 0, 0);

			return error;
		}
	}

	return nullptr;
}
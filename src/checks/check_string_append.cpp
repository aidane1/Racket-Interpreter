#include "evaluation.hpp"

#include "token.hpp"

Token *Evaluation::check_string_append(std::vector<Token *> args)
{

	if (args.size() == 0)
	{
		auto error_text = Environment::construct_argument_error("String Opperator", 2, 0);

		Token *error = Environment::error_message(arguments_error, error_text, 0, 0);

		return error;
	}

	for (int i = 0; i < args.size(); i++)
	{
		if (args[i]->type != string)
		{
			auto error_text = Environment::construct_type_error(TokenTypes::get(args[i]->type), Token::get_value(args[i]), "String");

			Token *error = Environment::error_message(type_error, error_text, 0, 0);

			return error;
		}
	}

	return nullptr;
}
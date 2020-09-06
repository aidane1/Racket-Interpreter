#include "evaluation.hpp"

#include "token.hpp"

Token *Evaluation::check_cons(std::vector<Token *> args)
{

	if (args.size() != 2)
	{
		auto error_text = Environment::construct_argument_error("cons", 2, args.size());

		Token *error = Environment::error_message(arguments_error, error_text, 0, 0);

		return error;
	}
	else
	{
		if (args[1]->type != list)
		{
			auto error_text = Environment::construct_type_error(TokenTypes::get(args[1]->type), Token::get_value(args[1]), "List");

			Token *error = Environment::error_message(type_error, error_text, 0, 0);

			return error;
		}
		else
		{
			return nullptr;
		}
	}
}
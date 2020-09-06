#include "evaluation.hpp"

#include "token.hpp"

Token *Evaluation::check_cons_q(std::vector<Token *> args)
{
	if (args.size() != 1)
	{
		auto error_text = Environment::construct_argument_error("List Identifier", 1, args.size());

		Token *error = Environment::error_message(arguments_error, error_text, 0, 0);

		return error;
	}
	else
	{
		if (args[0]->type != list)
		{
			auto error_text = Environment::construct_type_error(TokenTypes::get(args[0]->type), Token::get_value(args[0]), "List");

			Token *error = Environment::error_message(type_error, error_text, 0, 0);

			return error;
		}
		else
		{
			return nullptr;
		}
	}
}
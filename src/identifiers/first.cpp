#include "evaluation.hpp"

#include "token.hpp"

Token *Evaluation::evaluate_first(std::vector<Token *> args)
{
	if (Evaluation::check_type(args, {list}))
	{
	}
	else
	{
	}

	Token **new_token = args[0]->stored_value.list.first();
	if (new_token == nullptr)
	{
		return nullptr;
	}
	else
	{
		return *new_token;
	}
}
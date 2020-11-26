#include "evaluation.hpp"

#include "token.hpp"

Token *Evaluation::evaluate_less_equal(std::vector<Token *> args)
{
	bool comparison = (args[0]->type == lang_float ? args[0]->stored_value.lang_float : args[0]->stored_value.lang_int) <= (args[1]->type == lang_float ? args[1]->stored_value.lang_float : args[1]->stored_value.lang_int);

	Token *new_token = new Token(comparison ? "#t" : "#f", boolean);

	return new_token;
}
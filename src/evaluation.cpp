#include "evaluation.hpp"

bool Evaluation::check_type(std::vector<Token *> tokens, std::vector<TokenType> allowed_types)
{
	bool allowed = true;
	for (int i = 0; i < tokens.size(); i++)
	{
		bool is_type = false;
		for (int j = 0; j < allowed_types.size(); j++)
		{
			if (tokens[i]->type == allowed_types[j])
			{
				is_type = true;
			}
		}
		if (!is_type)
		{
			allowed = false;
		}
	}
	return allowed;
}

bool Evaluation::check_truth(Token *token)
{
	switch (token->type)
	{
	case boolean:
	{
		return token->stored_value.boolean;
	}
	case lang_int:
	{
		if (token->stored_value.lang_int == 0)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	default:
		return true;
	}
}

std::map<std::string, Token *(*)(std::vector<Token *>)> Evaluation::simple_identifiers = {
	{"+", &Evaluation::evaluate_plus},
	{"-", &Evaluation::evaluate_minus},
	{"display", &Evaluation::evaluate_display},
	{"first", &Evaluation::evaluate_first},
	{"list", &Evaluation::evaluate_list},
	{"rest", &Evaluation::evaluate_rest},
	{"cons", &Evaluation::evaluate_cons},
	{"cons?", &Evaluation::evaluate_cons_q},
	{"empty", &Evaluation::evaluate_empty},
	{"empty?", &Evaluation::evaluate_empty_q},
	{"equal?", &Evaluation::evaluate_equal_q},
};

std::map<std::string, Token *(*)(std::vector<Token *>)> Evaluation::simple_opperators = {
	{"+", &Evaluation::evaluate_plus},
	{"-", &Evaluation::evaluate_minus},
	{"*", &Evaluation::evaluate_times},
	{"/", &Evaluation::evaluate_divide},
	{">", &Evaluation::evaluate_greater},
	{"<", &Evaluation::evaluate_less},
};

std::map<std::string, Token *(*)(ASTTreeNode *, Environment *)> Evaluation::simple_keywords = {
	{"cond", &Evaluation::evaluate_cond},
	{"if", &Evaluation::evaluate_if},
	{"and", &Evaluation::evaluate_and},
	{"or", &Evaluation::evaluate_or},
	{"unless", &Evaluation::evaluate_unless},
};

std::map<std::string, Token *(*)(std::vector<Token *>)> Evaluation::check_opperators = {
	{"+", &Evaluation::check_math},
	{"-", &Evaluation::check_math},
	{"/", &Evaluation::check_math},
	{"*", &Evaluation::check_math},
};

std::map<std::string, Token *(*)(std::vector<Token *>)> Evaluation::check_identifiers = {
	{"cons", &Evaluation::check_cons},
	{"cons?", &Evaluation::check_cons_q},
	{"empty?", &Evaluation::check_cons_q},
	{"first", &Evaluation::check_cons_q},
	{"rest", &Evaluation::check_cons_q},
	{"empty", &Evaluation::check_empty},
	{"equal?", &Evaluation::check_equal},
};

bool Evaluation::check_simple(Token *token)
{
	switch (token->type)
	{
	case identifier:
	{
		auto itterator = Evaluation::simple_identifiers.find(token->string_value);
		return (itterator != simple_identifiers.end());
	}
	case opperand:
	{
		auto itterator = Evaluation::simple_opperators.find(token->string_value);
		return (itterator != simple_opperators.end());
	}
	case keyword:
	{
		auto itterator = Evaluation::simple_keywords.find(token->string_value);
		return (itterator != simple_keywords.end());
	}
	default:
	{
		return false;
	}
	}
}

Token *Evaluation::evaluate_simple(Token *token, std::vector<Token *> args, ASTTreeNode *node, Environment *environment)
{
	if (Evaluation::check_simple(token))
	{

		switch (token->type)
		{
		case identifier:
		{

			auto itterator = Evaluation::check_identifiers.find(token->string_value);

			if (itterator != check_identifiers.end())
			{
				Token *(*check_func)(std::vector<Token *>) = itterator->second;
				Token *check_result = (*check_func)(args);
				if (check_result != nullptr)
				{
					return check_result;
				}
			}

			Token *(*eval_func)(std::vector<Token *>) = Evaluation::simple_identifiers[token->string_value];
			return (*eval_func)(args);
		}
		case opperand:
		{
			auto itterator = Evaluation::check_opperators.find(token->string_value);

			if (itterator != check_opperators.end())
			{
				Token *(*check_func)(std::vector<Token *>) = itterator->second;
				Token *check_result = (*check_func)(args);
				if (check_result != nullptr)
				{
					return check_result;
				}
			}

			Token *(*eval_func)(std::vector<Token *>) = Evaluation::simple_opperators[token->string_value];
			return (*eval_func)(args);
		}
		case keyword:
		{
			Token *(*eval_func)(ASTTreeNode *, Environment *) = Evaluation::simple_keywords[token->string_value];
			return (*eval_func)(node, environment);
		}
		default:
		{
			return nullptr;
		}
		}
	}
	else
	{
		return nullptr;
	}
}
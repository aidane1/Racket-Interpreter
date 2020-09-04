#include "token.hpp"

#include <regex>
#include <string>
#include <vector>
#include <sstream>

Token::Token(std::string value, TokenType type) : string_value(value), type(type)
{
	switch (type)
	{
	case boolean:
		// TODO: Fix booleans
		stored_value.boolean = (value == "#t");
		break;
	case string:
		stored_value.string = value;
		break;
	case lang_char:
		// gets first char of string
		stored_value.lang_char = value[0];
		break;
	case lang_float:
		// converts string to float
		stored_value.lang_float = std::stof(value);
		break;
	case lang_int:
		// converts string to int
		stored_value.lang_int = std::stoi(value);
		break;
	default:
		stored_value.other = value;
	}
}

std::string Token::get_value(Token *token)
{
	switch (token->type)
	{
	case list:
	{
		std::stringstream value;
		value << "( list ";
		for (int i = 0; i < token->stored_value.list.get_length(); i++)
		{
			value << get_value(token->stored_value.list.access(i)) << " ";
		}
		value << ")";
		return value.str();
		break;
	}
	default:
	{
		return token->string_value;
		break;
	}
	}
}


std::string TokenTypes::get(int index)
{
	std::vector<std::string> names = {
		"keyword",
		"symbol",
		"identifier",
		"function",
		"boolean",
		"string",
		"list",
		"lang_symbol",
		"lang_char",
		"lang_float",
		"lang_integer",
		"lang_keyword",
		"variable",
		"lambda_reference",
		"opperand",
		"error"};
	if (index >= names.size())
	{
		return "No type matching that index";
	}
	else
	{
		return names[index];
	}
}

#include "tokenizer.hpp"
#include <regex>

TokenizerItem::TokenizerItem(std::regex match, int precedence, TokenType type, std::pair<int, Token *> (*callback)(std::string value, int index, std::smatch match)) : match(match), precedence(precedence), type(type), callback(callback)
{
}

void Tokenizer::add_symbol(std::regex match, int precedence, TokenType type, std::pair<int, Token *> (*callback)(std::string value, int index, std::smatch match))
{
	TokenizerItem *item = new TokenizerItem(match, precedence, type, callback);
	items.push_back(item);
}

std::vector<Token *> Tokenizer::tokenize(std::vector<std::string> input)
{

	int line = 1;
	int character = 1;

	std::vector<Token *> output;

	std::sort(items.begin(), items.end(), [](auto a, auto b) -> bool {
		return a->precedence > b->precedence;
	});

	for (int i = 0; i < input.size(); i++)
	{
		TokenizerItem *matching_item;
		bool match = false;
		std::smatch regex_match;

		for (int j = 0; j < items.size(); j++)
		{
			auto current = items[j];

			if (std::regex_match(input[i], regex_match, current->match))
			{
				// there was a match
				match = true;
				matching_item = items[j];
				break;
			}
		}

		// if there's a match, do something with it. Otherwise, just go to the next item in the loop
		if (match)
		{
			std::pair<int, Token *> matching_value = matching_item->callback(input[i], i, regex_match);
			Token *token = matching_value.second;
			token->line = line;
			token->character = character;
			output.push_back(matching_value.second);
		}
	}

	return output;
}

void Tokenizer::dump(std::vector<Token *> output)
{
	int min_length = 20;
	for (int i = 0; i < output.size(); i++)
	{
		int whitespace_length = min_length - output[i]->string_value.length();
		std::string whitespace;
		for (int j = 0; j < whitespace_length; j++)
		{
			whitespace += " ";
		}
		std::cout << "token: \"" << output[i]->string_value << "\"" << whitespace << "(" << TokenTypes::get(output[i]->type) << ")"
				  << "\n";
	}
}
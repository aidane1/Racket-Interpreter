#include "lexer.hpp"
#include "token.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <regex>

LexerItem::LexerItem(TokenMatcher token, std::pair<int, Token *> (*callback)(std::string value, int index, std::smatch match)) : token(token), callback(callback)
{
}

Lexer::Lexer()
{
}

void Lexer::add_symbol(TokenMatcher token, std::pair<int, Token *> (*callback)(std::string value, int index, std::smatch match))
{
	LexerItem *item = new LexerItem(token, callback);
	items.push_back(item);
}

std::vector<Token *> Lexer::lex(std::string value)
{

	int line = 1;
	int character = 1;

	std::vector<Token *> output;

	// sorts the lexical items by order of precedence, so the most important onces are matched first
	std::sort(items.begin(), items.end(), [](LexerItem *a, LexerItem *b) -> bool {
		return a->token.precedence > b->token.precedence;
	});

	// itterates over the string that is to be lexed
	for (int i = 0; i < value.length();)
	{
		LexerItem *matching_item;
		bool match = false;
		std::smatch regex_match;
		// itterates over all the lex items
		for (int j = 0; j < items.size(); j++)
		{
			TokenMatcher current = items[j]->token;

			std::string regex_substring = value.substr(i, value.length() - i);

			if (std::regex_search(regex_substring, regex_match, current.match))
			{
				// if there is a match, assign it to the top level matching_item variable and break from the loop
				if (regex_match.position() == 0)
				{
					match = true;
					matching_item = items[j];
					break;
				}
			}
		}

		// if there's a match, do something with it. Otherwise, just go to the next item in the loop
		if (match)
		{
			std::pair<int, Token *> matching_value = matching_item->callback(value, i, regex_match);
			Token *token = matching_value.second;
			token->line = line;
			token->character = character;
			output.push_back(matching_value.second);

			// for (int j = 0; j < matching_value.first; j++)
			// {
			// 	if (value[i] == '\n')
			// 	{
			// 		line++;
			// 		character = 1;
			// 	}
			// 	else
			// 	{
			// 		character++;
			// 	}
			// 	i++;
			// }
			i += matching_value.first;
		}
		else
		{
			// if (value[i] == '\n')
			// {
			// 	line++;
			// 	character = 1;
			// }
			// else
			// {
			// 	character++;
			// }

			i++;
		}
	}

	return output;
}

void Lexer::dump(std::vector<Token *> output)
{
	int min_length = 20;
	for (int i = 0; i < output.size(); i++)
	{
		int whitespace_length = min_length - output[i]->value.length();
		std::string whitespace;
		for (int j = 0; j < whitespace_length; j++)
		{
			whitespace += " ";
		}
		std::cout << "token: \"" << output[i]->value << "\"" << whitespace << "(" << TokenTypes::get(output[i]->type) << ")"
				  << "\n";
	}
}
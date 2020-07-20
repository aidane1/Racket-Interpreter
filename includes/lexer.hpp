#ifndef LEXER
#define LEXER

#include "token.hpp"
#include <vector>
#include <regex>

struct LexerItem
{
	TokenMatcher token;
	std::pair<int, Token *> (*callback)(std::string value, int index, std::smatch match);

	LexerItem(TokenMatcher token, std::pair<int, Token *> (*callback)(std::string value, int index, std::smatch match));
};

class Lexer
{
private:
	std::vector<LexerItem *> items;

public:
	Lexer();

	// takes a Token, and a pointer to a function that accepts a string & an index and returns an index
	void add_symbol(TokenMatcher token, std::pair<int, Token *> (*)(std::string value, int index, std::smatch match));

	std::pair<int, int> get_line_and_character(std::string string, int index);

	std::vector<Token *> lex(std::string value);

	void dump(std::vector<Token *> tokens);
};

#endif
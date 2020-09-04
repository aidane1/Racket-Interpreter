#ifndef TOKENIZER
#define TOKENIZER

#include <vector>
#include <regex>
#include "token.hpp"


struct TokenizerItem
{
	std::regex match;
	int precedence;
	TokenType type;
	std::pair<int, Token *> (*callback)(std::string value, int index, std::smatch match);

	TokenizerItem(std::regex match, int precedence, TokenType type, std::pair<int, Token *> (*callback)(std::string value, int index, std::smatch match));
};

class Tokenizer
{
private:
	std::vector<TokenizerItem *> items;

public:
	void add_symbol(std::regex match, int precedence, TokenType type, std::pair<int, Token *> (*)(std::string value, int index, std::smatch match));

	std::vector<Token *> tokenize(std::vector<std::string> input);

	void dump(std::vector<Token *> input);
};

#endif
#ifndef TOKEN
#define TOKEN

#include <string>
#include <regex>
#include <vector>
#include "linked_list.hpp"

enum TokenType
{
	keyword,
	symbol,
	identifier,
	function,
	boolean,
	string,
	list,
	lang_symbol,
	lang_char,
	lang_float,
	lang_int,
	variable,
	lambda_reference,
	opperand,
	error
};

class Token;

class ASTTreeNode;

struct TokenStoredType
{
	std::string string;
	// std::vector<Token *> list;
	LinkedList<Token *> list;
	float lang_float;
	int lang_int;
	char lang_char;
	bool boolean;

	ASTTreeNode *lambda_reference;

	std::string other;

	// std::string symbol;
	// std::string keyword;
	// std::string identifier;
	// std::string function;
	// std::string lang_symbol;
	// std::string variable;
	// std::string opperand;
	// std::string error;
};

class TokenTypes
{
public:
	static std::string get(int index);
};

class TokenMatcher
{
private:
public:
	std::regex match;
	int precedence;
	TokenType type;

	TokenMatcher(std::regex match, int precedence, TokenType type);
};

class Token
{
private:
	// std::string value;
	// int precedence;
	// TokenType type;

public:
	TokenStoredType stored_value;
	std::string value;
	int precedence;
	TokenType type;

	int line;
	int character;

	static std::string get_value(Token *token);

	Token(std::string value, int precedence, TokenType type);
};

#endif
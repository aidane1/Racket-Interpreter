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
	lang_keyword,
	variable,
	lambda_reference,
	opperand,
	error
};

class TokenTypes
{
public:
	static std::string get(int index);
};

class Token;

class ASTTreeNode;

struct TokenStoredType
{
	std::string string;

	LinkedList<Token *> list;

	float lang_float;

	int lang_int;

	char lang_char;

	bool boolean;

	ASTTreeNode *lambda_reference;

	std::string other;
};

class Token
{
private:
public:
	TokenStoredType stored_value;
	std::string string_value;
	TokenType type;

	int line;
	int character;

	static std::string get_value(Token *token);

	Token(std::string value, TokenType type);
};

#endif
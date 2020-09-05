#ifndef ENVIRONMENT
#define ENVIRONMENT

#include <vector>
#include <map>
// #include <hash_map>

#include "parser.hpp"
#include "token.hpp"

enum ErrorType
{
	type_error,
	arguments_error,
	definition_error,
	parse_error
};

class Environment
{
private:
	std::map<std::string, ASTTreeNode *> definitions;
	std::map<std::string, Token *> arg_map;

	bool verbose = true;

public:
	Environment(bool verbose = true);

	void evaluate(ASTTreeNode *root);

	Token *evaluate_node(ASTTreeNode *node);
	Token *evaluate_variable(Token *token);

	std::vector<Token *> get_rest(std::vector<ASTTreeNode *> rest);
	std::vector<Token *> get_all(std::vector<ASTTreeNode *> all);

	// handling errors
	static Token *error_message(ErrorType type, std::string error, int line, int character);
	static std::string construct_type_error(std::string type, std::string value, std::string expected);
	static std::string construct_argument_error(std::string function_call, int expected, int found);
	static std::string construct_definition_error(std::string function_name);
};

#endif
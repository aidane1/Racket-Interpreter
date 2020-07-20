#ifndef ENVIRONMENT
#define ENVIRONMENT

#include "tree_node.hpp"
#include "token.hpp"
#include <map>
#include <string>

enum ErrorType
{
	type_error,
	arguments_error,
	definition_error,
	parse_error
};

struct VariableDefinition
{
	ASTTreeNode *node;
	ASTTreeNode *scope;
};

class Environment
{
private:
	// std::map<ASTTreeNode *, std::map<std::string, ASTTreeNode *>> definitions;

	std::map<std::string, ASTTreeNode *> definitions;

public:
	void evaluate(ASTTreeNode *node);

	std::vector<Token *> get_compact_trees(ASTTreeNode *node, std::map<std::string, Token *> arg_map);

	Token *evaluate_ast(ASTTreeNode *node, std::map<std::string, Token *> args_map);

	// Token *evaluate_function(ASTTreeNode *node, std::vector<Token *> args, std::map<ASTTreeNode *, std::map<std::string, ASTTreeNode *>> &definitions, std::map<std::string, Token *> args_map = std::map<std::string, Token *>());

	// return reference to function if exists, otherwise return nullptr
	// ASTTreeNode *find_function_definition(ASTTreeNode *node, std::string name, std::map<ASTTreeNode *, std::map<std::string, ASTTreeNode *>> &definitions);

	static void error_message(ErrorType type, std::string error, int line, int character);

	static std::string construct_type_error(std::string type, std::string value, std::string expected);
	static std::string construct_argument_error(std::string function_call, int expected, int found);
	static std::string construct_definition_error(std::string function_name);
};

#endif
#ifndef AST_EVALUATION
#define AST_EVALUATION

#include "token.hpp"
#include "tree_node.hpp"
#include "environment.hpp"

#include <vector>
#include <map>

class ASTEvaluation
{
private:
public:
	static bool check_type(Token *token, std::vector<TokenType> types);

	// identifiers
	static Token *evaluate_print(ASTTreeNode *node, std::vector<Token *> args);
	static Token *evaluate_list(ASTTreeNode *node, std::vector<Token *> args);
	static Token *evaluate_first(ASTTreeNode *node, std::vector<Token *> args);
	static Token *evaluate_rest(ASTTreeNode *node, std::vector<Token *> args);
	static Token *evaluate_empty();
	static Token *evaluate_empty_q(ASTTreeNode *node, std::vector<Token *> args);
	static Token *evaluate_cons(ASTTreeNode *node, std::vector<Token *> args);
	static Token *evaluate_cons_q(ASTTreeNode *node, std::vector<Token *> args);
	static Token *evaluate_map(ASTTreeNode *node, std::vector<Token *> args, Environment *environment, std::map<std::string, Token *> arg_map);

	// keywords
	static Token *evaluate_cond(ASTTreeNode *node, Environment *environment, std::map<std::string, Token *> arg_map);
	static Token *evaluate_if(ASTTreeNode *node, Environment *environment, std::map<std::string, Token *> arg_map);
	static Token *evaluate_unless(ASTTreeNode *node, Environment *environment, std::map<std::string, Token *> arg_map);
	static Token *evaluate_and(ASTTreeNode *node, Environment *environment, std::map<std::string, Token *> arg_map);
	static Token *evaluate_or(ASTTreeNode *node, Environment *environment, std::map<std::string, Token *> arg_map);
	static Token *evaluate_values(ASTTreeNode *node, std::vector<Token *> args, Environment *environment, std::map<std::string, Token *> arg_map);

	// operations
	static Token *evaluate_plus(ASTTreeNode *node, std::vector<Token *> args);
	static Token *evaluate_greater_than(ASTTreeNode *node, std::vector<Token *> args);
	static Token *evaluate_less_than(ASTTreeNode *node, std::vector<Token *> args);
};

#endif
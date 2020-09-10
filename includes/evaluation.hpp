#ifndef EVALUATION
#define EVALUATION

#include <vector>
#include <map>

#include "token.hpp"
#include "environment.hpp"
#include "parser.hpp"

class Evaluation
{
private:
public:
	// identifiers
	static Token *evaluate_list(std::vector<Token *> args);
	static Token *evaluate_first(std::vector<Token *> args);
	static Token *evaluate_display(std::vector<Token *> args);
	static Token *evaluate_rest(std::vector<Token *> args);
	static Token *evaluate_cons(std::vector<Token *> args);
	static Token *evaluate_cons_q(std::vector<Token *> args);
	static Token *evaluate_empty(std::vector<Token *> args);
	static Token *evaluate_empty_q(std::vector<Token *> args);
	static Token *evaluate_equal_q(std::vector<Token *> args);
	static Token *evaluate_string_append(std::vector<Token *> args);

	// keywords
	static Token *evaluate_cond(ASTTreeNode *node, Environment *environment);
	static Token *evaluate_and(ASTTreeNode *node, Environment *environment);
	static Token *evaluate_or(ASTTreeNode *node, Environment *environment);
	static Token *evaluate_if(ASTTreeNode *node, Environment *environment);
	static Token *evaluate_unless(ASTTreeNode *node, Environment *environment);

	//opperators
	static Token *evaluate_plus(std::vector<Token *> args);
	static Token *evaluate_minus(std::vector<Token *> args);
	static Token *evaluate_times(std::vector<Token *> args);
	static Token *evaluate_divide(std::vector<Token *> args);
	static Token *evaluate_greater(std::vector<Token *> args);
	static Token *evaluate_less(std::vector<Token *> args);

	//checks
	static Token *check_math(std::vector<Token *> args);
	static Token *check_cons(std::vector<Token *> args);
	static Token *check_cons_q(std::vector<Token *> args);
	static Token *check_empty(std::vector<Token *> args);
	static Token *check_equal(std::vector<Token *> args);
	static Token *check_string_append(std::vector<Token *> args);

	static std::map<std::string, Token *(*)(std::vector<Token *>)> simple_identifiers;
	static std::map<std::string, Token *(*)(std::vector<Token *>)> simple_opperators;
	static std::map<std::string, Token *(*)(ASTTreeNode *, Environment *)> simple_keywords;

	static std::map<std::string, Token *(*)(std::vector<Token *>)> check_identifiers;
	static std::map<std::string, Token *(*)(std::vector<Token *>)> check_opperators;
	static std::map<std::string, Token *(*)(ASTTreeNode *, Environment *)> check_keywords;

	static bool check_simple(Token *token);
	static Token *evaluate_simple(Token *token, std::vector<Token *> args, ASTTreeNode *node = nullptr, Environment *environment = nullptr);

	static bool check_type(std::vector<Token *> tokens, std::vector<TokenType> allowed_types);
	static bool check_truth(Token *token);
};

#endif
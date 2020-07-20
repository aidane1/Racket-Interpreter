#include "ast_evaluation.hpp"

Token *ASTEvaluation::evaluate_empty()
{
	Token *new_token = new Token("list", 5, list);
	return new_token;
}
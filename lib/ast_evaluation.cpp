#include "ast_evaluation.hpp"

bool ASTEvaluation::check_type(Token *token, std::vector<TokenType> types)
{
	for (int i = 0; i < types.size(); i++)
	{
		if (types[i] == token->type)
			return true;
	}
	return false;
}
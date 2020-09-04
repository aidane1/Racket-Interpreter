#include "evaluation.hpp"

#include "token.hpp"

Token *Evaluation::evaluate_if(ASTTreeNode *node, Environment *environment)
{

	Token *return_val = nullptr;

	Token *expression = environment->evaluate_node(node->children[1]);

	if (Evaluation::check_truth(expression))
	{
		return_val = environment->evaluate_node(node->children[2]);
	}
	else
	{
		return_val = environment->evaluate_node(node->children[3]);
	}

	return return_val;
}
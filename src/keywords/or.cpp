#include "evaluation.hpp"

#include "token.hpp"

Token *Evaluation::evaluate_or(ASTTreeNode *node, Environment *environment)
{

	Token *return_val = nullptr;

	bool return_value = false;

	for (int i = 1; i < node->children.size(); i++)
	{

		Token *current_val = environment->evaluate_node(node->children[i]);

		if (Evaluation::check_truth(current_val))
		{
			return_value = true;
		}
	}

	if (return_value)
	{
		return_val = new Token("#t", boolean);
	}
	else
	{
		return_val = new Token("#f", boolean);
	}

	return return_val;
}
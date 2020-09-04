#include "evaluation.hpp"

#include "token.hpp"

Token *Evaluation::evaluate_cond(ASTTreeNode *node, Environment *environment)
{

	Token *return_val = nullptr;

	for (int i = 1; i < node->children.size(); i++)
	{
		ASTTreeNode *first_node = node->children[i]->children[0];
		Token *first_val = environment->evaluate_node(first_node);

		if (Evaluation::check_truth(first_val))
		{
			ASTTreeNode *second_node = node->children[i]->children[1];
			Token *second_val = environment->evaluate_node(second_node);
			return second_val;
		}
		else if (first_node->token != nullptr && first_node->token->string_value == "else")
		{
			ASTTreeNode *second_node = node->children[i]->children[1];
			Token *second_val = environment->evaluate_node(second_node);
			return second_val;
		}
	}

	return return_val;
}
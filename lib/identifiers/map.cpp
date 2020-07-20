#include "ast_evaluation.hpp"

Token *ASTEvaluation::evaluate_map(ASTTreeNode *node, std::vector<Token *> args, Environment *enviroment, std::map<std::string, Token *> arg_map)
{
	Token *new_token = new Token("list", 5, list);

	for (int i = 0; i < args[1]->stored_value.list.get_length(); i++)
	{

		ASTTreeNode *temp_node = new ASTTreeNode();
		temp_node->token = args[0];
		temp_node->parent = nullptr;

		ASTTreeNode *temp_child = new ASTTreeNode();
		temp_child->token = args[1]->stored_value.list.access(i);
		temp_child->parent = nullptr;

		temp_node->children.push_back(temp_child);

		Token *new_val = enviroment->evaluate_ast(temp_node, arg_map);

		new_token->stored_value.list.append(new_val);

	}

	return new_token;
}


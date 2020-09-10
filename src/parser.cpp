#include "parser.hpp"

ASTTreeNode::ASTTreeNode()
{
	token = nullptr;
	parent = nullptr;
}

ASTTreeNode *Parser::parse(std::vector<Token *> tokens)
{
	ASTTreeNode *root = new ASTTreeNode();

	ASTTreeNode *current = root;

	for (int i = 0; i < tokens.size(); i++)
	{
		if (tokens[i]->string_value == "(" || tokens[i]->string_value == "[")
		{
			ASTTreeNode *new_node = new ASTTreeNode();
			new_node->parent = current;
			current->children.push_back(new_node);
			current = new_node;
		}
		else if (tokens[i]->string_value == ")" || tokens[i]->string_value == "]")
		{

			current = current->parent;
		}
		else
		{
			ASTTreeNode *new_node = new ASTTreeNode();
			new_node->parent = current;
			new_node->token = tokens[i];
			current->children.push_back(new_node);
		}
	}

	return root;
}

void Parser::dump(ASTTreeNode *node, int depth)
{

	std::string whitespace;
	for (int i = 0; i < depth; i++)
	{
		whitespace += "    ";
	}

	if (node->token == nullptr)
	{
		// std::cout << whitespace << "____: " << node->children.size() << " child(ren) \n";
		std::cout << whitespace << "____"
				  << "\n";
	}
	else
	{
		std::cout << whitespace << node->token->string_value << "\n";
	}

	for (int i = 0; i < node->children.size(); i++)
	{
		dump(node->children[i], depth + 1);
	}
}
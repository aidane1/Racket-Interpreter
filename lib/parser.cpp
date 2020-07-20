#include "parser.hpp"
#include "tree_node.hpp"

#include <vector>
#include <stack>
#include <iostream>

// Whoops this is actually useless because reverse polish notation
// isn't applicible to lisp-esque langauages (like racket)
std::vector<Token *> Parser::generate_reverse_polish_notion(std::vector<Token *> tokens)
{
	std::stack<Token *> output;
	std::stack<Token *> operators;

	for (int i = 0; i < tokens.size(); i++)
	{
		Token *current_token = tokens[i];
	}

	return tokens;
}

ASTTreeNode *Parser::generate_abstract_syntax_tree(std::vector<Token *> tokens)
{

	// defines the root node of the abstract syntax tree
	ASTTreeNode *root = new ASTTreeNode;
	root->token = nullptr;
	root->parent = nullptr;

	// assigns the root node to be the current node.
	// Not necessary programming-wise, but makes the following code
	// easier to understand (semantically) and does not affect
	// execution
	ASTTreeNode *current = root;

	// lambdas are weird
	bool is_in_lambda = false;
	int lambda_counter = 0;

	bool is_values = false;

	// iterate over all of the tokens created by the lexical analyser
	for (int i = 0; i < tokens.size(); i++)
	{

		// the current token is the current token (shocker, i know...)
		Token *current_token = tokens[i];

		switch (current_token->type)
		{
		// if the current token is a symbol (ex. "(", ")")
		// NOTE: do not confuse lexical symbols (listed above) with symbols in the Racket programming language.
		// They are different constructs and unrelated
		case symbol:
			// if it's an open bracket, create a new node in the AST
			// and assign it as another child to the current node. Then jump
			// down one level in the AST
			if (current_token->value == "(")
			{
				Token *temp_token = new Token("values", 6, keyword);
				ASTTreeNode *node = new ASTTreeNode;
				node->parent = current;
				node->token = temp_token;
				current->children.push_back(node);
				current = node;

				// lambdas are weird
				// if (is_in_lambda)
				// {
				// 	lambda_counter++;
				// }

				// Square brackets indicate a list of consecutive unrelated values
				// that will be evaluated in order of appearance, with equal hierarchy
			}
			else if (current_token->value == "[")
			{
				Token *temp_token = new Token("values_list", 6, keyword);
				ASTTreeNode *node = new ASTTreeNode;
				node->parent = current;
				node->token = temp_token;
				current->children.push_back(node);
				current = node;
			}
			// if it's a close bracket, jump up one level in the AST
			else if (current_token->value == ")" || (current_token->value == "]"))
			{

				// lambdas are weird
				current = current->parent;
				// if (is_in_lambda)
				// {
				// 	if (lambda_counter > 0)
				// 	{
				// 		current = current->parent;
				// 	}
				// 	lambda_counter--;
				// }
				// else
				// {
				// 	current = current->parent;
				// }
			}
			break;

		// temporary (for now). If it isn't an open or closing bracket:
		//    if the current node doesn't have a token, it means it's the first token encountered
		//    after a new opening bracket. In that case, assign the current token to the current AST Node's token.
		//    otherwise, create a new AST Node and assign the current token as its token. Then, add the current AST NODE
		//    to the current
		default:

			// if it's a comment, ignore it
			if (current->token->value == "comment")
			{
			}
			else
			{
				// Note this all falls to pieces in lambdas because this language is dumb :)
				if (current->token->value == "values")
				{
					if (!is_in_lambda)
					{
						// std::cout << current_token->value << "\n";
						current->token = current_token;
					}
					else
					{
						// is lambda definition with args
						is_in_lambda = false;

						current->token->value = "lambda_args";

						ASTTreeNode *node = new ASTTreeNode;
						node->token = current_token;
						node->parent = current;
						current->children.push_back(node);
					}
				}
				else
				{
					ASTTreeNode *node = new ASTTreeNode;
					node->token = current_token;
					node->parent = current;
					current->children.push_back(node);
				}

				if (current_token->value == "lambda")
				{
					if (current->parent->token->value == "values")
					{
						current->parent->token = new Token("lambda_wrapper", 6, identifier);
					}
					// current = current->parent;
					// current->parent->children[0] = current;
					// current->parent = current;
					// current->token->value = "lambda";
					is_in_lambda = true;
				}
				break;
			}
		}
	}

	return current;
}

// A non-important and self explainitory function.
// It just displays an AST to the terminal
void Parser::dump(ASTTreeNode *node, int depth)
{
	std::string whitespace;
	for (int i = 0; i < depth; i++)
	{
		whitespace += "    ";
	}
	if (node->token != nullptr)
	{
		std::cout << whitespace << node->token->value << "\n";
	}
	for (int i = 0; i < node->children.size(); i++)
	{
		Parser::dump(node->children[i], depth + 1);
	}

	if (depth == 0 || depth == 1)
	{
		std::cout << "\n";
	}
}
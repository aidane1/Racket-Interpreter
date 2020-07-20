#include "environment.hpp"
#include "tree_node.hpp"
#include "token.hpp"
#include "colors.hpp"
#include "ast_evaluation.hpp"

#include <map>
#include <iostream>
#include <sstream>
#include <cmath>

// if a node is in the parent tree of any particular subtree of the AST, that subtree
// may use all definitions of that node. In general, this means that all subtree's of the main
// AST can access definitions on the root node.

// root
// |
// |- definition_1
// |
// subtree_of_ast_1
// |              |
// |			  |-definition_2
// |			  |
// |			  |-subtree_of_ast_2 (can access definition_1, definition_2 because
// |								  both subtree_of_ast_1 and root are in subtree_of_ast_2
// |								  parent tree)
// subtree_of_ast_3
// 				  |
// 				  |-definition_3
// 				  |
// 				  |-subtree_of_ast_4 (can access definition_1, definition 3 because )
//      							  both subtree_of_ast_1 and root are in subtree_of_ast_4
//  								  parent tree. Note that it CANNOT access definition_2 because
// 									  subtree_of_ast_1 is not in the parent tree of subtree_of_ast_4)

// the structure of our data will be line so: (Note that this has a runtime of O(n). If we need to improve that in
// 												the future we will look for a runtime of O(1) data structure)

// map<node_of_ast, map<name_of_function, reference_to_function_definition>
// When we need to get all the applicable definitions for a node, we will
// iterate over its parents and check at each level if the map contains
// a reference to that function. Lower level definitions take precedence over
// higher level definitions

void Environment::evaluate(ASTTreeNode *node)
{

	ASTTreeNode *current = node;

	std::map<std::string, Token *> arg_map;

	for (int i = 0; i < current->children.size(); i++)
	{
		evaluate_ast(current->children[i], arg_map);
	}
}

std::vector<Token *> Environment::get_compact_trees(ASTTreeNode *node, std::map<std::string, Token *> arg_map)
{
	std::vector<Token *> compact_trees;

	for (int i = 0; i < node->children.size(); i++)
	{
		compact_trees.push_back(evaluate_ast(node->children[i], arg_map));
	}

	return compact_trees;
}

Token *Environment::evaluate_ast(ASTTreeNode *node, std::map<std::string, Token *> arg_map)
{
	switch (node->token->type)
	{
	case lambda_reference:
	{
		auto definition = node->token->stored_value.lambda_reference;

		auto compact_trees = get_compact_trees(node, arg_map);

		if (definition->children[0]->children.size() != compact_trees.size())
		{
			// whoops, wrong number of arguments
			if (compact_trees.size() != 0)
			{
				Environment::error_message(arguments_error, Environment::construct_argument_error(node->token->value, definition->children[0]->children.size(), compact_trees.size()), node->token->line, node->token->character);
			}

			return node->token;
		}
		else
		{
			// map to hold arguments
			std::map<std::string, Token *> arg_map = std::map<std::string, Token *>();
			for (int i = 0; i < node->children.size(); i++)
			{
				arg_map[definition->children[0]->children[i]->token->value] = compact_trees[i];
			}

			return evaluate_ast(definition->children[1], arg_map);
		}

		break;
	}
	case variable:
	{
		// first, check if it's a passed argument (passed arguments get priority over defined functions)
		auto it = arg_map.find(node->token->value);

		if (it != arg_map.end())
		{
			// definition exists; evaluate it as it's own ast (only do this for possible function references)
			ASTTreeNode *temp_node = new ASTTreeNode();
			temp_node->token = it->second;
			temp_node->children = node->children;
			temp_node->parent = nullptr;
			return evaluate_ast(temp_node, arg_map);
		}
		else
		{
			// then, check if it's a function definition
			auto it_2 = definitions.find(node->token->value);
			if (it_2 != definitions.end())
			{
				auto definition = it_2->second;
				auto compact_trees = get_compact_trees(node, arg_map);

				if (definition->children[0]->children.size() != compact_trees.size())
				{
					// whoops, wrong number of arguments
					if (compact_trees.size() != 0)
					{
						Environment::error_message(arguments_error, Environment::construct_argument_error(node->token->value, definition->children[0]->children.size(), compact_trees.size()), node->token->line, node->token->character);
					}

					return node->token;
				}
				else
				{
					// map to hold arguments
					std::map<std::string, Token *> arg_map = std::map<std::string, Token *>();
					for (int i = 0; i < node->children.size(); i++)
					{
						arg_map[definition->children[0]->children[i]->token->value] = compact_trees[i];
					}

					return evaluate_ast(definition->children[1], arg_map);
				}

				break;
			}
			else
			{
				// No function under that name
				Environment::error_message(definition_error, Environment::construct_definition_error(node->token->value), node->token->line, node->token->character);
				return node->token;
			}
		}
		break;
	}
	case opperand:
	{
		if (node->token->value == "+")
		{
			auto compact_trees = get_compact_trees(node, arg_map);
			return ASTEvaluation::evaluate_plus(node, compact_trees);
		}
		else if (node->token->value == ">")
		{
			auto compact_trees = get_compact_trees(node, arg_map);
			return ASTEvaluation::evaluate_greater_than(node, compact_trees);
		}
		else if (node->token->value == "<")
		{
			auto compact_trees = get_compact_trees(node, arg_map);
			return ASTEvaluation::evaluate_less_than(node, compact_trees);
		}
		else
		{
			return node->token;
		}
		break;
	}
	case keyword:
	{
		if (node->token->value == "cond")
		{
			return ASTEvaluation::evaluate_cond(node, this, arg_map);
		}
		else if (node->token->value == "if")
		{
			return ASTEvaluation::evaluate_if(node, this, arg_map);
		}
		else if (node->token->value == "unless")
		{
			return ASTEvaluation::evaluate_unless(node, this, arg_map);
		}
		else if (node->token->value == "and")
		{
			return ASTEvaluation::evaluate_and(node, this, arg_map);
		}
		else if (node->token->value == "or")
		{
			return ASTEvaluation::evaluate_or(node, this, arg_map);
		}
		else if (node->token->value == "values")
		{
			auto compact_trees = std::vector<Token *>();
			return ASTEvaluation::evaluate_values(node, compact_trees, this, arg_map);
		}
		else
		{
			return node->token;
		}
		break;
	}
	case identifier:
	{

		if (node->token->value == "print")
		{
			auto compact_trees = get_compact_trees(node, arg_map);
			return ASTEvaluation::evaluate_print(node, compact_trees);
		}
		else if (node->token->value == "first")
		{
			auto compact_trees = get_compact_trees(node, arg_map);
			return ASTEvaluation::evaluate_first(node, compact_trees);
		}
		else if (node->token->value == "rest")
		{
			auto compact_trees = get_compact_trees(node, arg_map);
			return ASTEvaluation::evaluate_rest(node, compact_trees);
		}
		else if (node->token->value == "cons")
		{
			auto compact_trees = get_compact_trees(node, arg_map);
			return ASTEvaluation::evaluate_cons(node, compact_trees);
		}
		else if (node->token->value == "cons?")
		{
			auto compact_trees = get_compact_trees(node, arg_map);
			return ASTEvaluation::evaluate_cons_q(node, compact_trees);
		}
		else if (node->token->value == "empty")
		{
			return ASTEvaluation::evaluate_empty();
		}
		else if (node->token->value == "empty?")
		{
			auto compact_trees = get_compact_trees(node, arg_map);
			return ASTEvaluation::evaluate_empty_q(node, compact_trees);
		}
		else if (node->token->value == "define")
		{
			definitions[node->children[0]->token->value] = node;
			return node->token;
		}
		else if (node->token->value == "list")
		{
			auto compact_trees = get_compact_trees(node, arg_map);
			return ASTEvaluation::evaluate_list(node, compact_trees);
		}
		else if (node->token->value == "lambda")
		{

			Token *new_token = new Token("lambda", 4, lambda_reference);
			new_token->stored_value.lambda_reference = node;

			return new_token;
		}
		else if (node->token->value == "map")
		{
			auto compact_trees = get_compact_trees(node, arg_map);
			return ASTEvaluation::evaluate_map(node, compact_trees, this, arg_map);
		}
		else if (node->token->value == "lambda_wrapper")
		{

			ASTTreeNode *temp_node = new ASTTreeNode();
			temp_node->token = evaluate_ast(node->children[0], arg_map);
			temp_node->parent = nullptr;

			for (int i = 1; i < node->children.size(); i++)
			{
				temp_node->children.push_back(node->children[i]);
			}

			return evaluate_ast(temp_node, arg_map);
		}
		else
		{
			return node->token;
		}
	}
	default:
	{
		return node->token;
		break;
	}
	}
}

// Token *Environment::evaluate_ast(ASTTreeNode *node, std::map<std::string, Token *> arg_map)
// {

// 	switch (node->token->type)
// 	{
// 	case lambda_reference:
// 	{
// 		std::vector<Token *> compact_trees;
// 		for (int i = 0; i < node->children.size(); i++)
// 		{
// 			compact_trees.push_back(evaluate_ast(node->children[i], definitions, arg_map));
// 		}

// 		return evaluate_function(node->token->stored_value.lambda_reference, compact_trees, definitions);
// 		break;
// 	}

// 	case variable:
// 	{
// 		if (arg_map == nullptr)
// 		{
// 			std::vector<Token *> compact_trees;
// 			for (int i = 0; i < node->children.size(); i++)
// 			{
// 				compact_trees.push_back(evaluate_ast(node->children[i], definitions, arg_map));
// 			}

// 			return evaluate_function(node, compact_trees, definitions);
// 		}
// 		else
// 		{
// 			auto it = (*arg_map).find(node->token->value);

// 			if (it != (*arg_map).end())
// 			{
// 				// definition exists; evaluate it as it's own ast (only do this for possible function references)
// 				ASTTreeNode *temp_node = new ASTTreeNode();
// 				temp_node->token = it->second;
// 				temp_node->children = node->children;
// 				temp_node->parent = nullptr;
// 				return evaluate_ast(temp_node, definitions, arg_map);
// 			}
// 			else
// 			{
// 				std::vector<Token *> compact_trees;
// 				for (int i = 0; i < node->children.size(); i++)
// 				{
// 					compact_trees.push_back(evaluate_ast(node->children[i], definitions, arg_map));
// 				}

// 				return evaluate_function(node, compact_trees, definitions);
// 			}
// 		}

// 		break;
// 	}
// 	case keyword:
// 	{
// 		if (node->token->value == "if")
// 		{
// 			Token *test_expression = evaluate_ast(node->children[0], definitions, arg_map);

// 			switch (test_expression->type)
// 			{
// 			case boolean:
// 				if (test_expression->stored_value.boolean)
// 				{
// 					return evaluate_ast(node->children[1], definitions, arg_map);
// 				}
// 				else
// 				{
// 					return evaluate_ast(node->children[2], definitions, arg_map);
// 				}
// 				break;
// 			case lang_int:
// 				if (test_expression->stored_value.lang_int)
// 				{
// 					return evaluate_ast(node->children[1], definitions, arg_map);
// 				}
// 				else
// 				{
// 					return evaluate_ast(node->children[2], definitions, arg_map);
// 				}
// 			default:
// 				return evaluate_ast(node->children[1], definitions, arg_map);
// 				break;
// 			}
// 		}
// 		else if (node->token->value == "cond")
// 		{
// 			for (int i = 0; i < node->children.size(); i++)
// 			{

// 				ASTTreeNode *first = node->children[i]->children[0];
// 				ASTTreeNode *second = node->children[i]->children[1];

// 				if (first->token->value == "else")
// 				{
// 					return evaluate_ast(second, definitions, arg_map);
// 				}
// 				else
// 				{

// 					Token *current_expression = evaluate_ast(first, definitions, arg_map);

// 					switch (current_expression->type)
// 					{
// 					case boolean:
// 						if (current_expression->stored_value.boolean)
// 						{
// 							return evaluate_ast(second, definitions, arg_map);
// 						}
// 						break;
// 					case lang_int:
// 						if (current_expression->stored_value.lang_int)
// 						{
// 							return evaluate_ast(second, definitions, arg_map);
// 						}
// 					default:
// 						break;
// 					}
// 				}
// 			}
// 			return node->token;
// 		}
// 		else if (node->token->value == "unless")
// 		{
// 			Token *test_expression = evaluate_ast(node->children[0], definitions, arg_map);

// 			switch (test_expression->type)
// 			{
// 			case boolean:
// 				if (test_expression->stored_value.boolean)
// 				{
// 					return evaluate_ast(node->children[2], definitions, arg_map);
// 				}
// 				else
// 				{
// 					return evaluate_ast(node->children[1], definitions, arg_map);
// 				}
// 				break;
// 			case lang_int:
// 				if (test_expression->stored_value.lang_int)
// 				{
// 					return evaluate_ast(node->children[2], definitions, arg_map);
// 				}
// 				else
// 				{
// 					return evaluate_ast(node->children[1], definitions, arg_map);
// 				}
// 			default:
// 				return evaluate_ast(node->children[2], definitions, arg_map);
// 				break;
// 			}
// 		}
// 		else if (node->token->value == "and")
// 		{
// 			for (int i = 0; i < node->children.size(); i++)
// 			{
// 				Token *current_val = evaluate_ast(node->children[i], definitions, arg_map);
// 				bool evaluation = true;

// 				switch (current_val->type)
// 				{
// 				case boolean:
// 					if (!current_val->stored_value.boolean)
// 					{
// 						evaluation = false;
// 					}
// 					break;
// 				case lang_int:
// 					if (!current_val->stored_value.lang_int)
// 					{
// 						evaluation = false;
// 					}
// 				default:
// 					break;
// 				}
// 				if (!evaluation)
// 				{
// 					Token *new_token = new Token("#f", 1, boolean);
// 					return new_token;
// 				}
// 			}
// 			Token *new_token = new Token("#t", 1, boolean);
// 			return new_token;
// 		}
// 		else if (node->token->value == "or")
// 		{
// 			for (int i = 0; i < node->children.size(); i++)
// 			{
// 				Token *current_val = evaluate_ast(node->children[i], definitions, arg_map);
// 				bool evaluation = false;

// 				switch (current_val->type)
// 				{
// 				case boolean:
// 					if (current_val->stored_value.boolean)
// 					{
// 						evaluation = true;
// 					}
// 					break;
// 				case lang_int:
// 					if (current_val->stored_value.lang_int)
// 					{
// 						evaluation = true;
// 					}
// 				default:
// 					break;
// 				}
// 				if (evaluation)
// 				{
// 					Token *new_token = new Token("#t", 1, boolean);
// 					return new_token;
// 				}
// 			}
// 			Token *new_token = new Token("#f", 1, boolean);
// 			return new_token;
// 		}
// 		else if (node->token->value == "values")
// 		{
// 			for (int i = 0; i < node->children.size(); i++)
// 			{
// 				if (i == node->children.size() - 1)
// 				{
// 					return evaluate_ast(node->children[i], definitions, arg_map);
// 				}
// 				else
// 				{
// 					evaluate_ast(node->children[i], definitions, arg_map);
// 				}
// 			}
// 			return node->token;
// 		}
// 		else
// 		{
// 			return node->token;
// 		}
// 		break;
// 	}
// 	case identifier:
// 	case opperand:
// 	{

// 		if (node->token->value == "define")
// 		{
// 			std::vector<Token *> compact_trees;

// 			return evaluate_function(node, compact_trees, definitions);

// 			break;
// 		}
// 		else if (node->token->value == "lambda_wrapper")
// 		{
// 			std::vector<Token *> compact_trees;

// 			for (int i = 1; i < node->children.size(); i++)
// 			{
// 				compact_trees.push_back(evaluate_ast(node->children[i], definitions, arg_map));
// 			}

// 			return evaluate_function(node, compact_trees, definitions);

// 			break;
// 		}
// 		else if (node->token->value == "lambda")
// 		{
// 			node->token->type = lambda_reference;
// 			node->token->stored_value.lambda_reference = node;

// 			return node->token;
// 		}
// 		else if (node->token->value == "map")
// 		{

// 			Token *list_val = evaluate_ast(node->children[1], definitions, arg_map);

// 			Token *new_token = new Token("list", 5, list);
// 			std::stringstream value;
// 			value << "(list ";
// 			for (int i = 0; i < list_val->stored_value.list.get_length(); i++)
// 			{
// 				Token *new_val = evaluate_function(node->children[0], std::vector<Token *>{list_val->stored_value.list.access(i)}, definitions);

// 				new_token->stored_value.list.append(new_val);

// 				value << new_val->value;

// 				if (i != list_val->stored_value.list.get_length() - 1)
// 				{
// 					value << " ";
// 				}
// 			}

// 			value << ")";

// 			new_token->value = value.str();

// 			return new_token;
// 		}
// 		else
// 		{
// 			std::vector<Token *> compact_trees;
// 			for (int i = 0; i < node->children.size(); i++)
// 			{
// 				compact_trees.push_back(evaluate_ast(node->children[i], definitions, arg_map));
// 			}

// 			return evaluate_function(node, compact_trees, definitions);

// 			break;
// 		}
// 	}

// 	default:
// 		return node->token;
// 		break;
// 	}
// }

// Token *Environment::evaluate_function(ASTTreeNode *node, std::vector<Token *> args, std::map<ASTTreeNode *, std::map<std::string, ASTTreeNode *>> &definitions, std::map<std::string, Token *> args_map)
// {
// 	switch (node->token->type)
// 	{
// 	case lambda_reference:
// 		if (node->token->value == "lambda")
// 		{

// 			std::vector<ASTTreeNode *> argument_names = node->children[0]->children;

// 			std::map<std::string, Token *> *arg_map = new std::map<std::string, Token *>();

// 			for (int i = 0; i < argument_names.size(); i++)
// 			{
// 				(*arg_map)[argument_names[i]->token->value] = args[i];
// 			}

// 			ASTTreeNode *definition = node->children[1];

// 			return evaluate_ast(definition, definitions, arg_map);
// 		}
// 		else
// 		{
// 			return node->token;
// 		}
// 		break;
// 	case opperand:
// 		if (node->token->value == "+")
// 		{
// 			TokenType type = lang_int;
// 			float accumulator = 0;
// 			int precedence = -1;
// 			for (int i = 0; i < args.size(); i++)
// 			{
// 				if (args[i]->precedence > precedence)
// 				{
// 					precedence = args[i]->precedence;
// 				}

// 				if (args[i]->type == lang_int)
// 				{
// 					accumulator += args[i]->stored_value.lang_int;
// 				}
// 				else if (args[i]->type == lang_float)
// 				{
// 					type = lang_float;
// 					accumulator += args[i]->stored_value.lang_float;
// 				}
// 				else
// 				{
// 					// The value passed is not an int nor a float, so it is an error
// 					error_message(type_error, construct_type_error(TokenTypes::get(args[i]->type), args[i]->value, "number"));
// 				}
// 			}

// 			std::string new_value;

// 			if (type == lang_int)
// 			{
// 				int new_int = static_cast<int>(accumulator);
// 				new_value = std::to_string(new_int);
// 			}
// 			else
// 			{
// 				new_value = std::to_string(accumulator);
// 			}

// 			Token *new_token = new Token(new_value,
// 										 precedence, type);
// 			return new_token;
// 		}

// 		else if (node->token->value == "*")
// 		{
// 			TokenType type = lang_int;
// 			float accumulator = 1;
// 			int precedence = -1;
// 			for (int i = 0; i < args.size(); i++)
// 			{
// 				if (args[i]->precedence > precedence)
// 				{
// 					precedence = args[i]->precedence;
// 				}

// 				if (args[i]->type == lang_int)
// 				{
// 					accumulator *= std::stoi(args[i]->value);
// 				}
// 				else if (args[i]->type == lang_float)
// 				{
// 					type = lang_float;
// 					accumulator *= std::stof(args[i]->value);
// 				}
// 				else
// 				{
// 					// BIG FUCKIN ERROR
// 				}
// 			}
// 			Token *new_token = new Token(std::to_string(
// 											 type == lang_float ? accumulator : (int)accumulator),
// 										 precedence, type);
// 			return new_token;
// 		}
// 		else if (node->token->value == ">")
// 		{

// 			if (args.size() == 2)
// 			{

// 				if (
// 					((args[0]->type == lang_int) || (args[0]->type == lang_float)) &&
// 					((args[1]->type == lang_int) || (args[1]->type == lang_float)))
// 				{

// 					bool comparison = (args[0]->type == lang_float ? args[0]->stored_value.lang_float : args[0]->stored_value.lang_int) > (args[1]->type == lang_float ? args[1]->stored_value.lang_float : args[1]->stored_value.lang_int);

// 					Token *new_token = new Token(comparison ? "#t" : "#f",
// 												 4, boolean);

// 					return new_token;
// 				}
// 				else
// 				{
// 					// type error
// 					return node->token;
// 				}
// 			}
// 			else
// 			{
// 				// argument error
// 				return node->token;
// 			}
// 		}
// 		else if (node->token->value == "<")
// 		{

// 			if (args.size() == 2)
// 			{

// 				if (
// 					((args[0]->type == lang_int) || (args[0]->type == lang_float)) &&
// 					((args[1]->type == lang_int) || (args[1]->type == lang_float)))
// 				{

// 					bool comparison = (args[0]->type == lang_float ? args[0]->stored_value.lang_float : args[0]->stored_value.lang_int) < (args[1]->type == lang_float ? args[1]->stored_value.lang_float : args[1]->stored_value.lang_int);

// 					Token *new_token = new Token(comparison ? "#t" : "#f",
// 												 4, boolean);

// 					return new_token;
// 				}
// 				else
// 				{
// 					// type error
// 					return node->token;
// 				}
// 			}
// 			else
// 			{
// 				// argument error
// 				return node->token;
// 			}
// 		}
// 		// else if (name->value == "/")
// 		// {
// 		// }
// 		// else if (name->value == "-")
// 		// {
// 		// }

// 		else
// 		{
// 			return node->token;
// 		}
// 		break;
// 	case identifier:
// 		if (node->token->value == "print")
// 		{
// 			if (args.size() == 1)
// 			{
// 				std::cout << args[0]->value << "\n";
// 				return args[0];
// 			}
// 			else
// 			{
// 				Token *new_token = new Token("print", -1, error);
// 				return new_token;
// 				// BIG FUCKIN ERROR
// 			}
// 		}
// 		else if (node->token->value == "empty?")
// 		{
// 			if (args[0]->stored_value.list.get_length() == 0)
// 			{
// 				return new Token("#t", 1, boolean);
// 			}
// 			return new Token("#f", 1, boolean);
// 		}
// 		else if (node->token->value == "cons?")
// 		{
// 			if (args[0]->stored_value.list.get_length() == 0)
// 			{
// 				return new Token("#f", 1, boolean);
// 			}
// 			return new Token("#t", 1, boolean);
// 		}
// 		else if (node->token->value == "empty")
// 		{
// 			Token *new_token = new Token("list", 5, list);
// 			std::stringstream value;
// 			value << "(list )";
// 			new_token->value = value.str();
// 			return new_token;
// 		}
// 		else if (node->token->value == "cons")
// 		{

// 			Token *new_token = new Token("list", 5, list);

// 			new_token->stored_value.list = args[1]->stored_value.list.prepend(args[0]);

// 			std::stringstream value;
// 			value << "(list ";
// 			for (int i = 0; i < new_token->stored_value.list.get_length(); i++)
// 			{
// 				value << new_token->stored_value.list.access(i)->value;
// 				if (i != new_token->stored_value.list.get_length() - 1)
// 				{
// 					value << " ";
// 				}
// 			}
// 			value << ")";
// 			new_token->value = value.str();
// 			return new_token;
// 		}
// 		else if (node->token->value == "lambda_wrapper")
// 		{
// 			std::vector<ASTTreeNode *> argument_names = node->children[0]->children[0]->children;

// 			std::map<std::string, Token *> *arg_map = new std::map<std::string, Token *>();

// 			for (int i = 0; i < argument_names.size(); i++)
// 			{
// 				(*arg_map)[argument_names[i]->token->value] = args[i];
// 			}

// 			ASTTreeNode *definition = node->children[0]->children[1];

// 			return evaluate_ast(definition, definitions, arg_map);
// 		}
// 		else if (node->token->value == "list")
// 		{

// 			Token *new_token = new Token("list", 5, list);
// 			std::stringstream value;
// 			value << "(list ";
// 			for (int i = 0; i < args.size(); i++)
// 			{
// 				new_token->stored_value.list.append(args[i]);
// 				value << args[i]->value;
// 				if (i != args.size() - 1)
// 				{
// 					value << " ";
// 				}
// 			}
// 			value << ")";
// 			new_token->value = value.str();
// 			return new_token;
// 		}
// 		else if (node->token->value == "first")
// 		{
// 			Token **new_token = args[0]->stored_value.list.first();
// 			if (new_token == nullptr)
// 			{
// 				return node->token;
// 			}
// 			else
// 			{
// 				return *new_token;
// 			}
// 		}
// 		else if (node->token->value == "rest")
// 		{
// 			LinkedList<Token *> *new_list = args[0]->stored_value.list.rest();

// 			Token *new_token = new Token("list", 5, list);
// 			new_token->stored_value.list = *new_list;
// 			std::stringstream value;
// 			value << "(list ";
// 			for (int i = 0; i < new_list->get_length(); i++)
// 			{
// 				value << new_list->access(i)->value;
// 				if (i != new_list->get_length() - 1)
// 				{
// 					value << " ";
// 				}
// 			}
// 			value << ")";
// 			new_token->value = value.str();
// 			return new_token;
// 		}

// 		else if (node->token->value == "sqrt")
// 		{
// 			// return node->token;

// 			if (args.size() == 1)
// 			{

// 				float val = 0;

// 				if (args[0]->type == lang_int)
// 				{

// 					val = std::sqrt(args[0]->stored_value.lang_int);
// 				}
// 				else if (args[0]->type == lang_float)
// 				{
// 					val = std::sqrt(args[0]->stored_value.lang_float);
// 				}
// 				else
// 				{
// 					// The value passed is not an int nor a float, so it is an error
// 					error_message(type_error, construct_type_error(TokenTypes::get(args[0]->type), args[0]->value, "number"));
// 				}

// 				Token *new_token = new Token(std::to_string(val), args[0]->precedence, lang_float);
// 				return new_token;
// 			}
// 			else
// 			{
// 				// throw argument error

// 				// Token *new_token = new Token("0", 1, lang_float);

// 				return node->token;

// 				// return new_token;
// 			}
// 		}
// 		else if (node->token->value == "define")
// 		{
// 			// if it's a definition, add it to the definition map
// 			definitions[node->parent][node->children[0]->token->value] = node;
// 			return node->token;
// 		}
// 		else
// 		{
// 			return node->token;
// 		}
// 		break;
// 	case variable:
// 	{

// 		ASTTreeNode *definition = find_function_definition(node->parent, node->token->value, definitions);

// 		// std::cout << definition << "\n";

// 		if (definition != nullptr)
// 		{

// 			if (node->children.size() != args.size())
// 			{
// 				// whoops, wrong number of arguments
// 				return node->token;
// 			}
// 			else
// 			{
// 				// map to hold arguments
// 				std::map<std::string, Token *> *arg_map = new std::map<std::string, Token *>();
// 				for (int i = 0; i < node->children.size(); i++)
// 				{
// 					// std::cout << definition->children[0]->children[i]->token->value << "\n";
// 					(*arg_map)[definition->children[0]->children[i]->token->value] = args[i];
// 				}

// 				// std::cout << definition->children[1]->token->value << "\n";
// 				// std::cout << arg_map["arg_1"]->value << "\n";
// 				// std::cout << arg_map["arg_2"]->value << "\n";

// 				return evaluate_ast(definition->children[1], definitions, arg_map);
// 				// return evaluate_function(definition->children[0], args, definitions, arg_map);
// 				// return node->token;
// 			}
// 		}
// 		else
// 		{
// 			// std::cout << "called a function that doesn't exist\n";
// 			return node->token;
// 			// tried to call a function that doesn't exist
// 		}

// 		break;
// 	}
// 	default:
// 		return node->token;
// 		break;
// 	}
// }

// Token *Environment::evaluate_function_with_args(ASTTreeNode *node, std::map<std::string, Token *> args, std::map<ASTTreeNode *, std::map<std::string, ASTTreeNode *>> &definitions)
// {
// 	if (node)
// 		std::cout << node->children[1]->token->value << " tits\n";

// 	switch (node->token->type)
// 	{
// 	case variable:
// 	case identifier:
// 	case opperand:

// 		for (int i = 0; i < node->children.size(); i++)
// 		{
// 			compact_trees.push_back(evaluate_ast(node->children[i], definitions));
// 		}

// 		return evaluate_function(node, compact_trees, definitions);

// 		break;
// 	default:
// 		return node->token;
// 		break;
// 	}

// 	return node->token;
// }

// ASTTreeNode *Environment::find_function_definition(ASTTreeNode *node, std::string name, std::map<ASTTreeNode *, std::map<std::string, ASTTreeNode *>> &definitions)
// {

// 	// if we're past the root node, the definition doesn't exist. return a nullptr
// 	if (node == nullptr)
// 	{
// 		return nullptr;
// 	}
// 	else
// 	{
// 		// this all just checks if the parent node has any definitions at all.
// 		// if it does, continue with the function. If not, move up one level and try again.
// 		auto it = definitions.find(node);
// 		std::map<std::string, ASTTreeNode *> current_definitions;
// 		if (it != definitions.end())
// 		{
// 			//element found;
// 			current_definitions = it->second;

// 			// now check if the current definitions contain the particular one we're looking for
// 			auto it_2 = current_definitions.find(name);
// 			ASTTreeNode *definition;
// 			if (it_2 != current_definitions.end())
// 			{
// 				// definition exists; return reference
// 				definition = it_2->second;
// 				return definition;
// 			}
// 			else
// 			{
// 				// if not, then try again with parent
// 				return find_function_definition(node->parent, name, definitions);
// 			}
// 		}
// 		else
// 		{
// 			return find_function_definition(node->parent, name, definitions);
// 		}
// 	}
// }

void Environment::error_message(ErrorType type, std::string error, int line, int character)
{
	std::stringstream location;
	location << " On line " << line << " at character " << character;
	switch (type)
	{
	case type_error:
		std::cout << KRED << error << location.str() << RST << std::endl;
		break;
	case parse_error:
		std::cout << KRED << error << location.str() << RST << std::endl;
		break;
	default:
		std::cout << KRED << error << location.str() << RST << std::endl;
		break;
	}
}

std::string Environment::construct_type_error(std::string type, std::string value, std::string expected)
{
	std::stringstream ss;
	ss << "Type Error: " << type << " \"" << value << "\" is not a " << expected << ".";
	return ss.str();
}

std::string Environment::construct_argument_error(std::string function_name, int expected, int found)
{
	std::stringstream ss;
	ss << "Argument Error: Function call to " << function_name << " expected " << expected << " arguments, found " << found << ".";
	return ss.str();
}

std::string Environment::construct_definition_error(std::string function_name)
{
	std::stringstream ss;
	ss << "Definition Error: Undefined function " << function_name << ".";
	return ss.str();
}
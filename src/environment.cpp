#include <iostream>
#include <vector>
#include <sstream>

#include "colors.hpp"
#include "parser.hpp"
#include "token.hpp"
#include "evaluation.hpp"
#include "environment.hpp"

Environment::Environment(bool verbose)
{
	this->verbose = verbose;
	this->arg_map = std::map<std::string, Token *>();
}

void Environment::evaluate(ASTTreeNode *root)
{

	Token *final = nullptr;

	for (int i = 0; i < root->children.size(); i++)
	{
		arg_map.clear();
		Token *current = evaluate_node(root->children[i]);
		final = current;
	}

	if (verbose)
	{
		std::cout << "\n";
		if (final == nullptr)
		{
			std::cout << KGRN << BOLD("Program finished with exit code 0: No output") << RST << std::endl;
		}
		else
		{
			std::cout << KGRN << BOLD("Program finished with exit code 1: ") << Token::get_value(final) << RST << std::endl;
		}
		std::cout << "\n";
	}
	else
	{
		if (final == nullptr)
		{
			std::cout << KGRN << "0" << RST << std::endl;
		}
		else
		{
			std::cout << KGRN << Token::get_value(final) << RST << std::endl;
		}
		std::cout << "\n";
	}
}

Token *Environment::evaluate_variable(Token *token)
{
	if (token->type == variable)
	{

		auto itterator = arg_map.find(token->string_value);
		if (itterator != arg_map.end())
		{
			//element found;
			return evaluate_variable(itterator->second);
		}
		else
		{

			auto definition_itterator = definitions.find(token->string_value);

			if (definition_itterator != definitions.end())
			{
				// definition exists

				ASTTreeNode *function = definition_itterator->second;

				ASTTreeNode *args = function->children[1];

				if (args->children.size() == 0 || args->children.size() == 1)
				{
					ASTTreeNode *body = function->children[2];

					return evaluate_node(body);
				}
				else
				{
					return token;
				}
			}
			else
			{
				return token;
			}
		}
	}
	else
	{
		return token;
	}
}

Token *Environment::evaluate_node(ASTTreeNode *node)
{

	if (node->token == nullptr)
	{
		// No children, a useless node

		if (node->children.size() == 0)
		{
			return node->token;
		}
		else if (node->children[0]->token == nullptr)
		{

			Token *final = nullptr;

			for (int i = 0; i < node->children.size(); i++)
			{
				Token *current = evaluate_node(node->children[i]);
				final = current;
			}

			return final;
		}
		// Children, a non-useless node
		else
		{

			Token *first = evaluate_node(node->children[0]);

			if (first->type == keyword)
			{
				std::vector<Token *> rest;
				return Evaluation::evaluate_simple(first, rest, node, this);
			}
			else if (Evaluation::check_simple(first))
			{
				std::vector<Token *> rest = get_rest(node->children);
				return Evaluation::evaluate_simple(first, rest, node, this);
			}
			else
			{
				switch (first->type)
				{
				case identifier:
				{
					if (first->string_value == "lambda")
					{
						Token *new_token = new Token("lambda_reference", lambda_reference);
						new_token->stored_value.lambda_reference = node;
						return new_token;
					}
					else if (first->string_value == "define")
					{
						Token *name;

						if (node->children[1]->children.size() == 0)
						{
							name = node->children[1]->token;
						}
						else
						{
							name = node->children[1]->children[0]->token;
						}

						definitions[name->string_value] = node;
						return node->token;
					}
					else
					{
						return node->token;
					}
					break;
				}

				case variable:
				{
					auto itterator = definitions.find(first->string_value);
					if (itterator != definitions.end())
					{
						// definition exists

						std::vector<Token *> rest = get_rest(node->children);

						ASTTreeNode *function = itterator->second;

						ASTTreeNode *body = function->children[2];

						// just assume no argument errors for now :)
						for (int i = 1; i < function->children[1]->children.size(); i++)
						{
							Token *current = function->children[1]->children[i]->token;
							Token *value = rest[i - 1];
							arg_map[current->string_value] = value;
						}

						return evaluate_node(body);
					}
					else
					{
						return evaluate_variable(first);
					}

					break;
				}

				case opperand:
				{
					if (false)
					{
						return node->token;
					}
					else
					{
						return node->token;
					}
				}

				case lambda_reference:
				{

					std::vector<Token *> rest = get_rest(node->children);

					ASTTreeNode *body = first->stored_value.lambda_reference->children[2];

					// for now, just assume there wont be argument errors

					for (int i = 0; i < first->stored_value.lambda_reference->children[1]->children.size(); i++)
					{

						Token *current = first->stored_value.lambda_reference->children[1]->children[i]->token;
						Token *value = rest[i];
						arg_map[current->string_value] = value;
					}

					return evaluate_node(body);
					break;
				}

				case keyword:
				{
					if (false)
					{
						return node->token;
					}
					else
					{
						return node->token;
					}
					break;
				}

				default:
					return node->token;
					break;
				}

				return node->token;
			}
		}
	}
	else
	{
		Token *return_val = evaluate_variable(node->token);

		if (return_val->type == error)
		{
			throw return_val->string_value;
		}
		else
		{
			return return_val;
		}
	}
}

std::vector<Token *> Environment::get_rest(std::vector<ASTTreeNode *> children)
{
	std::vector<Token *> rest;
	for (int i = 1; i < children.size(); i++)
	{
		rest.push_back(evaluate_node(children[i]));
	}
	return rest;
}

std::vector<Token *> Environment::get_all(std::vector<ASTTreeNode *> children)
{
	std::vector<Token *> all;
	for (int i = 1; i < children.size(); i++)
	{
		all.push_back(evaluate_node(children[i]));
	}
	return all;
}

Token *Environment::error_message(ErrorType type, std::string error_message, int line, int character)
{
	std::stringstream location;
	location << " On line " << line << " at character " << character;
	switch (type)
	{
	case type_error:
		std::cout << KRED << error_message << location.str() << RST << std::endl;
		break;
	case parse_error:
		std::cout << KRED << error_message << location.str() << RST << std::endl;
		break;
	default:
		std::cout << KRED << error_message << location.str() << RST << std::endl;
		break;
	}

	Token *token = new Token(error_message, error);

	return token;
}

std::string Environment::construct_type_error(std::string type, std::string value, std::string expected)
{
	std::stringstream ss;
	ss << "Type Error: " << type << " \"" << value << "\" is not a(n) " << expected << ".";
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
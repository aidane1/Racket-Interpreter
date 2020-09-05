#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

#include "lexer.hpp"
#include "tokenizer.hpp"
#include "parser.hpp"
#include "environment.hpp"
#include "token.hpp"
#include "colors.hpp"

// tokenizer
#include "tokenizer_list.hpp"

int main(int argc, char *argv[])
{
	// runtime process

	// step 1: lexical analysis
	// splits the input into strings that will then be
	// classified into tokens by the tokenizer

	// step 2: tokenizing
	// classifies the strings from the lexer into
	// complete tokens to be read by the parser

	// step 3: parsing
	// generates an AST from the tokens

	// step 4: evaluation
	// evaluates the AST to produce an output

	std::vector<std::string> flags = {"-v", "-f", "-h"};

	std::map<std::string, bool> found_flags;

	for (int i = 0; i < flags.size(); i++)
	{
		found_flags[flags[i]] = false;
	}

	if (argc > 1)
	{

		for (int i = 1; i < argc; i++)
		{
			for (int j = 0; j < flags.size(); j++)
			{
				if (argv[i] == flags[j])
				{
					found_flags[argv[i]] = true;
				}
			}
		}

		if (found_flags["-h"])
		{
			std::ifstream t("./text/help.txt");
			std::stringstream buffer;
			buffer << t.rdbuf();
			std::string help = buffer.str();
			std::cout << "\n" << help << "\n\n";
		}
		else
		{
			std::ifstream t(argv[1]);
			std::stringstream buffer;
			buffer << t.rdbuf();
			std::string program = buffer.str();
			if (found_flags["-v"])
			{
				std::cout << KYEL << "Lexing..." << RST << std::endl;
			}

			Lexer *lexer = new Lexer();

			std::vector<std::string> lex_strings = lexer->lex(program);

			if (found_flags["-v"])
			{
				lexer->dump(lex_strings);

				std::cout << KRED << "Lexer Done" << RST << std::endl
						  << "\n";

				std::cout << KBLU << "Tokenizing..." << RST << std::endl;
			}

			Tokenizer *tokenizer = get_tokens();

			std::vector<Token *> tokens = tokenizer->tokenize(lex_strings);

			if (found_flags["-v"])
			{
				tokenizer->dump(tokens);

				std::cout << KRED << "Tokenizer Done" << RST << std::endl
						  << "\n";

				std::cout << KMAG << "Parsing..." << RST << std::endl;
			}

			Parser *parser = new Parser();

			ASTTreeNode *root = parser->parse(tokens);

			if (found_flags["-v"])
			{
				parser->dump(root, 0);

				std::cout << KRED << "Parser Done" << RST << std::endl
						  << "\n";

				std::cout << KCYN << "Evaluating..." << RST << std::endl;
			}

			Environment *environment = new Environment();

			environment->evaluate(root);

			if (found_flags["-v"])
			{

				std::cout << KRED << "Evaluation Done" << RST << std::endl
						  << "\n";
			}
		}
	}
	else
	{

		if (found_flags["-l"])
		{
		}
		else
		{
			Environment *environment = new Environment(false);

			std::cout << "\n^C to exit shell"
					  << "\n";
			std::cout << "Enter twice to execute statement"
					  << "\n";

			while (true)
			{
				std::cout << "\n>> ";
				std::string input;
				bool first_check = false;
				bool second_check = false;
				while (!second_check)
				{
					int c = getchar();
					input.push_back(c);
					if (c == '\n')
					{
						if (first_check)
						{
							second_check = first_check;
						}
						else
						{
							first_check = true;
						}
					}
					else
					{
						first_check = false;
					}
				}

				if (input == "exit")
				{
					break;
				}
				else
				{
					Lexer *lexer = new Lexer();

					std::vector<std::string> lex_strings = lexer->lex(input);

					Tokenizer *tokenizer = get_tokens();

					std::vector<Token *> tokens = tokenizer->tokenize(lex_strings);

					Parser *parser = new Parser();

					ASTTreeNode *root = parser->parse(tokens);

					environment->evaluate(root);
				}
			}
		}
	}

	return 0;
}
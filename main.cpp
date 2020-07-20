// path: /main.cpp

#include <iostream>
#include "lexer.hpp"
#include "token.hpp"
#include "parser.hpp"
#include "tree_node.hpp"
#include "environment.hpp"
#include "linked_list.hpp"
#include "colors.hpp"

#include <regex>
#include <map>
#include <sstream>
#include <fstream>

int main(int argc, char *argv[])
{

	Lexer *lexer = new Lexer();

	// matches comments, ";;" followed by any characters until the new line
	lexer->add_symbol(
		TokenMatcher(std::regex("^;;.*\n", std::regex_constants::ECMAScript | std::regex_constants::icase), 11, symbol), [](std::string value, int index, std::smatch match) -> auto {
			return std::pair<int, Token *>(match.length(), new Token("comment", 11, symbol));
		});

	// matches a "(" followed by zero or more whitespace characters
	lexer->add_symbol(
		TokenMatcher(std::regex("^\\(\\s*", std::regex_constants::ECMAScript | std::regex_constants::icase), 10, symbol), [](std::string value, int index, std::smatch match) -> auto {
			return std::pair<int, Token *>(match.length(), new Token("(", 10, symbol));
		});

	// matches a ")" followed by zero or more whitespace characters
	lexer->add_symbol(
		TokenMatcher(std::regex("^\\)\\s*", std::regex_constants::ECMAScript | std::regex_constants::icase), 10, symbol), [](std::string value, int index, std::smatch match) -> auto {
			return std::pair<int, Token *>(match.length(), new Token(")", 10, symbol));
		});

	// matches a "[" followed by zero or more whitespace characters
	lexer->add_symbol(
		TokenMatcher(std::regex("^\\[\\s*", std::regex_constants::ECMAScript | std::regex_constants::icase), 10, symbol), [](std::string value, int index, std::smatch match) -> auto {
			return std::pair<int, Token *>(match.length(), new Token("[", 10, symbol));
		});

	// matches a "]" followed by zero or more whitespace characters
	lexer->add_symbol(
		TokenMatcher(std::regex("^\\]\\s*", std::regex_constants::ECMAScript | std::regex_constants::icase), 10, symbol), [](std::string value, int index, std::smatch match) -> auto {
			return std::pair<int, Token *>(match.length(), new Token("]", 10, symbol));
		});

	// matches a "+" sign followed by at least one whitespace character
	lexer->add_symbol(
		TokenMatcher(std::regex("^\\+\\s+", std::regex_constants::ECMAScript | std::regex_constants::icase), 7, opperand), [](std::string value, int index, std::smatch match) -> auto {
			return std::pair<int, Token *>(match.length(), new Token("+", 7, opperand));
		});

	// matches a "-" sign followed by at least one whitespace character
	lexer->add_symbol(
		TokenMatcher(std::regex("^-\\s+", std::regex_constants::ECMAScript | std::regex_constants::icase), 7, opperand), [](std::string value, int index, std::smatch match) -> auto {
			return std::pair<int, Token *>(match.length(), new Token("-", 7, opperand));
		});

	// matches a "/" sign followed by at least one whitespace character
	lexer->add_symbol(
		TokenMatcher(std::regex("^/\\s+", std::regex_constants::ECMAScript | std::regex_constants::icase), 7, opperand), [](std::string value, int index, std::smatch match) -> auto {
			return std::pair<int, Token *>(match.length(), new Token("/", 7, opperand));
		});

	// matches a "*" sign followed by at least one whitespace character
	lexer->add_symbol(
		TokenMatcher(std::regex("^\\*\\s+", std::regex_constants::ECMAScript | std::regex_constants::icase), 7, opperand), [](std::string value, int index, std::smatch match) -> auto {
			return std::pair<int, Token *>(match.length(), new Token("*", 7, opperand));
		});

	// matches a ">" sign followed by at least one whitespace character
	lexer->add_symbol(
		TokenMatcher(std::regex("^\\>\\s+", std::regex_constants::ECMAScript | std::regex_constants::icase), 7, opperand), [](std::string value, int index, std::smatch match) -> auto {
			return std::pair<int, Token *>(match.length(), new Token(">", 7, opperand));
		});

	// matches a "<" sign followed by at least one whitespace character
	lexer->add_symbol(
		TokenMatcher(std::regex("^\\<\\s+", std::regex_constants::ECMAScript | std::regex_constants::icase), 7, opperand), [](std::string value, int index, std::smatch match) -> auto {
			return std::pair<int, Token *>(match.length(), new Token("<", 7, opperand));
		});

	//matches the "cond" keyword
	lexer->add_symbol(
		TokenMatcher(std::regex("^cond\\s+", std::regex_constants::ECMAScript | std::regex_constants::icase), 6, keyword), [](std::string value, int index, std::smatch match) -> auto {
			return std::pair<int, Token *>(match.length(), new Token("cond", 6, keyword));
		});

	//matches the "if" keyword
	lexer->add_symbol(
		TokenMatcher(std::regex("^if\\s+", std::regex_constants::ECMAScript | std::regex_constants::icase), 6, keyword), [](std::string value, int index, std::smatch match) -> auto {
			return std::pair<int, Token *>(match.length(), new Token("if", 6, keyword));
		});

	//matches the "unless" keyword
	lexer->add_symbol(
		TokenMatcher(std::regex("^unless\\s+", std::regex_constants::ECMAScript | std::regex_constants::icase), 6, keyword), [](std::string value, int index, std::smatch match) -> auto {
			return std::pair<int, Token *>(match.length(), new Token("unless", 6, keyword));
		});

	//matches the "and" keyword
	lexer->add_symbol(
		TokenMatcher(std::regex("^and\\s+", std::regex_constants::ECMAScript | std::regex_constants::icase), 6, keyword), [](std::string value, int index, std::smatch match) -> auto {
			return std::pair<int, Token *>(match.length(), new Token("and", 6, keyword));
		});

	//matches the "or" keyword
	lexer->add_symbol(
		TokenMatcher(std::regex("^or\\s+", std::regex_constants::ECMAScript | std::regex_constants::icase), 6, keyword), [](std::string value, int index, std::smatch match) -> auto {
			return std::pair<int, Token *>(match.length(), new Token("or", 6, keyword));
		});

	//matches the "define" identifier
	lexer->add_symbol(
		TokenMatcher(std::regex("^define\\s+", std::regex_constants::ECMAScript | std::regex_constants::icase), 5, identifier), [](std::string value, int index, std::smatch match) -> auto {
			return std::pair<int, Token *>(match.length(), new Token("define", 5, identifier));
		});

	//matches the "lambda" identifier
	lexer->add_symbol(
		TokenMatcher(std::regex("^lambda\\s+", std::regex_constants::ECMAScript | std::regex_constants::icase), 5, identifier), [](std::string value, int index, std::smatch match) -> auto {
			return std::pair<int, Token *>(match.length(), new Token("lambda", 5, identifier));
		});

	//matches the "print" identifier
	lexer->add_symbol(
		TokenMatcher(std::regex("^print\\s+", std::regex_constants::ECMAScript | std::regex_constants::icase), 5, identifier), [](std::string value, int index, std::smatch match) -> auto {
			return std::pair<int, Token *>(match.length(), new Token("print", 5, identifier));
		});

	//matches the "list" identifier
	lexer->add_symbol(
		TokenMatcher(std::regex("^list\\s+", std::regex_constants::ECMAScript | std::regex_constants::icase), 5, identifier), [](std::string value, int index, std::smatch match) -> auto {
			return std::pair<int, Token *>(match.length(), new Token("list", 5, identifier));
		});

	//matches the "first" identifier
	lexer->add_symbol(
		TokenMatcher(std::regex("^first\\s+", std::regex_constants::ECMAScript | std::regex_constants::icase), 5, identifier), [](std::string value, int index, std::smatch match) -> auto {
			return std::pair<int, Token *>(match.length(), new Token("first", 5, identifier));
		});

	//matches the "rest" identifier
	lexer->add_symbol(
		TokenMatcher(std::regex("^rest\\s+", std::regex_constants::ECMAScript | std::regex_constants::icase), 5, identifier), [](std::string value, int index, std::smatch match) -> auto {
			return std::pair<int, Token *>(match.length(), new Token("rest", 5, identifier));
		});

	//matches the "empty?" identifier
	lexer->add_symbol(
		TokenMatcher(std::regex("^empty\\?\\s+", std::regex_constants::ECMAScript | std::regex_constants::icase), 5, identifier), [](std::string value, int index, std::smatch match) -> auto {
			return std::pair<int, Token *>(match.length(), new Token("empty?", 5, identifier));
		});

	//matches the "empty" identifier
	lexer->add_symbol(
		TokenMatcher(std::regex("^empty\\s*", std::regex_constants::ECMAScript | std::regex_constants::icase), 5, identifier), [](std::string value, int index, std::smatch match) -> auto {
			return std::pair<int, Token *>(match.length(), new Token("empty", 4, identifier));
		});

	//matches the "cons?" identifier
	lexer->add_symbol(
		TokenMatcher(std::regex("^cons\\?\\s+", std::regex_constants::ECMAScript | std::regex_constants::icase), 5, identifier), [](std::string value, int index, std::smatch match) -> auto {
			return std::pair<int, Token *>(match.length(), new Token("cons?", 5, identifier));
		});

	//matches the "cons" identifier
	lexer->add_symbol(
		TokenMatcher(std::regex("^cons\\s+", std::regex_constants::ECMAScript | std::regex_constants::icase), 5, identifier), [](std::string value, int index, std::smatch match) -> auto {
			return std::pair<int, Token *>(match.length(), new Token("cons", 4, identifier));
		});

	//matches the "map" identifier
	lexer->add_symbol(
		TokenMatcher(std::regex("^map\\s+", std::regex_constants::ECMAScript | std::regex_constants::icase), 5, identifier), [](std::string value, int index, std::smatch match) -> auto {
			return std::pair<int, Token *>(match.length(), new Token("map", 5, identifier));
		});

	//matches the "reduce" identifier
	lexer->add_symbol(
		TokenMatcher(std::regex("^reduce\\s+", std::regex_constants::ECMAScript | std::regex_constants::icase), 5, identifier), [](std::string value, int index, std::smatch match) -> auto {
			return std::pair<int, Token *>(match.length(), new Token("reduce", 5, identifier));
		});

	//matches the "filter" identifier
	lexer->add_symbol(
		TokenMatcher(std::regex("^filter\\s+", std::regex_constants::ECMAScript | std::regex_constants::icase), 5, identifier), [](std::string value, int index, std::smatch match) -> auto {
			return std::pair<int, Token *>(match.length(), new Token("filter", 5, identifier));
		});

	//matches the "sqrt" identifier
	lexer->add_symbol(
		TokenMatcher(std::regex("^sqrt\\s+", std::regex_constants::ECMAScript | std::regex_constants::icase), 5, identifier), [](std::string value, int index, std::smatch match) -> auto {
			return std::pair<int, Token *>(match.length(), new Token("sqrt", 5, identifier));
		});

	// matches symbols (' followed by a character list)
	lexer->add_symbol(
		TokenMatcher(std::regex(R"(^'[a-zA-Z0-9]+)", std::regex_constants::ECMAScript | std::regex_constants::icase), 5, lang_symbol), [](std::string value, int index, std::smatch match) -> auto {
			return std::pair<int, Token *>(match.length(), new Token(match.str().substr(1, match.str().length() - 1), 5, lang_symbol));
		});

	//matches boolean false "#f"
	lexer->add_symbol(
		TokenMatcher(std::regex("^#f", std::regex_constants::ECMAScript | std::regex_constants::icase), 4, boolean), [](std::string value, int index, std::smatch match) -> auto {
			return std::pair<int, Token *>(2, new Token("#f", 4, boolean));
		});

	//matches boolean true "#t"
	lexer->add_symbol(
		TokenMatcher(std::regex("^#t", std::regex_constants::ECMAScript | std::regex_constants::icase), 4, boolean), [](std::string value, int index, std::smatch match) -> auto {
			return std::pair<int, Token *>(2, new Token("#t", 4, boolean));
		});

	// matches variables at least one of (characters, digits, dashes, underscores, question marks, exclamation marks) that
	// starts with a letter or an underscore and has whitespace before the start
	lexer->add_symbol(
		TokenMatcher(std::regex(R"(^[a-zA-Z_][A-Za-z0-9\-_!?]*)", std::regex_constants::ECMAScript | std::regex_constants::icase), 3, variable), [](std::string value, int index, std::smatch match) -> auto {
			return std::pair<int, Token *>(match.length(), new Token(value.substr(index, match.length()), 3, variable));
		});

	// matches floats (numbers with decimals)
	lexer->add_symbol(
		TokenMatcher(std::regex("^\\d+\\.\\d+", std::regex_constants::ECMAScript | std::regex_constants::icase), 3, lang_float), [](std::string value, int index, std::smatch match) -> auto {
			return std::pair<int, Token *>(match.length(), new Token(match.str(), 3, lang_float));
		});

	// matches Two quotes surrounding zero or more of "any character that's not a quote or a backslash" or "a backslash followed by any character"
	// in even plainer english, matches strings
	lexer->add_symbol(
		TokenMatcher(std::regex(R"(^"(?:[^"\\]|\\.)*")", std::regex_constants::ECMAScript | std::regex_constants::icase), 1, string), [](std::string value, int index, std::smatch match) -> auto {
			return std::pair<int, Token *>(match.length(), new Token(value.substr(index + 1, match.str().length() - 2), 1, string));
		});

	// matches ints (at least one digit, no decimal)
	lexer->add_symbol(
		TokenMatcher(std::regex("^\\d+", std::regex_constants::ECMAScript | std::regex_constants::icase), 1, lang_int), [](std::string value, int index, std::smatch match) -> auto {
			return std::pair<int, Token *>(match.length(), new Token(value.substr(index, match.length()), 1, lang_int));
		});

	if (argc > 1)
	{
		std::ifstream t(argv[1]);
		std::stringstream buffer;
		buffer << t.rdbuf();
		std::string program = buffer.str();

		std::cout << KYEL << "Lexing..." << RST << std::endl;

		std::vector<Token *> output = lexer->lex(program);

		// lexer->dump(output);

		std::cout << KRED << "Lexer Done" << RST << std::endl;

		Parser *parser = new Parser();

		std::cout << KBLU << "Parsing..." << RST << std::endl;

		ASTTreeNode *ast = parser->generate_abstract_syntax_tree(output);

		std::cout << KRED << "Parser Done" << RST << std::endl;

		// parser->dump(ast);


		Environment *environment = new Environment();

		environment->evaluate(ast);

		delete environment;

		delete parser;
	}
	else
	{
		std::cout << "No program passed\n";
	}

	// LinkedList<int> list;
	// list.append(5);
	// list.append(6);
	// list.append(7);
	// auto split_list = list.split();
	// std::cout << "first: " << "\n";
	// std::cout << *split_list.first << "\n";
	// std::cout << "rest: " << "\n";
	// split_list.second->print();
	// std::cout << list.access(0) << "\n";
	// std::cout << list.access(1) << "\n";
	// std::cout << list.access(2) << "\n";

	delete lexer;

	return 0;
}
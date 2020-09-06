#include "tokenizer_list.hpp"

Tokenizer *get_tokens()
{
	Tokenizer *tokenizer = new Tokenizer();

	// matches a "(" followed by zero or more whitespace characters
	tokenizer->add_symbol(
		std::regex("^\\(", std::regex_constants::ECMAScript | std::regex_constants::icase), 10, symbol, [](std::string value, int index, std::smatch match) -> auto {
			return std::pair<int, Token *>(1, new Token("(", symbol));
		});

	// matches a ")" followed by zero or more whitespace characters
	tokenizer->add_symbol(
		std::regex("^\\)", std::regex_constants::ECMAScript | std::regex_constants::icase), 10, symbol, [](std::string value, int index, std::smatch match) -> auto {
			return std::pair<int, Token *>(1, new Token(")", symbol));
		});

	// matches a "[" followed by zero or more whitespace characters
	tokenizer->add_symbol(
		std::regex("^\\[", std::regex_constants::ECMAScript | std::regex_constants::icase), 10, symbol, [](std::string value, int index, std::smatch match) -> auto {
			return std::pair<int, Token *>(match.length(), new Token("[", symbol));
		});

	// matches a "]" followed by zero or more whitespace characters
	tokenizer->add_symbol(
		std::regex("^\\]", std::regex_constants::ECMAScript | std::regex_constants::icase), 10, symbol, [](std::string value, int index, std::smatch match) -> auto {
			return std::pair<int, Token *>(match.length(), new Token("]", symbol));
		});

	//matches the "display" identifier
	tokenizer->add_symbol(
		std::regex("^display", std::regex_constants::ECMAScript | std::regex_constants::icase), 5, identifier, [](std::string value, int index, std::smatch match) -> auto {
			return std::pair<int, Token *>(match.length(), new Token("display", identifier));
		});

	//matches the "define" identifier
	tokenizer->add_symbol(
		std::regex("^define", std::regex_constants::ECMAScript | std::regex_constants::icase), 5, identifier, [](std::string value, int index, std::smatch match) -> auto {
			return std::pair<int, Token *>(match.length(), new Token("define", identifier));
		});

	// matches Two quotes surrounding zero or more of "any character that's not a quote or a backslash" or "a backslash followed by any character"
	// in even plainer english, matches strings
	tokenizer->add_symbol(
		std::regex(R"(^"(?:[^"\\]|\\.)*")", std::regex_constants::ECMAScript | std::regex_constants::icase), 1, string, [](std::string value, int index, std::smatch match) -> auto {
			return std::pair<int, Token *>(match.length(), new Token(value.substr(1, value.length() - 2), string));
		});

	//matches the "lambda" identifier
	tokenizer->add_symbol(
		std::regex("^lambda", std::regex_constants::ECMAScript | std::regex_constants::icase), 5, identifier, [](std::string value, int index, std::smatch match) -> auto {
			return std::pair<int, Token *>(match.length(), new Token("lambda", identifier));
		});

	// matches ints (at least one digit, no decimal)
	tokenizer->add_symbol(
		std::regex("^\\d+", std::regex_constants::ECMAScript | std::regex_constants::icase), 1, lang_int, [](std::string value, int index, std::smatch match) -> auto {
			return std::pair<int, Token *>(match.length(), new Token(value, lang_int));
		});

	// matches floats (numbers with decimals)
	tokenizer->add_symbol(
		std::regex("^\\d+\\.\\d+", std::regex_constants::ECMAScript | std::regex_constants::icase), 3, lang_float, [](std::string value, int index, std::smatch match) -> auto {
			return std::pair<int, Token *>(match.length(), new Token(match.str(), lang_float));
		});

	// matches variables at least one of (characters, digits, dashes, underscores, question marks, exclamation marks) that
	// starts with a letter or an underscore and has whitespace before the start
	tokenizer->add_symbol(
		std::regex(R"(^[a-zA-Z_][A-Za-z0-9\-_!?]*)", std::regex_constants::ECMAScript | std::regex_constants::icase), 3, variable, [](std::string value, int index, std::smatch match) -> auto {
			return std::pair<int, Token *>(match.length(), new Token(value, variable));
		});

	// matches a "+" sign followed by at least one whitespace character
	tokenizer->add_symbol(
		std::regex("^\\+", std::regex_constants::ECMAScript | std::regex_constants::icase), 7, opperand, [](std::string value, int index, std::smatch match) -> auto {
			return std::pair<int, Token *>(match.length(), new Token("+", opperand));
		});

	// matches a "-" sign followed by at least one whitespace character
	tokenizer->add_symbol(
		std::regex("^-", std::regex_constants::ECMAScript | std::regex_constants::icase), 7, opperand, [](std::string value, int index, std::smatch match) -> auto {
			return std::pair<int, Token *>(match.length(), new Token("-", opperand));
		});

	// matches a "*" sign followed by at least one whitespace character
	tokenizer->add_symbol(
		std::regex("^\\*", std::regex_constants::ECMAScript | std::regex_constants::icase), 7, opperand, [](std::string value, int index, std::smatch match) -> auto {
			return std::pair<int, Token *>(match.length(), new Token("*", opperand));
		});

	// matches a "/" sign followed by at least one whitespace character
	tokenizer->add_symbol(
		std::regex("^/", std::regex_constants::ECMAScript | std::regex_constants::icase), 7, opperand, [](std::string value, int index, std::smatch match) -> auto {
			return std::pair<int, Token *>(match.length(), new Token("/", opperand));
		});

	//matches the "list" identifier
	tokenizer->add_symbol(
		std::regex("^list", std::regex_constants::ECMAScript | std::regex_constants::icase), 5, identifier, [](std::string value, int index, std::smatch match) -> auto {
			return std::pair<int, Token *>(match.length(), new Token("list", identifier));
		});

	//matches the "first" identifier
	tokenizer->add_symbol(
		std::regex("^first", std::regex_constants::ECMAScript | std::regex_constants::icase), 5, identifier, [](std::string value, int index, std::smatch match) -> auto {
			return std::pair<int, Token *>(match.length(), new Token("first", identifier));
		});

	//matches the "rest" identifier
	tokenizer->add_symbol(
		std::regex("^rest", std::regex_constants::ECMAScript | std::regex_constants::icase), 5, identifier, [](std::string value, int index, std::smatch match) -> auto {
			return std::pair<int, Token *>(match.length(), new Token("rest", identifier));
		});

	//matches the "empty?" identifier
	tokenizer->add_symbol(
		std::regex("^empty\\?", std::regex_constants::ECMAScript | std::regex_constants::icase), 6, identifier, [](std::string value, int index, std::smatch match) -> auto {
			return std::pair<int, Token *>(match.length(), new Token("empty?", identifier));
		});

	//matches the "empty" identifier
	tokenizer->add_symbol(
		std::regex("^empty", std::regex_constants::ECMAScript | std::regex_constants::icase), 5, identifier, [](std::string value, int index, std::smatch match) -> auto {
			return std::pair<int, Token *>(match.length(), new Token("empty", identifier));
		});

	//matches the "cons?" identifier
	tokenizer->add_symbol(
		std::regex("^cons\\?", std::regex_constants::ECMAScript | std::regex_constants::icase), 6, identifier, [](std::string value, int index, std::smatch match) -> auto {
			return std::pair<int, Token *>(match.length(), new Token("cons?", identifier));
		});

	//matches the "equal?" identifier
	tokenizer->add_symbol(
		std::regex("^equal\\?", std::regex_constants::ECMAScript | std::regex_constants::icase), 6, identifier, [](std::string value, int index, std::smatch match) -> auto {
			return std::pair<int, Token *>(match.length(), new Token("equal?", identifier));
		});

	//matches the "cons" identifier
	tokenizer->add_symbol(
		std::regex("^cons", std::regex_constants::ECMAScript | std::regex_constants::icase), 5, identifier, [](std::string value, int index, std::smatch match) -> auto {
			return std::pair<int, Token *>(match.length(), new Token("cons", identifier));
		});

	//matches the "cond" keyword
	tokenizer->add_symbol(
		std::regex("^cond", std::regex_constants::ECMAScript | std::regex_constants::icase), 6, keyword, [](std::string value, int index, std::smatch match) -> auto {
			return std::pair<int, Token *>(match.length(), new Token("cond", keyword));
		});

	//matches the "if" keyword
	tokenizer->add_symbol(
		std::regex("^if", std::regex_constants::ECMAScript | std::regex_constants::icase), 6, keyword, [](std::string value, int index, std::smatch match) -> auto {
			return std::pair<int, Token *>(match.length(), new Token("if", keyword));
		});

	//matches the "unless" keyword
	tokenizer->add_symbol(
		std::regex("^unless", std::regex_constants::ECMAScript | std::regex_constants::icase), 6, keyword, [](std::string value, int index, std::smatch match) -> auto {
			return std::pair<int, Token *>(match.length(), new Token("unless", keyword));
		});

	//matches the "and" keyword
	tokenizer->add_symbol(
		std::regex("^and", std::regex_constants::ECMAScript | std::regex_constants::icase), 6, keyword, [](std::string value, int index, std::smatch match) -> auto {
			return std::pair<int, Token *>(match.length(), new Token("and", keyword));
		});

	//matches the "or" keyword
	tokenizer->add_symbol(
		std::regex("^or", std::regex_constants::ECMAScript | std::regex_constants::icase), 6, keyword, [](std::string value, int index, std::smatch match) -> auto {
			return std::pair<int, Token *>(match.length(), new Token("or", keyword));
		});

	//matches boolean false "#f"
	tokenizer->add_symbol(
		std::regex("^#f", std::regex_constants::ECMAScript | std::regex_constants::icase), 4, boolean, [](std::string value, int index, std::smatch match) -> auto {
			return std::pair<int, Token *>(2, new Token("#f", boolean));
		});

	//matches boolean true "#t"
	tokenizer->add_symbol(
		std::regex("^#t", std::regex_constants::ECMAScript | std::regex_constants::icase), 4, boolean, [](std::string value, int index, std::smatch match) -> auto {
			return std::pair<int, Token *>(2, new Token("#t", boolean));
		});

	// matches a ">" sign followed by at least one whitespace character
	tokenizer->add_symbol(
		std::regex("^\\>", std::regex_constants::ECMAScript | std::regex_constants::icase), 7, opperand, [](std::string value, int index, std::smatch match) -> auto {
			return std::pair<int, Token *>(match.length(), new Token(">", opperand));
		});

	// matches a "<" sign followed by at least one whitespace character
	tokenizer->add_symbol(
		std::regex("^\\<", std::regex_constants::ECMAScript | std::regex_constants::icase), 7, opperand, [](std::string value, int index, std::smatch match) -> auto {
			return std::pair<int, Token *>(match.length(), new Token("<", opperand));
		});

	return tokenizer;
}

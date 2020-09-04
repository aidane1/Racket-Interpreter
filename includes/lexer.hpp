#ifndef LEXER
#define LEXER

#include <string>
#include <vector>

class Lexer
{
private:
public:
	std::vector<std::string> lex(std::string input);
	void dump(std::vector<std::string> input);
};

#endif
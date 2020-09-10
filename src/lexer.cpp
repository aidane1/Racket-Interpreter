#include "lexer.hpp"
#include <iostream>
#include <ctype.h>
#include <algorithm>
#include <regex>

// trim from start (in place)
static inline void ltrim(std::string &s)
{
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
				return !std::isspace(ch);
			}));
}

// trim from end (in place)
static inline void rtrim(std::string &s)
{
	s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
				return !std::isspace(ch);
			}).base(),
			s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s)
{
	ltrim(s);
	rtrim(s);
}

std::vector<std::string> Lexer::lex(std::string input)
{
	std::vector<std::string> output;

	std::vector<std::string> intermediate;

	int previous_index = 0;
	bool is_in_string = false;

	for (int i = 0; i < input.size(); i++)
	{
		// if we're already in a string, then...
		if (is_in_string)
		{
			// hit a quote
			if (input[i] == '\"')
			{

				// if it isn't an escaped quote within the string then exit the string
				if (i != 0 && input[i - 1] != '\\')
				{
					is_in_string = false;
					intermediate.push_back(input.substr(previous_index, i - previous_index + 1));
					previous_index = i + 1;
				}
			}
		}
		// otherwise, continue as usual
		else
		{
			// hit a semicolon
			if (input[i] == ';')
			{
				while (input[++i] != '\n' && i < input.size())
				{
				};
			}
			// hit a quote while not in a string
			else if (input[i] == '\"')
			{
				is_in_string = true;
				previous_index = i;
			}
			// hit a space
			else if (isspace(input[i]))
			{
				intermediate.push_back(input.substr(previous_index, i - previous_index + 1));
				previous_index = i + 1;
			}
			else if (input[i] == '(' || input[i] == ')' || input[i] == '[' || input[i] == ']')
			{
				intermediate.push_back(input.substr(previous_index, i - previous_index));
				intermediate.push_back(input.substr(i, 1));
				previous_index = i + 1;
			}
		}
	}

	// now to filter uneccessary whitespace

	for (int i = 0; i < intermediate.size(); i++)
	{
		if (!std::all_of(intermediate[i].begin(), intermediate[i].end(), isspace))
		{
			trim(intermediate[i]);
			output.push_back(intermediate[i]);
		}
	}

	return output;
}

void Lexer::dump(std::vector<std::string> input)
{
	for (int i = 0; i < input.size(); i++)
	{
		std::cout << input[i] << "\n";
	}
}

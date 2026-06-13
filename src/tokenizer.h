#pragma once

#include <string>
#include <vector>

namespace TehJSON
{
	enum struct TokenType
	{
		LBrace, 	// {
		RBrace,		// }
		LSquare,	// [
		RSquare,	// ]
		Colon,		// :
		Comma,		// ,
		StringLit,	// ".+"
		IntLit,		// -?[0-9]+
		FloatLit,	// -?[0-9]+.[0-9]+
		BoolLit,	// true|false
	};

	std::string getTokenName(TokenType t);

	struct Token
	{
		TokenType type;
		std::string content;
	};

	class Tokenizer
	{
	public:
		void appendInput(std::string s);
		std::vector<Token> tokenize();
		std::string getInput();
	private:
		std::string input = "";
	};
}

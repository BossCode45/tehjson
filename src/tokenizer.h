#pragma once

#include <string>
#include <vector>

namespace TehJSON
{
	enum struct TokenType
	{
		LBrace,
		RBrace,
		Colon,
		Comma,
		StringLit,
		IntLit,
		FloatLit,
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

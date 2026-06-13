#include "tokenizer.h"
#include <iostream>
#include <stdexcept>

namespace TehJSON
{
	std::string getTokenName(TokenType t)
	{
		switch(t)
		{
		case TokenType::LBrace: return "LBrace";
		case TokenType::RBrace: return "RBrace";
		case TokenType::LSquare: return "LSquare";
		case TokenType::RSquare: return "RSquare";
		case TokenType::Colon: return "Colon";
		case TokenType::Comma: return "Comma";
		case TokenType::StringLit: return "StringLit";
		case TokenType::IntLit: return "IntLit";
		case TokenType::FloatLit: return "FloatLit";
		case TokenType::BoolLit: return "BoolLit";
		}
	}
	
	void Tokenizer::appendInput(std::string s)
	{
		input += s;
	}

	std::vector<Token> Tokenizer::tokenize()
	{
		std::vector<Token> tokens;

		int pos = 0;
		while(pos < input.size())
		{
			char c = input.at(pos);
			switch(c)
			{
			case '\t':
			case '\n':
			case ' ': break;
			case '"':
			{
				pos++;
				if(pos >= input.size())
					throw std::out_of_range("String literal never ends!");
				std::string literalContent = "";
				c = input.at(pos);
				while(c != '"')
				{
					literalContent += std::string{c};
					pos++;
					if(pos >= input.size())
						throw std::out_of_range("String literal never ends!");
					c = input.at(pos);
				}
				tokens.push_back({TokenType::StringLit, literalContent});
				break;
			}
			case '-':
			case '0' ... '9': {
				std::string literalContent{c};
				pos++;
				c = input.at(pos);
				bool isInt = true;
				while((c >= '0' && c <= '9') || (c == '.'))
				{
					if(c == '.')
					{
						if(!isInt)
							throw std::runtime_error("Cannot have multiple decimal places in float");
						isInt = false;
					}
					literalContent += std::string{c};
					pos++;
					if(pos >= input.size())
						throw std::out_of_range("Number literal never ends!");
					c = input.at(pos);
				}
				pos--;
				tokens.push_back({isInt?TokenType::IntLit:TokenType::FloatLit, literalContent});
				break;
			}
			case 't':
			{
				if(input.at(++pos) != 'r'||
				   input.at(++pos) != 'u'||
				   input.at(++pos) != 'e')
				{
					throw std::runtime_error("Was expecting 'true' but got something else");
				}
				tokens.push_back({TokenType::BoolLit, "true"});
				break;
			}
			case 'f':
			{
				if(input.at(++pos) != 'a'||
				   input.at(++pos) != 'l'||
				   input.at(++pos) != 's'||
				   input.at(++pos) != 'e')
				{
					throw std::runtime_error("Was expecting 'false' but got something else");
				}
				tokens.push_back({TokenType::BoolLit, "false"});
				break;
			}
			case '{': tokens.push_back({TokenType::LBrace, std::string{c}}); break;
			case '}': tokens.push_back({TokenType::RBrace, std::string{c}}); break;
			case '[': tokens.push_back({TokenType::LSquare, std::string{c}}); break;
			case ']': tokens.push_back({TokenType::RSquare, std::string{c}}); break;
			case ':': tokens.push_back({TokenType::Colon, std::string{c}}); break;
			case ',': tokens.push_back({TokenType::Comma, std::string{c}}); break;
			default: throw std::runtime_error("Unexpected character: '" + std::string{c} + "'");
			}
			pos++;
		}

		return tokens;
	}

	std::string Tokenizer::getInput()
	{
		return input;
	}
}

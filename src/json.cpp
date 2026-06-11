#include "json.h"
#include "tokenizer.h"

#include <cstddef>
#include <stdexcept>
#include <string>

namespace TehJSON
{
	JSON::JSON()
		:children()
	{
	}
	
	JSON::~JSON()
	{
	}

	std::string JSON::leafType()
	{
		if(!isLeaf)
			throw std::runtime_error("Node is not a leaf!");
		throw std::runtime_error("Not implemented yet");
	}

	std::string JSON::getSerialized()
	{
		return _getSerialized(0);
	}
	std::string JSON::_getSerialized(int currIndent)
	{
		if(isLeaf)
			return dataSerializer(data);

		std::string serialized = "{\n";

		int childrenLeft = childCount();
		for(auto [childName, child]: children)
		{
			childrenLeft--;
			for(int i = 0; i < currIndent + 1; i++)
				serialized += '\t';
			serialized += "\"" + childName + "\": ";
			serialized += child._getSerialized(currIndent + 1);
			if(childrenLeft != 0)
				serialized += ',';
			serialized += '\n';
		}
		for(int i = 0; i < currIndent; i++)
			serialized += '\t';
		serialized += "}";

		return serialized;
	}

	JSON& JSON::operator[](std::string name)
	{
		if(isLeaf)
			throw std::runtime_error("Node is a leaf!");
		// if(children.count(name) == 0)
		// 	throw std::out_of_range("Child \"" + name + "\" does not exist");
		return children[name];
	}

	size_t JSON::childCount()
	{
		if(isLeaf)
			throw std::runtime_error("Node is a leaf!");
		return children.size();
	}

	Token JSON::consume()
	{
		if(tokenPos >= tokens.size())
			throw std::out_of_range("No tokens left, but json not finished!");
		return tokens[tokenPos++];
	}

	Token JSON::consume(TokenType type)
	{
		Token t = consume();
		if(t.type != type)
			throw std::runtime_error("Wrong token type, expected: " + getTokenName(type) + ", but got: " + getTokenName(t.type));
		return t;
	}
	
	TokenType JSON::nextTokenType()
	{
		if(tokenPos >= tokens.size())
			throw std::out_of_range("No tokens left, but json not finished!");
		return tokens[tokenPos].type;
	}

	void JSON::readFromString(std::string s)
	{
		Tokenizer tokenizer;
		tokenizer.appendInput(s);
		std::vector<Token> stringTokens = tokenizer.tokenize();

		readFromTokens(stringTokens);
	}

	void JSON::readFromTokens(std::vector<Token> tokens)
	{
		this->tokens = tokens;
		tokenPos = 0;
		
		consume(TokenType::LBrace);
		while(nextTokenType() != TokenType::RBrace)
		{
			Token childName = consume(TokenType::StringLit);
			// std::cout << "Child: " << childName.content << std::endl;
			consume(TokenType::Colon);
			switch(nextTokenType())
			{
			case TokenType::LBrace:
			{
				std::vector<Token> childTokens;
				while(nextTokenType() != TokenType::RBrace)
				{
					childTokens.push_back(consume());
				}
				childTokens.push_back(consume(TokenType::RBrace));
				children[childName.content].readFromTokens(childTokens);
				break;
			}
			case TokenType::StringLit: children[childName.content].set<std::string>(consume(TokenType::StringLit).content); break;
			case TokenType::IntLit: children[childName.content].set<int>(std::stoi(consume(TokenType::IntLit).content)); break;
			case TokenType::FloatLit: children[childName.content].set<float>(std::stof(consume(TokenType::FloatLit).content)); break;
			case TokenType::LSquare:
			{
				consume(TokenType::LSquare);
				std::vector<int> vec;
				while(nextTokenType() != TokenType::RSquare)
				{
					if(nextTokenType() != TokenType::IntLit)
						throw std::runtime_error("Only int arrays are supported so far");
					vec.push_back(std::stoi(consume(TokenType::IntLit).content));
					if(nextTokenType() == TokenType::Comma)
					{
						consume(TokenType::Comma);
					}
				}
				consume(TokenType::RSquare);
				children[childName.content].set<int>(vec);
				break;
			};
			default: throw std::runtime_error("Token type is not a literal!");
			}
			if(nextTokenType() != TokenType::RBrace)
				consume(TokenType::Comma);
		}
		consume(TokenType::RBrace);
	}
	
	// Serializers for basic types
	template <> std::string TehJSON::JSON::serializeData<int>(int *data)
	{
		return std::to_string(*data);
	}
	template <> std::string TehJSON::JSON::serializeData<float>(float *data)
	{
		return std::to_string(*data);
	}
	template <> std::string TehJSON::JSON::serializeData<std::string>(std::string *data)
	{
		return '"' + *data + '"';
	}
	template <> std::string TehJSON::JSON::serializeData<bool>(bool *data)
	{
		return (*data)?"true":"false";
	}
}

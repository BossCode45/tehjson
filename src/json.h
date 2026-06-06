#pragma once

#include "tokenizer.h"

#include <cstddef>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace TehJSON
{
	class JSON
	{
	public:
		JSON();
		JSON(const JSON& other) = default;
		~JSON();

		// Writing methods
		std::string getSerialized();
		std::string _getSerialized(int currIndent);

		// Reading methods
		void readFromString(std::string s);

		// Leaf methods
		template <typename T>
		T& get();
		template <typename T>
		void set(T value);
		std::string leafType();
		template <typename T>
		static std::string serializeData(std::shared_ptr<void> data);

		// Non leaf methods
		JSON& operator[](std::string name);
		size_t childCount();
		// std::vector<std::string> childNames();
	private:
		bool isLeaf = false;

		// Reading data fields
		std::vector<Token> tokens;
		int tokenPos = 0;
		Token consume();
		Token consume(TokenType type);
		TokenType nextTokenType();
		int readFromTokens(std::vector<Token> tokens, int pos);

		// Leaf data fields
		std::shared_ptr<void> data;
		std::string (*dataSerializer)(std::shared_ptr<void>);

		// Not leaf data fields
		std::map<std::string, JSON> children;
	};
}

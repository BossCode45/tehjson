#include <json.hpp>
#include <tokenizer.h>

#include <iostream>
#include <memory>

using std::cout, std::endl;

int main()
{
	TehJSON::JSON jsonWriter;
	// TestClass test1;
	// json["test1"].set(test1);
	jsonWriter["test_string"].set<std::string>("stringy");
	jsonWriter["test_int"].set<int>(123);
	jsonWriter["test_float"].set<float>(51.8);
	jsonWriter["test_object"]["test_int"].set<int>(100);
	jsonWriter["test_object"]["test_float"].set<float>(100);

	std::string jsonString = jsonWriter.getSerialized();
	cout << jsonString << endl;

	// TehJSON::Tokenizer tokenizer;
	// tokenizer.appendInput(jsonString);
	// std::vector<TehJSON::Token> tokens = tokenizer.tokenize();

	// for(const auto& token : tokens)
	// {
	// 	cout << TehJSON::getTokenName(token.type) << ": " << token.content << endl;
	// }

	TehJSON::JSON jsonReader;
	cout << "Reading: " << endl;
	jsonReader.readFromString(jsonString);
	cout << jsonReader.getSerialized() << endl;
}

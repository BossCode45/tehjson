#include <json.hpp>

#include <iostream>
#include <memory>

using std::cout, std::endl;

class TestClass {
private:
    int id;
    // std::string* testData;

public:
    // 1. Default Constructor: Sets initial "empty" state [20, 24]
    TestClass() : id(-1)/*, testData(new std::string("default"))*/ {
        std::cout << "Default Constructor called" << std::endl;
    }

    // 2. Parameterized Constructor: For dependency injection/direct testing [24, 25]
    TestClass(int id/*, std::string val*/) : id(id)/*, testData(new std::string(val))*/ {
        std::cout << "Parameterized Constructor (id: " << id << ")" << std::endl;
    }

    // 3. Copy Constructor (Rule of 5): Deep copies resource [14, 23]
    TestClass(const TestClass& other) : id(other.id+1)/*, testData(new std::string(*other.testData))*/ {
        std::cout << "Copy Constructor called" << id << std::endl;
    }

    // 4. Move Constructor (Rule of 5): Transfers ownership of resource [14, 16]
    TestClass(TestClass&& other) noexcept : id(other.id+1)/*, testData(other.testData)*/ {
        // other.testData = nullptr;
        other.id = -1;
        std::cout << "Move Constructor called" << id << std::endl;
    }

    // 5. Destructor: Essential for RAII and preventing memory leaks [14, 29]
    ~TestClass() {
        // delete testData;
        std::cout << "Destructor called" << id << std::endl;
    }

    // Assignment Operators (Standard Rule of 5)
    TestClass& operator=(const TestClass& other) {
        if (this == &other) return *this;
        // delete testData;
        id = other.id + 1;
        // testData = new std::string(*other.testData);
		std::cout << "Assignment op 1 called" << id << std::endl;
        return *this;
    }

    TestClass& operator=(TestClass&& other) noexcept {
        if (this == &other) return *this;
        // delete testData;
        id = other.id + 1;
        // testData = other.testData;
        // other.testData = nullptr;
		std::cout << "Assignment op 2 called" << id << std::endl;
        return *this;
    }

    // Helper for verification [18, 21]
    int getId() const { return id; }
    // std::string getData() const { return testData ? *testData : "null"; }
};


template <> std::string TehJSON::JSON::serializeData<int>(std::shared_ptr<void> data)
{
	return std::to_string(*static_cast<int*>(data.get()));
}
template <> std::string TehJSON::JSON::serializeData<float>(std::shared_ptr<void> data)
{
	return std::to_string(*static_cast<float*>(data.get()));
}
template <> std::string TehJSON::JSON::serializeData<TestClass>(std::shared_ptr<void> data)
{
	return "test class";
}
template <> std::string TehJSON::JSON::serializeData<std::string>(std::shared_ptr<void> data)
{
	return '"' + *static_cast<std::string*>(data.get()) + '"';
}


int main()
{
	TehJSON::JSON json;
	// TestClass test1;
	// json["test1"].set(test1);
	json["test_string"].set<std::string>("stringy");
	json["test_int"].set<int>(123);
	json["test_float"].set<float>(51.8);
	json["test_object"]["test_int"].set<int>(100);
	json["test_object"]["test_float"].set<float>(100);

	cout << json.getSerialized() << endl;
	
	// std::shared_ptr<void> test;
	// test = std::make_shared<TestClass>(1);
	// test = std::make_shared<TestClass>(2);
	// test = std::make_shared<std::string>(std::string("test"));
	// std::string& testRef = *(std::string*)test.get();
	// cout << *(std::string*)test.get() << endl;
	// testRef += " test2";
	// cout << *(std::string*)test.get() << endl;
	
	
	cout << "abc" << endl;
}

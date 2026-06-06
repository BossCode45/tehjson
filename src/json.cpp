#include "json.h"

#include <cstddef>
#include <stdexcept>

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
}

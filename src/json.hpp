#include "json.h"

#include <stdexcept>
#include <iostream>

namespace TehJSON
{

	template<typename T>
	T& JSON::get()
	{
		if(!isLeaf)
			throw std::runtime_error("Node is not a leaf!");
		
		return *static_cast<T*>(data.get());
	}

	template<typename T>
	void JSON::set(T value)
	{
		if(children.size() != 0)
			throw std::runtime_error("Node is not a leaf (has children already)!");
		isLeaf = true;
		dataSerializer = JSON::serializeData<T>;
		data = std::make_shared<T>(value);
	}

}

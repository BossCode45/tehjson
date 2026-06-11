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
	std::string TehJSON::JSON::serializeData(std::vector<T>* data)
	{
		std::string res = "[";
		for(int i = 0; i < data->size(); i++)
		{
			T x = data->at(i);
			// res += "inty";
			res += TehJSON::JSON::serializeData<T>(&x);
			if(i != data->size() - 1)
				res += ", ";
		}
		res += "]";
		return res;
	}

	template<typename T>
	void TehJSON::JSON::set(std::vector<T> value)
	{
		if(children.size() != 0)
			throw std::runtime_error("Node is not a leaf (has children already)!");
		isLeaf = true;
		dataSerializer = [](std::shared_ptr<void> data) -> std::string {
			return TehJSON::JSON::serializeData<T>((std::vector<T>*)(data.get()));
		};
		data = std::make_shared<std::vector<T>>(value);
	}
	template<typename T>
	void JSON::set(T value)
	{
		if(children.size() != 0)
			throw std::runtime_error("Node is not a leaf (has children already)!");
		isLeaf = true;
		dataSerializer = [](std::shared_ptr<void> data) -> std::string {
			return JSON::serializeData<T>((T*)(data.get()));
		};
		data = std::make_shared<T>(value);
	}
}

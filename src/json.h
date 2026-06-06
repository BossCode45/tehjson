#include <cstddef>
#include <map>
#include <memory>
#include <string>

namespace TehJSON
{
	class JSON
	{
	public:
		JSON();
		JSON(const JSON& other) = default;
		~JSON();

		// Leaf methods
		template <typename T>
		T& get();
		template <typename T>
		void set(T value);
		std::string leafType();
		std::string getSerialized();
		std::string _getSerialized(int currIndent);
		template <typename T>
		static std::string serializeData(std::shared_ptr<void> data);

		// Non leaf methods
		JSON& operator[](std::string name);
		size_t childCount();
		// std::vector<std::string> childNames();
	private:
		bool isLeaf = false;

		// Leaf data fields
		std::shared_ptr<void> data;
		std::string (*dataSerializer)(std::shared_ptr<void>);

		// Not leaf data fields
		std::map<std::string, JSON> children;
	};
}

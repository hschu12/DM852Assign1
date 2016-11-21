#include <functional>
#include <string>
#include <utility>
#include <iostream>
#include <iterator>
#include <vector>

namespace DM852{
template<typename Key, typename Value, typename Compare = std::less<Key>>
class sortedVector
{
	using key_type = Key;
	using mapped_type = Value;
	using value_type = std::pair<Key, Value>;
	using key_compare = Compare;

	public:
		sortedVector()
		{
		}
		~sortedVector()
		{

		}
	
		
		void find(Key &k)
		{

		}

		void insert(value_type &v) {
			std::cout << "insert &" << std::endl;
		}

		void insert(value_type &&v)
		{
			sortedVector.push_back(v.second);
		}

		void erase()
		{

		}

	};
}
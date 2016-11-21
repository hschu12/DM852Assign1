#include "sortedVector.hpp"
#include <iostream>
int main()
{

	DM852::sortedVector<int, int> sortedVector;
	std::pair<int, int> pair = std::make_pair(4,4);
	sortedVector.insert(pair);
	pair = std::make_pair(5,5);
	sortedVector.insert(pair);
	pair = std::make_pair(6,6);
	sortedVector.insert(pair);
	pair = std::make_pair(1,1);
	sortedVector.insert(pair);
	pair = std::make_pair(3,3);
	sortedVector.insert(pair);
	pair = std::make_pair(2,2);
	sortedVector.insert(pair);

}
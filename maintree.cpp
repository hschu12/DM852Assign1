#include "rbtree.hpp"
#include <iostream>
int main()
{

	DM852::RBtree<int, int> tree;
	std::pair<int, int> pair = std::make_pair(4,4);
	tree.insert(pair);
	std::cout << tree.root->color << " with value "<< tree.root->data << std::endl;
	return 0;
}
#include "rbtree.hpp"
#include <iostream>
int main()
{

	DM852::RBtree<int, int> tree;
	std::pair<int, int> pair = std::make_pair(4,4);
	tree.insert(pair);
	pair = std::make_pair(5,5);
	tree.insert(pair);
	pair = std::make_pair(6,6);
	tree.insert(pair);
	pair = std::make_pair(1,1);
	tree.insert(pair);
	pair = std::make_pair(3,3);
	tree.insert(pair);
	pair = std::make_pair(2,2);
	tree.insert(pair);

	std::cout << "done inserting" << std::endl;

	std::cout << "begin is " << (*(tree.begin())).data << std::endl;
	//std::cout << "end is " << (*(tree.end())).data << std::endl;
	/*for (auto it = tree.begin(); it != tree.end(); ++it)
	{
		std::cout << "for" << std::endl;
	}
	std::cout << std::endl;
	//std::cout << tree.root->color << " with value "<< tree.root->data << std::endl;
	*/
	tree.printTree(tree.root);

	return 0;
}
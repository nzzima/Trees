#include <iostream>
#include "BinaryTree.hpp"

int main()
{
    BinaryTree<int> tree;

	for (auto i = 0; i < 15; ++i)
		tree.AddKey(std::rand() % 15);

	tree.OutTree();

	bool check1 = tree.FindKey(10);
	bool check2 = tree.FindKey(8);
	
	std::cout << std::endl;
	std::cout << "Check_of_find_10 --> " << check1 << std::endl;
	std::cout << "Check_of_find_8 --> " << check2 << std::endl;
	std::cout << std::endl;
	
	tree.DeleteKey(1);
	tree.DeleteKey(3);
	tree.OutTree();
}

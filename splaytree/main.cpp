#include "splay_tree_api.h"
#include <iostream>

int main() {
	SplayTree<uint32_t, double> tree;

	tree.insert(67, 1.5);
	tree.insert(123, 0.5);

	double* value = tree.search(67);
	if (value) {
		std::cout << "value = " << *value << std::endl;
	} else {
		std::cout << "failed to find" << std::endl;
	}

	std::cout << "Size = " << tree.size() << std::endl;
	std::cout << "Is valid: " << tree.isValidBST() << std::endl;
	
	SplayTree<std::string, double> tree2;

	tree2.insert("apple", 1.5);
	tree2.insert("cherry", 0.5);

	double* value2 = tree2.search("apple");
	if (value2) {
		std::cout << "value = " << *value2 << std::endl;
	} else {
		std::cout << "failed to find" << std::endl;
	}

	std::cout << "Size = " << tree2.size() << std::endl;
	std::cout << "Is valid: " << tree2.isValidBST() << std::endl;
}

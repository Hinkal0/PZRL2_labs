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
}

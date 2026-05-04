#include <tuple>
#include <iostream>

struct Node {
    double val;
    Node* next;
	Node* prev;
};

Node* findStart(Node* head, Node* turtle) {
	while (head != turtle) {
		head = head->next;
		turtle = turtle->next;
	}
	return head;
}

size_t measure(Node* turtle, Node* hare) {
	size_t count = 0;
	while (hare) {
		hare = hare->next;
		++count;
		if (hare == turtle) return count;
	}
	return 0;
}

std::pair<Node*, size_t> floyd(Node* head) {
		Node* turtle = head;
		Node* hare = head;

		while (hare && turtle) {
			turtle = turtle->next;
			if (hare->next) hare = hare->next->next;
			else hare = nullptr;

			if (hare && (hare == turtle)) {
				return {findStart(head, turtle), measure(turtle, hare)};
			}
		}

		return {nullptr, 0};
}

int main() {
		Node* nodes[6];
		nodes[5] = new Node{6, nullptr};
		nodes[4] = new Node{5, nodes[5]};
		nodes[3] = new Node{4, nodes[4]};
		nodes[2] = new Node{3, nodes[3]};
		nodes[1] = new Node{2, nodes[2]};
		nodes[0] = new Node{1, nodes[1]};
		nodes[5]->next = nodes[2];

		std::pair<Node*, size_t> result = floyd(nodes[0]);
		if (result.first) {
				std::cout << "Цикл длины " << result.second << " в узле \'" << result.first->val << "\'" << std::endl;
		} else {
				std::cout << "Цикл не найден" << std::endl;
		}

		for (size_t i = 0; i < 6; i++) {
			delete nodes[i];
		}
}

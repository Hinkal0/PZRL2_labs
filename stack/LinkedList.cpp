#include "LinkedList.h"

DoubleLinkedList::DoubleLinkedList(const DoubleLinkedList& fl) {
	Node* t1 = fl.head;
	if (!t1) return;
	head = new Node({t1->val, nullptr, nullptr});
	Node* t2 = head;
	t1 = t1->next;
	while (t1) {
		t2->next = new Node({t1->val, nullptr, t2});
		t1 = t1->next;
		t2 = t2->next;
	}
	tail = t2;
}

DoubleLinkedList& DoubleLinkedList::operator=(const DoubleLinkedList& fl) {
	this->clear();
	Node* t1 = fl.head;
	if (!t1) return *this;
	head = new Node({t1->val, nullptr, nullptr});
	Node* t2 = head;
	t1 = t1->next;
	while (t1) {
		t2->next = new Node({t1->val, nullptr, t2});
		t1 = t1->next;
		t2 = t2->next;
	}
	tail = t2;
	return *this;
}

DoubleLinkedList::DoubleLinkedList(DoubleLinkedList&& fl) : head {fl.head}, tail {fl.tail} {
	fl.head = nullptr;
	fl.tail = nullptr;
}

DoubleLinkedList& DoubleLinkedList::operator=(DoubleLinkedList&& fl) {
	this->head = fl.head;
	this->tail = fl.tail;
	fl.head = nullptr;
	fl.tail = nullptr;
	return *this;
}

DoubleLinkedList::~DoubleLinkedList() {
	this->clear();
}

void DoubleLinkedList::push_front(double val) {
    head = new Node({val, head, nullptr});
	if (!head->next) {
		tail = head;	
		return;
	}
	head->next->prev = head;
}

void DoubleLinkedList::pop_front() {
    Node* t = head;
    head = head->next;
	head->prev = nullptr;
	if (!head) tail = nullptr;
    delete t;
}

void DoubleLinkedList::push_back(double val) {
	if (tail) {
		tail->next = new Node({val, nullptr, tail});
		tail = tail->next;
		return;
	}
	head = tail = new Node({val, nullptr, nullptr});
}

void DoubleLinkedList::pop_back() {
	if (!tail) return;
	if (!tail->prev) {
		delete tail;
		head = tail = nullptr;
		return;
	}
	Node* t = tail;
	tail = tail->prev;
	tail->next = nullptr;
	delete t;
}

void DoubleLinkedList::insert(size_t index, double val) {
	Node* current = head;
	while (index--) {
		current = current->next;
		if (!current) return;
	}
	
	Node* t = new Node({val, current, current->prev});
	current->prev = t;
	if (t->prev) t->prev->next = t;
}

double& DoubleLinkedList::front() {
	return head->val;
}

const double& DoubleLinkedList::front() const {
    return head->val;
}

double& DoubleLinkedList::back() {
	return tail->val;
}

const double& DoubleLinkedList::back() const {
	return tail->val;
}

size_t DoubleLinkedList::size() const {
    const Node* current = head;
    size_t s = 0;
    while (current) {
        current = current->next;
        ++s;
    }
    return s;
}

bool DoubleLinkedList::empty() const {
    return head == nullptr;
}

void DoubleLinkedList::erase(double val) {
    Node* current = head;
    while (current->next) {
        if (current->next->val != val) {
            current = current->next;
            continue;
        }
        Node* t = current->next->next;
        delete current->next;
        current->next = t;
		if (t) t->prev = current;
    }
	tail = current;
    if (head->val == val) {
        Node* t = head->next;
        delete head;
        head = t;
		if (t) t->prev = nullptr;
		else tail = nullptr;
    }
}

void DoubleLinkedList::clear() {
    while (head) {
        Node* t = head->next;
        delete head;
        head = t;
    }
	tail = nullptr;
}

double& DoubleLinkedList::operator[](size_t index) {
	Node* current = head;
	while (index--) {
		current = current->next;
		if (!current) return this->back();
	}	
	return current->val;
}

DoubleLinkedList operator+(const DoubleLinkedList& left, const DoubleLinkedList& right) {
	if (!left.head) {
		return right + left;
	}
	DoubleLinkedList res = left;
	DoubleLinkedList::Node* current = right.head;
	while (current) {
		res.push_back(current->val);
		current = current->next;
	}
	
	return res;
}

std::ostream& operator<<(std::ostream& out, const DoubleLinkedList& fl) {
    const DoubleLinkedList::Node* current = fl.head;
    while (current) {
        out << current->val << " ";
		current = current->next;
    }
	return out;
}

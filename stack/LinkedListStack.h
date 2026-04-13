#pragma once
#include <cstddef>
#include <iostream>
#include "StackImplementation.h"

class DoubleLinkedList : IStackImplementation {
    struct Node {
        double val;
        Node* next;
		Node* prev;
    };
		
	friend std::ostream& operator<<(std::ostream& out, const DoubleLinkedList& fl);
	friend DoubleLinkedList operator+(const DoubleLinkedList& left, const DoubleLinkedList& right);

    Node* head = nullptr;	
	Node* tail = nullptr;

public:
	DoubleLinkedList() = default;
	DoubleLinkedList(const DoubleLinkedList& fl);
	DoubleLinkedList& operator=(const DoubleLinkedList& fl);
	DoubleLinkedList(DoubleLinkedList&& fl);
	DoubleLinkedList& operator=(DoubleLinkedList&& fl);
	
	~DoubleLinkedList();

    void push_front(double val);
    void pop_front();
    void push(double val) override;
    void pop() override;
	void insert(size_t index, double val);
    double& front();
    const double& front() const;
	double& back();
	const double& back() const;
	const double& top() const override;
    size_t size() const override;
    bool isEmpty() const override;
    void erase(double val);
    void clear();

	double& operator[](size_t index);
};

DoubleLinkedList operator+(const DoubleLinkedList& left, const DoubleLinkedList& right);
std::ostream& operator<<(std::ostream& out, const DoubleLinkedList& fl);

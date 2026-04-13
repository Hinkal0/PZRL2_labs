#include "StackImplementation.h"


void VectorStack::push(const ValueType& value) {
    container.pushBack(value);
}

void VectorStack::pop() {
    container.popBack();
}

const ValueType& VectorStack::top() const {
    return container[container.size()-1];
}

bool VectorStack::isEmpty() const {
    return container.size() == 0;
}

size_t VectorStack::size() const {
    return container.size();
}

void LinkedListStack::push(const ValueType& value) {
    container.push_back(value);
}

void LinkedListStack::pop() {
    container.pop_back();
}

const ValueType& LinkedListStack::top() const {
    return container.back();
}

bool LinkedListStack::isEmpty() const {
    return container.empty();
}

size_t LinkedListStack::size() const {
    return container.size();
}

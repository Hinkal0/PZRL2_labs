#pragma once
#include <cstddef>
#include "Vector.h"
#include "LinkedList.h"

using ValueType = double;

// интерфейс для конкретных реализаций контейнера для стека
class IStackImplementation {
public:
    // добавление в хвост
    virtual void push(const ValueType& value) = 0;
    // удаление с хвоста
    virtual void pop() = 0;
    // посмотреть элемент в хвосте
    virtual const ValueType& top() const = 0;
    // проверка на пустоту
    virtual bool isEmpty() const = 0;
    // размер 
    virtual size_t size() const = 0;
    // виртуальный деструктор
    virtual ~IStackImplementation() = default;
};

class VectorStack : public IStackImplementation {
    Vector container;
public:
    void push(const ValueType& value) override;
    void pop() override;
    const ValueType& top() const override;
    bool isEmpty() const override;
    size_t size() const override;
};

class LinkedListStack : public IStackImplementation {
    DoubleLinkedList container;
public:
    void push(const ValueType& value) override;
    void pop() override;
    const ValueType& top() const override;
    bool isEmpty() const override;
    size_t size() const override;
};

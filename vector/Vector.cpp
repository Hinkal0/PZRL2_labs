#include "Vector.h"
#include <cstring>
#include <utility>
#include <stdexcept>

Vector::Vector(const ValueType* rawArray, const size_t size, float coef)
    : _capacity {size}, _size {size}, _multiplicativeCoef {coef} {
    if (!rawArray) return;
    _data = new ValueType[_capacity];
    std::memcpy(_data, rawArray, _size * sizeof(ValueType));
}

Vector::Vector(const Vector& other) 
    : _capacity {other._size}, _size {other._size}, _multiplicativeCoef {other._multiplicativeCoef} {
    _data = new ValueType[_capacity];
    std::memcpy(_data, other._data, _size * sizeof(ValueType));
}

Vector& Vector::operator=(const Vector& other) {
    if (this == &other) return *this;

    delete[] _data;

    _capacity = other._size;
    _size = other._size;
    _multiplicativeCoef = other._multiplicativeCoef;

    _data = new ValueType[_capacity];
    std::memcpy(_data, other._data, _size * sizeof(ValueType));

    return *this;
}

Vector::Vector(Vector&& other) noexcept 
    : _capacity {other._capacity}, _size {other._size},
    _multiplicativeCoef {other._multiplicativeCoef}, _data {other._data} {
    other._size = 0;
    other._capacity = 0;
    other._data = nullptr;
}

Vector& Vector::operator=(Vector&& other) noexcept {
    _capacity = other._capacity;
    _size = other._size;
    _multiplicativeCoef = other._multiplicativeCoef;
    std::swap(_data, other._data);

    return *this;
}

Vector::~Vector() {
    delete[] _data;
}


void Vector::pushBack(const ValueType& value) {
    if (_size == _capacity) {
        reserve((_size+1) * _multiplicativeCoef);
    }

    _data[_size++] = value;
}

void Vector::pushFront(const ValueType& value) {
    if (_size == _capacity) {
        reserve((_size+1) * _multiplicativeCoef);
    }

    std::memmove(_data+1, _data, _size * sizeof(ValueType));
    _data[0] = value;
    ++_size;
}

void Vector::insert(const ValueType& value, size_t pos) {
    if (_size == _capacity) {
        reserve(_capacity * _multiplicativeCoef);
    }

    std::memmove(_data+pos+1, _data+pos, (_size-pos) * sizeof(ValueType));
    _data[pos] = value;
    ++_size;
}

void Vector::insert(const ValueType* values, size_t size, size_t pos) {
    if (_size + size > _capacity) {
        reserve((_size + size) * _multiplicativeCoef);
    }

    std::memmove(_data+pos+size, _data+pos, (_size-pos) * sizeof(ValueType));
    std::memcpy(_data+pos, values, size * sizeof(ValueType));
    _size += size;
}

void Vector::insert(const Vector& vector, size_t pos) {
    insert(vector._data, vector._size, pos);
}

void Vector::popBack() {
    if (!_size) throw std::runtime_error("Pop back from empty vector");
    --_size;
}

void Vector::popFront() {
    if (!_size) throw std::runtime_error("Pop front from empty vector");
    std::memmove(_data, _data+1, (--_size) * sizeof(ValueType));
}


void Vector::erase(size_t pos, size_t count) {
    if (pos + count < _size) {
        std::memmove(_data+pos, _data+pos+count, (_size-pos-count) * sizeof(ValueType));
        _size -= count;
        return;
    }
    _size = pos;
}

void Vector::eraseBetween(size_t beginPos, size_t endPos) {
    if (endPos < _size) {
        std::memmove(_data+beginPos, _data+endPos, (_size-endPos) * sizeof(ValueType));
        _size -= endPos - beginPos;
        return;
    }
    _size = beginPos;
}

size_t Vector::size() const {
    return _size;
}

size_t Vector::capacity() const {
    return _capacity;
}

double Vector::loadFactor() const {
    return (double)_size/_capacity;
}


ValueType& Vector::operator[](size_t idx) {
    if (idx >= _size) throw std::out_of_range("Out of range");
    return _data[idx];
}

const ValueType& Vector::operator[](size_t idx) const {
    if (idx >= _size) throw std::out_of_range("Out of range");
    return _data[idx];
}

long long Vector::find(const ValueType& value) const {
    for (long long i = 0; i < _size; ++i) {
        if (_data[i] == value) {
            return i;
        }
    }
    return -1;
}

void Vector::reserve(size_t capacity) {
    if (capacity == 0) capacity = 1;
    if (capacity <= _capacity) return;
    
    _capacity = capacity;
    ValueType* t = _data;
    _data = new ValueType[_capacity];
    std::memcpy(_data, t, _size*sizeof(ValueType));
    delete[] t;
}

void Vector::shrinkToFit() {
    _capacity = _size;
    ValueType* t = _data;
    _data = new ValueType[_capacity];
    std::memcpy(_data, t, _size*sizeof(ValueType));
    delete[] t;
}

Vector::Iterator Vector::begin() {
    return Iterator(_data);
}

Vector::Iterator Vector::end() {
    return Iterator(_data+_size);
}

Vector::Iterator::Iterator(ValueType* ptr) : _ptr {ptr} {}

ValueType& Vector::Iterator::operator*() {
    return *_ptr;
}

const ValueType& Vector::Iterator::operator*() const {
    return *_ptr;
}

ValueType* Vector::Iterator::operator->() {
    return _ptr;
}

const ValueType* Vector::Iterator::operator->() const {
    return _ptr;
}

Vector::Iterator Vector::Iterator::operator++() {
    ++_ptr;
    return *this;
}

Vector::Iterator Vector::Iterator::operator++(int) {
    Iterator t = *this;
    ++_ptr;
    return t;
}

bool Vector::Iterator::operator==(const Iterator& other) const {
    return _ptr == other._ptr;
}

bool Vector::Iterator::operator!=(const Iterator& other) const {
    return _ptr != other._ptr;
}

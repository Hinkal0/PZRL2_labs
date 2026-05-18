#include "BST.h"
#include <iostream>
#include <limits>

BinarySearchTree::Node::Node(Key key, Value value, Node* parent, Node* left, Node* right) 
    : keyValuePair(key, value), parent(parent), left(left), right(right) {}

BinarySearchTree::Node::Node(const Node& other) : keyValuePair(other.keyValuePair) {}

bool BinarySearchTree::Node::operator==(const Node& other) const {
    return this->keyValuePair == other.keyValuePair;
}

void BinarySearchTree::Node::output_node_tree() const {
    if (left) left->output_node_tree();
    
    if (this->keyValuePair.first == std::numeric_limits<Key>::max()) return;
    std::cout << "(" << this->keyValuePair.first << "," << this->keyValuePair.second << ")" << std::endl;
    
    if (right) right->output_node_tree();
}

void BinarySearchTree::Node::insert(const Key& key, const Value& value) {
    if (key < keyValuePair.first) {
        if (left) {
            left->insert(key, value);
            return;
        }
        this->left = new Node(key, value, this);
    } else {
        if (right) {
            right->insert(key, value);
            return;
        }
        this->right = new Node(key, value, this);
    }
}

void BinarySearchTree::Node::erase(const Key& key) {
    if (key != keyValuePair.first) {
        if (left && key < keyValuePair.first) left->erase(key);
        else if (right) right->erase(key);
        return;
    }
    
    if (left && right) {
        Node* current = right;
        while (current->left) current = current->left;
        
        this->keyValuePair = current->keyValuePair;

        current->erase(current->keyValuePair.first);
        
        return;
    }

    Node* ptr = nullptr;
    if (left) ptr = left;
    else ptr = right;

    if (parent) {
        if (parent->left == this) parent->left = ptr;
        else parent->right = ptr;
    }
    if (ptr) ptr->parent = parent;

    delete this;
    return;
}

BinarySearchTree::Node* BinarySearchTree::copySubtree(const Node* other) {
    if (other == nullptr) return nullptr;

    Node* n = new Node(*other);
    n->left = copySubtree(other->left);
	if (n->left) n->left->parent = n;
    n->right = copySubtree(other->right);
	if (n->right) n->right->parent = n;
    return n;
}

void BinarySearchTree::freeSubtree(Node* node) {
    if (!node) return;
    freeSubtree(node->left);
    freeSubtree(node->right);
    delete node;
}

BinarySearchTree::BinarySearchTree(const BinarySearchTree &other) 
    : _root(copySubtree(other._root)), _size(other._size) {
}

BinarySearchTree& BinarySearchTree::operator=(const BinarySearchTree &other) {
    if (this == &other) return *this;

    freeSubtree(_root);
    _root = copySubtree(other._root);
    _size = other._size;
    return *this;
}

BinarySearchTree::BinarySearchTree(BinarySearchTree &&other) noexcept 
    : _root(other._root), _size(other._size) {
    other._root = nullptr;
    other._size = 0;
}

BinarySearchTree& BinarySearchTree::operator=(BinarySearchTree &&other) noexcept {
    if (this == &other) return *this;
    std::swap(this->_root, other._root);
    std::swap(this->_size, other._size);
    return *this;
}

BinarySearchTree::~BinarySearchTree() {
    freeSubtree(_root);
}

BinarySearchTree::Iterator::Iterator(Node *node) : _node(node) {}

std::pair<Key, Value>& BinarySearchTree::Iterator::operator*() {
    if (!_node) throw std::runtime_error("Null iterator");
    return _node->keyValuePair;
}

const std::pair<Key, Value>& BinarySearchTree::Iterator::operator*() const {
    if (!_node) throw std::runtime_error("Null iterator");
    return _node->keyValuePair;
}

std::pair<Key, Value>* BinarySearchTree::Iterator::operator->() {
    if (!_node) throw std::runtime_error("Null iterator");
    return &_node->keyValuePair;
}

const std::pair<Key, Value>* BinarySearchTree::Iterator::operator->() const {
    if (!_node) throw std::runtime_error("Null iterator");
    return &_node->keyValuePair;
}

BinarySearchTree::Iterator BinarySearchTree::Iterator::operator++() {
    if (!_node) throw std::runtime_error("Null iterator");
    if (_node->right) {
        _node = _node->right;
        while (_node->left) _node = _node->left;
        return *this;
    }

    while (_node->parent) {
        if (_node == _node->parent->left) {
            _node = _node->parent;
            return *this;
        }
        _node = _node->parent;
    }

    throw std::runtime_error("++end");
}

BinarySearchTree::Iterator BinarySearchTree::Iterator::operator++(int) {
    if (!_node) throw std::runtime_error("Null iterator");
    Iterator it = *this;

    if (_node->right) {
        _node = _node->right;
        while (_node->left) _node = _node->left;
        return it;
    }

    while (_node->parent) {
        if (_node == _node->parent->left) {
            _node = _node->parent;
            return it;
        }
        _node = _node->parent;
    }
    
    throw std::runtime_error("end++");

}

BinarySearchTree::Iterator BinarySearchTree::Iterator::operator--() {
    if (!_node) throw std::runtime_error("Null iterator");
    if (_node->left) {
        _node = _node->left;
        while (_node->right) _node = _node->right;
        return *this;
    }

    while (_node->parent) {
        if (_node == _node->parent->right) {
            _node = _node->parent;
            return *this;
        }
        _node = _node->parent;
    }

    throw std::runtime_error("--begin");
}

BinarySearchTree::Iterator BinarySearchTree::Iterator::operator--(int) {
    if (!_node) throw std::runtime_error("Null iterator");

    Iterator it = *this;
    if (_node->left) {
        _node = _node->left;
        while (_node->right) _node = _node->right;
        return it;
    }

    while (_node->parent) {
        if (_node == _node->parent->right) {
            _node = _node->parent;
            return it;
        }
        _node = _node->parent;
    }

    throw std::runtime_error("begin--");
}

bool BinarySearchTree::Iterator::operator==(const Iterator &other) const {
    return _node == other._node;
}

bool BinarySearchTree::Iterator::operator!=(const Iterator &other) const {
    return _node != other._node;
}

BinarySearchTree::ConstIterator::ConstIterator(const Node *node) : _node(node) {}

const std::pair<Key, Value>& BinarySearchTree::ConstIterator::operator*() const {
    if (!_node) throw std::runtime_error("Null iterator");
    return _node->keyValuePair;
}

const std::pair<Key, Value>* BinarySearchTree::ConstIterator::operator->() const {
    if (!_node) throw std::runtime_error("Null iterator");
    return &_node->keyValuePair;
}

BinarySearchTree::ConstIterator BinarySearchTree::ConstIterator::operator++() {
    if (!_node) throw std::runtime_error("Null iterator");
    if (_node->right) {
        _node = _node->right;
        while (_node->left) _node = _node->left;
        return *this;
    }

    while (_node->parent) {
        if (_node == _node->parent->left) {
            _node = _node->parent;
            return *this;
        }
        _node = _node->parent;
    }

    throw std::runtime_error("++end");
}

BinarySearchTree::ConstIterator BinarySearchTree::ConstIterator::operator++(int) {
    if (!_node) throw std::runtime_error("Null iterator");
    ConstIterator it = *this;

    if (_node->right) {
        _node = _node->right;
        while (_node->left) _node = _node->left;
        return it;
    }

    while (_node->parent) {
        if (_node == _node->parent->left) {
            _node = _node->parent;
            return it;
        }
        _node = _node->parent;
    }
    
    throw std::runtime_error("end++");

}

BinarySearchTree::ConstIterator BinarySearchTree::ConstIterator::operator--() {
    if (!_node) throw std::runtime_error("Null iterator");
    if (_node->left) {
        _node = _node->left;
        while (_node->right) _node = _node->right;
        return *this;
    }

    while (_node->parent) {
        if (_node == _node->parent->right) {
            _node = _node->parent;
            return *this;
        }
        _node = _node->parent;
    }

    throw std::runtime_error("--begin");
}

BinarySearchTree::ConstIterator BinarySearchTree::ConstIterator::operator--(int) {
    if (!_node) throw std::runtime_error("Null iterator");

    ConstIterator it = *this;
    if (_node->left) {
        _node = _node->left;
        while (_node->right) _node = _node->right;
        return it;
    }

    while (_node->parent) {
        if (_node == _node->parent->right) {
            _node = _node->parent;
            return it;
        }
        _node = _node->parent;
    }

    throw std::runtime_error("begin--");
}

bool BinarySearchTree::ConstIterator::operator==(const ConstIterator &other) const {
    return _node == other._node;
}

bool BinarySearchTree::ConstIterator::operator!=(const ConstIterator &other) const {
    return _node != other._node;
}

void BinarySearchTree::insert(const Key &key, const Value &value) {
    if (!_root) {
        _root = new Node(key, value);
        _root->right = new Node(std::numeric_limits<Key>::max(), value, _root);
        ++_size;
        return;
    }

    _root->insert(key, value);
    ++_size;
}

void BinarySearchTree::erase(const Key &key) {
    if (!_root) return;
    Iterator i(_root);
    while ((i = find(key)) != end()) {
        i._node->erase(key);
        --_size;
    }
}

BinarySearchTree::ConstIterator BinarySearchTree::find(const Key &key) const {
    const Node* current = _root;
    while (current) {
        if (current->keyValuePair.first < key) {
            current = current->right;
        } else if (current->keyValuePair.first > key) {
            current = current->left;
        } else {
            return ConstIterator(current);
        }
    }

    return cend();
}

BinarySearchTree::Iterator BinarySearchTree::find(const Key &key) {
    Node* current = _root;
    while (current) {
        if (current->keyValuePair.first < key) {
            current = current->right;
        } else if (current->keyValuePair.first > key) {
            current = current->left;
        } else {
            return Iterator(current);
        }
    }

    return end();
}

std::pair<BinarySearchTree::Iterator, BinarySearchTree::Iterator> BinarySearchTree::equalRange(const Key &key) {
    Iterator e = end();
    Iterator current = begin();
    while (current != e && current->first != key) ++current;

    Iterator first = current;
    while (current != e && current->first == key) ++current;
    return {first, current};
}

std::pair<BinarySearchTree::ConstIterator, BinarySearchTree::ConstIterator> BinarySearchTree::equalRange(const Key &key) const {
    ConstIterator e = cend();
    ConstIterator current = cbegin();
    while (current != e && current->first != key) ++current;

    ConstIterator first = current;
    while (current != e && current->first == key) ++current;
    return {first, current};
}

BinarySearchTree::ConstIterator BinarySearchTree::min() const {
    return cbegin();
}

BinarySearchTree::ConstIterator BinarySearchTree::max() const {
    return --cend();
}

BinarySearchTree::ConstIterator BinarySearchTree::min(const Key &key) const {
    std::pair<ConstIterator, ConstIterator> range = equalRange(key);
    ConstIterator current = range.first;
    ConstIterator m = current;
    
    for (; current != range.second; ++current) {
        if (current->second < m->second) m = current;
    }

    return m;
}

BinarySearchTree::ConstIterator BinarySearchTree::max(const Key &key) const {
    std::pair<ConstIterator, ConstIterator> range = equalRange(key);
    ConstIterator current = range.first;
    ConstIterator m = current;
    
    for (; current != range.second; ++current) {
        if (current->second > m->second) m = current;
    }

    return m;
}

BinarySearchTree::Iterator BinarySearchTree::begin() {
    Node* current = _root;
    while (current->left) current = current->left;
    return Iterator(current);
}

BinarySearchTree::Iterator BinarySearchTree::end() {
    Node* current = _root;
    while (current->right) current = current->right;
    return Iterator(current);
}

BinarySearchTree::ConstIterator BinarySearchTree::cbegin() const {
    Node* current = _root;
    while (current->left) current = current->left;
    return ConstIterator(current);
}

BinarySearchTree::ConstIterator BinarySearchTree::cend() const  {
    Node* current = _root;
    while (current->right) current = current->right;
    return ConstIterator(current);
}

size_t BinarySearchTree::size() const {
    return _size;
}

void BinarySearchTree::output_tree() const {
    if (!_root) return;
    _root->output_node_tree();
}

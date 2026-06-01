#pragma once
#include <cstddef>
#include <tuple>
#include <limits>

/**
 * @brief Класс SplayTree — самобалансирующееся дерево поиска (splay tree).
 * 
 * @tparam Key Тип ключа (должен поддерживать сравнение).
 * @tparam Value Тип значения.
 */
template<typename Key, typename Value>
class SplayTree {
	struct Node;
	Node* _root = nullptr;
	size_t _size = 0;
public:
	static void freeSubtree(Node* node) {
	    if (!node) return;
	    freeSubtree(node->left);
	    freeSubtree(node->right);
	    delete node;
	}
    /**
     * @brief Конструктор по умолчанию. Создаёт пустое дерево.
     */
    SplayTree() = default;

    /**
     * @brief Деструктор. Очищает все ресурсы, связанные с деревом.
     */
    ~SplayTree() {
		freeSubtree(_root);
		_size = 0;
		_root = nullptr;
	}

	void splay(Node* node) {
	    if (_root == node || !node) return;
	    
	    if (_root == node->parent) {
	        if (node == _root->left) _root->rotateRight();
	        else _root->rotateLeft();
	        _root = node;
	        return;
	    }
	    
	    bool f = node->parent->parent == _root;
	
	    if (node->parent->left == node && node->parent->parent->left == node->parent
	        || node->parent->right == node && node->parent->parent->right == node->parent) {
	        if (node == node->parent->left) {
	            node->parent->parent->rotateRight();
	            node->parent->rotateRight();
	        } else {
	            node->parent->parent->rotateLeft();
	            node->parent->rotateLeft();
	        }
	        if (f) _root = node;
	        splay(node);
	        return;
	    }
	    
	    if (node == node->parent->right) {
	        node->parent->rotateLeft();
	        node->parent->rotateRight();
	    } else {
	        node->parent->rotateRight();
	        node->parent->rotateLeft();
	    }
	    if (f) _root = node;
	    splay(node);
	}

    /**
     * @brief Вставляет пару (key, value) в дерево.
     * Если ключ уже существует, его значение обновляется.
     * После вставки/обновления соответствующий узел становится корнем (splay).
     * 
     * @param key Ключ для вставки.
     * @param value Значение для вставки.
     */
    void insert(const Key& key, const Value& value) {
    	if (!_root) {
    	    _root = new Node(key, value);
    	    _root->right = new Node(std::numeric_limits<Key>::max(), value, _root);
    	    ++_size;
    	    return;
    	}
    	Node* _end = end();
    	if (_end->parent) _end->parent->right = nullptr;

    	splay(_root->insert(key, value, &_root));
    	++_size;

    	Node* current = _root;
    	while (current->right) current = current->right;
    	current->right = _end;
    	_end->parent = current;
	}

	Node* find(const Key& key) {
    	Node* current = _root;
		Node* prev = nullptr;
    	while (current) {
    	    if (current->keyValuePair.first < key) {
				prev = current;
    	        current = current->right;
    	    } else if (current->keyValuePair.first > key) {
				prev = current;
    	        current = current->left;
    	    } else {
    	        return current;
    	    }
    	}

    	return nullptr;
		
	}

	Node* end() {
		Node* current = _root;
		while (current->right) current = current->right;
		return current;
	}

    /**
     * @brief Удаляет узел с заданным ключом из дерева.
     * 
     * @param key Ключ для удаления.
     * @return true если элемент был найден и удалён, false если такого ключа нет.
     */
    bool remove(const Key& key) {
    	if (!_root) return 0;
    	Node* i = _root;
		bool f = 0;
    	while ((i = find(key)) != nullptr) {
			f = 1;
    	    Node* _end = end();
    	    _end->parent->right = nullptr;
    	    
    	    splay(i);
    	    i->erase(key, &_root);
    	    --_size;
    	    if (!_root) {
    	        delete _end;
    	        return 1;
    	    }

    	    Node* current = _root;
    	    while (current->right) current = current->right;
    	    current->right = _end;
    	    _end->parent = current;
    	}

		return f;

	}

    /**
     * @brief Ищет элемент по ключу.
     * Если найден, возвращает указатель на значение (Value*), иначе nullptr.
     * После поиска найденный (или последний просмотренный) узел становится корнем (splay).
     * 
     * @param key Ключ для поиска.
     * @return Value* Указатель на значение или nullptr.
     */
    Value* search(const Key& key) {
    	Node* current = _root;
		Node* prev = nullptr;
    	while (current) {
    	    if (current->keyValuePair.first < key) {
				prev = current;
    	        current = current->right;
    	    } else if (current->keyValuePair.first > key) {
				prev = current;
    	        current = current->left;
    	    } else {
				splay(current);
    	        return &current->keyValuePair.second;
    	    }
    	}

		splay(prev);
    	return nullptr;
	}

    /**
     * @brief Константная версия поиска.
     * Не изменяет структуру дерева.
     * 
     * @param key Ключ для поиска.
     * @return const Value* Указатель на значение или nullptr.
     */
    const Value* search(const Key& key) const {
    	const Node* current = _root;
    	while (current) {
    	    if (current->keyValuePair.first < key) {
    	        current = current->right;
    	    } else if (current->keyValuePair.first > key) {
    	        current = current->left;
    	    } else {
    	        return &current->keyValuePair.second;
    	    }
    	}

    	return nullptr;
	}

    /**
     * @brief Проверяет, что дерево удовлетворяет свойству бинарного дерева поиска (BST).
     * 
     * @return true если дерево корректно, false иначе.
     */
    bool isValidBST() const {
		if (!_root) return 1;
		return _root->isValid();
	}

    /**
     * @brief Возвращает количество элементов в дереве.
     * 
     * @return size_t Количество элементов.
     */
    size_t size() const {
		return _size;
	}

    /**
     * @brief Проверяет, пусто ли дерево.
     * 
     * @return true если дерево пустое, false иначе.
     */
    bool empty() const {
		return _root == nullptr;
	}

private:

	struct Node {
		Node* left;
		Node* right;
		Node* parent;
        std::pair<Key, Value> keyValuePair;
		Node(Key key, Value value, Node* parent = nullptr, Node* left = nullptr, Node* right = nullptr) 
    	: keyValuePair(key, value), parent(parent), left(left), right(right) {}
        
		bool isValid() {
			if (left && left->keyValuePair.first > keyValuePair.first) return false;
			if (right && right->keyValuePair.first < keyValuePair.first) return false;
			bool v1 = 1;
			bool v2 = 1;
			if (left) v1 = left->isValid();
			if (right) v2 = right->isValid();
			return v1 && v2;
		}

		Node* insert(const Key &key, const Value &value, Node** root) {
    		if (!root) return nullptr;
    		if (key <= keyValuePair.first) {
    		    if (left) {
    		        return left->insert(key, value, root);
    		    }
    		    left = new Node(key, value, this);
    		    return left;
    		} else {
    		    if (right) {
    		        return right->insert(key, value, root);
    		    }
    		    right = new Node(key, value, this);
    		    return right;
    		}

		}
        
		void erase(const Key &key, Node** root) {
    		if (!root) return;
    		if (key != keyValuePair.first) {
    		    if (left && key <= keyValuePair.first) left->erase(key, root);
    		    else if (right) right->erase(key, root);
    		    return;
    		}
    		
    		if (left && right) {
    		    Node* current = right;
    		    while (current->left) current = current->left;
    		    
    		    this->keyValuePair = current->keyValuePair;

    		    current->erase(current->keyValuePair.first, root);
    		    
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

    		if (this == *root) *root = ptr;
    		delete this;
    		return;

		}
 
        void rotateLeft() {
    		Node* pivot = this->right;

    		pivot->parent = this->parent;
    		if (this->parent) {
    		    if (this->parent->left == this) {
    		        this->parent->left = pivot;
    		    } else {
    		        this->parent->right = pivot;
    		    }
    		}

    		this->right = pivot->left;
    		if (pivot->left) pivot->left->parent = this;

    		this->parent = pivot;
    		pivot->left = this;

		}

        void rotateRight() {
    		Node* pivot = this->left;

    		pivot->parent = this->parent;
    		if (this->parent) {
    		    if (this->parent->left == this) {
    		        this->parent->left = pivot;
    		    } else {
    		        this->parent->right = pivot;
    		    }
    		}

    		this->left = pivot->right;
    		if (pivot->right) pivot->right->parent = this;

    		this->parent = pivot;
    		pivot->right = this;

		}

	};


};

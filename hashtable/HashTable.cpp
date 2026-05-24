#include "HashTable.h"

#define SIX_SEVEN 67

static size_t strhash(const KeyType& key) {
    size_t hash = 0;
    for (size_t i = 0; i < key.size(); i++) {
        hash = hash * SIX_SEVEN + key[i];
    }
    return hash;
}

static size_t rehash(std::vector<std::list<std::pair<KeyType, ValueType>>>& table) {
    size_t newSize = table.size()*2;
    size_t filled = 0;
    std::vector<std::list<std::pair<KeyType, ValueType>>> newTable(newSize);
    for (size_t i = 0; i < table.size(); i++) {
        for (auto it = table[i].cbegin(); it != table[i].cend(); ++it) {
            size_t hash = strhash(it->first);
            newTable[hash%newSize].push_back(*it);
            if (newTable[hash%newSize].size() == 1) ++filled;
        }
    }   
    table = std::move(newTable);
    return filled;
}

size_t HashTable::hash_function(const KeyType &key) const {
    return strhash(key);
}

HashTable::HashTable(size_t size) noexcept : table(size), _capacity(size), _filled(0) {}

HashTable::~HashTable() {}

void HashTable::insert(const KeyType &key, const ValueType &value) {
    ValueType valCopy;
    if (find(key, valCopy)) {
        (*this)[key] = value;
        return;
    }

    table[hash_function(key)%_capacity].push_back(std::pair<KeyType, ValueType>(key, value));
    
    if (table[hash_function(key)%_capacity].size() == 1) ++_filled;

    if (getLoadFactor() > 0.75) {
        _filled = rehash(table);
        _capacity *= 2;
    }
}

bool HashTable::find(const KeyType &key, ValueType &value) const {
    const std::list<std::pair<KeyType, ValueType>>& list = table[hash_function(key)%_capacity];
    for (auto it = list.cbegin(); it != list.cend(); ++it) {
        if (it->first == key) {
            value = it->second;
            return 1;
        }
    }
    return 0;
}

void HashTable::remove(const KeyType &key) {
    auto& list = table[hash_function(key)%_capacity];
    for (auto it = list.begin(); it != list.end();) {
        if (it->first == key) {
            list.erase(it);
            --_filled;
            return;
        }
        else ++it;
    }
}

ValueType& HashTable::operator[](const KeyType &key) {
    std::list<std::pair<KeyType, ValueType>>& list = table[hash_function(key)%_capacity];
    for (auto it = list.begin(); it != list.end(); ++it) {
        if (it->first == key) return it->second;
    }
    
    insert(key, 0);
    return (*this)[key];
}

double HashTable::getLoadFactor() {
    return (double)_filled/_capacity;
}

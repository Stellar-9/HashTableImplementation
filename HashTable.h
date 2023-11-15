#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <list>
#include <vector>
#include <stdexcept>

template<typename K, typename V>
class HashTable {

private:
    static const int INITIAL_SIZE = 16;
    std::vector<std::list<std::pair<K, V>>> table;
    int currentSize;

    // Private utility functions, like your hash function
    int hash(K key) const;

public:
    // Constructor
    HashTable();

    // Public API for the hash table
    void insert(const K& key, const V& value);
    void remove(const K& key);
    V get(const K& key) const;

    // Other potential functions (e.g., size, resize, isEmpty, etc.)



};

#include "HashTableImplementation.cpp" // Include the implementation here for template class

#endif // !HASHTABLE_H


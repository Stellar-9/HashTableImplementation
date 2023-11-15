#include <iostream>
#include <list>
#include <vector>
#include <functional> // for std::hash

template<typename K, typename V>
class HashTable {
private:
    static const int INITIAL_SIZE = 16; // Initial size of the hash table
    int size;                           // Current size of the hash table
    int count;                          // Number of key-value pairs in the hash table
    std::vector<std::list<std::pair<K, V>>> table;

    int hash(K key) {
        // Using std::hash to generate a hash value for a wide range of key types
        std::hash<K> hashFunc;
        return hashFunc(key) % size;
    }

    void resize() {
        int oldSize = size;
        size *= 2; // Double the size
        std::vector<std::list<std::pair<K, V>>> newTable(size);

        // Rehash all entries into the new table
        for (int i = 0; i < oldSize; ++i) {
            for (auto& it : table[i]) {
                int hashValue = hash(it.first);
                newTable[hashValue].push_back(it);
            }
        }

        // Swap old table with the new table
        table.swap(newTable);
    }

public:
    HashTable() : size(INITIAL_SIZE), count(0) {
        table.resize(INITIAL_SIZE);
    }

    void insert(K key, V value) {
        // Resize if the load factor becomes too high
        if (count >= size) {
            resize();
        }

        int hashValue = hash(key);
        auto& list = table[hashValue];

        // Check if the key already exists
        for (auto& it : list) {
            if (it.first == key) {
                it.second = value;
                return;
            }
        }

        // Add new key-value pair
        list.emplace_back(key, value);
        count++;
    }

    void remove(K key) {
        int hashValue = hash(key);
        auto& list = table[hashValue];

        auto it = list.begin();
        while (it != list.end()) {
            if (it->first == key) {
                list.erase(it);
                count--;
                return;
            }
            ++it;
        }
    }

    V get(K key) {
        int hashValue = hash(key);
        auto& list = table[hashValue];

        for (auto& it : list) {
            if (it.first == key) {
                return it.second;
            }
        }

        throw std::range_error("Key not found");
    }
};

int main() {
    HashTable<int, std::string> myHashTable;

    // Example usage
    myHashTable.insert(1, "Hello");
    myHashTable.insert(2, "World");
    myHashTable.insert(3, "C++");

    try {
        std::cout << myHashTable.get(2) << std::endl; // Should print "World"
        myHashTable.remove(2);
        std::cout << myHashTable.get(2) << std::endl; // Should throw an exception
    }
    catch (const std::range_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    return 0;
}

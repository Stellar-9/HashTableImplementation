#include "HashTable.h"
#include <iostream>

int main() {
    HashTable<int, std::string> hashTable;

    hashTable.insert(1, "Value 1");
    hashTable.insert(2, "Value 2");
    hashTable.insert(3, "Value 3");

    std::cout << "Key 2: " << hashTable.get(2) << std::endl;

    // More code to demonstrate removal, collision handling, etc.

    return 0;
}
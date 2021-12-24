// AED 2021/2022 - Aula Pratica 08
// Pedro Ribeiro (DCC/FCUP) [12/12/2021]

#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include <functional>
#include <vector>

using namespace std;

template <class KeyType> class HashTable {
    enum EntryType { EMPTY, ACTIVE, DELETED }; // Type of table entry
    struct HashEntry {                         // One table entry
        EntryType state;
        KeyType key;
    };

    int numActive;           // Number of active table entries (with keys)
    int numEmpty;            // Number of empty table entries
    vector<HashEntry> table; // The hash table itself
    function<unsigned(const KeyType &)> hash; // Hash function: key -> unsigned

    int findPos(const KeyType &k); // Linear probing to find suitable position

public:
    HashTable(int n, function<unsigned(const KeyType &)> h);
    bool contains(const KeyType &k); // Does it contain key k?
    void clear();                    // Clear hash table
    int getNumActive();              // Number of active table entries
    int getNumEmpty();               // Number of empty table entries

    // ----- Functions to implement in this exercise -----
    bool insert(const KeyType &k); // Insert key k (true if sucessfull)
    bool remove(const KeyType &k); // Remove key k (true if sucessfull)
    bool rehash(int n);            // Resize to n and rehash (true if suc.)
};

// Constructor: receives the table size n and the hash function h
template <class KeyType>
HashTable<KeyType>::HashTable(int n, function<unsigned(const KeyType &)> h)
    : table(n), hash(h) {
    clear();
}

// Getter for data member numActive
template <class KeyType> int HashTable<KeyType>::getNumActive() {
    return numActive;
}

// Getter for data member numEmpty
template <class KeyType> int HashTable<KeyType>::getNumEmpty() {
    return numEmpty;
}

// Uses the hash function to find the correct position for the key and then
// uses linear probing until it either finds the key already on the table
// or an empty position (it skips over deleted positions)
template <class KeyType> int HashTable<KeyType>::findPos(const KeyType &k) {
    int pos = hash(k) % table.size();
    while (table[pos].state != EMPTY &&
           !(table[pos].state == ACTIVE && table[pos].key == k))
        pos = (pos + 1) % table.size();
    return pos;
}

// Clear the hash table (setting all positions to the empty state)
template <class KeyType> void HashTable<KeyType>::clear() {
    numActive = 0;
    numEmpty = table.size();
    for (size_t i = 0; i < table.size(); i++)
        table[i].state = EMPTY;
}

// Returns true if the key is on the table, or false otherwise
template <class KeyType> bool HashTable<KeyType>::contains(const KeyType &k) {
    int pos = findPos(k);
    return (table[pos].state == ACTIVE && table[pos].key == k);
}

// ----------------------------------------------------------
// Exercicio 1: Tabelas de Dispersão
// ----------------------------------------------------------

// ..............................
// a) Inserindo elementos
template <class KeyType> bool HashTable<KeyType>::insert(const KeyType &k) {
    if (numEmpty == 1)
        return false;

    int pos{findPos(k)};
    HashEntry &entry{table[pos]};

    if (entry.state == ACTIVE && entry.key == k)
        return false;

    entry.state = ACTIVE;
    entry.key = k;
    ++numActive;
    --numEmpty;
    return true;
}

// ..............................
// b) Removendo elementos
template <class KeyType> bool HashTable<KeyType>::remove(const KeyType &k) {
    int pos{findPos(k)};
    HashEntry &entry{table[pos]};

    if (entry.state == ACTIVE && entry.key == k) {
        entry.state = DELETED;
        --numActive;
        return true;
    }

    return false;
}

// ..............................
// c) Refazendo a tabela
template <class KeyType> bool HashTable<KeyType>::rehash(int n) {
    if (n < numActive + 1)
        return false;

    auto temp{table};

    table.resize(n);
    clear();

    for (auto entry : temp)
        if (entry.state == ACTIVE)
            insert(entry.key);

    return true;
}

#endif

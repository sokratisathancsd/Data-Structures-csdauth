#ifndef HASHTABLE_H_INCLUDED
#define HASHTABLE_H_INCLUDED

#include "HashNode.h"


class HashTable
{
public:
    HashNode **ptr;
    int capacity;
    int size;
    HashTable(int capacity);
    int hashCode(string data);
    void insertNode(string data);
    int Search(string data);
    int sizeofMap();
    bool isEmpty();
    void display();
    HashTable* reHashing(HashTable* h1, double newCapacity);
};


#endif // HASHTABLE_H_INCLUDED

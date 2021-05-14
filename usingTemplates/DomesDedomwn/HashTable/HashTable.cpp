#include <string>
#include <unordered_map>
#include<bits/stdc++.h>
#include <math.h>
using namespace std;
#include "HashTable.h"
#include "HashNode.h"



HashNode::HashNode(string data)
{
    this->data = data;
    this->appearances = 1;
}
void HashNode::changeAppearances(int newAppearances)
{
    appearances=newAppearances;
}



HashTable::HashTable(int capacity)
{
    //Initial capacity of hash table
    this->capacity = capacity;
    size=0;
    ptr = new HashNode*[capacity];

    //Initialise all elements of table as NULL
    for(int i=0 ; i < capacity ; i++)
    {
        ptr[i] = NULL;
    }


}
// hashFunction
//https://stackoverflow.com/questions/18174988/how-can-i-add-c11-support-to-codeblocks-compiler

int HashTable::hashCode(string data)
{
    hash<string> mystdhash;
    //cout << mystdhash(data)%capacity<<endl;
    return mystdhash(data)%capacity;

}

//add to hashTable
void HashTable::insertNode(string data)
{
    HashNode *temp = new HashNode(data);
    int hashIndex = hashCode(data);

    while(ptr[hashIndex] != NULL)
    {
        if(ptr[hashIndex]->data.compare(data) == 0)
        {
            temp->changeAppearances(ptr[hashIndex]->appearances+=1);
            break;
        }
        hashIndex++;
        hashIndex %= capacity;
    }

    if(ptr[hashIndex] == NULL)
        size++;
    ptr[hashIndex] = temp;
}


//Function to search the value for a given key
int HashTable::Search(string data)
{
    // Apply hash function to find index for given key
    int hashIndex = hashCode(data);
    int counter=0;
    //finding the node with given key
    while(ptr[hashIndex] != NULL)
    {
        //Not found
        if(counter++>capacity)   //to avoid infinite loop
        {
            cout<<"Not Found"<<endl;
            return false;
        }
        //Found
        if(ptr[hashIndex]->data == data)
        {
            cout<<ptr[hashIndex]->data<<" "<<"Found: ";
            return ptr[hashIndex]->appearances ;
        }
        hashIndex++;
        hashIndex %= capacity; //an ginei iso me to capacity paei stin arxi tou pinaka
    }
    if(ptr[hashIndex] == NULL)
    {
        cout<<"Not Found"<<endl;
        return false;
    }
    return false;

}

//Return current size
int HashTable::sizeofMap()
{
    return size;
}

//Return true if size is 0
bool HashTable::isEmpty()
{
    return size == 0;
}

//Function to display the stored key value pairs
void HashTable::display()
{
    for(int i=0 ; i<capacity ; i++)
    {
        if(ptr[i] != NULL)
        {
            cout << "data = " << ptr[i]->data
                 <<"  appearances = "<< ptr[i]->appearances << endl;
        }
        else
        {
            cout<<"NULL"<<endl;
        }
    }
}


HashTable* HashTable::reHashing(HashTable* h1, double newCapacity)
{
    double newCapacityInt;
    modf(newCapacity,&newCapacityInt);
    HashTable* h2 = new HashTable((int) newCapacityInt);
    //cout<<newCapacityInt<<endl;
    for(int i=0; i<h1->capacity; i++)
    {
        if(h1->ptr[i] != NULL)
        {
            h2->insertNode(h1->ptr[i]->data);
            h2->ptr[h2->hashCode(h1->ptr[i]->data)]->appearances=h1->ptr[i]->appearances;

            delete h1->ptr[i];
        }
    }
    //delete old hashtable
    delete h1;
    return h2;

}

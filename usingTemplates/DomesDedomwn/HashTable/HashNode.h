#ifndef HASHNODE_H_INCLUDED
#define HASHNODE_H_INCLUDED

class HashNode
{
public:
    string data;
    int appearances;
    HashNode(string data);
    void changeAppearances(int newAppearances);
};

#endif // HASHNODE_H_INCLUDED

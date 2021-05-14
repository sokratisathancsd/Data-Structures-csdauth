#ifndef BSTNODE_H_INCLUDED
#define BSTNODE_H_INCLUDED

template <class Type>
class BstNode
{
private:
    Type data;
    int appearances;
    BstNode<Type>* left;
    BstNode<Type>* right;
public:
    BstNode<Type>* GetNewNode(Type data);
    BstNode<Type>* Insert(BstNode<Type>* root, Type data);
    int Search(BstNode<Type>* root, Type data);
    void printPostorder(BstNode<Type>* root);
    void printInorder(BstNode<Type>* root);
    void printPreorder(BstNode<Type>* root);
    BstNode<Type>* findMin(BstNode<Type>* root);
    BstNode<Type>* Delete(BstNode<Type>* root, Type data);


    void print2DUtil(BstNode<Type>* root, int space);
    void print2D(BstNode<Type>* root);
    unsigned int getSize(BstNode<Type>* root);

};

template class BstNode<int>;
template class BstNode<float>;
template class BstNode<string>;
#endif // BSTNODE_H_INCLUDED

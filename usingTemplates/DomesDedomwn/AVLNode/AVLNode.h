#ifndef AVLNODE_H_INCLUDED
#define AVLNODE_H_INCLUDED

template <class Type>
class AVLNode
{
private:
    Type data;
    int appearances;
    AVLNode<Type>* left;
    AVLNode<Type>* right;
    int heightt;
public:
    int height(AVLNode<Type>* Node);
    AVLNode<Type>* GetNewNode(Type data);
    AVLNode<Type>* rightRotate(AVLNode<Type>* y);
    AVLNode<Type>* leftRotate(AVLNode<Type>* x);
    int balance(AVLNode<Type>* Node);

    AVLNode<Type>* Insert(AVLNode<Type>* root, Type data);
    AVLNode<Type>* Delete(AVLNode<Type>* root, Type data);
    AVLNode<Type>* findMin(AVLNode<Type>* root);
    int Search(AVLNode<Type>* root, Type data);

    void printPostorder(AVLNode<Type>* root);
    void printInorder(AVLNode<Type>* root);
    void printPreorder(AVLNode<Type>* root);

    void print2DUtil(AVLNode<Type>* root, int space);
    void print2D(AVLNode<Type>* root);
    unsigned int GetSize(AVLNode<Type>* root);

};
template class AVLNode<int>;
template class AVLNode<float>;
template class AVLNode<string>;
#endif // AVLNODE_H_INCLUDED

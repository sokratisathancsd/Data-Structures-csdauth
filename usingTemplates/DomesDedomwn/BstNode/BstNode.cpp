#include <bits/stdc++.h>
using namespace std;
#define COUNT 10
#include "BstNode.h"
#include <string>

template <class Type>
BstNode<Type>* BstNode<Type>::GetNewNode(Type data)
{
    //create a Node
    //return address of this new Node
    BstNode<Type>* newNode = new BstNode(); //- (BstNode*) malloc(sizeof(BstNode));
    newNode->appearances = 1;
    newNode->data=data;
    newNode->left = newNode->right = NULL; //initialize left and right child as NULL
    return newNode;

}
//Insert Data in BST
template <class Type>
BstNode<Type>* BstNode<Type>::Insert(BstNode* root, Type data) //gets address of the root node and the data we want to Insert to BST
{
    if(root==NULL)
    {
        root = GetNewNode(data); //if tree is empty we create a new Node and set it as root
    }
    else if(data == (root->data)) //its the same string appearing again
    {
        root->appearances++;
    }
    else if(data<(root->data) )
    {
        root->left = Insert(root->left,data);//we add the Node to the left subTree
    }
    else
    {
        root->right = Insert(root->right,data);
    }
    return root;

}
//Search Data in BST
template <class Type>
int BstNode<Type>::Search(BstNode<Type>* root, Type data) //data = data to be searched
{
    if(root == NULL)
    {
        cout<<"Not Found"<<endl;
        return false;
    }
    else if(root->data == data)
    {
        cout<<root->data<<" "<<"Found: ";
        return root->appearances;
    }
    //else we search on the left subtree or in the right subtree
    else if(data<root->data)
    {
        return Search(root->left,data);
    }
    else
    {
        return Search(root->right,data);
    }

}


//Postorder
template <class Type>
void BstNode<Type>::printPostorder(BstNode* root)
{
    if (root == NULL)
        return;
    printPostorder(root->left);
    printPostorder(root->right);
    cout << root->data <<" ";
}
//Inorder
template <class Type>
void BstNode<Type>::printInorder(BstNode* root)
{
    if (root == NULL)
        return;
    printInorder(root->left);
    cout << root->data <<" ";
    printInorder(root->right);
}
//Preorder
template <class Type>
void BstNode<Type>::printPreorder(BstNode* root)
{
    if (root == NULL)
        return;
    cout << root->data <<" ";
    printPreorder(root->left);
    printPreorder(root->right);
}


//the minimum element is the leftmost element in the subtree that we search
//we use this function in Delete method
template <class Type>
BstNode<Type>* BstNode<Type>::findMin(BstNode* root)
{
    while(root->left != NULL)
        root = root->left;
    return root;
}

//Delete
template <class Type>
BstNode<Type>* BstNode<Type>::Delete(BstNode* root, Type data)
{
    if(root == NULL)
        return root;
    else if(data<(root->data) )
        root->left = Delete(root->left,data);
    else if (data>(root->data))
        root->right = Delete(root->right,data);

    else
    {
        //it has more than one appearances we remove 1 appearance not the whole node!
        if(root->appearances > 1)
        {
            root->appearances--;
        }
        //Node has no child
        else if(root->left == NULL && root->right == NULL)
        {
            delete root;
            root = NULL;
        }
        //Node has 1 child
        else if(root->left == NULL)
        {
            BstNode *temp = root;
            root = root->right;
            delete temp;
        }
        else if(root->right == NULL)
        {
            BstNode *temp = root;
            root = root->left;
            delete temp;
        }
        //Node has 2 children
        else
        {
            BstNode *temp = findMin(root->right);
            root->data = temp->data;
            root->appearances = temp->appearances;
            root->right = Delete(root->right,temp->data);
        }
    }
    return root;
}





//https://www.geeksforgeeks.org/print-binary-tree-2-dimensions/
// Function to print binary tree in 2D
// It does reverse inorder traversal
template <class Type>
void BstNode<Type>::print2DUtil(BstNode* root, int space)
{
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += COUNT;

    // Process right child first
    print2DUtil(root->right, space);

    // Print current node after space
    // count
    cout<<endl;
    for (int i = COUNT; i < space; i++)
        cout<<" ";
    cout<<root->data<<"\n";

    // Process left child
    print2DUtil(root->left, space);
}
// Wrapper over print2DUtil()
template <class Type>
void BstNode<Type>::print2D(BstNode* root)
{
    // Pass initial space count as 0
    print2DUtil(root, 0);
}

//https://www.geeksforgeeks.org/write-a-c-program-to-calculate-size-of-a-tree/
// Computes the number of nodes in a tree.
template <class Type>
unsigned int BstNode<Type>::getSize(BstNode* root)
{
    unsigned int count = 1;
    if (root->left != NULL)
    {
        count += getSize(root->left);
    }
    if (root->right != NULL)
    {
        count += getSize(root->right);
    }
    return count;
}



#include <bits/stdc++.h>
using namespace std;
#include "AVLNode.h"
#include <iostream>
#include <fstream>
#define COUNT 20

template <class Type>
int AVLNode<Type>::height(AVLNode<Type>* Node)
{
    if (Node == NULL)
        return 0;
    else
    {
        /* compute the depth of each subtree */
        int rightHeight = height(Node->left);
        int leftHeight = height(Node->right);

        /* use the larger one */
        if (leftHeight > rightHeight)
            return(leftHeight+1);
        else
            return(rightHeight+1);
    }
}

template <class Type>
AVLNode<Type>* AVLNode<Type>::GetNewNode(Type data)
{
    AVLNode<Type>* newNode = new AVLNode(); //- (AVLNode*) malloc(sizeof(AVLNode));
    newNode->appearances = 1;
    newNode->data=data;
    newNode->left = newNode->right = NULL; //initialize left and right child as NULL
    newNode->heightt=1;
    return newNode;
}

template <class Type>
AVLNode<Type>* AVLNode<Type>::rightRotate(AVLNode<Type>* y)
{
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;                                     //-------------------------------------
                                                                //-----Y--------------------X----------
    //ROTATION T1 and T3 stay the same                          //----/-\------------------/-\---------
    x->right = y;                                               //---X---Τ3-----RIGHT-----T1--Y--------
    y->left = T2;                                               //--/-\-------ROTATION-------/-\-------
                                                                //-Τ1--Τ2-------------------T2--T3-----
    //change heights                                            //-------------------------------------
    x->heightt = max(height(x->left),height(x->right))+1;       //-------------------------------------
    y->heightt = max(height(y->left),height(y->right))+1;

    return x;
}

template <class Type>
AVLNode<Type>* AVLNode<Type>::leftRotate(AVLNode<Type>* x)
{
    //T1 and T3 don't change root
    AVLNode* y = x->right;                                      //-------------------------------------
    AVLNode* T2 = y->left;                                      //-----X----------------------Y--------
                                                                //----/-\--------------------/-\-------
    y->left = x;                                                //---T1--Y-------LEFT-------X---T3-----
    x->right = T2;                                              //------/-\----ROTATION----/-\---------
                                                                //-----Τ2--Τ3------------T1--T2--------
    x->heightt = max(height(x->left),height(x->right))+1;       //-------------------------------------
    y->heightt = max(height(y->left),height(y->right))+1;

    return y;
}


//balanceFactor = height(left subtree) - height(right subtree)
//The balance factor of any node of an AVL tree is in the integer range [-1,+1].
//If after any modification in the tree, the balance factor becomes less than −1 or greater than +1,
//the subtree rooted at this node is unbalanced, and a rotation is needed.
template <class Type>
int AVLNode<Type>::balance(AVLNode<Type>* Node)
{
    if (Node == NULL)
        return 0;
    return height(Node->left) - height(Node->right);
}

//Insert Data in BST
template <class Type>
AVLNode<Type>* AVLNode<Type>::Insert(AVLNode<Type>* root, Type data) //gets address of the root node and the data we want to Insert to BST
{

    if(root==NULL)
    {
        root = AVLNode::GetNewNode(data); //if tree is empty we create a new Node and set it as root

    }
    else if(data ==(root->data)) //its the same string appearing again
    {
        root->appearances++;
    }
    else if(data <(root->data) )
    {
        root->left = Insert(root->left,data);//we add the Node to the left subTree
    }
    else
    {
        root->right = Insert(root->right,data);
    }

    //in the root we have the parent of the node that we inserted
    //so we have to update its height
    root->heightt = max(height(root->left), height(root->right));
    //and we have to check if the root became unbalanced after the insertion
    int rootBalance = balance(root);
    // RR rotation
    if (rootBalance > 1 && data < root->left->data)
        return rightRotate(root);

    // LL
    if (rootBalance < -1 && data > root->right->data)
        return leftRotate(root);

    // LR
    if (rootBalance > 1 && data > root->left->data)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // RL
    if (rootBalance < -1 && data < root->right->data)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;


}
//DELETE data
template <class Type>
AVLNode<Type>* AVLNode<Type>::Delete(AVLNode<Type>* root, Type data)
{
    if(root == NULL)
        return root;
    else if(data <(root->data) )
        root->left = Delete(root->left,data);
    else if (data >(root->data) )
        root->right = Delete(root->right,data);

    else//delete or edit appearances of this node
    {
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
            AVLNode *temp = root;
            root = root->right;
            delete temp;
        }
        else if(root->right == NULL)
        {
            AVLNode *temp = root;
            root = root->left;
            delete temp;
        }
        //Node has 2 children
        else
        {
            AVLNode *temp = findMin(root->right);
            root->data = temp->data;
            root->right = Delete(root->right,temp->data);
        }
    }
    if(root == NULL)
        return root;

    //balance the tree
    //o kwdikas einai idios me to insert
    root->heightt = max(height(root->left), height(root->right)) + 1;
    int rootBalance = balance(root);
    // RR rotation
    if (rootBalance > 1 && balance(root->left) >=0 )
    {
        return rightRotate(root);
    }
    // LL
    if (rootBalance < -1 && balance(root->right) <= 0)
    {
        cout<<"MPIKE"<<endl;
        return leftRotate(root);
    }
    // LR
    if (rootBalance > 1 && balance(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // RL
    if (rootBalance < -1 && balance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

template <class Type>
AVLNode<Type>* AVLNode<Type>::findMin(AVLNode<Type>* root)
{
    while(root->left != NULL)
        root = root->left;
    return root;
}

//Search Data in BST
template <class Type>
int AVLNode<Type>::Search(AVLNode<Type>* root, Type data) //data = data to be searched
{
    if(root == NULL)
    {
        cout<<"Not Found"<<endl;
        return false;
    }
    else if(root->data ==(data) )
    {
        cout<<root->data<<" "<<"Found: ";
        return root->appearances;
    }
    //else we search on the left subtree or in the right subtree
    else if(data <(root->data) )
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
void AVLNode<Type>::printPostorder(AVLNode<Type>* root)
{
    if (root == NULL)
        return;
    printPostorder(root->left);
    printPostorder(root->right);
    cout << root->data <<" ";
}
//Inorder
template <class Type>
void AVLNode<Type>::printInorder(AVLNode<Type>* root)
{
    if (root == NULL)
        return;
    printInorder(root->left);
    cout << root->data <<" ";
    printInorder(root->right);
}
//Preorder
template <class Type>
void AVLNode<Type>::printPreorder(AVLNode<Type>* root)
{
    if (root == NULL)
        return;
    cout << root->data <<" ";
    printPreorder(root->left);
    printPreorder(root->right);
}

// Function to print binary tree in 2D
// It does reverse inorder traversal
template <class Type>
void AVLNode<Type>::print2DUtil(AVLNode<Type>* root, int space)
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
void AVLNode<Type>::print2D(AVLNode<Type>* root)
{
    // Pass initial space count as 0
    print2DUtil(root, 0);
}

/* Computes the number of nodes in a tree. */
template <class Type>
unsigned int AVLNode<Type>::GetSize(AVLNode<Type>* node)
{
    if (node == NULL)
        return 0;
    else
        return(GetSize(node->left) + 1 + GetSize(node->right));
}


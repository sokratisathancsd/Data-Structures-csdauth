#include <iostream>
using namespace std;
#include <fstream>
#include <iostream>
#include <string>
#include <string.h>
#include <sstream>
#include <algorithm>
#include <bits/stdc++.h>
#include <cstdlib>
#include <ctime>
#include <typeinfo>
#include <chrono>

#include "BstNode/BstNode.h"
#include "AVLNode/AVLNode.h"
#include "HashTable/HashTable.h"

using namespace std::chrono;
int main()
{

    BstNode<string>* root = NULL;
    //code to read from file
    ifstream myReadFile;
    myReadFile.open("small-file.txt");
    string line;
    int progress=1;
    //code for timer
    auto start = high_resolution_clock::now();

    char chars[] = "()-#*+!@#$%^&*,._'\?/<>:;][}{|¿~├├╣░";
    if (myReadFile.is_open())
    {
        while (!myReadFile.eof())
        {
            myReadFile >> line;
            for (unsigned int i = 0; i < strlen(chars); ++i)
            {
                line.erase (std::remove(line.begin(), line.end(), chars[i]), line.end());
            }
            transform(line.begin(), line.end(), line.begin(), ::tolower);
            //cout<<line<<"\n";
            root = root->Insert(root, line);
            if(progress%10000==0)
            {
                cout<<100*progress/251353<<"%\n";
            }
            progress++;
        }
    }
    myReadFile.close();

    //time taken to make the Binary Search Tree
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout<<endl;
    cout << "Time to construct BST: "
         << duration.count()/1000000.00 << " seconds" << endl;


//------------------------------------------------------------------------------------

    //AVL TREE
    AVLNode<string>* avlroot = NULL; //pointer to the root Node of BST
    //code to read from file
    myReadFile.open("small-file.txt");
    progress=1;
    //code for timer
    start = high_resolution_clock::now();

    if (myReadFile.is_open())
    {
        while (!myReadFile.eof())
        {
            myReadFile >> line;
            for (unsigned int i = 0; i < strlen(chars); ++i)
            {
                line.erase (std::remove(line.begin(), line.end(), chars[i]), line.end());
            }
            transform(line.begin(), line.end(), line.begin(), ::tolower);
            //cout<<line<<"\n";
            avlroot = avlroot->Insert(avlroot, line);
            if(progress%10000==0)
            {
                cout<<100*progress/251353<<"%\n";
            }
            progress++;
        }
    }
    myReadFile.close();

    //time taken to make the Binary Search Tree
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);

    cout<<endl;
    cout << "Time to construct AVL Tree: "
         << duration.count()/1000000.00 << " seconds" << endl;


//------------------------------------------------------------------------------------

    //HASH TABLE
    HashTable *h = new HashTable(5);
    //code to read from file
    myReadFile.open("small-file.txt");
    progress=1;
    //code for timer
    start = high_resolution_clock::now();

    if (myReadFile.is_open())
    {
        while (!myReadFile.eof())
        {
            myReadFile >> line;
            for (unsigned int i = 0; i < strlen(chars); ++i)
            {
                line.erase (std::remove(line.begin(), line.end(), chars[i]), line.end());
            }
            transform(line.begin(), line.end(), line.begin(), ::tolower);
            //cout<<line<<"\n";
            h->insertNode(line);
            if(progress%10000==0)
            {
                cout<<100*progress/251353<<"%\n";
            }
            progress++;
            if((float) h->sizeofMap()==h->capacity)
            {
                h=h->reHashing(h,h->capacity*3/2+h->capacity);
            }
        }
    }

    myReadFile.close();
    //time taken to make the Binary Search Tree
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);

    cout<<endl;
    cout << "Time to construct Hash Table: "
         << duration.count()/1000000.00 << " seconds" << endl;
    //h->display();

//------------------------------------------------------------------------------------
//ETSI PREPEI NA GINEI TO DELETE
/*
    avlroot->print2D(avlroot);
    cout<<"TEST DELETE"<<endl;
    avlroot=avlroot->Delete(avlroot,"a");
    avlroot->print2D(avlroot);
    return 0;
    */
//------------------------------------------------------------------------------------

    //MAKE Q SET
    int qsize=1000;
    srand((unsigned int)time(NULL));
    int random[qsize];
    for(int i=0 ; i<qsize; i++)
    {
        random[i] = rand() % 10000 + 1;
    }
    int n = sizeof(random)/sizeof(random[0]);
    sort(random, random+n);
    string Q[qsize];
    int j=0;
    int l=0;
    myReadFile.open("small-file.txt");
    if (myReadFile.is_open())
    {
        while (!myReadFile.eof())
        {

            myReadFile >> line;
            for (unsigned int i = 0; i < strlen(chars); ++i)
            {
                line.erase (std::remove(line.begin(), line.end(), chars[i]), line.end());
            }
            transform(line.begin(), line.end(), line.begin(), ::tolower);
            if(j==random[l])
            {
                int templ=l;
                while(random[templ]==random[l])
                {
                    Q[l]=line;
                    l++;
                }
            }
            j++;
        }
    }
    myReadFile.close();

//------------------------------------------------------------------------------------

    //SEARCH IN BINARY SEARCH TREE
    start = high_resolution_clock::now();
    for(j=0; j<qsize; j++)
    {
        cout<<root->Search(root,Q[j])<<" times || ";
    }
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);

    cout<<endl;
    cout << "Time taken for Searches in BST: "
         << duration.count()/1000000.00 << " seconds" << endl;
    cout<<endl<<endl<<endl<<endl<<"----------------------------------------------"<<endl<<endl<<endl<<endl;
//------------------------------------------------------------------------------------


    //SEARCH IN AVL TREE
    start = high_resolution_clock::now();
    for(j=0; j<qsize; j++)
    {
        cout<<avlroot->Search(avlroot,Q[j])<<" times || ";
    }
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);

    cout<<endl;
    cout << "Time taken for Searches in AVL Tree: "
         << duration.count()/1000000.00 << " seconds" << endl;
    cout<<endl<<endl<<endl<<endl<<"----------------------------------------------"<<endl<<endl<<endl<<endl;
//------------------------------------------------------------------------------------

    //SEARCH IN HASH TABLE
    start = high_resolution_clock::now();
    for(j=0; j<qsize; j++)
    {
        cout<<h->Search(Q[j])<<" times || ";
    }
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);

    cout<<endl;
    cout << "Time taken for Searches in Hash Table: "
         << duration.count()/1000000.00 << " seconds" << endl;
    cout<<endl<<endl<<endl<<endl<<"----------------------------------------------"<<endl<<endl<<endl<<endl;

//---------------------------------------------------------------------------------


}

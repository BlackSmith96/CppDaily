#include "BTree.h"
#include <iostream>
// Constructor for BTreeNode
template <typename KEY, typename  VALUE>
BTreeNode::BTreeNode(int _t, bool _leaf) {
    // Copy the minimum degree and leaf property
    t = _t;
    leaf = _leaf;

    // Initialize the number of current keys to 0
    n = 0;

    // Allocating Space
    keys = new KEY[2*t-1];
    values = new VALUE[2*t-1];
    childptr = new BTreeNode<KEY, VALUE> * [2*t];
}

// Deconstructor for BTreeNOde
template <typename KEY, typename  VALUE>
BTreeNode::~BTreeNode() {
    // Release memory
    delete [] keys;
    delete [] values;
    delete [] childptr;
}

// Function to traverse all children node
template <typename KEY, typename  VALUE>
void BTreeNode::traverse() {
    // try to traverse n nodes
    for(int i=0;i < n;++i){
        if(!leaf)
            childptr[i]->traverse();
        std::cout << ' ' << values[i];
    }

    //Print last children
    if(!leaf)
        childptr[n]->traverse();
}

// Function to search key k in subtree rooted with this node
template <typename KEY, typename  VALUE>
BTreeNode* BTreeNode::search(KEY k) {
    // Find the first key equal or greater than k
    int i=0;
    while (i < n && keys[i] < k) ++i;

    if(keys[i] == k)
        return this;

    if(leaf)
        return nullptr;

    return childptr[i]->search(k);
}
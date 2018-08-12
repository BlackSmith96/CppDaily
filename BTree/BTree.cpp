#include "BTree.h"
#include <iostream>
// Constructor for BTreeNode
template <typename KEY, typename  VALUE>
BTreeNode<KEY, VALUE>::BTreeNode(int _t, bool _leaf) {
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
BTreeNode<KEY, VALUE>::~BTreeNode() {
    // Release memory
    delete [] keys;
    delete [] values;
    delete [] childptr;
}

// Function to traverse all children node
template <typename KEY, typename  VALUE>
void BTreeNode<KEY, VALUE>::traverse() {
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
BTreeNode<KEY, VALUE>* BTreeNode<KEY, VALUE>::search(KEY k) {
    // Find the first key equal or greater than k
    int i=0;
    while (i < n && keys[i] < k) ++i;

    if(keys[i] == k)
        return this;

    if(leaf)
        return nullptr;

    return childptr[i]->search(k);
}

// A utility function to insert a new key in this node
// The assumption is, the node must be non-full when this
// function is called
template <typename KEY, typename VALUE>
void BTreeNode<KEY, VALUE>::insertNonFull(KEY k, VALUE v) {
    // Initialize i the index of rightmost element
    int i = n-1;

    // If this node is leaf node
    if(leaf){

        //Find the proper position for new element
        while(keys[i] > k && i >= 0){
            keys[i+1] = keys[i];
            values[i+1] = values[i];
            --i;
        }

        keys[i+1] = k;
        values[i+1] = v;
        ++n;
    }
    else{   //If this node is not leaf node
        // Find the child which is going to have the new key
        while(i >= 0 && keys[i] > k)
            --i;

        if(childptr[i+1]->n == 2*t-1){
            //If the child is full, we have to split it.
            splitChild(i+1, childptr[i+1]);

            // After split, the middle key of C[i] goes up and
            // C[i] is splitted into two.  See which of the two
            // is going to have the new key
            if (keys[i+1] < k)
                i++;
        }
        childptr[i+1]->insertNonFull(k, v);
    }
}

// A utility function to split the child y of this node
// Note that y must be full when this function is called
template <typename KEY, typename VALUE>
void BTreeNode<KEY, VALUE>::splitChild(int i, BTreeNode<KEY, VALUE> *y) {
    // Create a new node which is going to store t-1 keys
    // of y
    BTreeNode *z = new BTreeNode<KEY, VALUE>(y->t, y->leaf);
    z->n = t-1;

    // Copy the last t-1 keys and values of y to z
    for(int j=0;j < t-1;++j){
        z->keys[j] = y->keys[j+t];
        z->values[j] = y->values[j+t];
    }

    // Copy the last t child ptr of y to z
    if(y->leaf)
        for(int j=0;j < t;++j)
            z->childptr[j] = y->childptr[j+t];

    // Reduce the number of keys in y
    y->n = t - 1;

    // Since this node is going to have a new child,
    // create space of new child
    for(int j = n; j > i;--j){
        childptr[j+1] = childptr[j];
    }

    childptr[i+1] = z;

    // A key of y will move to this node. Find location of
    // new key and move all greater keys one space ahead
    for (int j = n-1; j >= i; j--){
        keys[j+1] = keys[j];
        values[j+1] = values[j];
    }

    // Copy the middle key and values of y to this node
    keys[i] = y->keys[t-1];

    // Increment count of keys in this node
    ++n;
}

// Initialize tree as empty
template <typename KEY, typename VALUE>
BTree<KEY, VALUE>::BTree(int _t) {
    t = _t;
    root = nullptr;
}

// deconstructor of BTree
template <typename KEY, typename VALUE>
BTree<KEY, VALUE>::~BTree() {
    //haven't consider well
}

// function to traverse all nodes in this tree
template <typename KEY, typename VALUE>
void BTree<KEY, VALUE>::traverse() {
    if(root != nullptr)
        root->traverse();
}

// function to search key k in this tree
template <typename KEY, typename VALUE>
BTreeNode* BTree<KEY, VALUE>::search(KEY k) {
    return (root == nullptr)? nullptr : root->search(k);
}

// The main function that inserts a new key in this B-Tree
template <typename KEY, typename VALUE>
void BTree<KEY, VALUE>::insert(KEY k, VALUE v) {
    //If tree is empty
    if(root == nullptr){
        //allocate memory to root
        root = new BTreeNode<KEY, VALUE>(t, true);
        root->keys[0] = k;
        root->values[0] = v;
        root->n = 1;
    }
    else {
        // If root is full, then tree grows in height
        if(root->n == 2*t-1){
            // Allocating memory for new root
            BTreeNode<KEY, VALUE> * s = new BTreeNode<KEY, VALUE>(t, false);

            // Make old root as child of new root
            s->childptr[0] = root;

            // Split the old root and move 1 key to the new root
            s->splitChild(0, root);

            // New root has two children now.  Decide which of the
            // two children is going to have new key
            int i = 0;
            if (s->keys[0] < k)
                i++;
            s->childptr[i]->insertNonFull(k);

            // Change root
            root = s;

        }
        else //If root is not full, call insertNonFull for root
            root->insertNonFull(k, v);
    }
}


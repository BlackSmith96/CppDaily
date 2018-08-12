#ifndef BTREE_LIBRARY_H
#define BTREE_LIBRARY_H

const int N = 2;    //N is minimum degree

template <typename KEY, typename  VALUE>
class BTreeNode{
private:
    KEY * keys;        //An array of keys
    VALUE * values;    //An array of values
    BTreeNode<KEY, VALUE> ** childptr;    //An array of child pointers
    int t;    //The minimum degree
    int n;    //Current number of keys
    bool leaf;    //Whether this node is leaf
public:
    BTreeNode(int _t, bool _leaf);    //constructor

    ~BTreeNode();   //deconstructor

    // A function to traverse all nodes in a subtree rooted with this node
    void traverse();

    // A function to search a key in the subtree rooted with this node.
    BTreeNode *search(KEY k);   // returns NULL if k is not present.

    // A utility function to insert a new key in the subtree rooted with
    // this node. The assumption is, the node must be non-full when this
    // function is called
    void insertNonFull(KEY k, VALUE v);

    // A utility function to split the child y of this node. i is index of y in
    // child array childptr[].  The Child y must be full when this function is called
    void splitChild(int i, BTreeNode<KEY, VALUE> *y);

    // Make the BTree friend of this so that we can access private members of this
    // class in BTree functions
    friend class BTree<KEY, VALUE>;
};

template <typename KEY, typename VALUE>
class BTree{
private:
    BTreeNode<KEY, VALUE>  * root;    // Pointer to the root node
    int t;    // The minimum degree of the tree
public:
    BTree(int _t);    // Constructor

    ~BTree();    // Deconstructor

    // Traverse all nodes of the tree
    void traverse();

    // Search a specific node of the tree
    BTreeNode * search(KEY k);

    // The main function that inserts a new key in this B-Tree
    void insert(KEY k, VALUE v);

};

#endif
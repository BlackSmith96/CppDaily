#ifndef BTREE_LIBRARY_H
#define BTREE_LIBRARY_H

#include <vector>

const int N = 2;    //N is minimum degree

template <typename KEY, typename  VALUE>
typedef struct node{
    KEY index;
    VALUE v;
    std::vector<KEY> keys;
    std::vector<struct node *> pchildren;
} NODE;

template <typename KEY, typename VALUE>
class BTree{
public:
    // Construction Function
    BTree();

    // Decomposition Function
    ~BTree();

    // Insert (key,value) pair
    void Insert(KEY key, VALUE value);

    // judge a given key's existence
    bool find(KEY key);

private:
    NODE<KEY,VALUE> * root;
};

#endif
#ifndef FQL_BTREE_H
#define FQL_BTREE_H

#include "BTreeNode.h"

template <typename T>
class BTree {
private:
    BTreeNode<T>* root;
    int degree;

public:
    BTree();
    explicit BTree(int _degree);
    ~BTree();

    void insert(const T& key);
    bool search(const T& key) const;
    void deleteTree(BTreeNode<T>* node);
};

template<typename T>
BTree<T>::BTree() : root(nullptr), degree(100) {}

template<typename T>
BTree<T>::BTree(int _degree) : root(nullptr), degree(_degree) {}

template<typename T>
BTree<T>::~BTree() { deleteTree(root); }

template<typename T>
void BTree<T>::insert(const T &key) {
    if (root == nullptr) {
        root = new BTreeNode<T>(degree, true);
        std::vector<T> rootKeys{key};
        root->setKeys(rootKeys);
    }
    else{
        if (root->getKeys().size() == 2 * degree - 1) {
            auto* newRoot = new BTreeNode<T>(degree, false);

            std::vector<BTreeNode<T>*> rootChildren{root};
            newRoot->setChildren(rootChildren);

            newRoot->splitChild(0);

            int index = (key < newRoot->getKeys()[0]) ? 0 : 1;
            newRoot->getChildren()[index]->insertNonFull(key);

            root = newRoot;
        }
        else root->insertNonFull(key);
    }
}

template<typename T>
bool BTree<T>::search(const T &key) const {
    if (root == nullptr) return false;

    return root->search(key) != nullptr;
}

template<typename T>
void BTree<T>::deleteTree(BTreeNode<T>* node) {
    if (node == nullptr) return;

    for (BTreeNode<T>* child : node->getChildren()) {
        deleteTree(child);
    }
    delete node;
}

#endif //FQL_BTREE_H
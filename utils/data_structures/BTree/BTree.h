#ifndef FQL_BTREE_H
#define FQL_BTREE_H

#include "BTreeNode.h"

template <typename T>
class BTree {
private:
    BTreeNode<T>* root;
    long degree;

    // Helper function to print the tree recursively
    void showNode(BTreeNode<T>* node) const;

public:
    BTree();
    explicit BTree(long _degree);
    ~BTree();

    void insert(const T& key);
    bool search(const T& key) const;
    void deleteTree(BTreeNode<T>* node);

    // New method to show all values in the B-tree
    void show() const;
};

template<typename T>
BTree<T>::BTree() : root(nullptr), degree(100) {}

template<typename T>
BTree<T>::BTree(long _degree) : root(nullptr), degree(_degree) {}

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

template<typename T>
void BTree<T>::show() const {
    if (root != nullptr) {
        showNode(root);
    }
}

template<typename T>
void BTree<T>::showNode(BTreeNode<T>* node) const {
    for (const T& key : node->getKeys()) {
        std::cout << key << " ";
    }

    if (!node->isLeaf()) {
        for (BTreeNode<T>* child : node->getChildren()) {
            showNode(child);
        }
    }
}

#endif //FQL_BTREE_H

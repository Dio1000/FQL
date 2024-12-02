#ifndef FQL_BTREENODE_H
#define FQL_BTREENODE_H

#include <vector>

template <typename T>
class BTreeNode {
private:
    int degree;
    bool leaf;
    std::vector<T> keys;
    std::vector<BTreeNode*> children;

public:
    BTreeNode();
    BTreeNode(int _degree, bool _leaf);

    int getDegree() const;
    bool isLeaf() const;

    const std::vector<T>& getKeys() const;
    const std::vector<BTreeNode*>& getChildren() const;

    void setLeaf(bool _leaf);
    void setKeys(const std::vector<T>& _keys);
    void setChildren(const std::vector<BTreeNode*>& _children);

    void insertNonFull(const T& key);
    void splitChild(int childIndex);
    BTreeNode<T>* search(const T& key);
};

template<typename T>
BTreeNode<T>::BTreeNode() : degree(100), leaf(true) {}

template<typename T>
BTreeNode<T>::BTreeNode(int _degree, bool _leaf) : degree(_degree), leaf(_leaf) {}

template<typename T>
int BTreeNode<T>::getDegree() const { return this->degree; }

template<typename T>
bool BTreeNode<T>::isLeaf() const { return this->leaf; }

template<typename T>
const std::vector<T>& BTreeNode<T>::getKeys() const { return this->keys; }

template<typename T>
const std::vector<BTreeNode<T>*>& BTreeNode<T>::getChildren() const { return this->children; }

template<typename T>
void BTreeNode<T>::setLeaf(bool _leaf) { this->leaf = _leaf; }

template<typename T>
void BTreeNode<T>::setKeys(const std::vector<T>& _keys) { this->keys = _keys; }

template<typename T>
void BTreeNode<T>::setChildren(const std::vector<BTreeNode*>& _children) { this->children = _children; }

template<typename T>
void BTreeNode<T>::splitChild(int childIndex) {
    BTreeNode<T>* child = children[childIndex];
    auto* newChild = new BTreeNode<T>(child->getDegree(), child->isLeaf());

    int middle = (degree - 1) / 2;
    std::vector<T> childKeys(child->getKeys().begin() + middle + 1, child->getKeys().end());
    newChild->setKeys(childKeys);

    child->setKeys(std::vector<T>(child->getKeys().begin(), child->getKeys().begin() + middle));

    if (!child->isLeaf()) {
        std::vector<BTreeNode*> childChildren(child->getChildren().begin() + middle + 1, child->getChildren().end());
        newChild->setChildren(childChildren);
        child->setChildren(std::vector<BTreeNode*>(child->getChildren().begin(), child->getChildren().begin() + middle + 1));
    }

    keys.insert(keys.begin() + childIndex, child->getKeys()[middle]);
    child->setKeys(std::vector<T>(child->getKeys().begin(), child->getKeys().begin() + middle));

    children.insert(children.begin() + childIndex + 1, newChild);
}

template<typename T>
void BTreeNode<T>::insertNonFull(const T &key) {
    int rightIndex = keys.size() - 1;

    if (leaf) {
        keys.push_back(key);
        while (rightIndex >= 0 && keys[rightIndex] > key) {
            keys[rightIndex + 1] = keys[rightIndex];
            rightIndex--;
        }
        keys[rightIndex + 1] = key;

        return;
    } else {
        while (rightIndex >= 0 && keys[rightIndex] > key) rightIndex--;
        rightIndex++;

        if (children[rightIndex]->getKeys().size() == 2 * degree - 1) {
            splitChild(rightIndex);
            if (keys[rightIndex] < key) rightIndex++;
        }
        children[rightIndex]->insertNonFull(key);
    }
}

template<typename T>
BTreeNode<T>* BTreeNode<T>::search(const T &key) {
    int index = 0;
    while (index < keys.size() && key > keys[index]) index++;

    if (index < keys.size() && keys[index] == key) {
        return this;
    }

    if (leaf) return nullptr;
    return children[index]->search(key);
}

#endif //FQL_BTREENODE_H
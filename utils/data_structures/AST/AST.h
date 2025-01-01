#ifndef FQL_AST_H
#define FQL_AST_H

#include "ASTNode.h"

class AST {
private:
    ASTNode* end;
    ASTNode* root;
    ASTNode* currentNode;

public:
    AST();

    void insertLeft(const std::string &value);
    void insertRight(const std::string &value);

    void createChildren();
    void insertInCurrentNode(const std::string &value);
    bool currentNodeIsRoot() const;
    bool currentNodeIsNull() const;

    bool rightNodeIsNull() const;
    bool leftNodeIsNull() const;
    bool isEnded() const;

    void goUp();
    void goLeft();
    void goRight();

    std::string getRoot();
    std::string getCurrentNode();
};

AST::AST() {
    end = new ASTNode();
    root = new ASTNode();
    currentNode = new ASTNode();

    end->setLeft(root);
    root->setParent(end);
    currentNode = root;
}

void AST::insertLeft(const std::string &value) {
    if (!currentNode) {
        root = new ASTNode(value);
        currentNode = root;
    } else {
        if (!currentNode->getLeft()) {
            auto* newNode = new ASTNode(value);
            currentNode->setLeft(newNode);
            newNode->setParent(currentNode);
        } else {
            currentNode->getLeft()->setKey(value);
        }
    }
}

void AST::insertRight(const std::string &value) {
    if (!currentNode) {
        root = new ASTNode(value);
        currentNode = root;
    } else {
        if (!currentNode->getRight()) {
            auto* newNode = new ASTNode(value);
            currentNode->setRight(newNode);
            newNode->setParent(currentNode);
        } else {
            currentNode->getRight()->setKey(value);
        }
    }
}

bool AST::currentNodeIsRoot() const {
    return currentNode == root;
}

bool AST::currentNodeIsNull() const {
    return currentNode == nullptr;
}

void AST::createChildren() {
    if (!currentNode) {
        root = new ASTNode();
        currentNode = root;
    }

    auto* newLeftNode = new ASTNode();
    auto* newRightNode = new ASTNode();
    newLeftNode->setParent(currentNode);
    newRightNode->setParent(currentNode);

    currentNode->setLeft(newLeftNode);
    currentNode->setRight(newRightNode);
}

void AST::insertInCurrentNode(const std::string &value) {
    if (!currentNode) {
        root = new ASTNode(value);
        currentNode = root;
    }
    else {
        currentNode->setKey(value);
    }
}

bool AST::rightNodeIsNull() const {
    return currentNode->getRight()->getKey() == "Null";
}

bool AST::leftNodeIsNull() const {
    return currentNode->getLeft()->getKey() == "Null";
}

void AST::goUp() {
    if (currentNode && currentNode->getParent()) {
        currentNode = currentNode->getParent();
    }
}

void AST::goLeft() {
    if (currentNode && currentNode->getLeft()) {
        currentNode = currentNode->getLeft();
    }
}

void AST::goRight() {
    if (currentNode && currentNode->getRight()) {
        currentNode = currentNode->getRight();
    }
}

std::string AST::getRoot() {
    if (this->root) {
        return this->root->getKey();
    }
    else {
        return "Null";
    }
}

std::string AST::getCurrentNode() {
    if (this->currentNode) {
        return this->currentNode->getKey();
    }
    else {
        return "Null";
    }
}

bool AST::isEnded() const {
    return currentNode == end;
}


#endif
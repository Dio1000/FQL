#ifndef FQL_ASTNODE_H
#define FQL_ASTNODE_H

#include <string>
#include <utility>

class ASTNode {
private:
    ASTNode *left;
    ASTNode *right;
    ASTNode *parent;
    std::string key;

public:
    ASTNode();
    explicit ASTNode(const std::string &key);

    ASTNode* getLeft();
    void setLeft(ASTNode* node);

    ASTNode* getRight();
    void setRight(ASTNode* node);

    ASTNode* getParent();
    void setParent(ASTNode* node);

    [[nodiscard]] const std::string& getKey() const;
    void setKey(const std::string &value);
};

ASTNode::ASTNode() {
    this->parent = nullptr;
    this->left = nullptr;
    this->right = nullptr;
    this->key = "Null";
}

ASTNode::ASTNode(const std::string &key){
    this->parent = nullptr;
    this->left = nullptr;
    this->right = nullptr;
    this->key = key;
}

ASTNode* ASTNode::getLeft() { return this->left; }
void ASTNode::setLeft(ASTNode* node) { this->left = node; }

ASTNode* ASTNode::getRight() { return this->right; }
void ASTNode::setRight(ASTNode* node) { this->right = node; }

ASTNode* ASTNode::getParent() { return this->parent; }
void ASTNode::setParent(ASTNode* node) { this->parent = node; }

const std::string& ASTNode::getKey() const { return this->key; }
void ASTNode::setKey(const std::string &value) { this->key = value; }

#endif

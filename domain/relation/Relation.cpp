#include "Relation.h"

#include <utility>
#include "../../io/io.h"

Relation::Relation() : name("null"), attributes() {}

Relation::Relation(std::string name)
        : name(std::move(name)){}

Relation::~Relation() {
    for (auto attribute : attributes) {
        delete attribute;
    }
}

std::string Relation::getName() const {
    return this->name;
}

void Relation::setName(const std::string &newName) {
    this->name = newName;
}

Attribute* Relation::getAttribute(int index) const {
    if (index < 1 || index > static_cast<int>(attributes.size()) + 1) {
        throw std::out_of_range("Attribute index out of range");
    }
    return attributes[index - 1];
}

void Relation::addAttribute(Attribute* attribute) {
    attributes.push_back(attribute);
}

void Relation::removeAttribute(int index) {
    if (index < 1 || index > static_cast<int>(attributes.size())) {
        throw std::out_of_range("Attribute index out of range");
    }
    delete attributes[index - 1];
    attributes.erase(attributes.begin() + (index - 1));
}

int Relation::getAttributeNumber() const {
    return static_cast<int>(attributes.size());
}

void Relation::storeRelation(const std::string &schema) const {
    std::string filePath = "DB/" + schema + "/relations/" + this->getName();
    if (validFile(filePath)) return;

    createFile(filePath);
    std::string attributeHeader = "RID,";

    for (int index = 0 ; index < attributes.size() ; index++){
        if (index != attributes.size() - 1) attributeHeader += attributes[index]->getName() + ",";
        else attributeHeader += attributes[index]->getName();
    }

    writeLine(filePath, attributeHeader);
}
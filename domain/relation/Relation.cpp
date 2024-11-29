#include "Relation.h"

Relation::Relation() : name("null"), attributes() {}

Relation::Relation(const std::string &name, const std::vector<Attribute*> &attributes)
        : name(name), attributes(attributes) {}

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
    if (index < 1 || index > static_cast<int>(attributes.size())) {
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

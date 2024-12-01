#include <string>
#include <utility>
#include <vector>

#include "Schema.h"

Schema::Schema() : name("null"), relations() {}

Schema::Schema(std::string name, std::vector<Relation *> relations) :
    name(std::move(name)), relations(std::move(relations)) {}

Schema::~Schema() {
    for (auto relation : relations){
        delete relation;
    }
}

std::string Schema::getName() const {
    return this->name;
}

void Schema::setName(const std::string &_name) {
    this->name = _name;
}

Relation *Schema::getRelation(int index) const {
    if (index < 1 || index > static_cast<int>(relations.size())) {
        throw std::out_of_range("Attribute index out of range");
    }
    return relations[index - 1];
}

void Schema::addRelation(Relation *relation) {
    relations.push_back(relation);
}

void Schema::removeRelation(int index) {
    if (index < 1 || index > static_cast<int>(relations.size())) {
        throw std::out_of_range("Attribute index out of range");
    }
    delete relations[index - 1];
    relations.erase(relations.begin() + (index - 1));
}

int Schema::getRelationNumber() const {
    return static_cast<int>(relations.size());
}

#include <string>
#include <utility>
#include <vector>

#include "Schema.h"
#include "../../io/io.h"

Schema::Schema() : name("null"), relations() {}

Schema::Schema(std::string name) :
    name(std::move(name)) {}

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

void Schema::storeSchema() const {
    std::string directoryPath = "DB/" + this->getName();
    std::string directoryPath2 = directoryPath + "/relations";

    if (validDirectory(directoryPath)) return;
    if (validDirectory(directoryPath2)) return;

    createDirectory(directoryPath.c_str());
    createDirectory(directoryPath2.c_str());

    std::string filePath = directoryPath + "/currentRID";
    std::string filePath2 = directoryPath + "/relationAttributes";
    createFile(filePath);
    createFile(filePath2);
}

bool Schema::hasRelation(Relation *relation) {
    for (const auto &_relation : relations){
        if (_relation == relation) return true;
    }

    return false;
}
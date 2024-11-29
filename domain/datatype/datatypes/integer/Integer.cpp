#include "Integer.h"

Integer::Integer() {
    this->name = "int";
    this->maxLength = 10;
}

std::string Integer::getName() {
    return this->name;
}

void Integer::setName(const std::string &newName) {
    this->name = newName;
}

int Integer::getMaxLength() {
    return this->maxLength;
}

void Integer::setMaxLength(int newMaxLength) {
    this->maxLength = newMaxLength;
}

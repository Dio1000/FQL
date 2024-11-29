#include <string>
#include "Boolean.h"

Boolean::Boolean() {
    this->name = "bool";
    this->maxLength = 10;
}

std::string Boolean::getName() {
    return this->name;
}

void Boolean::setName(const std::string &newName) {
    this->name = newName;
}

int Boolean::getMaxLength() {
    return this->maxLength;
}

void Boolean::setMaxLength(int newMaxLength) {
    this->maxLength = newMaxLength;
}


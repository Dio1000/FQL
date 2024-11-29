#include "Char.h"

Char::Char() {
    this->name = "char";
    this->maxLength = 50;
}

Char::Char(int maxLength) {
    this->name = "char";
    this->maxLength = maxLength;
}

std::string Char::getName() {
    return this->name;
}

void Char::setName(const std::string &newName) {
    this->name = newName;
}

int Char::getMaxLength() {
    return this->maxLength;
}

void Char::setMaxLength(int newMaxLength) {
    this->maxLength = newMaxLength;
}

#include "Varchar.h"

Varchar::Varchar() {
    this->name = "varchar";
    this->maxLength = 500;
}

Varchar::Varchar(int maxLength) {
    this->name = "varchar";
    this->maxLength = maxLength;
}

std::string Varchar::getName() {
    return this->name;
}

void Varchar::setName(const std::string &newName) {
    this->name = newName;
}

int Varchar::getMaxLength() {
    return this->maxLength;
}

void Varchar::setMaxLength(int newMaxLength) {
    this->maxLength = newMaxLength;
}

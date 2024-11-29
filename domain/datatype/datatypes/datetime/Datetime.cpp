#include "Datetime.h"

Datetime::Datetime() {
    this->name = "datetime";
    this->maxLength = 20;
}

std::string Datetime::getName() {
    return this->name;
}

void Datetime::setName(const std::string &newName) {
    this->name = newName;
}

int Datetime::getMaxLength() {
    return this->maxLength;
}

void Datetime::setMaxLength(int newMaxLength) {
    this->maxLength = newMaxLength;
}

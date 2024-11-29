#include "Date.h"


Date::Date() {
    this->name = "date";
    this->maxLength = 10;
}

std::string Date::getName() {
    return this->name;
}

void Date::setName(const std::string &newName) {
    this->name = newName;
}

int Date::getMaxLength() {
    return this->maxLength;
}

void Date::setMaxLength(int newMaxLength) {
    this->maxLength = newMaxLength;
}

#include <string>

#include "../datatype/Datatype.h"
#include "Attribute.h"

void Attribute::setName(std::string &_name) {
    this->name = _name;
}

std::string Attribute::getName() {
    return this->name;
}

void Attribute::setDataType(Datatype *_dataType) {
    this->dataType = (Datatype *) _dataType;
}

Datatype & Attribute::getDataType() {
    if (this->dataType == nullptr) {
        throw std::runtime_error("DataType is null!");
    }
    return *this->dataType; // Dereference the pointer to return a reference
}



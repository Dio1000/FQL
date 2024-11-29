#include <string>

#include "../datatype/Datatype.h"
#include "Attribute.h"

Attribute::Attribute() {
    this->name = "null";
    this->dataType = nullptr;
    this->nullable = false;
}

Attribute::Attribute(const std::string &name, Datatype *dataType, bool nullable) {
    this->name = name;
    this->dataType = dataType;
    this->nullable = nullable;
}

void Attribute::setName(std::string &_name) {
    this->name = _name;
}

std::string Attribute::getName() {
    return this->name;
}

void Attribute::setDataType(Datatype *_dataType) {
    this->dataType = (Datatype *) _dataType;
}

Datatype &Attribute::getDataType() {
    if (this->dataType == nullptr) {
        throw std::runtime_error("DataType is null!");
    }
    return *this->dataType;
}

void Attribute::setNullable(bool _nullable) {
    this->nullable = _nullable;
}

bool Attribute::getNullable() {
    return this->nullable;
}

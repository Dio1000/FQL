#include <string>

#include "../datatype/Datatype.h"
#include "Attribute.h"

Attribute::Attribute() {
    this->name = "null";
    this->dataType = nullptr;
    this->constraint = "null";
}

Attribute::Attribute(const std::string &name, Datatype *dataType, const std::string &constraint) {
    this->name = name;
    this->dataType = dataType;
    this->constraint = constraint;
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

void Attribute::setConstraint(std::string &_constraint) {
    this->constraint = _constraint;
}

std::string Attribute::getConstraint() {
    return this->constraint;
}


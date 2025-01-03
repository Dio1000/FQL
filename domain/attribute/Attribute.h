#ifndef FQL_ATTRIBUTE_H
#define FQL_ATTRIBUTE_H

#include "../datatype/Datatype.h"

/**
 * Using this class allows the user to create and insert
 * an attribute (column) into a relation (table).
 */
class Attribute {
private:
    std::string name;
    Datatype* dataType;
    std::string constraint;

public:
    Attribute();
    Attribute(const std::string &name, Datatype *dataType, const std::string &constraint);

    void setName(std::string &_name);
    std::string getName();

    void setDataType(Datatype *_dataType);
    Datatype &getDataType();

    void setConstraint(std::string &_constraint);
    std::string getConstraint();
};


#endif //FQL_ATTRIBUTE_H

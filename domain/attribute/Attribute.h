#ifndef FQL_ATTRIBUTE_H
#define FQL_ATTRIBUTE_H

/**
 * Using this class allows the user to create and insert
 * an attribute (column) into a relation (table).
 */
class Attribute {
private:
    std::string name;
    Datatype* dataType;

public:
    void setName(std::string &_name);
    std::string getName();

    void setDataType(Datatype *_dataType);
    Datatype & getDataType();
};


#endif //FQL_ATTRIBUTE_H

#ifndef FQL_DATATYPE_H
#define FQL_DATATYPE_H

#include <string>

/**
 * Using this interface allows the user to specify
 * the datatype of an attribute.
 */
class Datatype {
public:
    virtual ~Datatype() = default;

    virtual std::string getName() = 0;
    virtual void setName(const std::string &name) = 0;

    virtual int getMaxLength() = 0;
    virtual void setMaxLength(int maxLength) = 0;
};

#endif //FQL_DATATYPE_H
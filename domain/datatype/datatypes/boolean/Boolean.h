#ifndef FQL_BOOLEAN_H
#define FQL_BOOLEAN_H

#include "../../Datatype.h"

class Boolean : public Datatype {
private:
    std::string name;
    int maxLength;

public:
    Boolean();

    std::string getName() override;
    void setName(const std::string &newName) override;

    int getMaxLength() override;
    void setMaxLength(int newMaxLength) override;
};

#endif // FQL_BOOLEAN_H

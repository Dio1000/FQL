#ifndef FQL_INTEGER_H
#define FQL_INTEGER_H

#include "../../Datatype.h"

class Integer : public Datatype {
private:
    std::string name;
    int maxLength;

public:
    Integer();

    std::string getName() override;
    void setName(const std::string &newName) override;

    int getMaxLength() override;
    void setMaxLength(int newMaxLength) override;
};

#endif //FQL_INTEGER_H

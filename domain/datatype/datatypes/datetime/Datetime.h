#ifndef FQL_DATETIME_H
#define FQL_DATETIME_H

#include "../../Datatype.h"

class Datetime : public Datatype {
private:
    std::string name;
    int maxLength;

public:
    Datetime();

    std::string getName() override;
    void setName(const std::string &newName) override;

    int getMaxLength() override;
    void setMaxLength(int newMaxLength) override;
};


#endif //FQL_DATETIME_H

#ifndef FQL_DATE_H
#define FQL_DATE_H

#include "../../Datatype.h"

class Date : public Datatype {
private:
    std::string name;
    int maxLength;

public:
    Date();

    std::string getName() override;
    void setName(const std::string &newName) override;

    int getMaxLength() override;
    void setMaxLength(int newMaxLength) override;
};


#endif //FQL_DATE_H

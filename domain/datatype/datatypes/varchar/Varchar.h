#ifndef FQL_VARCHAR_H
#define FQL_VARCHAR_H

#include "../../Datatype.h"

class Varchar : public Datatype {
private:
    std::string name;
    int maxLength;

public:
    Varchar();
    explicit Varchar(int maxLength);

    std::string getName() override;
    void setName(const std::string &newName) override;

    int getMaxLength() override;
    void setMaxLength(int newMaxLength) override;
};


#endif //FQL_VARCHAR_H

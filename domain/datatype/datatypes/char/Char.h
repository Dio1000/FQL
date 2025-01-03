#ifndef FQL_CHAR_H
#define FQL_CHAR_H

#include "../../Datatype.h"

class Char : public Datatype {
private:
    std::string name;
    int maxLength;

public:
    Char();
    explicit Char(int maxLength);

    std::string getName() override;
    void setName(const std::string &newName) override;

    int getMaxLength() override;
    void setMaxLength(int newMaxLength) override;
};


#endif //FQL_CHAR_H

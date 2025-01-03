#ifndef FQL_RELATION_H
#define FQL_RELATION_H

#include <vector>
#include <string>
#include "../attribute/Attribute.h"

/**
 * Using this class allows the user to create a Relation
 * to be used in a Database (schema).
 */
class Relation {
private:
    std::string name;
    std::vector<Attribute*> attributes;

public:
    Relation();
    explicit Relation(std::string name);
    ~Relation();

    [[nodiscard]] std::string getName() const;
    void setName(const std::string &newName);

    [[nodiscard]] Attribute* getAttribute(int index) const;
    void addAttribute(Attribute* attribute);
    void removeAttribute(int index);

    [[nodiscard]] int getAttributeNumber() const;

    void storeRelation(const std::string &schema) const;
};

#endif // FQL_RELATION_H

#ifndef FQL_SCHEMA_H
#define FQL_SCHEMA_H

#include "../relation/Relation.h"

/**
 * Using this class allows the user to define a Schema
 * for their Database.
 */
class Schema {
private:
    std::string name;
    std::vector<Relation*> relations;

public:
    Schema();
    Schema(std::string name, std::vector<Relation*> relations);
    ~Schema();

    std::string getName() const;
    void setName(const std::string &_name);

    Relation* getRelation(int index) const;
    void addRelation(Relation* relation);
    void removeRelation(int index);

    int getRelationNumber() const;
};


#endif //FQL_SCHEMA_H

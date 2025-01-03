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
    explicit Schema(std::string name);
    ~Schema();

    [[nodiscard]] std::string getName() const;
    void setName(const std::string &_name);

    [[nodiscard]] Relation* getRelation(int index) const;
    void addRelation(Relation* relation);
    bool hasRelation(Relation* relation);

    void removeRelation(int index);

    [[nodiscard]] int getRelationNumber() const;

    void storeSchema() const;
};


#endif //FQL_SCHEMA_H

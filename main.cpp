#include <iostream>
#include <vector>

#include "./domain/relation/Relation.h"
#include "./domain/attribute/Attribute.h"
#include "./domain/schema/Schema.h"
#include "./domain/datatype/datatypes/integer/Integer.h"
#include "./domain/datatype/datatypes/boolean/Boolean.h"
#include "./domain/datatype/datatypes/date/Date.h"

int main() {
    std::cout << "Work in progress!" << std::endl;

    auto* attr1 = new Attribute("studentNum", new Integer(), true);
    auto* attr2 = new Attribute("isStudent", new Boolean(), true);
    auto* attr3 = new Attribute("enrollmentDate", new Date(), false);

    std::vector<Attribute*> attributes;
    attributes.push_back(attr1);
    attributes.push_back(attr2);
    attributes.push_back(attr3);

    auto* relation = new Relation("Student", attributes);

    std::vector<Relation*> relations;
    relations.push_back(relation);

    auto* schema = new Schema("School", relations);

    std::cout << schema->getName() << std::endl;
    std::cout << schema->getRelation(1)->getAttribute(1)->getDataType().getName();
}

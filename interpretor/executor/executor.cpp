#include <string>
#include <vector>
#include <iostream>

#include "executor.h"
#include "../../utils/algorithms/algorithms.h"
#include "../../io/io.h"
#include "../../domain/attribute/Attribute.h"
#include "../../domain/relation/Relation.h"
#include "../../domain/schema/Schema.h"
#include "../../domain/datatype/datatypes/boolean/Boolean.h"
#include "../../domain/datatype/datatypes/char/Char.h"
#include "../../domain/datatype/datatypes/date/Date.h"
#include "../../domain/datatype/datatypes/datetime/Datetime.h"
#include "../../domain/datatype/datatypes/integer/Integer.h"
#include "../../domain/datatype/datatypes/varchar/Varchar.h"

std::vector<Schema*> schemas;
std::vector<Relation*> relations;

int executeCode(const std::string &filePath){
    std::vector<std::string> codeLines = readLines(filePath);

    int index = 0;
    while (index < codeLines.size()){
        auto tokens = split(codeLines[index], ":");
        std::string opCode = tokens[0];
        std::string command = tokens[1];

        if (opCode == "createSchema") index = executeSchema(index, codeLines);
        else if (opCode == "createRelation") index = executeRelation(index, codeLines);
        else if (opCode == "createRelationAttributes") index = executeRelationAttributes(index, codeLines);
        else if (opCode == "array") index = executeArray(index, codeLines);
        else if (isMethodCall(opCode)) index = executeMethodCall(index, codeLines);
        else index++;
    }

    return index;
}

int executeSchema(int index, const std::vector<std::string> &codeLines){
    auto tokens = split(codeLines[index], ":");
    auto *newSchema = new Schema(tokens[1]);

    schemas.push_back(newSchema);
    newSchema->storeSchema();
    return index + 1;
}

int executeRelation(int index, const std::vector<std::string> &codeLines){
    auto tokens = split(codeLines[index], ":");
    std::string relationName = split(tokens[1], ",")[1];
    std::string schemaName = split(tokens[1], ",")[0];

    auto *schema = getSchema(schemaName);
    auto *newRelation = new Relation(relationName);
    schema->addRelation(newRelation);

    relations.push_back(newRelation);
    newRelation->storeRelation(getSchemaFromRelation(newRelation)->getName());
    return index + 1;
}

int executeRelationAttributes(int index, const std::vector<std::string> &codeLines){
    auto tokens = split(codeLines[index], ":");
    std::string relationName = tokens[1];
    index++;

    Relation *relation = getRelation(relationName);
    tokens = split(codeLines[index], ":");
    while (tokens[0] == "createAttribute"){
        auto attributeTokens = split(tokens[1], ":");
        std::string attributeName = split(attributeTokens[0], ",")[0];
        std::string attributeDataType = split(attributeTokens[0], ",")[1];
        std::string attributeConstraint = split(attributeTokens[0], ",")[2];

        Datatype *datatype = getDataType(attributeDataType);
        auto *newAttribute = new Attribute(attributeName, datatype, attributeConstraint);
        relation->addAttribute(newAttribute);

        index++;
        tokens = split(codeLines[index], ":");
    }

    relation->storeRelation(getSchemaFromRelation(relation)->getName());
    return index;
}

bool isMethodCall(const std::string &method){
    if (method == "addRelation" || method == "updateRelation" || method == "deleteRelation"
        || method == "fetchRelation") return true;

    return false;
}

int executeMethodCall(int index, const std::vector<std::string> &codeLines){
    auto tokens = split(codeLines[index], ":");

    if (tokens[0] == "addRelation") return executeAddRelation(index, codeLines);
    else if (tokens[0] == "updateRelation") return executeUpdateRelation(index, codeLines);
    else if (tokens[0] == "deleteRelation") return executeDeleteRelation(index, codeLines);
    else if (tokens[0] == "fetchRelation") return executeFetchRelation(index, codeLines);
    else return index + 1;
}

int executeAddRelation(int index, const std::vector<std::string> &codeLines){
    return index + 1;
}

int executeUpdateRelation(int index, const std::vector<std::string> &codeLines){
    return index + 1;
}

int executeDeleteRelation(int index, const std::vector<std::string> &codeLines){
    return index + 1;
}

int executeArray(int index, const std::vector<std::string> &codeLines){
    return index + 1;
}

int executeFetchRelation(int index, const std::vector<std::string> &codeLines){
    return index + 1;
}

int executeConcatenate(int index, const std::vector<std::string> &codeLines){
    return index + 1;
}


bool isRelationInSchema(Relation* relation, Schema* schema){
    if (schema->hasRelation(relation)) return true;
    return false;
}

Schema *getSchemaFromRelation(Relation *relation){
    for (auto schema : schemas){
        if (isRelationInSchema(relation, schema)) return schema;
    }

    return nullptr;
}

Schema *getSchema(const std::string &schemaName){
    for (auto schema : schemas){
        if (schema->getName() == schemaName) return schema;
    }

    return new Schema("Null");
}

Relation *getRelation(const std::string &relationName){
    for (auto relation : relations){
        if (relation->getName() == relationName) return relation;
    }

    return new Relation("Null");
}

Datatype *getDataType(const std::string &dataType){
    if (dataType == "boolean") return new Boolean();
    else if (dataType == "date") return new Date();
    else if (dataType == "datetime") return new Datetime();
    else if (dataType == "integer") return new Integer();
    else if (dataType.rfind("varchar(", 0) == 0 && dataType.back() == ')') {
        int size = std::stoi(dataType.substr(8, dataType.size() - 9));
        auto _varchar = new Varchar();
        _varchar->setMaxLength(size);

        return _varchar;
    }
    else if (dataType.rfind("char(", 0) == 0 && dataType.back() == ')') {
        int size = std::stoi(dataType.substr(5, dataType.size() - 6));
        auto _char = new Char();
        _char->setMaxLength(size);

        return _char;
    }
    return nullptr;
}

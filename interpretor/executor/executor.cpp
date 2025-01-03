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
#include "../../ui/ui.h"

std::vector<Schema*> schemas;
std::vector<Relation*> relations;
std::unordered_map<std::string, std::vector<std::string>> relationPKMap;

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
        else if (opCode == "show") index = executeShow(index, codeLines);
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
    updateRID(relationName, getRID(relationName));
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

    relationPKMap[relationName] = getRelationPK(relation);
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

int executeAddRelation(int index, const std::vector<std::string> &codeLines) {
    auto tokens = split(codeLines[index], ":");
    std::string relation = tokens[1];
    std::string entry = std::to_string(getRID(relation)) + ",";
    int PKIndex = getRelationPKIndex(getRelation(relation));
    index++;

    int currentIndex = 1;
    tokens = split(codeLines[index], ":");

    while (tokens[0] == "addArgument") {
        std::string value = tokens[1];

        if (currentIndex == PKIndex) {
            if (std::find(relationPKMap[relation].begin(), relationPKMap[relation].end(), value) != relationPKMap[relation].end()) {
                std::cout << "Warning: Duplicate primary key detected: " << value << std::endl;

                while (tokens[0] == "addArgument"){
                    index++;
                    tokens = split(codeLines[index], ":");
                }

                return index;
            }
            relationPKMap[relation].push_back(value);
        }
        entry += (split(codeLines[index + 1], ":")[0] == "addArgument") ? value + "," : value;

        index++;
        tokens = split(codeLines[index], ":");
        currentIndex++;
    }

    std::string filePath = "DB/" + getSchemaFromRelation(getRelation(relation))->getName() + "/" + relation;
    writeLine(filePath, entry);
    updateRID(relation, getRID(relation) + 1);

    return index;
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

int executeShow(int index, const std::vector<std::string> &codeLines){
    auto tokens = split(codeLines[index], ":");
    std::string filePath = "DB/" + getSchemaFromRelation(getRelation(tokens[1]))->getName() + "/" + tokens[1];
    showRelation(filePath, tokens[1]);

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

int getRID(const std::string &relationName){
    std::string filePath = "DB/" + getSchemaFromRelation(getRelation(relationName))->getName()
                           + "/currentRID";
    std::vector<std::string> lines = readLines(filePath);

    for (auto const &line : lines){
        if (split(line, ":")[0] == relationName) return std::stoi(split(line, ":")[1]);
    }
    return -1;
}

void updateRID(const std::string &relationName, int newRID){
    std::string filePath = "DB/" + getSchemaFromRelation(getRelation(relationName))->getName()
                           + "/currentRID";
    std::vector<std::string> lines = readLines(filePath);

    bool found = false;
    for (int index = 0 ; index < lines.size() ; index++){
        if (split(lines[index], ":")[0] == relationName){
            std::string newLine = relationName + ":" + std::to_string(newRID);
            lines[index] = newLine;
            found = true;
            break;
        }
    }

    if (!found) lines.push_back(relationName + ":0");
    writeLines(filePath, lines);
}

int getRelationPKIndex(Relation *relation){
    for (int index = 1 ; index <= relation->getAttributeNumber() ; index++){
        if (relation->getAttribute(index)->getConstraint() == "PK") return index;
    }

    return -1;
}

std::vector<std::string> getRelationPK(Relation *relation){
    int indexPK = getRelationPKIndex(relation);
    std::vector<std::string> pks;

    std::string filePath = "DB/" + getSchemaFromRelation(getRelation(relation->getName()))->getName() + "/" + relation->getName();
    if (!validFile(filePath)) return {};
    std::vector<std::string> lines = readLines(filePath);

    for (const auto &line : lines){
        auto tokens = split(line, ",");
        pks.push_back(tokens[indexPK]);
    }
    return pks;
}

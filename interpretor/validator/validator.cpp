#include <string>
#include <vector>
#include <unordered_map>
#include <regex>
#include <iostream>

#include "validator.h"
#include "../../utils/algorithms/algorithms.h"

bool isSchema(const std::string &schema, const std::vector<std::string> &codeLines){
    std::vector<std::string> schemas = getSchemas(codeLines);

    for (const std::string &currentSchema : schemas) {
        if (currentSchema == schema) return true;
    }

    return false;
}

bool isRelation(const std::string &relation, const std::vector<std::string> &codeLines){
    std::vector<std::string> relations = getRelations(codeLines);

    for (const std::string &currentSchema : relations) {
        if (currentSchema == relation) return true;
    }

    return false;
}

bool isAttribute(const std::string &attribute, const std::vector<std::string> &attributes){
    auto it = attributes.begin();
    while (it != attributes.end()){
        if (*it == attribute) return true;
        it++;
    }

    return false;

}

bool isKeyword(const std::string &keyword){
    std::regex keywordsRegex(R"(^\s*(schema|relation|varchar|int|date|boolean|PK|FK|nullable|char|datetime|using|nullable|not null|NULLABLE|NOT NULL))");

    return std::regex_search(keyword, keywordsRegex);
}

bool isDataType(const std::string &dataType){
    if (dataType == "int" || dataType == "boolean" ||
        dataType == "date" || dataType == "datetime" ||
        dataType == "uuid" || dataType == "UUID") return true;

    return false;
}

bool isConstraint(const std::string &constraint){
    if (constraint == "NULLABLE" || constraint == "NOT NULL" ||
        constraint == "PK" || constraint == "FK") return true;

    return false;
}

bool isMethod(const std::string &method){
    if (method == "add" || method == "delete"
        || method == "fetch" || method == "update") return true;

    return false;
}

bool isParameterDataType(const std::string &dataType){
    if (dataType == "varchar" || dataType == "char") return true;

    return false;
}

std::vector<std::string> getSchemas(const std::vector<std::string> &codeLines) {
    std::vector<std::string> schemas;
    auto it = codeLines.begin();

    while (it != codeLines.end()) {
        auto tokens = split(*it, ";");
        if (tokens[0] == "Keyword" && tokens[1] == "schema") {
            it++;
            if (it != codeLines.end() && split(*it, ";")[0] == "Separator" && split(*it, ";")[1] == ":") {
                it++;
                if (it != codeLines.end() && split(*it, ";")[0] == "Identifier") schemas.push_back(split(*it, ";")[1]);
            }
        }
        else it++;
    }

    return schemas;
}

std::vector<std::string> getRelations(const std::vector<std::string> &codeLines){
    std::vector<std::string> relations;
    auto it = codeLines.begin();

    while (it != codeLines.end() - 1) {
        auto tokens = split(*it, ";");

        if ((tokens[0] == "Keyword" && tokens[1] == "relation")) {
            it++;
            if (it != codeLines.end() && split(*it, ";")[0] == "Separator" && split(*it, ";")[1] == ":") {
                it++;
                if (it != codeLines.end() && split(*it, ";")[0] == "Identifier" && split(*(std::next(it)), ";")[1] != "->") relations.push_back(split(*it, ";")[1]);
            }
        }
        else it++;
    }

    return relations;
}

std::unordered_map<std::string, std::string> getRelationSchema(const std::vector<std::string> &codeLines){
    std::unordered_map<std::string, std::string> relationSchemaMap;
    std::string usedSchema = "NULL"; //TODO try to find another way to initialise usedSchema
    auto it = codeLines.begin();

    while (it != codeLines.end()) {
        auto tokens = split(*it, ";");

        if (tokens[0] == "Keyword" && tokens[1] == "using"){
            it++;
            if (it != codeLines.end() && split(*it, ";")[0] == "Separator" && split(*it, ";")[1] == ":") {
                it++;
                if (it != codeLines.end() && split(*it, ";")[0] == "Identifier") usedSchema = split(*it, ";")[1];
            }
        }
        else if (tokens[0] == "Keyword" && tokens[1] == "relation"){
            it++;
            if (it != codeLines.end() && split(*it, ";")[0] == "Separator" && split(*it, ";")[1] == ":") {
                it++;
                if (it != codeLines.end() && split(*it, ";")[0] == "Identifier") relationSchemaMap.insert(make_pair(split(*it, ";")[1], usedSchema));
            }
        }
        else it++;
    }

    return relationSchemaMap;
}

std::vector<std::string> getRelationDataTypes(const std::string &relation, const std::vector<std::string> &codeLines){
    std::vector<std::string> dataTypes;

    auto it = codeLines.begin();
    while (it != codeLines.end()){
        if (split(*it, ";")[0] == "Identifier" && split(*it, ";")[1] == relation
            && split(*(it + 1), ";")[1] == "->"){
            it++;
            auto tokens = split(*it, ";");
            while (tokens[1] != "}"){
                if (tokens[0] == "Keyword" && isDataType(tokens[1])){
                    dataTypes.push_back(tokens[1]);
                    it++;
                }
                else if (tokens[0] == "Keyword" && isParameterDataType(tokens[1])){
                    std::string attr;
                    while (tokens[1] != ")"){
                        attr += tokens[1];
                        it++;
                        tokens = split(*it, ";");
                    }
                    dataTypes.push_back(attr + ")");
                }
                else it++;
                tokens = split(*it, ";");
            }
            if (!dataTypes.empty()) return dataTypes;
        }
        it++;
    }
    return dataTypes;
}

std::vector<std::string> getRelationAttributes(const std::string &relation, const std::vector<std::string> &codeLines) {
    std::vector<std::string> attributes;

    for (auto it = codeLines.begin(); it != codeLines.end(); ++it) {
        auto tokens = split(*it, ";");
        if (tokens[0] == "Identifier" && tokens[1] == relation) {
            auto nextIt = std::next(it);
            if (nextIt != codeLines.end()) {
                auto nextTokens = split(*nextIt, ";");
                if (nextTokens[1] == "->") {
                    nextIt++;
                    while (nextIt != codeLines.end()) {
                        auto attrTokens = split(*nextIt, ";");
                        if (attrTokens[1] == "}") {
                            break;
                        }
                        if (attrTokens[0] == "Identifier") {
                            attributes.push_back(attrTokens[1]);
                        }
                        nextIt++;
                    }
                }
            }
        }
    }

    return attributes;
}

bool schemaAlreadyExists(const std::string &schema, const std::vector<std::string> &codeLines) {
    std::vector<std::string> schemas = getSchemas(codeLines);
    int count = 0;

    for (const std::string &currentSchema : schemas) {
        if (currentSchema == schema) {
            count++;
            if (count >= 2) return true;
        }
    }

    return false;
}

bool schemaExists(const std::string &schema, const std::vector<std::string> &codeLines){
    std::vector<std::string> schemas = getSchemas(codeLines);

    for (const std::string &currentSchema : schemas) {
        if (currentSchema == schema) return true;
    }

    return false;
}

bool relationExists(const std::string &relation, const std::vector<std::string> &codeLines) {
    std::vector<std::string> relations = getRelations(codeLines);
    int count = 0;

    for (const std::string &currentRelation : relations) {
        if (currentRelation == relation) {
            count++;
            if (count >= 2) return true;
        }
    }

    return false;
}

bool isExpression(const std::string &relation, const std::vector<std::string> &expressionTokens,
                  const std::unordered_map<std::string, std::string> &dataTypes){
    auto it = expressionTokens.begin();
    bool inExpression = false;

    while (it != expressionTokens.end()){
        auto tokens = split(*it, ";");
        if (tokens[0] == "Separator" && tokens[1] == "("){
            if (inExpression) return false;
            inExpression = true;
        }
        else if (tokens[0] == "Separator" && tokens[1] == ")"){
            if (!inExpression) return false;
            inExpression = false;
        }
        else if (tokens[0] == "Separator" && tokens[1] == "=="){
            if (it == expressionTokens.begin() || (it + 1) == expressionTokens.end()) {
                return false;
            }

            auto prevTokens = split(*(it - 1), ";");
            auto nextTokens = split(*(it + 1), ";");

            if (prevTokens[0] != "Identifier") return false;

            auto itDataType = dataTypes.find(prevTokens[1]);
            if (itDataType == dataTypes.end()) return false;

            std::string attributeType = itDataType->second;

            if (nextTokens[0] == "Constant") {
                if (attributeType == "int" && !isNumber(nextTokens[1])) return false;
            }
            else if (nextTokens[0] == "Identifier") {
                auto nextDataTypeIt = dataTypes.find(nextTokens[1]);
                if (nextDataTypeIt == dataTypes.end()) return false;

                std::string nextAttributeType = nextDataTypeIt->second;
                if (attributeType != nextAttributeType) return false;
            }
            else {
                return false;
            }
        }
        else if (tokens[0] == "Separator" && tokens[1] == "+"){

        }
        else if (tokens[0] == "Separator" && tokens[1] == "-"){

        }
        else if (tokens[0] == "Identifier"){

        }
        else {
            return false;
        }

        it++;
    }
    return true;
}


#include <string>
#include <vector>
#include <unordered_map>
#include <regex>

#include "validator.h"
#include "../../utils/algorithms/algorithms.h"
#include "../../utils/data_structures/AST/AST.h"
#include <iostream>

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
        || method == "fetch" || method == "update"
        || method == "addf") return true;

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

std::vector<std::string> getArrays(const std::vector<std::string> &codeLines){
    std::vector<std::string> arrays;
    auto it = codeLines.begin();

    while (it != codeLines.end() - 1){
        auto tokens = split(*it, ";");

        if ((tokens[0] == "Keyword" && tokens[1] == "let")) {
            it++;
            if (it != codeLines.end() && split(*it, ";")[0] == "Identifier") arrays.push_back(split(*it, ";")[1]);
        }
        else it++;
    }

    return arrays;
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

bool arrayAlreadyExists(const std::string &array, const std::vector<std::string> &codeLines){
    std::vector<std::string> arrays = getArrays(codeLines);
    int count = 0;

    for (const std::string &currentArray : arrays) {
        if (currentArray == array) {
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

    for (const std::string &currentRelation: relations) {
        if (currentRelation == relation) {
            count++;
            if (count >= 2) return true;
        }
    }

    return false;
}

bool isOperator(const std::string &op){
    if (op == "==" || op == ">" || op == "<" || op == ">=" || op == "<="
        || op == "and" || op == "or" || op == "!=" || op == "=") return true;
    return false;
}

bool isExpressionValid(const std::vector<std::string>& expressionTokens,
                       const std::unordered_map<std::string, std::string>& dataTypes) {
    std::vector<std::string> attributes;
    attributes.reserve(dataTypes.size());

    for (const auto& [key, value] : dataTypes) {
        attributes.push_back(key);
    }

    auto *expressionTree = new AST();
    for (const auto &token : expressionTokens){
        auto tokens = split(token, ";");

        if (tokens[0] == "Separator" && tokens[1] == "("){
            if (expressionTree->getCurrentNode() == "Operator") return false;
            expressionTree->createChildren();
            expressionTree->insertInCurrentNode("Operator");
            expressionTree->goLeft();
        }
        else if (tokens[0] == "Separator" && tokens[1] == ")"){
            expressionTree->goUp();
        }
        else if (tokens[0] == "Identifier"){
            if (!isAttribute(tokens[1], attributes)) return false;
            expressionTree->insertInCurrentNode(tokens[1] + ";" + getKeyValue(dataTypes, tokens[1]));
            expressionTree->goUp();
        }
        else if (tokens[0] == "Separator" && isOperator(tokens[1])){
            if (isOperator(expressionTree->getCurrentNode())) return false;
            expressionTree->insertInCurrentNode(tokens[1]);

            if (expressionTree->rightNodeIsNull()) expressionTree->goRight();
            else {
                //TODO Check if the separator is valid between the children
            }
        }
        else if (tokens[0] == "Constant"){
            expressionTree->insertInCurrentNode(tokens[1]);
            expressionTree->goUp();
        }
        else return false;
    }

    if (expressionTree->isEnded()) return true;
    return false;
}

bool isStatementValid(const std::vector<std::string> &statementTokens){
    for (auto const &token : statementTokens){
        auto tokens = split(token, ";");
        if (tokens[0] == "Separator" && (tokens[1] == "(" || tokens[1] == ")")) continue;
        if (tokens[0] == "Separator" && (tokens[1] != "=" && tokens[1] != "and")) return false;
        else if (tokens[0] == "Separator" && tokens[1] == "or") return false;
    }

    return true;
}
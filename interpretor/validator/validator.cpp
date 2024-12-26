#include <string>
#include <vector>
#include <unordered_map>

#include "validator.h"
#include "../../utils/algorithms/algorithms.h"

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
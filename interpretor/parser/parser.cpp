#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

#include "parser.h"
#include "../../utils/algorithms/algorithms.h"
#include "../validator/validator.h"

std::vector<std::string> warnings;
std::vector<std::string> errors;

bool parseCode(const std::vector<std::string> &codeLines){
    for (int index = 0 ; index < codeLines.size() ; index++){
        std::vector<std::string> tokens = split(codeLines[index], ";");
        if (tokens.size() != 2) return false;

        if (tokens[0] == "Keyword" && tokens[1] == "schema"){
            if (!parseSchema(index + 1, codeLines)) {
                showMessages();
                return false;
            }
        }
        else if (tokens[0] == "Identifier" && (split(codeLines[index + 1], ";")[0] == "Separator") && (split(codeLines[index + 1], ";")[1] == "->")) {
            showMessages();
            if (!parseRelationAttributes(index, codeLines)) {
                showMessages();
                return false;
            }
        }
        else if (tokens[0] == "Keyword" && tokens[1] == "relation"){
            showMessages();
            if (!parseRelation(index, codeLines)) {
                showMessages();
                return false;
            }
        }
    }

    std::cout << "Build successful!";
    return true;
}

bool parseSchema(int index, const std::vector<std::string> &codeLines){
    std::vector<std::string> tokens = split(codeLines[index], ";");
    if (tokens.size() != 2) return false;
    if (tokens[0] != "Separator" || tokens[1] != ":") {
        errors.push_back("Syntax error at line " + std::to_string(index) + "! Expected ':' separator!");
        return false;
    }
    index++;

    tokens = split(codeLines[index], ";");
    if (tokens.size() != 2) return false;
    if (tokens[0] != "Identifier" || schemaExists(tokens[1], codeLines)) {
        errors.push_back("Syntax error at line " + std::to_string(index) + "! Schema '" + tokens[1] + "' was already declared!");
        return false;
    }

    return true;
}

bool parseRelation(int index, const std::vector<std::string> &codeLines){
    std::unordered_map<std::string, std::string> relationSchema = getRelationSchema(codeLines);

    std::vector<std::string> tokens = split(codeLines[index], ";");
    if (tokens.size() != 2) return false;
    if (relationSchema[tokens[1]] == "NULL") {
        errors.push_back("Syntax error at line " + std::to_string(index) + "! Relation '" + tokens[1] + "' does not belong to any schema!");
        return false;
    }
    index++;

    tokens = split(codeLines[index], ";");
    if (tokens[0] != "Separator" || tokens[1] != ":") {
        errors.push_back("Syntax error at line " + std::to_string(index) + "! Expected ':' separator!");
        return false;
    }
    index++;

    tokens = split(codeLines[index], ";");
    if (tokens.size() != 2) return false;
    if (tokens[0] != "Identifier" || relationExists(tokens[1], codeLines)) {
            errors.push_back("Syntax error at line " + std::to_string(index) + "! Relation '" + tokens[1] + "' was already declared!");
        return false;
    }

    return true;
}

bool parseAttribute(int index, const std::vector<std::string>& codeLines) {
    auto tokens = split(codeLines[index], ";");

    if (tokens[0] != "Identifier") {
        errors.push_back("Syntax error at line " + std::to_string(index) + "! Expected an attribute name.");
        return false;
    }

    std::string attributeName = tokens[1];
    index++;

    tokens = split(codeLines[index], ";");
    if (tokens[0] != "Separator" || tokens[1] != ",") {
        errors.push_back("Syntax error at line " + std::to_string(index) + "! Expected ',' between declarations.");
        return false;
    }
    index++;

    tokens = split(codeLines[index], ";");
    std::string dataType = tokens[1];

    if (dataType == "varchar"){
        index++;

        tokens = split(codeLines[index], ";");
        if (tokens[0] != "Separator" || tokens[1] != "("){
            errors.push_back("Syntax error at line " + std::to_string(index) + "! Expected '(' after varchar datatype!");
            return false;
        }
        index++;

        tokens = split(codeLines[index], ";");
        if (tokens[0] != "Constant" || !is_number(tokens[1])){
            errors.push_back("Syntax error at line " + std::to_string(index) + "! Size of varchar must be a positive integer!");
            return false;
        }
        index++;

        tokens = split(codeLines[index], ";");
        if (tokens[0] != "Separator" || tokens[1] != ")"){
            errors.push_back("Syntax error at line " + std::to_string(index) + "! Expected ')' to match '('!");
            return false;
        }
        index++;
    }
    else{
        if (tokens[0] != "Keyword" || (tokens[1] != "int" && tokens[1] != "boolean" && tokens[1] != "date" && tokens[1] != "datetime")){
            errors.push_back("Syntax error at line " + std::to_string(index) + "! " + tokens[1] + " is not a valid datatype!");
            return false;
        }
        index++;
    }

    tokens = split(codeLines[index], ";");
    if (tokens[0] != "Separator" || tokens[1] != ","){
        errors.push_back("Syntax error at line " + std::to_string(index) + "! Expected ',' between declarations.");
        return false;
    }
    index++;

    tokens = split(codeLines[index], ";");
    if (tokens[0] != "Keyword" || (tokens[1] != "NULLABLE" && tokens[1] != "NOT NULL" && tokens[1] != "PK" && tokens[1] != "FK")){
        errors.push_back("Syntax error at line " + std::to_string(index) + "! " + tokens[1] + " is not a valid constraint!");
        return false;
    }

    return true;
}

bool parseRelationAttributes(int index, const std::vector<std::string>& codeLines) {
    auto tokens = split(codeLines[index], ";");
    if (!isRelation(tokens[1], codeLines)) {
        errors.push_back("Syntax error at line " + std::to_string(index) +
                         "! Relation '" + tokens[1] + "' was not declared!");
        return false;
    }
    index += 2;

    tokens = split(codeLines[index], ";");
    if (tokens[0] != "Separator" || tokens[1] != "{") {
        errors.push_back("Syntax error at line " + std::to_string(index) +
                         "! Expected '{' after relation declaration!");
        return false;
    }
    index++;

    while (index < codeLines.size()) {
        if (!parseAttribute(index, codeLines)) return false;
        index++;

        while (split(codeLines[index], ";")[0] != "Identifier") index++;
        tokens = split(codeLines[index - 1], ";");
        if (tokens[0] == "Separator" && tokens[1] == "}") {
            break;
        }
    }

    if (tokens[0] != "Separator" || tokens[1] != "}") {
        errors.push_back("Syntax error at line " + std::to_string(index) +
                         "! Expected '}' after relation attributes!");
        return false;
    }

    return true;
}

void showMessages(){
    if (!errors.empty()){
        std::cout << std::to_string(errors.size()) + " error(s) generated." << std::endl;
        for (const std::string &error : errors){
            std::cout << error << std::endl;
        }
    }

    if (!warnings.empty()){
        std::cout << std::to_string(warnings.size()) + " warning(s) generated." << std::endl;
        for (const std::string &warning : warnings){
            std::cout << warning << std::endl;
        }
    }
}

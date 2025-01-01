#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <unordered_set>

#include "parser.h"
#include "../../utils/algorithms/algorithms.h"
#include "../validator/validator.h"

std::unordered_set<unsigned long> errorLines;
std::unordered_set<unsigned long> warningLines;

std::unordered_set<std::string> createdRelations;
std::unordered_set<std::string> usedRelations;

std::unordered_set<std::string> createdArrays;
std::unordered_set<std::string> usedArrays;

std::vector<std::string> warnings;
std::vector<std::string> errors;

void logError(const std::string& errorMessage, unsigned long lineNumber) {
    if (errorLines.find(lineNumber) == errorLines.end()) {
        errors.push_back(errorMessage);
        errorLines.insert(lineNumber);
    }
}

void logWarning(const std::string& warningMessage) {
    warnings.push_back(warningMessage);
}

int parseCode(const std::vector<std::string>& codeLines) {
    int index = 0;

    while (index < codeLines.size() && index != -1) {
        if (errorLines.find(index) != errorLines.end()) {
            index++;
            continue;
        }

        std::vector<std::string> tokens = split(codeLines[index], ";");

        if (tokens[0] == "Keyword" && tokens[1] == "schema") {
            index = parseSchema(index + 1, codeLines);
        }
        else if (tokens[0] == "Keyword" && tokens[1] == "using") {
            index = parseUsing(index + 1, codeLines);
        }
        else if (tokens[0] == "Keyword" && tokens[1] == "relation") {
            index = parseRelation(index + 1, codeLines);
        }
        else if (tokens[0] == "Keyword" && tokens[1] == "let"){
            index = parseLet(index + 1, codeLines);
        }
        else if (tokens[0] == "Identifier" &&
                (split(codeLines[index + 1], ";")[0] == "Separator") &&
                (split(codeLines[index + 1], ";")[1] == ".")) {
            index = parseMethod(index, codeLines);
        }
        else if (tokens[0] == "Identifier" &&
                 (split(codeLines[index + 1], ";")[0] == "Separator") &&
                 (split(codeLines[index + 1], ";")[1] == "->")) {
            index = parseRelationAttributes(index, codeLines);
        }
        else {
            logError("Syntax error at line " + tokens[2] +
                     "! Could not find keyword '" + tokens[1] + "'!", index);
            index++;
        }
    }
    getWarnings();

    if (!errors.empty()) {
        std::cout << "Build failed!" << std::endl;
        showMessages();
        return false;
    }

    if (!warnings.empty()) showMessages();
    std::cout << "Build successful!" << std::endl;
    return true;
}

int parseSchema(int index, const std::vector<std::string>& codeLines) {
    std::vector<std::string> tokens = split(codeLines[index], ";");

    if (tokens[0] != "Separator" || tokens[1] != ":") {
        logError("Syntax error at line " + tokens[2] + "! Expected ':' separator!", index);
        return -1;
    }
    index++;

    tokens = split(codeLines[index], ";");
    if (tokens[0] != "Identifier" || schemaAlreadyExists(tokens[1], codeLines)) {
        logError("Syntax error at line " + tokens[2] +
                         "! Schema '" + tokens[1] + "' was already declared!", index);
        return -1;
    }

    return index + 1;
}

int parseRelation(int index, const std::vector<std::string>& codeLines) {
    std::unordered_map<std::string, std::string> relationSchema = getRelationSchema(codeLines);

    std::vector<std::string> tokens = split(codeLines[index], ";");
    if (tokens[0] != "Separator" || tokens[1] != ":") {
        logError("Syntax error at line " + tokens[2] + "! Expected ':' separator!", index);
        return -1;
    }
    index++;

    tokens = split(codeLines[index], ";");
    auto it = relationSchema.find(tokens[1]);
    if (it == relationSchema.end() || it->second == "NULL") {
        logError("Syntax error at line " + tokens[2] +
                 "! Relation '" + tokens[1] + "' does not belong to any schema!", index);
        return -1;
    }

    createdRelations.insert(tokens[1]);
    return index + 1;
}

int parseRelationAttributes(int index, const std::vector<std::string>& codeLines) {
    auto tokens = split(codeLines[index], ";");
    if (!isRelation(tokens[1], codeLines)) {
        logError("Syntax error at line " + tokens[2] + "! Relation '" + tokens[1] + "' was not declared.", index);
        return index + 1;
    }
    index += 2;

    tokens = split(codeLines[index], ";");
    if (tokens[0] != "Separator" || tokens[1] != "{") {
        logError("Syntax error at line " + tokens[2] + "! Expected '{' after relation declaration.", index);
        return index + 1;
    }
    index++;

    while (index < codeLines.size()) {
        tokens = split(codeLines[index], ";");

        if (tokens[0] == "Separator" && tokens[1] == "}") {
            return index + 1;
        }

        int nextIndex = parseAttribute(index, codeLines);
        if (nextIndex <= index) {
            logError("Stuck parsing attributes at line " + tokens[2] + ".", index);
            return index + 1;
        }

        index = nextIndex;
    }

    logError("Syntax error at line " + tokens[2] + "! Expected '}' after relation attributes.", index);
    return index + 1;
}

int parseUsing(int index, const std::vector<std::string>& codeLines) {
    auto tokens = split(codeLines[index], ";");
    if (tokens[0] != "Separator" || tokens[1] != ":") {
        logError("Syntax error at line " + tokens[2] + "! Expected ':' separator after 'using' keyword!", index);
        return -1;
    }
    index++;

    tokens = split(codeLines[index], ";");
    if (tokens[0] != "Identifier" || !schemaExists(tokens[1], codeLines)) {
        logError("Syntax error at line " + tokens[2] +
                         "! Schema '" + tokens[1] + "' was not declared!", index);
        return -1;
    }

    return index + 1;
}

int parseAttribute(int index, const std::vector<std::string>& codeLines) {
    auto tokens = split(codeLines[index], ";");
    if (tokens[0] != "Identifier") {
        logError("Syntax error at line " + tokens[2] + "! Expected an attribute name.", index);
        while (tokens[0] != "Identifier"){
            index++;
            tokens = split(codeLines[index], ";");
        }
    }
    std::string attributeName = tokens[1];
    index++;

    tokens = split(codeLines[index], ";");
    if (tokens[0] != "Separator" || tokens[1] != ",") {
        logError("Syntax error at line " + tokens[2] + "! Expected ',' after attribute name.", index);
        return index + 1;
    }
    index++;

    tokens = split(codeLines[index], ";");
    std::string dataType = tokens[1];

    if (dataType == "varchar" || dataType == "char") {
        index++;
        tokens = split(codeLines[index], ";");
        if (tokens[0] != "Separator" || tokens[1] != "(") {
            logError("Syntax error at line " + tokens[2] + "! Expected '(' after varchar datatype.", index);
            return index + 1;
        }
        index++;

        tokens = split(codeLines[index], ";");
        if (tokens[0] != "Constant" || !isNumber(tokens[1])) {
            logError("Syntax error at line " + tokens[2] + "! Size of varchar must be a positive integer.", index);
            return index + 1;
        }
        index++;

        tokens = split(codeLines[index], ";");
        if (tokens[0] != "Separator" || tokens[1] != ")") {
            logError("Syntax error at line " + tokens[2] + "! Expected ')' to match '('.", index);
            return index + 1;
        }
        index++;
    }
    else {
        if (tokens[0] != "Keyword" || (!isDataType(tokens[1]))) {
            logError("Syntax error at line " + tokens[2] + "! " + tokens[1] + " is not a valid datatype.", index);
            return index + 1;
        }
        index++;
    }

    tokens = split(codeLines[index], ";");
    if (tokens[0] != "Separator" || tokens[1] != ",") {
        logError("Syntax error at line " + tokens[2] + "! Expected ',' after datatype.", index);
        return index + 1;
    }
    index++;

    tokens = split(codeLines[index], ";");
    if (tokens[0] != "Keyword" || (!isConstraint(tokens[1]))) {
        logError("Syntax error at line " + tokens[2] + "! " + tokens[1] + " is not a valid constraint.", index);
        return index + 1;
    }
    index++;

    return index;
}

int parseLet(int index, const std::vector<std::string> &codeLines){
    auto tokens = split(codeLines[index], ";");

    if (tokens[0] != "Identifier" || arrayAlreadyExists(tokens[1], codeLines)){
        logError("Syntax error at line " + tokens[2] + "! " + tokens[1] + " has already been declared!", index);
        return -1;
    }
    createdArrays.insert(tokens[1]);
    index++;

    tokens = split(codeLines[index], ";");
    if (tokens[0] != "Separator" || tokens[1] != "="){
        logError("Syntax error at line " + tokens[2] + "! Expected '=' after array declaration!", index);
        return -1;
    }
    index++;

    return parseMethod(index, codeLines);
}

int parseMethod(int index, const std::vector<std::string> &codeLines){
    auto tokens = split(codeLines[index], ";");
    std::string relation = tokens[1];
    if (!isRelation(tokens[1], codeLines)){
        logError("Syntax error at line " + tokens[2] + "! " + tokens[1] + " is not a valid relation!", index);
        return -1;
    }
    usedRelations.insert(tokens[1]);
    index += 2;

    tokens = split(codeLines[index], ";");
    std::string method = tokens[1];
    if (tokens[0] != "Method" || !isMethod(tokens[1])){
        logError("Syntax error at line " + tokens[2] + "! "
        + tokens[1] + " is not a valid method to call within a relation!", index);
    }
    index++;

    if (method == "add") return parseAdd(index, relation, codeLines);
    else if (method == "update") return parseUpdate(index, relation, codeLines);
    else if (method == "fetch") return parseFetch(index, relation, codeLines);

    return -1;
}

void validConstantDataTypes(int index, const std::string &argumentType, const std::vector<std::string> &tokens){
    if (argumentType == "UUID"){
        if (!isUUID(tokens[1])) {
            logError("Syntax error at line " + tokens[2] + "! Expected type 'UUID' for argument.", index);
        }
    }
    if (argumentType == "int") {
        if (!isNumber(tokens[1])) {
            logError("Syntax error at line " + tokens[2] + "! Expected type 'int' for argument.", index);
        }
    }
}

void validIdentifierDataTypes(int index, const std::string &argumentType, const std::vector<std::string> &tokens){
    if (argumentType == "UUID"){
        if (!isUUID(tokens[1])) {
            logError("Syntax error at line " + tokens[2] + "! Expected type 'UUID' for argument.", index);
        }
    }
    if (argumentType == "boolean") {
        if (!isBoolean(tokens[1])) {
            logError("Syntax error at line " + tokens[2] + "! Expected type 'boolean' for argument.", index);
        }
    }
    else if (argumentType == "date") {
        if (!isDate(tokens[1])) {
            logError("Syntax error at line " + tokens[2] + "! Expected type 'date' for argument.", index);
        }
    }
    else if (argumentType == "datetime") {
        if (!isDateTime(tokens[1])) {
            logError("Syntax error at line " + tokens[2] + "! Expected type 'datetime' for argument.", index);
        }
    }
    else if (argumentType.find("char(") == 0) {
        unsigned long startIndex = argumentType.find('(');
        unsigned long endIndex = argumentType.find(')');
        if (startIndex != std::string::npos && endIndex != std::string::npos && endIndex > startIndex) {
            int size = std::stoi(argumentType.substr(startIndex + 1, endIndex - startIndex - 1));
            if (!isChar(tokens[1], size)) {
                logError("Syntax error at line " + tokens[2] + "! Expected type 'char(" + std::to_string(size) +
                         ")' for argument.", index);
            }
        }
    }
    else if (argumentType.find("varchar(") == 0) {
        unsigned long startIndex = argumentType.find('(');
        unsigned long endIndex = argumentType.find(')');
        if (startIndex != std::string::npos && endIndex != std::string::npos && endIndex > startIndex) {
            int size = std::stoi(argumentType.substr(startIndex + 1, endIndex - startIndex - 1));
            if (!isVarchar(tokens[1], size)) {
                logError("Syntax error at line " + tokens[2] + "! Expected type 'varchar(" + std::to_string(size) +
                         ")' for argument.", index);
            }
        }
    }
}

int parseArgument(int index, const std::string &argumentType, const std::vector<std::string> &codeLines) {
    auto tokens = split(codeLines[index], ";");

    if (tokens[0] == "Constant") {
        validConstantDataTypes(index, argumentType, tokens);
    }
    else if (tokens[0] == "Identifier") {
        validIdentifierDataTypes(index, argumentType, tokens);
    }
    else logError("Syntax error at line " + tokens[2] + "! Unexpected argument type.", index);

    return index + 1;
}

int parseAdd(int index, const std::string &relation, const std::vector<std::string> &codeLines) {
    auto tokens = split(codeLines[index], ";");
    if (tokens[0] != "Separator" || tokens[1] != "(") {
        logError("Syntax error at line " + tokens[2] + "! Expected '(' after method call!", index);
        return -1;
    }
    index++;

    tokens = split(codeLines[index], ";");
    if (tokens[0] == "Separator" && tokens[1] == ")") {
        logError("Syntax error at line " + tokens[2] + "! No arguments provided to add method!", index);
        return -1;
    }

    std::vector<std::string> attributes = getRelationDataTypes(relation, codeLines);
    int attributeCount = 0;

    while (true) {
        index = parseArgument(index, attributes[attributeCount], codeLines);
        if (index == -1) {
            return -1;
        }

        tokens = split(codeLines[index], ";");
        attributeCount++;

        if (tokens[1] == ")") {
            break;
        }
        else if (tokens[1] != ",") {
            logError("Syntax error at line " + tokens[2] + "! Expected ',' or ')'!", index);
            return -1;
        }
        index++;
    }

    if (attributeCount != attributes.size()) {
        logError("Syntax error! Expected " + std::to_string(attributes.size()) +
                 " arguments but got " + std::to_string(attributeCount) + "!", index);
        return -1;
    }

    return index + 1;
}

int parseUpdate(int index, const std::string &relation, const std::vector<std::string> &codeLines) {
    if (index >= codeLines.size()) {
        logError("Index out of range!", index);
        return -1;
    }

    auto tokens = split(codeLines[index], ";");
    if (tokens[0] != "Separator" || tokens[1] != "(") {
        logError("Syntax error at line " + tokens[2] + "! Expected '(' after method call!", index);
        return -1;
    }
    index++;

    if (index >= codeLines.size()) {
        logError("Syntax error: Unexpected end of input!", index);
        return -1;
    }

    tokens = split(codeLines[index], ";");
    if (tokens[0] == "Separator" && tokens[1] == ")") {
        logError("Syntax error at line " + tokens[2] + "! No arguments provided to method!", index);
        return -1;
    }

    std::vector<std::string> attributes = getRelationAttributes(relation, codeLines);
    while (true) {
        if (index >= codeLines.size()) {
            logError("Syntax error: Missing closing ')'!", index);
            return -1;
        }

        tokens = split(codeLines[index], ";");
        if (tokens[0] == "Identifier" && !isAttribute(tokens[1], attributes)) {
            logError("Syntax error at line " + tokens[2] + "! " + tokens[1] +
                     " is not a valid attribute in " + relation + "!", index);
            return -1;
        }

        if (tokens[1] == ")") {
            break;
        }
        index++;
    }
    index++;

    if (index >= codeLines.size()) {
        logError("Syntax error: Unexpected end of input!", index);
        return -1;
    }

    tokens = split(codeLines[index], ";");
    if (tokens[0] != "Keyword" || tokens[1] != "where"){
        logError("Syntax error at line " + tokens[2] + "! Expected 'where' keyword after update method call!", index);
        return -1;
    }
    index++;

    tokens = split(codeLines[index], ";");
    if (tokens[0] != "Separator" || tokens[1] != "{") {
        logError("Syntax error at line " + tokens[2] + "! Expected '{' after method call!", index);
        return -1;
    }
    index++;

    std::vector<std::string> expressionTokens;
    while (true) {
        if (index >= codeLines.size()) {
            logError("Syntax error: Missing closing '}' in expression!", index);
            return -1;
        }

        tokens = split(codeLines[index], ";");
        if (tokens[1] == "}") {
            break;
        }

        expressionTokens.push_back(codeLines[index]);
        index++;
    }
    index++;

    std::vector<std::string> types = getRelationDataTypes(relation, codeLines);
    std::unordered_map<std::string, std::string> dataTypes;

    if (attributes.size() != types.size()) {
        logError("Mismatch between attributes and data types for relation " + relation, index);
        return -1;
    }

    for (size_t i = 0; i < attributes.size(); i++) {
        dataTypes[attributes[i]] = types[i];
    }

    if (!isExpressionValid(relation, expressionTokens, dataTypes)) {
        logError("Syntax error: Invalid expression inside method call!", index);
        return -1;
    }

    return index;
}

int parseFetch(int index, const std::string& relation, const std::vector<std::string>& codeLines) {
    auto tokens = split(codeLines[index], ";");

    if (tokens[0] != "Separator" || tokens[1] != "(") {
        logError("Syntax error at line " + tokens[2] + "! Expected '(' after method call!", index);
        return -1;
    }
    index++;

    if (index >= codeLines.size()) {
        logError("Syntax error: Unexpected end of input!", index);
        return -1;
    }

    tokens = split(codeLines[index], ";");
    if (tokens[0] == "Separator" && tokens[1] == ")") {
        logError("Syntax error at line " + tokens[2] + "! No arguments provided to fetch method!", index);
        return -1;
    }

    std::vector<std::string> attributes = getRelationAttributes(relation, codeLines);
    bool argumentParsed = false;
    while (true) {
        if (index >= codeLines.size()) {
            logError("Syntax error: Missing closing ')'!", index);
            return -1;
        }

        tokens = split(codeLines[index], ";");
        if (tokens[0] == "Identifier" && !isAttribute(tokens[1], attributes)) {
            logError("Syntax error at line " + tokens[2] + "! " + tokens[1] + " is not a valid attribute in " + relation + "!", index);
            return -1;
        }

        if (tokens[0] == "Identifier") {
            argumentParsed = true;
        }

        if (tokens[1] == ")") {
            break;
        }
        index++;
    }

    if (!argumentParsed) {
        logError("Syntax error at line " + tokens[2] + "! Fetch method expects at least one argument!", index);
        return -1;
    }
    index++;

    tokens = split(codeLines[index], ";");
    if (tokens[0] == "Separator" && tokens[1] == "+") {
        index++;

        tokens = split(codeLines[index], ";");
        if ((tokens[0] != "Constant" && tokens[0] != "Identifier") || tokens[1].empty()) {
            logError("Syntax error at line " + tokens[2] + "! Expected a valid identifier or constant after '+'.", index);
            return -1;
        }
        index = parseConcatenation(index + 1, codeLines);
    }

    while (index < codeLines.size()) {
        tokens = split(codeLines[index], ";");
        if (tokens[0] == "Keyword" && tokens[1] == "where") {
            index = parseWhere(index + 1, relation, codeLines);
        } else if (tokens[0] == "Separator" && tokens[1] == "+") {
            index = parseConcatenation(index + 1, codeLines);
        } else {
            break;
        }
    }

    return index;
}

int parseConcatenation(int index, const std::vector<std::string>& codeLines) {
    auto tokens = split(codeLines[index], ";");

    if (tokens[0] == "Constant") {
        index++;
        tokens = split(codeLines[index], ";");

        if (tokens[0] == "Separator" && tokens[1] == "+") {
            index++;
            tokens = split(codeLines[index], ";");

            if (tokens.empty() || (tokens[0] != "Constant" && tokens[0] != "Identifier")) {
                logError("Syntax error at line " + tokens[2] + "! Expected constant or identifier after '+' operator.", index);
                return -1;
            }
            return parseConcatenation(index, codeLines);
        }
        return index;
    }
    else if (tokens[0] == "Identifier") {
        if (isRelation(tokens[1], codeLines)) {
            std::string relation = tokens[1];
            index++;

            tokens = split(codeLines[index], ";");
            if (tokens[0] != "Separator" || tokens[1] != ".") {
                logError("Syntax error at line " + tokens[2] + "! Expected '.' before method call!", index);
                return -1;
            }
            index++;

            tokens = split(codeLines[index], ";");
            if (tokens[0] != "Method" || tokens[1] != "fetch") {
                logError("Syntax error at line " + tokens[2] + "! Expected fetch method call in concatenation chain!", index);
                return -1;
            }
            index++;

            index = parseFetch(index, relation, codeLines);
            tokens = split(codeLines[index], ";");

            if (tokens[0] == "Separator" && tokens[1] == "+") {
                index++;

                tokens = split(codeLines[index], ";");
                if (tokens.empty() || (tokens[0] != "Constant" && tokens[0] != "Identifier")) {
                    logError("Syntax error at line " + tokens[2] + "! Expected constant or identifier after '+' operator.", index);
                    return -1;
                }
                return parseConcatenation(index, codeLines);
            }
        }
    }
    return index;
}

int parseWhere(int index, const std::string &relation, const std::vector<std::string> &codeLines){

}

void getWarnings(){
    getUnusedRelationsWarnings();
    getUnusedArraysWarning();
}

void getUnusedRelationsWarnings(){
    for (const auto& relation: createdRelations)
        if (!usedRelations.contains(relation)) {
            logWarning("Relation " + relation + " is created but never queried!");
        }
}

void getUnusedArraysWarning(){
    for (const auto& array: createdArrays)
        if (!usedArrays.contains(array)) {
            logWarning("Array " + array + " is created but never queried!");
        }
}

void showMessages() {
    if (!errors.empty()) {
        std::cout << std::to_string(errors.size()) + " error(s) generated." << std::endl;
        for (const std::string& error : errors) {
            std::cout << error << std::endl;
        }
    }

    if (!warnings.empty()) {
        std::cout << std::to_string(warnings.size()) + " warning(s) generated." << std::endl;
        for (const std::string& warning : warnings) {
            std::cout << warning << std::endl;
        }
    }
}
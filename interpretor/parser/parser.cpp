#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <unordered_set>

#include "parser.h"
#include "../../utils/algorithms/algorithms.h"
#include "../validator/validator.h"

std::unordered_set<unsigned long> errorLines;
std::vector<std::string> warnings;
std::vector<std::string> errors;

void logError(const std::string& errorMessage, unsigned long lineNumber) {
    if (errorLines.find(lineNumber) == errorLines.end()) {
        errors.push_back(errorMessage);
        errorLines.insert(lineNumber);
    }
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

    if (!errors.empty()) {
        std::cout << "Build failed!" << std::endl;
        showMessages();
        return false;
    }

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
        logError("Syntax error at line " + std::to_string(index) +
                         "! Schema '" + tokens[1] + "' was already declared!", index);
        return -1;
    }

    return index + 1;
}

int parseUsing(int index, const std::vector<std::string>& codeLines) {
    auto tokens = split(codeLines[index], ";");
    if (tokens[0] != "Separator" || tokens[1] != ":") {
        logError("Syntax error at line " + tokens[2] + "! Expected ':' separator!", index);
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

    if (dataType == "varchar") {
        index++;
        tokens = split(codeLines[index], ";");
        if (tokens[0] != "Separator" || tokens[1] != "(") {
            logError("Syntax error at line " + tokens[2] + "! Expected '(' after varchar datatype.", index);
            return index + 1;
        }
        index++;

        tokens = split(codeLines[index], ";");
        if (tokens[0] != "Constant" || !is_number(tokens[1])) {
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
    } else {
        if (tokens[0] != "Keyword" || (tokens[1] != "int" && tokens[1] != "boolean" &&
                                       tokens[1] != "date" && tokens[1] != "datetime")) {
            logError("Syntax error at line " + tokens[2] + "! " + tokens[1] + " is not a valid datatype.", index);
            return index + 1;
        }
        index++;
    }

    tokens = split(codeLines[index], ";");
    if (tokens[0] != "Separator" || tokens[1] != ",") {
        logError("Syntax error at line " + std::to_string(index) + "! Expected ',' after datatype.", index);
        return index + 1;
    }
    index++;

    tokens = split(codeLines[index], ";");
    if (tokens[0] != "Keyword" || (tokens[1] != "NULLABLE" && tokens[1] != "NOT NULL" &&
                                   tokens[1] != "PK" && tokens[1] != "FK")) {
        logError("Syntax error at line " + std::to_string(index) + "! Expected a valid constraint but found none.", index);
        return index + 1;
    }
    index++;

    return index;
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
            logError("Stuck parsing attributes at line " + std::to_string(index) + ".", index);
            return index + 1;
        }

        index = nextIndex;
    }

    logError("Syntax error at line " + std::to_string(index) + "! Expected '}' after relation attributes.", index);
    return index + 1;
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
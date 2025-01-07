#include <string>
#include <vector>
#include <iostream>
#include <unistd.h>
#include <chrono>
#include <filesystem>

#include "executor.h"
#include "../../utils/algorithms/algorithms.h"
#include "../scanner/scanner.h"
#include "../../io/io.h"
#include "../../domain/datatype/datatypes/boolean/Boolean.h"
#include "../../domain/datatype/datatypes/char/Char.h"
#include "../../domain/datatype/datatypes/date/Date.h"
#include "../../domain/datatype/datatypes/datetime/Datetime.h"
#include "../../domain/datatype/datatypes/integer/Integer.h"
#include "../../domain/datatype/datatypes/varchar/Varchar.h"
#include "../../ui/ui.h"
#include "../../utils/data_structures/BTree/BTree.h"

std::vector<Schema*> schemas;
std::vector<Relation*> relations;

std::unordered_map<std::string, std::vector<std::string>> relationPKMap;
std::unordered_map<Relation*, BTree<std::string>*> relationBTreeMap;
std::unordered_map<Relation*, std::unordered_map<std::string, std::string>> relationPKLineMap;

std::vector<std::string> arrays;
std::unordered_map<std::string, std::unordered_map<size_t, std::vector<std::string>>> arrayElementsMap;

int executeCode(const std::string &filePath) {
    using namespace std::chrono;
    auto start = high_resolution_clock::now();

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
        else if (opCode == "showSchema") index = executeShowSchema(index, codeLines);
        else if (opCode == "showArray") index = executeShowArray(index, codeLines);
        else if (isMethodCall(opCode)) index = executeMethodCall(index, codeLines);
        else index++;
    }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    if (duration.count() > 1000) std::cout << "Code execution time: " << duration.count() / 1000 << "s" << std::endl;
    else std::cout << "Code execution time: " << duration.count() << "ms" << std::endl;

    return index;
}

int executeSchema(int index, const std::vector<std::string> &codeLines){
    auto tokens = split(codeLines[index], ":");
    auto *newSchema = new Schema(tokens[1]);

    schemas.push_back(newSchema);
    newSchema->storeSchema();
    return index + 1;
}

int executeRelation(int index, const std::vector<std::string> &codeLines) {
    auto tokens = split(codeLines[index], ":");
    std::string relationName = split(tokens[1], ",")[1];
    std::string schemaName = split(tokens[1], ",")[0];

    auto *schema = getSchema(schemaName);
    auto *newRelation = new Relation(relationName);
    schema->addRelation(newRelation);

    relations.push_back(newRelation);
    updateRID(relationName, getRID(relationName));
    updateRelationPKLineMap(newRelation, schemaName, relationName);

    return index + 1;
}

int executeRelationAttributes(int index, const std::vector<std::string> &codeLines){
    auto tokens = split(codeLines[index], ":");
    std::string relationName = tokens[1];
    index++;

    Relation *relation = getRelation(relationName);
    if (relationAlreadyDeclared(relation)) {
        relationPKMap[relationName] = getRelationPK(relation);
        buildRelationBTree(relation);

        tokens = split(codeLines[index], ":");
        while (tokens[0] == "createAttribute"){
            index++;
            tokens = split(codeLines[index], ":");
        }
        return index;
    }
    tokens = split(codeLines[index], ":");

    std::string schemaName = getSchemaFromRelation(relation)->getName();
    std::string relationFilePath = "DB/" + schemaName + "/" + "relationAttributes";

    writeLine(relationFilePath, "Relation," + relationName);

    while (tokens[0] == "createAttribute"){
        auto attributeTokens = split(tokens[1], ":");
        std::string attributeName = split(attributeTokens[0], ",")[0];
        std::string attributeDataType = split(attributeTokens[0], ",")[1];
        std::string attributeConstraint = split(attributeTokens[0], ",")[2];

        Datatype *datatype = getDataType(attributeDataType);
        auto *newAttribute = new Attribute(attributeName, datatype, attributeConstraint);
        relation->addAttribute(newAttribute);

        writeLine(relationFilePath, tokens[1]);

        index++;
        tokens = split(codeLines[index], ":");
    }

    relationPKMap[relationName] = getRelationPK(relation);
    relation->storeRelation(getSchemaFromRelation(relation)->getName());

    buildRelationBTree(relation);

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
    else return index + 1;
}

int executeAddRelation(int index, const std::vector<std::string> &codeLines) {
    auto tokens = split(codeLines[index], ":");
    std::string relation = tokens[1];
    std::string entry = std::to_string(getRID(relation)) + ",";
    int PKIndex = getRelationPKIndex(getRelation(relation));
    std::string PK;
    index++;

    int currentIndex = 1;
    tokens = split(codeLines[index], ":");

    while (tokens[0] == "addArgument") {
        std::string value = tokens[1];

        if (currentIndex == PKIndex) {
            if (std::find(relationPKMap[relation].begin(), relationPKMap[relation].end(), value) != relationPKMap[relation].end()) {
                std::cout << "Warning: Duplicate primary key detected: " << value << std::endl;
                addPKLineToRelationMap(getRelation(relation), PK, entry);

                while (tokens[0] == "addArgument"){
                    index++;
                    tokens = split(codeLines[index], ":");
                }

                return index;
            }

            relationPKMap[relation].push_back(value);
            updateRelationBTree(getRelation(relation), value);
            PK = value;
        }
        entry += (split(codeLines[index + 1], ":")[0] == "addArgument") ? value + "," : value;

        index++;
        tokens = split(codeLines[index], ":");
        currentIndex++;
    }

    std::string filePath = "DB/" + getSchemaFromRelation(getRelation(relation))->getName() + "/relations/" + relation;
    writeLine(filePath, entry);
    addPKLineToRelationMap(getRelation(relation), PK, entry);
    updateRID(relation, getRID(relation) + 1);

    return index;
}

int executeUpdateRelation(int index, const std::vector<std::string> &codeLines){
    auto tokens = split(codeLines[index], ":");
    std::string relation = tokens[1];
    index++;

    tokens = split(codeLines[index], ":");
    std::string expression = tokens[1];
    std::vector<std::string> expressionTokens = tokenizeExpression(getRelation(relation), expression);
    index++;

    tokens = split(codeLines[index], ":");
    std::string statement = tokens[1];
    std::vector<std::string> statementTokens = tokenizeExpression(getRelation(relation), statement);

    if (isPKQueried(getRelation(relation), expressionTokens)){
        std::vector<std::string> info = getPKQueryInformation(getRelation(relation), expressionTokens);
        handlePKInfoForUpdate(getRelation(relation), info,
                              getAttributeValueMap(getRelation(relation), statementTokens));
    }
    else{
        std::vector<std::string> validExpressions = getValidExpressions(expressionTokens);
        std::string filePath = "DB/" + getSchemaFromRelation(getRelation(relation))->getName() + "/relations/" + relation;
        updateLinesByNonPK(filePath, getRelation(relation), validExpressions,
                           getAttributeValueMap(getRelation(relation), statementTokens));
    }

    return index;
}

int executeDeleteRelation(int index, const std::vector<std::string> &codeLines){
    auto tokens = split(codeLines[index], ":");
    std::string relation = tokens[1];
    index++;

    tokens = split(codeLines[index], ":");
    std::string expression = tokens[1];
    std::vector<std::string> expressionTokens = tokenizeExpression(getRelation(relation), expression);

    if (isPKQueried(getRelation(relation), expressionTokens)){
        std::vector<std::string> info = getPKQueryInformation(getRelation(relation), expressionTokens);
        handlePKInfoForDelete(getRelation(relation), info);
    }
    else{
        std::vector<std::string> validExpressions = getValidExpressions(expressionTokens);
        std::string filePath = "DB/" + getSchemaFromRelation(getRelation(relation))->getName() + "/relations/" + relation;
        deleteLinesByNonPK(filePath, getRelation(relation), validExpressions);
    }

    return index + 1;
}

int executeArray(int index, const std::vector<std::string>& codeLines) {
    std::string relation;
    auto tokens = split(codeLines[index], ":");
    std::string array = tokens[1];

    arrays.push_back(array);
    arrayElementsMap[array].clear();
    index++;

    int originalIndex = index;
    while (split(codeLines[index], ":")[0] != "where"){
        if (split(codeLines[index], ":")[0] == "fetchRelation")
            relation = split(codeLines[index], ":")[1];

        index++;
        if (codeLines.size() < index) break;
    }

    std::vector<std::string> expressionTokens;
    std::vector<std::string> validExpressions;

    if (split(codeLines[index], ":")[0] == "where"){
        std::string expression = split(codeLines[index], ":")[1];
        expressionTokens = tokenizeExpression(getRelation(relation), expression);
        validExpressions = getValidExpressions(expressionTokens);
    }

    return executeFetchRelation(originalIndex, array, codeLines, validExpressions);
}

int executeFetchRelation(int index, const std::string &array,
                         const std::vector<std::string> &codeLines,
                         const std::vector<std::string> &validExpressions) {
    auto tokens = split(codeLines[index], ":");
    std::string relation;
    bool isConcatenation = false;

    std::unordered_map<size_t, std::vector<std::string>> tempMap;

    while (tokens[0] == "fetchRelation" || tokens[0] == "fetchAttribute" || tokens[0] == "concatenate") {
        if (tokens[0] == "fetchRelation") {
            relation = tokens[1];
            index++;
            tokens = split(codeLines[index], ":");
            continue;
        }

        if (tokens[0] == "concatenate") {
            isConcatenation = true;
            index++;
            tokens = split(codeLines[index], ":");
            continue;
        }

        size_t attributeIndex = 0;
        while (tokens[0] == "fetchAttribute") {
            auto elements = getElementsByAttribute(getRelation(relation), tokens[1], validExpressions);

            if (!isConcatenation) tempMap[attributeIndex] = elements;
            else {
                if (tempMap.find(attributeIndex) != tempMap.end()) {
                    auto &targetVector = tempMap[attributeIndex];
                    std::vector<std::string> concatenatedVector;

                    for (size_t i = 0; i < targetVector.size(); ++i) {
                        concatenatedVector.push_back(targetVector[i] + " " + elements[i]);
                    }
                    tempMap[attributeIndex] = concatenatedVector;
                }
                else tempMap[attributeIndex] = elements;
            }

            attributeIndex++;
            index++;
            tokens = split(codeLines[index], ":");
        }
    }

    for (const auto &[key, vec] : tempMap) {
        if (arrayElementsMap[array].find(key) == arrayElementsMap[array].end()) {
            arrayElementsMap[array][key] = vec;
        }
        else {
            auto &existingVector = arrayElementsMap[array][key];
            for (size_t i = 0; i < vec.size(); ++i) {
                existingVector[i] += " " + vec[i];
            }
        }
    }

    return index;
}

int executeConcatenate(int index, const std::string &array, const std::string &constant) {
    auto &innerMap = arrayElementsMap[array];
    for (auto &[key, vec] : innerMap) {
        vec.push_back(constant);
    }

    return index + 1;
}

int executeShow(int index, const std::vector<std::string> &codeLines){
    auto tokens = split(codeLines[index], ":");
    std::string filePath = "DB/" + getSchemaFromRelation(getRelation(tokens[1]))->getName() + "/relations/" + tokens[1];
    showRelation(filePath, tokens[1]);

    return index + 1;
}

int executeShowSchema(int index, const std::vector<std::string> &codeLines) {
    auto tokens = split(codeLines[index], ":");

    std::string schemaName = tokens[1];
    std::string filePath = "DB/" + schemaName + "/relations/";

    for (const auto &entry : std::filesystem::directory_iterator(filePath)) {
        if (entry.is_regular_file()) {
            std::string fullFilePath = entry.path().string();
            std::string relationName = entry.path().filename().string();

            showRelation(fullFilePath, relationName);
        }
    }
    return index + 1;
}

int executeShowArray(int index, const std::vector<std::string> &codeLines){
    auto tokens = split(codeLines[index], ":");

    std::string array = tokens[1];
    std::unordered_map<size_t, std::vector<std::string>> indexVectorMap = arrayElementsMap[array];

    for (const auto &[mapIndex, vec] : indexVectorMap) {
        std::cout << "Index: " << mapIndex << "\n";
        std::cout << "Vector: [";
        for (size_t i = 0; i < vec.size(); i++) {
            std::cout << vec[i];
            if (i != vec.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "]\n";
    }
    return index + 1;
}

void handlePKInfoForUpdate(Relation* relation, const std::vector<std::string> &info,
                           const std::unordered_map<size_t, std::string> &attributeValueMap){
    std::string op = info[0];
    std::string constant = info[1];
    auto *btree = relationBTreeMap[relation];

    if (op == "==" && btree->search(constant)) {
        std::string line = getPKLineForConstant(relation, constant);
        if (!line.empty()) {
            std::string filePath = "DB/" + getSchemaFromRelation(getRelation(relation->getName()))->getName() + "/relations/" + relation->getName();
            updateLinesByPK(filePath, relation, constant, attributeValueMap);
        }
    }
    else {
        //TODO Handle other cases of expressions.
    }
}

void handlePKInfoForDelete(Relation *relation, const std::vector<std::string> &info) {
    std::string op = info[0];
    std::string constant = info[1];
    auto *btree = relationBTreeMap[relation];

    if (op == "==" && btree->search(constant)) {
        std::string line = getPKLineForConstant(relation, constant);
        if (!line.empty()) {
            std::string filePath = "DB/" + getSchemaFromRelation(getRelation(relation->getName()))->getName() + "/relations/" + relation->getName();
            deleteLine(filePath, line);
            relationPKLineMap[relation].erase(constant);
        }
    }
    else {
        //TODO handle other cases of expressions
    }
}

bool isRelationInSchema(Relation* relation, Schema* schema){
    if (schema->hasRelation(relation)) return true;
    return false;
}

bool isAttributeInRelation(Relation* relation, const std::string &attribute){
    for (int index = 1 ; index <= relation->getAttributeNumber() ; index++){
        if (relation->getAttribute(index)->getName() == attribute) return true;
    }

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

    std::string filePath = "DB/" + getSchemaFromRelation(getRelation(relation->getName()))->getName() + "/relations/" + relation->getName();
    if (!validFile(filePath)) return {};
    std::vector<std::string> lines = readLines(filePath);

    for (size_t index = 1 ; index < lines.size() ; index++){
        auto tokens = split(lines[index], ",");
        pks.push_back(tokens[indexPK]);
    }
    return pks;
}

std::string getRelationPKAttribute(Relation *relation){
    for (int index = 1 ; index <= relation->getAttributeNumber() ; index++){
        if (relation->getAttribute(index)->getConstraint() == "PK") return relation->getAttribute(index)->getName();
    }

    return "Null";
}

std::unordered_map<std::string, std::string> getPKLineMap(Relation *relation){
    int indexPK = getRelationPKIndex(relation);
    std::unordered_map<std::string, std::string> pkLineMap;

    std::string filePath = "DB/" + getSchemaFromRelation(getRelation(relation->getName()))->getName() + "/relations/" + relation->getName();
    if (!validFile(filePath)) return {};
    std::vector<std::string> lines = readLines(filePath);

    for (const auto &line : lines){
        auto tokens = split(line, ",");
        pkLineMap[tokens[indexPK]] = line;
    }

    return pkLineMap;
}

void buildRelationBTree(Relation *relation){
    const long pageSize = sysconf(_SC_PAGESIZE); // UNIX only
    const long overhead = sizeof(BTreeNode<std::string>);
    const long keySize = sizeof(std::string);
    const long pointerSize = sizeof(int*);

    const long degree = (pageSize + overhead) / (keySize + pointerSize);
    auto *btree = new BTree<std::string>(degree);

    std::vector<std::string> relationPKs = getRelationPK(relation);
    for (auto const &PK : relationPKs){
        btree->insert(PK);
    }

    relationBTreeMap[relation] = btree;
}

void updateRelationBTree(Relation *relation, const std::string &newKey){
    auto *btree = relationBTreeMap[relation];
    btree->insert(newKey);

    relationBTreeMap[relation] = btree;
}

std::vector<std::string> tokenizeExpression(Relation *relation, const std::string &expression) {
    std::vector<std::string> tokens = scanLine(expression);
    std::vector<std::string> optimizedTokens;

    for (const auto &token : tokens){
        auto parts = split(token, ";");
        if (parts[0] == "Identifier" && !isAttributeInRelation(relation, parts[1])){
            parts[0] = "Constant";
            optimizedTokens.push_back(parts[0] + ";" + parts[1]);
        }
        else optimizedTokens.push_back(token);
    }
    return optimizedTokens;
}

bool isPKQueried(Relation *relation, const std::vector<std::string> &tokens){
    std::string PK = getRelationPKAttribute(relation);
    bool found = false;
    bool disjunction = false;
    for (auto const &token : tokens){
        auto parts = split(token, ";");
        if (parts[0] == "Identifier" && parts[1] != PK && found)
            std::cout << "Warning: Primary key " + PK + " uniquely identifies a tuple! " +
            "Querying " + parts[1] + " is redundant!" << std::endl;
        if (parts[0] == "Identifier" && parts[1] == PK) found = true;
        if (parts[0] == "Separator" && parts[1] == "or") disjunction = true;
    }

    return (found && !disjunction);
}

std::vector<std::string> getPKQueryInformation(Relation *relation, const std::vector<std::string> &tokens) {
    std::string PK = getRelationPKAttribute(relation);
    std::vector<std::string> info;

    for (size_t i = 1; i < tokens.size() - 1; ++i) {
        auto currentToken = split(tokens[i], ";");
        auto previousToken = split(tokens[i - 1], ";");
        auto nextToken = split(tokens[i + 1], ";");

        if (currentToken[0] == "Separator" && currentToken[1] != "(" && currentToken[1] != ")"
            && previousToken[0] == "Identifier" && previousToken[1] == PK) {

            info.push_back(currentToken[1]);
            info.push_back(nextToken[1]);
            break;
        }
    }

    return info;
}

void createPKLineToRelationMap(Relation* relation){
    std::string filePath = "DB/" + getSchemaFromRelation(relation)->getName() + "/relations/" + relation->getName();
    std::vector<std::string> lines = readLines(filePath);

    int PKIndex = getRelationPKIndex(relation);
    for (int index = 1 ; index <= lines.size() ; index++){
        auto tokens = split(lines[index], ",");
        std::string pk = tokens[PKIndex];

        addPKLineToRelationMap(relation, pk, lines[index]);
    }
}

void addPKLineToRelationMap(Relation* relation, const std::string& pk, const std::string& line) {
    if (relationPKLineMap.find(relation) == relationPKLineMap.end()) {
        relationPKLineMap[relation] = std::unordered_map<std::string, std::string>();
    }
    relationPKLineMap[relation][pk] = line;
}

void updateRelationPKLineMap(Relation* relation, const std::string& schemaName, const std::string& relationName) {
    std::string filePath = "DB/" + schemaName + "/relations/" + relationName;
    if (!validFile(filePath)) return;

    std::vector<std::string> lines = readLines(filePath);
    int pkIndex = getRelationPKIndex(relation);
    if (pkIndex < 0) return;

    if (relationPKLineMap.find(relation) == relationPKLineMap.end()) {
        relationPKLineMap[relation] = std::unordered_map<std::string, std::string>();
    }

    for (const auto& line : lines) {
        auto lineTokens = split(line, ",");
        if (pkIndex < lineTokens.size()) {
            std::string pk = lineTokens[pkIndex];
            relationPKLineMap[relation][pk] = line;
        }
    }
}

std::string getPKLineForConstant(Relation *relation, const std::string &primaryKey) {
    auto relationPKMapIt = relationPKLineMap.find(relation);

    if (relationPKMapIt == relationPKLineMap.end() || relationPKMapIt->second.empty()) {
        std::cerr << "No PK lines found for the relation: " << relation->getName() << std::endl;
        return "";
    }

    auto pkLineMap = relationPKMapIt->second;
    auto lineIt = pkLineMap.find(primaryKey);
    if (lineIt != pkLineMap.end()) {
        return lineIt->second;
    }
    else {
        std::cerr << "Primary Key not found: " << primaryKey << " in relation: " << relation->getName() << std::endl;
        return "";
    }
}

bool relationAlreadyDeclared(Relation *relation){
    std::string filePath = "DB/" + getSchemaFromRelation(relation)->getName() + "/relationAttributes";
    std::vector<std::string> lines = readLines(filePath);

    bool foundRelation = false;
    for (const auto &line : lines){
        auto tokens = split(line, ",");
        if (tokens[0] == "Relation" && tokens[1] == relation->getName() && !foundRelation) foundRelation = true;
        else if (tokens[0] == "Relation" && tokens[1] != relation->getName() && foundRelation) break;

        if (foundRelation && split(tokens[0], ",")[0] != "Relation"){
            std::string attributeName = tokens[0];
            std::string attributeDataType = tokens[1];
            std::string attributeConstraint = tokens[2];

            Datatype *datatype = getDataType(attributeDataType);
            auto *newAttribute = new Attribute(attributeName, datatype, attributeConstraint);
            relation->addAttribute(newAttribute);
        }
    }

    if (foundRelation) {
        createPKLineToRelationMap(relation);
        return true;
    }
    return false;
}

void updateLinesByPK(const std::string &filePath, Relation *relation,
                     const std::string &PK,
                     std::unordered_map<size_t, std::string> attributeValueMap) {
    std::vector<std::string> lines = readLines(filePath);
    int PKIndex = getRelationPKIndex(relation);

    for (auto &line : lines) {
        auto tokens = split(line, ",");
        if (tokens[PKIndex] == PK) {
            for (int index = 0; index < tokens.size(); index++) {
                if (attributeValueMap.find(index) != attributeValueMap.end()) {
                    tokens[index] = attributeValueMap[index];
                }
            }
            line = join(tokens, ",");
        }
    }
    writeLines(filePath, lines);
}

void updateLinesByNonPK(const std::string &filePath, Relation* relation,
                        const std::vector<std::string> &validExpressions,
                        std::unordered_map<size_t, std::string> attributeValueMap){
    std::vector<std::string> lines = readLines(filePath);

    for (auto &line : lines){
        auto tokens = split(line, ",");
        if (checkValidExpressions(relation, tokens, validExpressions)){
            for (int index = 0; index < tokens.size(); index++) {
                if (attributeValueMap.find(index) != attributeValueMap.end()) {
                    tokens[index] = attributeValueMap[index];
                }
            }
            line = join(tokens, ",");
        }
    }
    writeLines(filePath, lines);
}

void deleteLinesByNonPK(const std::string &filePath, Relation* relation,
                       const std::vector<std::string> &validExpressions){
    std::vector<std::string> lines = readLines(filePath);
    std::vector<std::string> newLines;

    for (auto &line : lines){
        auto tokens = split(line, ",");
        if (!checkValidExpressions(relation, tokens, validExpressions)){
            newLines.push_back(line);
        }
    }

    writeLines(filePath, newLines);
}

bool checkValidExpressions(Relation *relation, const std::vector<std::string> &tokens,
                           const std::vector<std::string> &validExpressions){

    for (const auto &expression : validExpressions){
        bool validUpdateLine = true;

        auto expressions = split(expression, ",");
        for (const auto &expr : expressions){
            auto expressionTokens = split(expr, "==");
            //TODO Also add other operations
            if (tokens[getIndexOfAttribute(relation, expressionTokens[0])] != expressionTokens[1]){
                validUpdateLine = false;
            }
        }

        if (validUpdateLine) return true;
    }
    return false;
}

std::unordered_map<size_t, std::string> getAttributeValueMap(Relation *relation,
                                                             const std::vector<std::string> &statementTokens){
    std::unordered_map<size_t, std::string> attributeValueMap;
    std::unordered_map<std::string, size_t> attributeIndexMap;

    std::string filePath = "DB/" + getSchemaFromRelation(relation)->getName() + "/relations/" + relation->getName();
    std::string header = getLine(filePath, 0);
    auto headerTokens = split(header, ",");
    for (int index = 0 ; index < headerTokens.size() ; index++) attributeIndexMap[headerTokens[index]] = index;

    for (size_t index = 0 ; index < statementTokens.size() ; index++){
        auto tokens = split(statementTokens[index], ";");
        if (tokens[0] == "Separator" && (tokens[1] == "(" || tokens[1] == ")")) continue;
        if (tokens[0] == "Separator" && tokens[1] == "=") {
            auto prevTokens = split(statementTokens[index - 1], ";");
            auto nextTokens = split(statementTokens[index + 1], ";");

            if (prevTokens[0] == "Identifier" && isAttributeInRelation(relation, prevTokens[1])){
                attributeValueMap[attributeIndexMap[prevTokens[1]]] = nextTokens[1];
            }
            else if (nextTokens[0] == "Identifier" && isAttributeInRelation(relation, nextTokens[1])){
                attributeValueMap[attributeIndexMap[nextTokens[1]]] = prevTokens[1];
            }
        }
    }

    return attributeValueMap;
}

std::vector<std::string> getElementsByAttribute(Relation *relation, const std::string &attribute,
                                                const std::vector<std::string> &validExpressions){
    std::vector<std::string> elements;

    std::string filePath = "DB/" + getSchemaFromRelation(relation)->getName() + "/relations/" + relation->getName();
    std::string header = getLine(filePath, 0);
    auto headerTokens = split(header, ",");

    int attributeIndex;
    for (int index = 0 ; index < headerTokens.size() ; index++) {
        if (headerTokens[index] == attribute) {
            attributeIndex = index;
            break;
        }
    }

    std::vector<std::string> lines = readLines(filePath);
    for (int index = 1 ; index <= lines.size() ; index++){
        auto tokens = split(lines[index], ",");
        if (validExpressions.empty()) elements.push_back(tokens[attributeIndex]);
        else if (checkValidExpressions(relation, tokens, validExpressions)){
            elements.push_back(tokens[attributeIndex]);
        }
    }

    return elements;
}

size_t getIndexOfAttribute(Relation *relation, const std::string &attribute){
    std::string filePath = "DB/" + getSchemaFromRelation(relation)->getName() + "/relations/" + relation->getName();
    std::string header = getLine(filePath, 0);
    auto headerTokens = split(header, ",");

    for (int index = 1 ; index < headerTokens.size() ; index++){
        if (headerTokens[index] == attribute) return index;
    }

    return 0;
}
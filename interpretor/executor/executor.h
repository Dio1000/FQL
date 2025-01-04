#ifndef FQL_EXECUTOR_H
#define FQL_EXECUTOR_H

#include <unordered_map>
#include "../../domain/schema/Schema.h"

/**
 * Executes the code after it has been parsed.
 * @param filePath Path of the file.
 * @return Index of the next executed line.
 */
int executeCode(const std::string &filePath);

/**
 * Checks whether a given string is a method call.
 * @param method String to check for.
 * @return True if the string is a method call, false otherwise.
 */
bool isMethodCall(const std::string &method);

/**
 * Executes the schema creation function in the parsed code.
 * @param index Index of the line that is executed.
 * @param codeLines Lines of code to be executed.
 * @return Index of the next executed line.
 */
int executeSchema(int index, const std::vector<std::string> &codeLines);

/**
 * Executes the relation creation function in the parsed code.
 * @param index Index of the line that is executed.
 * @param codeLines Lines of code to be executed.
 * @return Index of the next executed line.
 */
int executeRelation(int index, const std::vector<std::string> &codeLines);

/**
 * Executes the relation attribute declaration function in the parsed code.
 * @param index Index of the line that is executed.
 * @param codeLines Lines of code to be executed.
 * @return Index of the next executed line.
 */
int executeRelationAttributes(int index, const std::vector<std::string> &codeLines);

/**
 * Executes the methods in the parsed code.
 * @param index Index of the line that is executed.
 * @param codeLines Lines of code to be executed.
 * @return Index of the next executed line.
 */
int executeMethodCall(int index, const std::vector<std::string> &codeLines);

/**
 * Executes the relation add method in the parsed code.
 * @param index Index of the line that is executed.
 * @param codeLines Lines of code to be executed.
 * @return Index of the next executed line.
 */
int executeAddRelation(int index, const std::vector<std::string> &codeLines);

/**
 * Executes the relation updates in the parsed code.
 * @param index Index of the line that is executed.
 * @param codeLines Lines of code to be executed.
 * @return Index of the next executed line.
 */
int executeUpdateRelation(int index, const std::vector<std::string> &codeLines);

/**
 * Executes the relation deletion in the parsed code.
 * @param index Index of the line that is executed.
 * @param codeLines Lines of code to be executed.
 * @return Index of the next executed line.
 */
int executeDeleteRelation(int index, const std::vector<std::string> &codeLines);

/**
 * Executes the array declaration in the parsed code.
 * @param index Index of the line that is executed.
 * @param codeLines Lines of code to be executed.
 * @return Index of the next executed line.
 */
int executeArray(int index, const std::vector<std::string> &codeLines);

/**
 * Executes the relation fetches in the parsed code.
 * @param index Index of the line that is executed.
 * @param codeLines Lines of code to be executed.
 * @return Index of the next executed line.
 */
int executeFetchRelation(int index, const std::vector<std::string> &codeLines);

/**
 * Executes the concatenation in the parsed code.
 * @param index Index of the line that is executed.
 * @param codeLines Lines of code to be executed.
 * @return Index of the next executed line.
 */
int executeConcatenate(int index, const std::vector<std::string> &codeLines);

/**
 * Executes the show function in the parsed code.
 * @param index Index of the line that is executed.
 * @param codeLines Lines of code to be executed.
 * @return Index of the next executed line.
 */
int executeShow(int index, const std::vector<std::string> &codeLines);

/**
 * Checks whether a relation belongs in a schema.
 * @param relation Relation to check for.
 * @param schema Schema to check for.
 * @return True if the relation is in the schema, false otherwise.
 */
bool isRelationInSchema(Relation* relation, Schema* schema);

/**
 * Checks whether an attribute is in a relation.
 * @param relation Relation to check in.
 * @param attribute Attribute to check for.
 * @return True if the attribute is in the relation, false otherwise.
 */
bool isAttributeInRelation(Relation* relation, const std::string &attribute);

/**
 * Returns the schema a given relation belongs to.
 * @param relation Relation to fetch the schema for.
 * @return The fetched schema the relation belongs to.
 */
Schema *getSchemaFromRelation(Relation *relation);

/**
 * Returns a Schema object from a given schema name.
 * @param schemaName Schema name to create the object for.
 * @return Schema object with the given name.
 */
Schema *getSchema(const std::string &schemaName);

/***
 * Returns a Relation object from a given Relation name.
 * @param relationName Relation name to create the object for.
 * @return Relation object with the given name.
 */
Relation *getRelation(const std::string &relationName);

/**
 * Returns a DataType object from a given name.
 * @param dataType Name of the data type.
 * @return Object representing a data type that implements the
 * DataType interface.
 */
Datatype *getDataType(const std::string &dataType);

/**
 * Gets the current RID of a given relation.
 * @param relationName Name of the relation.
 * @return Integer representing the current RID of a relation.
 */
int getRID(const std::string &relationName);

/**
 * Updates the current RID of a given relation.
 * @param relationName Name of the relation
 * @param newRID New RID to update.
 */
void updateRID(const std::string &relationName, int newRID);

/**
 * Fetches the index the PK attribute is at.
 * @param relation Relation to get for.
 * @return Index of the PK.
 */
int getRelationPKIndex(Relation *relation);

/**
 * Fetches all the PK values in a relation.
 * @param relation Relation to fetch for.
 * @return Vector of strings representing the values of the PKs.
 */
std::vector<std::string> getRelationPK(Relation *relation);

/**
 * Gets the attribute that is the PK in a relation.
 * @param relation Relation to get for.
 * @return String representing the PK attribute.
 */
std::string getRelationPKAttribute(Relation *relation);

/**
 * Builds and returns a map which maps all the PKs to their respective lines.
 * @param relation Relation to build the map for.
 * @return Unordered map representing the mapping of the PKs to the lines they are in.
 */
std::unordered_map<std::string, std::string> getPKLineMap(Relation *relation);

/**
 * Builds the BTree for a relation containing all the PKs.
 * @param relation Relation to build for.
 */
void buildRelationBTree(Relation *relation);

/**
 * Updates the Btree with a new value.
 * @param relation Relation to update for.
 * @param newKey New key to update with.
 */
void updateRelationBTree(Relation *relation, const std::string &newKey);

/**
 * Breaks an expression into tokens that can be parsed.
 * @param relation Relation the expression is in.
 * @param expression Expression to parse.
 * @return Vector of strings representing the expression tokens.
 */
std::vector<std::string> tokenizeExpression(Relation *relation, const std::string &expression);

/**
 * Checks if a query can be uniquely identified by the PK.
 * @param relation Relation to check in.
 * @param tokens Tokens of the expression.
 * @return True if the PK uniquely identifies the query, false otherwise.
 */
bool isPKQueried(Relation *relation, const std::vector<std::string> &tokens);

/**
 * Fetches the operation and the constant a PK is used for if the query is
 * uniquely identified by the PK.
 * @param relation Relation to check in.
 * @param tokens Tokens of the expression.
 * @return Vector of exactly two strings, first one is the operator, second is the constant.
 */
std::vector<std::string> getPKQueryInformation(Relation *relation, const std::vector<std::string> &tokens);

/**
 * Handles the information of the PK if the query is uniquely identified by the PK.
 * @param relation Relation to check in.
 * @param info Vector of exactly two strings representing Information about the operation.
 */
void handlePKInfoForDelete(Relation* relation, const std::vector<std::string> &info);

/**
 * Adds a PK to the relationPKLineMap of a given relation.
 * @param relation Relation object.
 * @param pk Name of the PK.
 * @param line Line the PK is on.
 */
void addPKLineToRelationMap(Relation* relation, const std::string& pk, const std::string& line);

/**
 * Creates the PKLineToRelation map for a relation.
 * @param relation Relation to create for.
 */
void createPKLineToRelationMap(Relation* relation);

/**
 * Updates the relationPKLineMap of a given relation.
 * @param relation Relation object.
 * @param schemaName Name of the schema the relation is in.
 * @param relationName Name of the relation to update for.
 */
void updateRelationPKLineMap(Relation* relation, const std::string& schemaName, const std::string& relationName);

/**
 * Returns the line that is uniquely identified by a PK in a relation.
 * @param relation Relation to check in.
 * @param primaryKey Primary key to check for.
 * @return Line the PK is on.
 */
std::string getPKLineForConstant(Relation *relation, const std::string &primaryKey);

/**
 * Checks if a relation is already declared (is in disk memory). If it is, it loads it into memory.
 * @param relation Relation to check for.
 * @return True if the relation is already declared, false otherwise.
 */
bool relationAlreadyDeclared(Relation *relation);

#endif //FQL_EXECUTOR_H

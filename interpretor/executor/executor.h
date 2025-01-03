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
 * Auxiliary function to check whether a relation belongs in a schema.
 * @param relation Relation to check for.
 * @param schema Schema to check for.
 * @return True if the relation is in the schema, false otherwise.
 */
bool isRelationInSchema(Relation* relation, Schema* schema);

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

int getRelationPKIndex(Relation *relation);

std::vector<std::string> getRelationPK(Relation *relation);

#endif //FQL_EXECUTOR_H

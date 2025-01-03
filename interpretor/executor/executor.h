#ifndef FQL_EXECUTOR_H
#define FQL_EXECUTOR_H

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

bool isRelationInSchema(Relation* relation, Schema* schema);

Schema *getSchemaFromRelation(Relation *relation);

Schema *getSchema(const std::string &schemaName);

Relation *getRelation(const std::string &relationName);

Datatype *getDataType(const std::string &dataType);

#endif //FQL_EXECUTOR_H

#ifndef FQL_EXECUTOR_H
#define FQL_EXECUTOR_H

/**
 * Executes the code after it has been parsed.
 * @param codeLines Lines of code to be executed.
 * @return Index of the next executed line.
 */
int executeCode(const std::vector<std::string> &codeLines);

/**
 * Executes the using function in the parsed code.
 * @param index Index of the line that is executed.
 * @param codeLines Lines of code to be executed.
 * @return Index of the next executed line.
 */
int executeUsing(int index, const std::vector<std::string> &codeLines);

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
int executeMethod(int index, const std::vector<std::string> &codeLines);

#endif //FQL_EXECUTOR_H

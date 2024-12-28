#ifndef FQL_EXECUTOR_H
#define FQL_EXECUTOR_H

/**
 * Executes the code after it has been parsed.
 * @param codeLines Lines of code to be executed.
 * @return
 */
int executeCode(const std::vector<std::string> &codeLines);

int executeUsing(int index, const std::vector<std::string> &codeLines);

int executeSchema(int index, const std::vector<std::string> &codeLines);

int executeRelation(int index, const std::vector<std::string> &codeLines);

int executeRelationAttributes(int index, const std::vector<std::string> &codeLines);

int executeMethod(int index, const std::vector<std::string> &codeLines);

#endif //FQL_EXECUTOR_H

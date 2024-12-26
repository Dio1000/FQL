#ifndef FQL_PARSER_H
#define FQL_PARSER_H

void logError(const std::string& errorMessage, unsigned long lineNumber);
/**
 * Parses the code to check for syntax errors.
 * @param codeLines Lines of code to parse.
 * @return True if code is syntactically correct, false otherwise.
 */
int parseCode(const std::vector<std::string> &codeLines);

int parseSchema(int index, const std::vector<std::string> &codeLines);

int parseUsing(int index, const std::vector<std::string> &codeLines);

int parseAttribute(int index, const std::vector<std::string> &codeLines);

int parseRelation(int index, const std::vector<std::string> &codeLines);

int parseRelationAttributes(int index, const std::vector<std::string> &codeLines);

void showMessages();

#endif //FQL_PARSER_H

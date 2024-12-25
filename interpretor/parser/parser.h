#ifndef FQL_PARSER_H
#define FQL_PARSER_H

/**
 * Parses the code to check for syntax errors.
 * @param codeLines Lines of code to parse.
 * @return True if code is syntactically correct, false otherwise.
 */
bool parseCode(const std::vector<std::string> &codeLines);

bool parseSchema(int index, const std::vector<std::string> &codeLines);

bool parseAttribute(int index, const std::vector<std::string> &codeLines);

bool parseRelation(int index, const std::vector<std::string> &codeLines);

bool parseRelationAttributes(int index, const std::vector<std::string> &codeLines);

void showMessages();

#endif //FQL_PARSER_H

#ifndef FQL_PARSER_H
#define FQL_PARSER_H

/**
 * Auxiliary functions for logging errors.
 * @param errorMessage Error message to log.
 * @param lineNumber Number of the line that has an error.
 */
void logError(const std::string& errorMessage, unsigned long lineNumber);

/**
 * Parses the code to check for syntax errors.
 * @param codeLines Lines of code to parse.
 * @return True if code is syntactically correct, false otherwise.
 */
int parseCode(const std::vector<std::string> &codeLines);

/**
 * Parses the scanned lines when finding a schema to check for syntax errors.
 * @param index Index of the line.
 * @param codeLines Lines of the code to parse.
 * @return True if code is syntactically correct, false otherwise.
 */
int parseSchema(int index, const std::vector<std::string> &codeLines);

/**
 * Parses the scanned lines when finding a using keyword to check for syntax errors.
 * @param index Index of the line.
 * @param codeLines Lines of the code to parse.
 * @return True if code is syntactically correct, false otherwise.
 */
int parseUsing(int index, const std::vector<std::string> &codeLines);

/**
 * Parses the scanned lines when finding an attribute to check for syntax errors.
 * @param index Index of the line.
 * @param codeLines Lines of the code to parse.
 * @return True if code is syntactically correct, false otherwise.
 */
int parseAttribute(int index, const std::vector<std::string> &codeLines);

/**
 * Parses the scanned lines when finding a relation to check for syntax errors.
 * @param index Index of the line.
 * @param codeLines Lines of the code to parse.
 * @return True if code is syntactically correct, false otherwise.
 */
int parseRelation(int index, const std::vector<std::string> &codeLines);

/**
 * Parses the scanned lines when finding a relation that has its attributes set
 * to check for syntax error.
 * @param index Index of the line.
 * @param codeLines Lines of the code to parse.
 * @return True if code is syntactically correct, false otherwise.
 */
int parseRelationAttributes(int index, const std::vector<std::string> &codeLines);

/**
 * Shows the warning and error messages in case the build fails.
 */
void showMessages();

#endif //FQL_PARSER_H

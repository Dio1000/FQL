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
 * @return Index of the next parsed line.
 */
int parseCode(const std::vector<std::string> &codeLines);

/**
 * Parses the scanned lines when finding a schema to check for syntax errors.
 * @param index Index of the line.
 * @param codeLines Lines of the code to parse.
 * @return Index of the next parsed line.
 */
int parseSchema(int index, const std::vector<std::string> &codeLines);

/**
 * Parses the scanned lines when finding a 'using' keyword to check for syntax errors.
 * @param index Index of the line.
 * @param codeLines Lines of the code to parse.
 * @return Index of the next parsed line.
 */
int parseUsing(int index, const std::vector<std::string> &codeLines);

/**
 * Parses the scanned lines when finding an attribute to check for syntax errors.
 * @param index Index of the line.
 * @param codeLines Lines of the code to parse.
 * @return Index of the next parsed line.
 */
int parseAttribute(int index, const std::vector<std::string> &codeLines);

/**
 * Parses the scanned lines when finding a relation to check for syntax errors.
 * @param index Index of the line.
 * @param codeLines Lines of the code to parse.
 * @return Index of the next parsed line.
 */
int parseRelation(int index, const std::vector<std::string> &codeLines);

/**
 * Parses the scanned lines when finding a relation that has its attributes set
 * to check for syntax error.
 * @param index Index of the line.
 * @param codeLines Lines of the code to parse.
 * @return Index of the next parsed line.
 */
int parseRelationAttributes(int index, const std::vector<std::string> &codeLines);

/**
 * Parses a method that can be called with a relation identifier.
 * @param index Index of the line.
 * @param codeLines Lines of the code to parse.
 * @return Index of the next parsed line.
 */
int parseMethod(int index, const std::vector<std::string> &codeLines);

/**
 * Parses an argument passed to a function.
 * @param index Index of the line.
 * @param codeLines Lines of the code to parse.
 * @return Index of the next parsed line.
 */
int parseArgument(int index, const std::vector<std::string> &codeLines);

/**
 * Parses the add method for relations.
 * @param index Index of the line.
 * @param relation Relation to get the attributes from.
 * @param codeLines Lines of code to parse.
 * @return Index of the next parsed line.
 */
int parseAdd(int index, const std::string &relation, const std::vector<std::string> &codeLines);

/**
 * Shows the warning and error messages in case the build fails.
 */
void showMessages();

#endif //FQL_PARSER_H

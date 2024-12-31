#ifndef FQL_PARSER_H
#define FQL_PARSER_H

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
 * Parses the scanned lines when finding an attribute to check for syntax errors.
 * @param index Index of the line.
 * @param codeLines Lines of the code to parse.
 * @return Index of the next parsed line.
 */
int parseAttribute(int index, const std::vector<std::string> &codeLines);

/**
 * Parses the scanned lines when finding a 'using' keyword to check for syntax errors.
 * @param index Index of the line.
 * @param codeLines Lines of the code to parse.
 * @return Index of the next parsed line.
 */
int parseUsing(int index, const std::vector<std::string> &codeLines);

/**
 * Parses the scanned lines when finding a 'let' keyword to check for syntax errors.
 * @param index Index of the line.
 * @param codeLines Lines of the code to parse.
 * @return Index of the next parsed line.
 */
int parseLet(int index, const std::vector<std::string> &codeLines);

/**
 * Parses a method that can be called with a relation identifier.
 * @param index Index of the line.
 * @param codeLines Lines of the code to parse.
 * @return Index of the next parsed line.
 */
int parseMethod(int index, const std::vector<std::string> &codeLines);

/**
 * Parses the add method for relations.
 * @param index Index of the line.
 * @param relation Relation to get the attributes from.
 * @param codeLines Lines of code to parse.
 * @return Index of the next parsed line.
 */
int parseAdd(int index, const std::string &relation, const std::vector<std::string> &codeLines);

/**
 * Parses the fetch method for relations.
 * @param index Index of the line.
 * @param relation Relation to get the attributes from.
 * @param codeLines Lines of code to parse.
 * @return Index of the next parsed line.
 */
int parseFetch(int index, const std::string &relation, const std::vector<std::string> &codeLines);

/**
 * Parses the concatenation between fetch resulting arrays.
 * @param index Index of the line.
 * @param relation Relation to get the attributes from.
 * @param codeLines Lines of code to parse.
 * @return Index of the next parsed line.
 */
int parseConcatenation(int index, const std::vector<std::string> &codeLines);

/**
 * Parses the where keyword for fetch expressions.
 * @param index Index of the line.
 * @param relation Relation to get the attributes from.
 * @param codeLines Lines of code to parse.
 * @return Index of the next parsed line.
 */
int parseWhere(int index, const std::string &relation, const std::vector<std::string> &codeLines);

/**
 * Parses the update method for relations.
 * @param index Index of the line.
 * @param relation Relation to get the attributes from.
 * @param codeLines Lines of code to parse.
 * @return Index of the next parsed line.
 */
int parseUpdate(int index, const std::string &relation, const std::vector<std::string> &codeLines);

/**
 * Parses an argument passed to a function.
 * @param index Index of the line.
 * @param argumentType Type of the argument required.
 * @param codeLines Lines of the code to parse.
 * @return Index of the next parsed line.
 */
int parseArgument(int index, const std::string &argumentType, const std::vector<std::string> &codeLines);

/**
 * Parses a constant data type of a relation.
 * @param index Index of the line.
 * @param argumentType Type of the argument required.
 * @param tokens Tokens of the code to parse.
 */
void validConstantDataTypes(int index, const std::string &argumentType, const std::vector<std::string> &tokens);

/**
 * Parses an identifier data type of a relation.
 * @param index Index of the line.
 * @param argumentType Type of the argument required.
 * @param tokens Tokens of the code to parse.
 */
void validIdentifierDataTypes(int index, const std::string &argumentType, const std::vector<std::string> &tokens);

/**
 * Gets all the warnings regarding the scanned lines.
 */
void getWarnings();

/**
 * Stores the messages related to unused relation warnings.
 */
void getUnusedRelationsWarnings();

/**
 * Stores the messages related to unused arrays warnings.
 */
void getUnusedArraysWarning();

/**
 * Auxiliary functions for logging errors.
 * @param errorMessage Error message to log.
 * @param lineNumber Number of the line that has an error.
 */
void logError(const std::string& errorMessage, unsigned long lineNumber);

/**
 * Shows the warning and error messages in case the build fails.
 */
void showMessages();

#endif //FQL_PARSER_H

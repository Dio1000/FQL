#ifndef FQL_SCANNER_H
#define FQL_SCANNER_H

#include <regex>

/**
 * Reads a file line by line and removes empty lines and comments.
 * @param filePath File path.
 * @return Vector of lines containing the code with the correct removals.
 */
std::vector<std::string> readCode(const std::string &filePath);

/**
 * Scans the code and breaks it down into tokens that can be parsed.
 * @param codeLines Lines to be scanned.
 * @return Vector of lines containing the tokens.
 */
std::vector<std::string> scanCode(const std::vector<std::string> &codeLines);

/**
 * Scans a line and breaks it down into tokens.
 * @param line Line to be scanned.
 * @return Vector of tokens.
 */
std::vector<std::string> scanLine(const std::string &line);

#endif //FQL_SCANNER_H

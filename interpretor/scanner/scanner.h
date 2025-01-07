#pragma once

#ifndef FQL_SCANNER_H
#define FQL_SCANNER_H

#include <regex>
#include <unordered_set>

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
std::vector<std::string> scanCode(const std::string &filePath, std::unordered_set<std::string> &scannedFiles);

/**
 * Gets a given line from the original lines of code.
 * @param lineNumber Number of the line to fetch.
 * @return Line from the original code with the given line number.
 */
std::string getLine(int lineNumber);

/**
 * Scans a line and breaks it down into tokens.
 * @param line Line to be scanned.
 * @return Vector of tokens.
 */
std::vector<std::string> scanLine(const std::string &line);

#endif //FQL_SCANNER_H

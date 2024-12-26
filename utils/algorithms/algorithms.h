#ifndef FQL_ALGORITHMS_H
#define FQL_ALGORITHMS_H

/**
 * Auxiliary function to compute the LPS of a given pattern.
 * @param pattern Given pattern to compute the LPS for.
 * @return The computed LPS.
 */
std::vector<unsigned long> longestPrefixSuffix(const std::string& pattern);

/**
 * Searches for a pattern in a given string using the KMP algorithm.
 * @param str String to search in.
 * @param pattern Pattern to search for.
 * @return List of indices where the pattern starts, -1 if no pattern was not found.
 */
std::vector<unsigned long> searchPattern(const std::string& str, const std::string& pattern);

/**
 * Splits a given string based on a given pattern and returns the whole resulting list.
 * @param str String to split.
 * @param pattern Pattern to split based on.
 * @return Resulting list
 */
std::vector<std::string> split(const std::string& str, const std::string& pattern);

/**
 * Splits a given string based on a given pattern and returns the element
 * at the given index from the resulting list.
 * @param str String to split.
 * @param pattern Pattern to split based on.
 * @param index Index of the returned element.
 * @return String on the given index after split.
 */
std::string split(const std::string& str, const std::string& pattern, int index);

/**
 * Strips the trailing characters given by the user from the front and back of a string.
 * @param str String to strip.
 * @param delimiter Stripped characters.
 * @return New string with the stripped characters.
 */
std::string strip(const std::string& str, char delimiter);

/**
 * Checks if a string can be cast to integer.
 * @param s String to check.
 * @return True if the string can be cast to integer, false otherwise.
 */
bool isNumber(const std::string& s);

#endif
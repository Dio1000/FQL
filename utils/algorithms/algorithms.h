#ifndef FQL_ALGORITHMS_H
#define FQL_ALGORITHMS_H

#include <unordered_map>

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

/**
 * Checks if a string can be cast to char.
 * @param chr String to check.
 * @return True if the string can be cast to char, false otherwise.
 */
bool isChar(const std::string &chr, int size);

/**
 * Checks if a string can be cast to varchar.
 * @param chr String to check.
 * @return True if the string can be cast to varchar, false otherwise.
 */
bool isVarchar(const std::string &chr, int size);

/**
 * Checks if a string can be cast to boolean.
 * @param b String to check.
 * @return True if the string can be cast to boolean, false otherwise.
 */
bool isBoolean(const std::string &b);

/**
 * Checks if a string can be cast to date.
 * @param date String to check.
 * @return True if the string can be cast to date, false otherwise.
 */
bool isDate(const std::string &date);

/**
 * Checks if a string can be cast to datetime.
 * @param datetime String to check.
 * @return True if the string can be cast to datetime, false otherwise.
 */
bool isDateTime(const std::string &datetime);

/**
 * Checks if a string can be cast to UUID.
 * @param uuid String to check
 * @return True if the string can be cast to UUID, false otherwise.
 */
bool isUUID(const std::string &uuid);

/**
 * Generates a random UUID (aka char(16)).
 * @return The generated UUID.
 */
std::string generateUUID();

/**
 * Removes all the escaping characters from a string.
 * @param str String to remove escaping characters from.
 * @return String without escaping characters.
 */
std::string unescapeString(const std::string& str);

/**
 * Helper function to return the value of a key in a map.
 * @param map Map which maps the key to the value.
 * @param key Key to find the value of.
 * @return Value of the key.
 */
std::string getKeyValue(const std::unordered_map<std::string, std::string>& map, const std::string& key);

/**
 * Joins a vector of strings with a given delimiter between them.
 * @param tokens Tokens to be joined.
 * @param delimiter Delimited to be put between them.
 * @return The newly formed string representing the join.
 */
std::string join(const std::vector<std::string>& tokens, const std::string& delimiter);

/**
 * Eliminates the whitespaces before and after a given string.
 * @param str String to trim.
 * @return New string representing the trim.
 */
std::string trim(const std::string &str);


#endif
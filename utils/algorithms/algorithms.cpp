#include <string>
#include <vector>
#include <regex>
#include <unordered_map>

#include "algorithms.h"

std::vector<unsigned long> longestPrefixSuffix(const std::string& pattern) {
    unsigned long len = pattern.length();
    std::vector<unsigned long> LPS(len, 0);

    unsigned long i = 1;
    unsigned long j = 0;

    while (i < len) {
        if (pattern[i] == pattern[j]) {
            j++;
            LPS[i] = j;
            i++;
        }
        else if (j == 0) {
            LPS[i] = 0;
            i++;
        }
        else j = LPS[j - 1];
    }

    return LPS;
}

std::vector<unsigned long> searchPattern(const std::string& str, const std::string& pattern) {
    unsigned long stringLength = str.length();
    unsigned long patternLength = pattern.length();
    std::vector<unsigned long> LPS = longestPrefixSuffix(pattern);

    unsigned long i = 0;
    unsigned long j = 0;

    std::vector<unsigned long> foundIndices;
    while (i < stringLength) {
        if (pattern[j] == str[i]) {
            i++;
            j++;
        }

        if (j == patternLength) {
            foundIndices.push_back(i - j);
            j = LPS[j - 1];
        }
        else if (i < stringLength && pattern[j] != str[i]) {
            if (j != 0) j = LPS[j - 1];
            else i++;
        }
    }

    return foundIndices;
}

std::vector<std::string> split(const std::string& str, const std::string& pattern){
    std::vector<unsigned long> patternIndexes = searchPattern(str, pattern);
    std::vector<std::string> tokenString;

    if (patternIndexes.empty()){
        tokenString.push_back(str);
        return tokenString;
    }

    tokenString.push_back(str.substr(0, patternIndexes[0]));
    unsigned long index = 1;
    unsigned long patternSize = pattern.size();

    unsigned long start;
    unsigned long len;
    while (index < patternIndexes.size()){
        start = patternIndexes[index - 1] + patternSize;
        len = patternIndexes[index] - start;

        tokenString.push_back(str.substr(start, len));
        index++;
    }

    start = patternIndexes[index - 1] + patternSize;
    len = str.length() - start;
    tokenString.push_back(str.substr(start, len));

    return tokenString;
}

std::string split(const std::string& str, const std::string& pattern, int index){
    std::vector<std::string> result = split(str, pattern);
    return result[index];
}

std::string strip(const std::string &line, char delimiter){
    std::string strippedLine;
    unsigned long firstIndex = 0;
    unsigned long lastIndex = line.size() - 1;

    while (firstIndex != line.size()){
        if (line[firstIndex] == delimiter) firstIndex++;
        else break;
    }

    while (lastIndex != 0){
        if (line[lastIndex] == delimiter) lastIndex--;
        else break;
    }

    for (unsigned long index = firstIndex ; index < lastIndex + 1 ; index++) strippedLine += line[index];
    return strippedLine;

}

bool isNumber(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

bool isChar(const std::string &chr, int size) {
    return chr.length() == size;
}

bool isVarchar(const std::string &chr, int size) {
    return chr.length() <= size;
}

bool isBoolean(const std::string &b) {
    return b == "true" || b == "false" || b == "1" || b == "0"
        || b == "True" || b == "False";
}

bool isDate(const std::string &date) {
    std::regex dateRegex(R"(^\d{4}-(0[1-9]|1[0-2])-(0[1-9]|[12]\d|3[01])$)");
    return std::regex_match(date, dateRegex);
}

bool isDateTime(const std::string &datetime) {
    std::regex datetimeRegex(R"(^\d{4}-(0[1-9]|1[0-2])-(0[1-9]|[12]\d|3[01]) (0[0-9]|1[0-9]|2[0-3]):([0-5]\d):([0-5]\d)$)");
    return std::regex_match(datetime, datetimeRegex);
}

bool isUUID(const std::string &uuid){
    if (uuid.size() > 16) return false;

    std::string::const_iterator it = uuid.begin();
    while (it != uuid.end() && std::isdigit(*it)) ++it;
    return !uuid.empty() && it == uuid.end();
}

std::string unescapeString(const std::string& str) {
    std::string result;
    bool inEscape = false;

    for (size_t i = 0; i < str.size(); ++i) {
        if (inEscape) {
            if (str[i] == '\"') result += '\"';
            else if (str[i] == '\\') result += '\\';
            else result += str[i];

            inEscape = false;
        }
        else if (str[i] == '\\') inEscape = true;
        else result += str[i];
    }

    return result;
}

std::string getKeyValue(const std::unordered_map<std::string, std::string>& map, const std::string& key) {
    auto it = map.find(key);
    if (it != map.end()) {
        return it->second;
    }
    else return "Null";
}

std::string join(const std::vector<std::string>& tokens, const std::string& delimiter) {
    if (tokens.empty()) return "";

    std::string result = tokens[0];
    for (size_t i = 1; i < tokens.size(); ++i) {
        result += delimiter + tokens[i];
    }
    return result;
}

std::string trim(const std::string &str) {
    size_t first = str.find_first_not_of(" \t\n");
    size_t last = str.find_last_not_of(" \t\n");
    return (first == std::string::npos || last == std::string::npos) ? "" : str.substr(first, last - first + 1);
}
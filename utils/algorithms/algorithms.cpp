#include <string>
#include <vector>
#include <regex>


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
    return b == "true" || b == "false" || b == "1" || b == "0";
}

bool isDate(const std::string &date) {
    std::regex dateRegex(R"(^\d{4}-(0[1-9]|1[0-2])-(0[1-9]|[12]\d|3[01])$)");
    return std::regex_match(date, dateRegex);
}

bool isDateTime(const std::string &datetime) {
    std::regex datetimeRegex(R"(^\d{4}-(0[1-9]|1[0-2])-(0[1-9]|[12]\d|3[01]) (0[0-9]|1[0-9]|2[0-3]):([0-5]\d):([0-5]\d)$)");
    return std::regex_match(datetime, datetimeRegex);
}


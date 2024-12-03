#include <string>
#include <vector>

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

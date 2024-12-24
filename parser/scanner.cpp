#include <string>
#include <vector>
#include <regex>
#include <iostream>

#include "scanner.h"
#include "../io/output.h"

std::vector<std::string> readCode(const std::string& filePath) {
    std::regex oneLineComment(R"(\s*--\s*.*?\s*--)");
    std::regex startMultiLineComment(R"(\s*-/\s*.*?$)");
    std::regex endMultiLineComment(R"(\s*^.*?\s*-?/)");

    std::vector<std::string> codeLines = readLines(filePath);
    bool inMultiLineComment = false;

    auto it = codeLines.begin();
    while (it != codeLines.end()) {
        if (it->empty()) it = codeLines.erase(it);
        else if (std::regex_match(*it, oneLineComment)) it = codeLines.erase(it);
        else if (std::regex_match(*it, startMultiLineComment)) {
            it = codeLines.erase(it);
            inMultiLineComment = true;
        }
        else if (std::regex_match(*it, endMultiLineComment) && inMultiLineComment) {
            it = codeLines.erase(it);
            inMultiLineComment = false;
        }
        else if (inMultiLineComment) it = codeLines.erase(it);
        else it++;
    }

    return codeLines;
}


std::vector<std::string> scanLine(const std::string &line) {
    std::regex keywordsRegex(R"(^\s*(schema|relation|varchar|int|date|boolean|PK|FK|nullable|char|datetime))");
    std::regex constantsRegex(R"(^\s*(->|[^a-zA-Z0-9\s]))");
    std::regex identifierRegex(R"(^\s*[a-zA-Z]+)");
    std::regex endOfFileRegex(R"(\n)");
    std::regex errorRegex(R"(\s*.+)");

    std::string remainingString = line;
    std::vector<std::string> tokens;

    while (!remainingString.empty()) {
        std::smatch match;
        if (std::regex_search(remainingString, match, keywordsRegex)) {
            std::string str = match[0].str();
            str.erase(remove_if(str.begin(), str.end(), isspace), str.end());
            tokens.push_back("Keyword:" + str);

            remainingString = remainingString.substr(match.position() + match.length());
        }
        else if (std::regex_search(remainingString, match, constantsRegex)) {
            std::string str = match[0].str();
            str.erase(remove_if(str.begin(), str.end(), isspace), str.end());
            tokens.push_back("Constant:" + str);

            remainingString = remainingString.substr(match.position() + match.length());
        }
        else if (std::regex_search(remainingString, match, identifierRegex)) {
            std::string str = match[0].str();
            str.erase(remove_if(str.begin(), str.end(), isspace), str.end());
            tokens.push_back("Identifier:" + str);

            remainingString = remainingString.substr(match.position() + match.length());
        }
        else if (std::regex_search(remainingString, match, endOfFileRegex)) {
            std::string str = match[0].str();
            str.erase(remove_if(str.begin(), str.end(), isspace), str.end());
            tokens.push_back("EOF:" + str);

            remainingString = remainingString.substr(match.position() + match.length());
        }
        else if (std::regex_search(remainingString, match, errorRegex)) {
            std::string str = match[0].str();
            str.erase(remove_if(str.begin(), str.end(), isspace), str.end());
            tokens.push_back("Error:" + str);

            remainingString = remainingString.substr(match.position() + match.length());
        }
    }

    return tokens;
}

std::vector<std::string> scanCode(const std::vector<std::string> &codeLines){
    std::vector<std::string> scannedCode;
    auto it = codeLines.begin();

    while (it != codeLines.end()){
        std::vector<std::string> scannedTokens = scanLine(*it);
        scannedCode.insert(scannedCode.end(), scannedTokens.begin(), scannedTokens.end());

        it++;
    }

    return scannedCode;
}




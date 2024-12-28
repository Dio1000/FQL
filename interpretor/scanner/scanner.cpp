#include <string>
#include <vector>
#include <regex>
#include <iostream>

#include "scanner.h"
#include "../../io/io.h"
#include "../../utils/algorithms/algorithms.h"

std::vector<std::string> readCode(const std::string& filePath) {
    std::regex oneLineComment(R"(\s*--\s*.*?\s*--)");
    std::regex startMultiLineComment(R"(\s*-/\s*.*?$)");
    std::regex endMultiLineComment(R"(\s*^.*?\s*-?/)");

    std::vector<std::string> codeLines = readLines(filePath);
    bool inMultiLineComment = false;

    auto it = codeLines.begin();
    while (it != codeLines.end()) {
        if (std::regex_match(*it, oneLineComment)) it = codeLines.erase(it);
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

std::vector<std::string> scanLine(const std::string& line) {
    std::regex keywordsRegex(R"(^\s*(include|schema|relation|varchar|int|date|boolean|PK|FK|nullable|char|datetime|using|nullable|not null|NULLABLE|NOT NULL))");
    std::regex methodRegex(R"(^\s*(add|delete|fetch))");
    std::regex separatorRegex(R"(^\s*(->|:|=|\+|-|\(|\)|\{|\}|\.|\,))"); // Matches `.`
    std::regex constantRegex(R"(^\s*(-?\d+(\.\d+)?|\"(?:\\.|[^\"])*\"))");
    std::regex identifierRegex(R"(^\s*[a-zA-Z0-9_\-/\\]+)"); // Removed `.` from regex
    std::regex endOfFileRegex(R"(^$)");
    std::regex errorRegex(R"(\S+)");

    std::string remainingString = line;
    std::vector<std::string> tokens;

    while (!remainingString.empty()) {
        std::smatch match;

        if (std::regex_search(remainingString, match, keywordsRegex)) {
            tokens.push_back("Keyword;" + strip(match.str(1), ' '));
            remainingString = remainingString.substr(match.length());
        }
        else if (std::regex_search(remainingString, match, separatorRegex)) { // Match separator first
            tokens.push_back("Separator;" + strip(match.str(1), ' '));
            remainingString = remainingString.substr(match.length());
        }
        else if (std::regex_search(remainingString, match, methodRegex)) {
            tokens.push_back("Method;" + strip(match.str(1), ' '));
            remainingString = remainingString.substr(match.length());
        }
        else if (std::regex_search(remainingString, match, constantRegex)) {
            tokens.push_back("Constant;" + strip(match.str(1), ' '));
            remainingString = remainingString.substr(match.length());
        }
        else if (std::regex_search(remainingString, match, identifierRegex)) {
            tokens.push_back("Identifier;" + strip(match.str(0), ' '));
            remainingString = remainingString.substr(match.length());
        }
        else if (std::regex_match(remainingString, match, endOfFileRegex)) {
            tokens.emplace_back("EOF");
            break;
        }
        else if (std::regex_search(remainingString, match, errorRegex)) {
            tokens.push_back("Error;" + strip(match.str(0), ' '));
            remainingString = remainingString.substr(match.length());
        }

        remainingString = std::regex_replace(remainingString, std::regex(R"(^\s+)"), "");
    }

    return tokens;
}

std::vector<std::string> scanCode(const std::string &filePath, std::unordered_set<std::string> &scannedFiles) {
    if (scannedFiles.find(filePath) != scannedFiles.end()) {
        return {};
    }

    scannedFiles.insert(filePath);

    std::vector<std::string> codeLines = readCode(filePath);
    std::vector<std::string> scannedCode;
    int lineNumber = 1;

    for (const auto &line : codeLines) {
        std::vector<std::string> tokens = scanLine(line);

        for (const auto &token : tokens) {
            if (token.find("Keyword;include") == 0) {
                size_t pos = line.find(":");
                if (pos != std::string::npos) {
                    std::string includedFile = strip(line.substr(pos + 1), ' ');
                    std::vector<std::string> includedTokens = scanCode(includedFile, scannedFiles);
                    scannedCode.insert(scannedCode.end(), includedTokens.begin(), includedTokens.end());
                } else {
                    std::cerr << "Error: Invalid include statement in " << filePath << " at line " << lineNumber << std::endl;
                }
            }
            else scannedCode.push_back(token + ";" + std::to_string(lineNumber));
        }

        lineNumber++;
    }

    return scannedCode;
}
#include <string>
#include <vector>
#include <regex>
#include <iostream>
#include <unordered_set>

#include "scanner.h"
#include "../../io/io.h"
#include "../../utils/algorithms/algorithms.h"

std::vector<std::string> originalCodeLines;

std::vector<std::string> readCode(const std::string& filePath) {
    std::regex oneLineComment(R"(\s*--\s*.*?\s*--)");
    std::regex startMultiLineComment(R"(\s*-/\s*.*?$)");
    std::regex endMultiLineComment(R"(\s*^.*?\s*-?/)");

    std::vector<std::string> codeLines = readLines(filePath);
    originalCodeLines = codeLines;
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

std::string getLine(int lineNumber) {
    if (lineNumber > 0 && lineNumber <= originalCodeLines.size()) {
        return originalCodeLines[lineNumber - 1];
    }
    return "";
}

std::vector<std::string> scanLine(const std::string& line) {
    std::regex keywordsRegex(R"(^\s*(include|schema|relation|let|varchar|int|uuid|UUID|date|boolean|PK|FK|nullable|char|datetime|
        |using|nullable|not null|NULLABLE|NOT NULL|where|set|default|set))");
    std::regex methodRegex(R"(^\s*(add|delete|fetch|update))");
    std::regex separatorRegex(R"(^\s*(and|or|>|<|>=|<=|!=|==|->|:|=|\+|-|\(|\)|\{|\}|\.|\,))");
    std::regex constantRegex(R"(^\s*(-?\d+(\.\d+)?|\"([^\"\\]|\\.)*\"|[Tt][Rr][Uu][Ee]|[Ff][Aa][Ll][Ss][Ee]))");
    std::regex identifierRegex(R"(^\s*[a-zA-Z0-9_\-/\\]+)");
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
        else if (std::regex_search(remainingString, match, separatorRegex)) {
            tokens.push_back("Separator;" + strip(match.str(1), ' '));
            remainingString = remainingString.substr(match.length());
        }
        else if (std::regex_search(remainingString, match, methodRegex)) {
            tokens.push_back("Method;" + strip(match.str(1), ' '));
            remainingString = remainingString.substr(match.length());
        }
        else if (std::regex_search(remainingString, match, constantRegex)) {
            std::string constant = strip(match.str(1), ' ');
            if (constant.front() == '"' && constant.back() == '"') {
                constant = constant.substr(1, constant.length() - 2);
                constant = unescapeString(constant);
            }
            tokens.push_back("Constant;" + constant);
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

    if (!validFile(filePath)) {
        std::cerr << "Linker Error: Invalid file path " << filePath << std::endl;
        return {};
    }
    scannedFiles.insert(filePath);

    std::vector<std::string> codeLines = readCode(filePath);
    std::vector<std::string> scannedCode;
    int lineNumber = 1;

    for (const auto &line : codeLines) {
        std::vector<std::string> tokens = scanLine(line);

        bool isIncludeLine = false;
        for (const auto &token : tokens) {
            if (token.find("Keyword;include") == 0) {
                isIncludeLine = true;
                size_t pos = line.find(":");
                if (pos != std::string::npos) {
                    std::string includedFile = strip(line.substr(pos + 1), ' ');

                    if (validFile(includedFile)) {
                        std::vector<std::string> includedTokens = scanCode(includedFile, scannedFiles);
                        scannedCode.insert(scannedCode.end(), includedTokens.begin(), includedTokens.end());
                    } else {
                        std::cerr << "Linker error: Invalid include file path " << includedFile << " in "
                                  << filePath << " at line " << lineNumber << std::endl;
                    }
                }
                else std::cerr << "Linker error: Invalid include statement in " << filePath << " at line " << lineNumber << std::endl;
                break;
            }
        }

        if (!isIncludeLine) {
            for (const auto &token : tokens) {
                scannedCode.push_back(token + ";" + std::to_string(lineNumber));
            }
        }
        lineNumber++;
    }

    return scannedCode;
}

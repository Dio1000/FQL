#include <string>
#include <vector>
#include <regex>

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
    std::regex keywordsRegex(R"(^\s*(schema|relation|varchar|int|date|boolean|PK|FK|nullable|char|datetime|using|nullable|not null|NULLABLE|NOT NULL))");
    std::regex separatorRegex(R"(^\s*(->|:|=|\+|-|\(|\)|\{|\}|\.|\,))");
    std::regex constantRegex(R"(^\s*(-?\d+(\.\d+)?|\"(?:\\.|[^\"])*\"))");
    std::regex identifierRegex(R"(^\s*[a-zA-Z]+)");
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

std::vector<std::string> scanCode(const std::vector<std::string>& codeLines) {
    std::vector<std::string> scannedCode;
    int lineNumber = 1;

    for (const auto& line : codeLines) {
        std::vector<std::string> scannedTokens = scanLine(line);

        for (const auto& token : scannedTokens) {
            scannedCode.push_back(token + ";" + std::to_string(lineNumber));
        }

        lineNumber++;
    }

    return scannedCode;
}

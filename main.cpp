#include <vector>

#include "./domain/relation/Relation.h"
#include "./interpretor/parser/parser.h"
#include "./interpretor/scanner/scanner.h"

int main() {
    std::unordered_set<std::string> scannedFiles;
    std::vector<std::string> tokens = scanCode("files/code", scannedFiles);
    parseCode(tokens, "codeExecute");
}

//TODO fix some bug messages from relation attributes
//TODO fix add argument type check.
//TODO allow array declaration to start with a constant

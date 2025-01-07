#include <vector>

#include "./domain/relation/Relation.h"
#include "./interpretor/parser/parser.h"
#include "./interpretor/scanner/scanner.h"
#include "./interpretor/executor/executor.h"

int main() {
    std::unordered_set<std::string> scannedFiles;
    std::vector<std::string> scannedTokens = scanCode("files/code", scannedFiles);
    parseCode(scannedTokens, "codeExecute");

    executeCode("executables/codeExecute");
}

//TODO fix 'and' and 'or' operators within strings not being correctly parsed
//TODO fix some bug messages from relation attributes
//TODO allow array declaration to start with a constant
//TODO switch the executor for finding the page size for different operating systems.
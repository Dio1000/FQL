#include <vector>
#include <iostream>

#include "./domain/relation/Relation.h"
#include "./interpretor/parser/parser.h"
#include "./interpretor/scanner/scanner.h"
#include "./interpretor/executor/executor.h"
#include "./io/io.h"
#include "utils/data_structures/BTree/BTree.h"

int main() {
//    std::unordered_set<std::string> scannedFiles;
//    std::vector<std::string> scannedTokens = scanCode("files/code", scannedFiles);
//    parseCode(scannedTokens, "codeExecute");

    executeCode("executables/codeExecute");
}

//TODO fix some bug messages from relation attributes
//TODO fix add argument type check.
//TODO allow array declaration to start with a constant
//TODO switch the executor for finding the page size for different operating systems.
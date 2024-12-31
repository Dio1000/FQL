#include <iostream>
#include <vector>
#include <unordered_map>

#include "./domain/relation/Relation.h"
#include "./interpretor/parser/parser.h"
#include "./interpretor/scanner/scanner.h"
#include "./interpretor/validator/validator.h"

int main() {
    std::unordered_set<std::string> scannedFiles;
    std::vector<std::string> tokens = scanCode("files/code", scannedFiles);

//    for (const auto &token : tokens) {
//        std::cout << token << std::endl;
//    }

    parseCode(tokens);

}

//TODO fix some bug messages from relation attributes
//TODO allow array declaration to start with a constant

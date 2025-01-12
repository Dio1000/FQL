#include <vector>
#include <iostream>
#include <cstdio>

#include "./domain/relation/Relation.h"
#include "./interpretor/parser/parser.h"
#include "./interpretor/scanner/scanner.h"
#include "./interpretor/executor/executor.h"
#include "./utils/algorithms/algorithms.h"

int main(int argc, char **argv) {
    if (argc < 3){
        std::cerr << "Too few arguments were provided!\n";
        std::cerr << "Try running:\n";
        std::cerr << "1. <exec> run <buildFile>\n";
        std::cerr << "2. <exec> build <codeFile> <buildFile>\n";

        return 1;
    }

    if (strcmp(argv[1], "run") == 0){
        executeCode(argv[2]);
    }
    else if (strcmp(argv[1], "build") == 0){
        std::unordered_set<std::string> scannedFiles;
        std::vector<std::string> scannedTokens = scanCode(argv[2], scannedFiles);
        parseCode(scannedTokens, argv[3]);
    }
    else {
        fprintf(stderr, "%s is not a valid operation!\n", argv[1]);
        std::cerr << "Try running:\n";
        std::cerr << "1. <exec> run <buildFile>\n";
        std::cerr << "2. <exec> build <codeFile> <buildFile>\n";

        return 1;
    }
}

//TODO fix 'and' and 'or' operators within strings not being correctly parsed
//TODO allow array declaration to start with a constant
//TODO switch the executor for finding the page size for different operating systems.
#include <iostream>
#include <vector>
#include <unordered_map>

#include "./domain/relation/Relation.h"
#include "./domain/attribute/Attribute.h"
#include "./domain/schema/Schema.h"
#include "./domain/datatype/datatypes/integer/Integer.h"
#include "./domain/datatype/datatypes/boolean/Boolean.h"
#include "./domain/datatype/datatypes/date/Date.h"
#include "./io/io.h"
#include "./utils/data_structures/BTree/BTree.h"
#include "./utils/algorithms/algorithms.h"
#include "./ui/ui.h"
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

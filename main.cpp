#include <iostream>
#include <vector>

#include "./domain/relation/Relation.h"
#include "./domain/attribute/Attribute.h"
#include "./domain/schema/Schema.h"
#include "./domain/datatype/datatypes/integer/Integer.h"
#include "./domain/datatype/datatypes/boolean/Boolean.h"
#include "./domain/datatype/datatypes/date/Date.h"
#include "./io/output.h"
#include "./utils/data_structures/BTree/BTree.h"
#include "./utils/algorithms/algorithms.h"
#include "./ui/ui.h"
#include "./parser/scanner.h"

int main() {
    std::cout << "Work in progress!" << std::endl;
    std::vector<std::string> lines = readCode("files/code");
    std::vector<std::string> scannedLines = scanCode(lines);

    for (auto line : scannedLines) std::cout << line << std::endl;
}

#include <vector>

#include "./domain/relation/Relation.h"
#include "./interpretor/parser/parser.h"
#include "./interpretor/scanner/scanner.h"
#include "./interpretor/executor/executor.h"
#include "./io/io.h"

int main() {
    executeCode("executables/codeExecute");
}

//TODO fix some bug messages from relation attributes
//TODO fix add argument type check.
//TODO allow array declaration to start with a constant

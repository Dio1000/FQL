cmake_minimum_required(VERSION 3.27)
project(FQL)

set(CMAKE_CXX_STANDARD 23)

add_executable(FQL main.cpp
        domain/attribute/Attribute.cpp
        domain/attribute/Attribute.h
        domain/validator/Validator.cpp
        domain/validator/Validator.h
        domain/datatype/Datatype.cpp
        domain/datatype/Datatype.h
        domain/datatype/datatypes/integer/Integer.cpp
        domain/datatype/datatypes/integer/Integer.h
        domain/datatype/datatypes/char/Char.cpp
        domain/datatype/datatypes/char/Char.h
        domain/datatype/datatypes/varchar/Varchar.cpp
        domain/datatype/datatypes/varchar/Varchar.h
        domain/datatype/datatypes/boolean/Boolean.cpp
        domain/datatype/datatypes/boolean/Boolean.h
        domain/datatype/datatypes/date/Date.cpp
        domain/datatype/datatypes/date/Date.h
        domain/datatype/datatypes/datetime/Datetime.cpp
        domain/datatype/datatypes/datetime/Datetime.h
        domain/relation/Relation.cpp
        domain/relation/Relation.h
        utils/algorithms/algorithms.cpp
        utils/algorithms/algorithms.h
        domain/schema/Schema.cpp
        domain/schema/Schema.h
        io/io.cpp
        io/io.h
        utils/data_structures/BTree/BTreeNode.h
        utils/data_structures/BTree/BTree.h
        ui/ui.cpp
        ui/ui.h
        interpretor/scanner/scanner.cpp
        interpretor/scanner/scanner.h
        interpretor/parser/parser.cpp
        interpretor/parser/parser.h
        interpretor/validator/validator.cpp
        interpretor/validator/validator.h
        interpretor/executor/executor.cpp
        interpretor/executor/executor.h
        utils/data_structures/AST/ASTNode.h
        utils/data_structures/AST/AST.h
        interpretor/builder/builder.cpp
        interpretor/builder/builder.h)

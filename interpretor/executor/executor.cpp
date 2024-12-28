#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "executor.h"
#include "../../utils/algorithms/algorithms.h"

int executeCode(const std::vector<std::string> &codeLines){
    int index = 0;
    while (index < codeLines.size()){
        auto tokens = split(codeLines[index], ";");

        if (tokens[0] == "Keyword" && tokens[1] == "using"){
            index = executeUsing(index + 1, codeLines);
        }
        else if (tokens[0] == "Keyword" && tokens[1] == "schema"){
            index = executeSchema(index + 1, codeLines);
        }
        else if (tokens[0] == "Keyword" && tokens[1] == "relation"){
            index = executeRelation(index + 1, codeLines);
        }
        else if (tokens[0] == "Identifier" &&
                 (split(codeLines[index + 1], ";")[0] == "Separator") &&
                 (split(codeLines[index + 1], ";")[1] == "->")) {
            index = executeRelationAttributes(index, codeLines);
        }
        else if (tokens[0] == "Identifier" &&
                 (split(codeLines[index + 1], ";")[0] == "Separator") &&
                 (split(codeLines[index + 1], ";")[1] == ".")) {
            index = executeMethod(index, codeLines);
        }
    }
}

int executeUsing(int index, const std::vector<std::string> &codeLines){

}

int executeSchema(int index, const std::vector<std::string> &codeLines){

}

int executeRelation(int index, const std::vector<std::string> &codeLines){

}

int executeRelationAttributes(int index, const std::vector<std::string> &codeLines){

}

int executeMethod(int index, const std::vector<std::string> &codeLines){

}

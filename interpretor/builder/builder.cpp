#include <string>
#include <vector>

#include "builder.h"
#include "../../io/io.h"

void buildExecutable(const std::vector<std::string> &builderLines, const std::string &filePath){
    if (!validFile("executables/" + filePath)){
        writeLines("executables/" + filePath, builderLines);
    }
    else{
        createFile("executables/" + filePath);
        writeLines("executables/" + filePath, builderLines);
    }
}

void buildSchema(std::vector<std::string> &builderLines, const std::string &schema){
    builderLines.push_back("createSchema: " + schema);
}

void buildRelation(std::vector<std::string> &builderLines, const std::string &schema,
                   const std::string &relation){
    builderLines.push_back("createRelation: " + relation + "," + schema);
}

void buildRelationAttributes(std::vector<std::string> &builderLines, const std::string &relation,
                             const std::vector<std::string> &attributes){
    builderLines.push_back("createRelationAttributes: " + relation);
    for (const auto &attribute : attributes) builderLines.push_back("createAttribute: " + attribute);
}

void buildRelationAdd(std::vector<std::string> &builderLines, const std::string &relation,
                      const std::vector<std::string> &arguments){
    builderLines.push_back("addRelation: " + relation);
    for (const auto &argument : arguments) builderLines.push_back("addArgument: " + argument);
}

void buildRelationDelete(std::vector<std::string> &builderLines, const std::string &relation,
                         const std::string &whereExpression){
    builderLines.push_back("deleteRelation: " + relation);
    builderLines.push_back("where: " + whereExpression);
}

void buildRelationUpdate(std::vector<std::string> &builderLines, const std::string &relation,
                         const std::string &whereExpression, const std::string &setExpression){
    builderLines.push_back("updateRelation: " + relation);
    builderLines.push_back("where: " + whereExpression);
    builderLines.push_back("set: " + setExpression);
}

void buildArray(std::vector<std::string> &builderLines, const std::string &array){
    builderLines.push_back("array: " + array);
}

void buildFetch(std::vector<std::string> &builderLines, const std::string &relation,
                const std::vector<std::string> &attributes){
    builderLines.push_back("fetchRelation: " + relation);
    for (auto const &attribute : attributes) builderLines.push_back("fetchAttribute: " + attribute);
}

void buildWhere(std::vector<std::string> &builderLines, const std::string &whereExpression){
    builderLines.push_back("where: " + whereExpression);
}

void buildConcatenate(std::vector<std::string> &builderLines, const std::string &op){
    builderLines.push_back("concatenate: " + op);
}
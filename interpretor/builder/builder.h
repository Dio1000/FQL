#ifndef FQL_BUILDER_H
#define FQL_BUILDER_H

void buildExecutable(const std::vector<std::string> &builderLines, const std::string &filePath);

void buildSchema(std::vector<std::string> &builderLines, const std::string &schema);

void buildRelation(std::vector<std::string> &builderLines, const std::string &schema,
                   const std::string &relation);

void buildRelationAttributes(std::vector<std::string> &builderLines, const std::string &relation,
                             const std::vector<std::string> &attributes);

void buildRelationAdd(std::vector<std::string> &builderLines, const std::string &relation,
                      const std::vector<std::string> &arguments);

void buildRelationDelete(std::vector<std::string> &builderLines, const std::string &relation,
                         const std::string &whereExpression);

void buildRelationUpdate(std::vector<std::string> &builderLines, const std::string &relation,
                      const std::string &whereExpression, const std::string &setExpression);

void buildArray(std::vector<std::string> &builderLines, const std::string &array);

void buildFetch(std::vector<std::string> &builderLines, const std::string &relation,
                const std::vector<std::string> &attributes);

void buildWhere(std::vector<std::string> &builderLines, const std::string &whereExpression);

void buildConcatenate(std::vector<std::string> &builderLines, const std::string &op);

#endif //FQL_BUILDER_H

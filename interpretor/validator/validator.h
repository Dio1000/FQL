#ifndef FQL_VALIDATOR_H
#define FQL_VALIDATOR_H

std::vector<std::string> getSchemas(const std::vector<std::string> &codeLines);

std::vector<std::string> getRelations(const std::vector<std::string> &codeLines);

std::unordered_map<std::string, std::string> getRelationSchema(const std::vector<std::string> &codeLines);

bool schemaAlreadyExists(const std::string &schema, const std::vector<std::string> &codeLines);

bool schemaExists(const std::string &schema, const std::vector<std::string> &codeLines);

bool relationExists(const std::string &relation, const std::vector<std::string> &codeLines);

bool isSchema(const std::string &schema, const std::vector<std::string> &codeLines);

bool isRelation(const std::string &relation, const std::vector<std::string> &codeLines);

#endif //FQL_VALIDATOR_H

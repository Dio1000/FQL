#ifndef FQL_VALIDATOR_H
#define FQL_VALIDATOR_H

/**
 * Fetches all the schemas from the lines of code.
 * @param codeLines Lines of code to fetch the schemas from.
 * @return Vector of strings containing all the schemas.
 */
std::vector<std::string> getSchemas(const std::vector<std::string> &codeLines);

/**
 * Fetches all the relations from the lines of code.
 * @param codeLines Lines of code to fetch the relations from.
 * @return Vector of strings containing all the relations.
 */
std::vector<std::string> getRelations(const std::vector<std::string> &codeLines);

/**
 * Constructs a map with the relations as keys and the schema they belong to as the value,
 * or "NULL" in case the relation does not belong to any schema.
 * @param codeLines Lines of code to fetch from.
 * @return Map of strings containing relations as keys and the schema they belong to as values.
 */
std::unordered_map<std::string, std::string> getRelationSchema(const std::vector<std::string> &codeLines);

/**
 * Fetches all data types required for a relation.
 * @param codeLines Lines of code to fetch from.
 * @return Vector of strings containing the data types required for a relation.
 */
std::vector<std::string> getRelationAttributes(const std::string &relation, const std::vector<std::string> &codeLines);

/**
 * Checks whether a schema exists when declaring it.
 * @param schema Schema to check.
 * @param codeLines Lines of code to check in.
 * @return True if the schema exists, false otherwise.
 */
bool schemaAlreadyExists(const std::string &schema, const std::vector<std::string> &codeLines);

/**
 * Checks whether a schema exists when using it before declaring relations.
 * @param schema Schema to check.
 * @param codeLines Lines of code to check in.
 * @return True if the schema exists and can be used, false otherwise.
 */
bool schemaExists(const std::string &schema, const std::vector<std::string> &codeLines);

/**
 * Checks whether a relation exists when declaring it.
 * @param relation Relation to check.
 * @param codeLines Lines of code to check in.
 * @return True if relation exists, false otherwise.
 */
bool relationExists(const std::string &relation, const std::vector<std::string> &codeLines);

/**
 * Checks whether a given string is a schema.
 * @param schema String representing the schema.
 * @param codeLines Lines of code to check in.
 * @return True if the string is a schema, false otherwise.
 */
bool isSchema(const std::string &schema, const std::vector<std::string> &codeLines);

/**
 * Checks whether a given string is a relation.
 * @param relation String representing the relation.
 * @param codeLines Lines of code to check in.
 * @return True if the string is a relation, false otherwise.
 */
bool isRelation(const std::string &relation, const std::vector<std::string> &codeLines);

/**
 * Checks whether a given string is a keyword.
 * @param dataType String representing the keyword.
 * @return True if the string is a keyword, false otherwise.
 */
bool isKeyword(const std::string &keyword);

/**
 * Checks whether a given string is a data type.
 * @param dataType String representing the data type.
 * @return True if the string is a data type, false otherwise.
 */
bool isDataType(const std::string &dataType);

/**
 * Checks whether a given string is a constraint.
 * @param constraint String representing the constraint.
 * @return True if the string is a constraint, false otherwise.
 */
bool isConstraint(const std::string &constraint);

/**
 * Checks whether a given string is a method.
 * @param method String representing the method.
 * @return True if the string is a method, false otherwise.
 */
bool isMethod(const std::string &method);

/**
 * Checks whether a given string is a data type that requires parameters.
 * @param dataType String representing the data type.
 * @return True if the string is a data type that requires parameters, false otherwise.
 */
bool isParameterDataType(const std::string &dataType);

#endif //FQL_VALIDATOR_H

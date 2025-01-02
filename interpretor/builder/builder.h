#ifndef FQL_BUILDER_H
#define FQL_BUILDER_H

/**
 * Builds the executable code from a source code (aka scanned lines).
 * @param builderLines Builder lines to save for execution.
 * @param filePath File path in which the builder lines are saved.
 */
void buildExecutable(const std::vector<std::string> &builderLines, const std::string &filePath);

/**
 * Builds the execution lines for a schema.
 * @param builderLines Builder lines to save for execution.
 * @param schema Schema to build.
 */
void buildSchema(std::vector<std::string> &builderLines, const std::string &schema);

/**
 * Builds the execution lines for a relation.
 * @param builderLines Builder lines to save for execution.
 * @param schema Schema to build.
 * @param relation Relation to build.
 */
void buildRelation(std::vector<std::string> &builderLines, const std::string &schema,
                   const std::string &relation);

/**
 * Builds the execution lines for the attributes of a relation.
 * @param builderLines Builder lines to save for execution.
 * @param relation Relation to build.
 * @param attributes Attributes of the relation.
 */
void buildRelationAttributes(std::vector<std::string> &builderLines, const std::string &relation,
                             const std::vector<std::string> &attributes);

/**
 * Builds the execution lines for the add method.
 * @param builderLines Builder lines to save for execution.
 * @param relation Relation to build.
 * @param arguments Arguments of the add method.
 */
void buildRelationAdd(std::vector<std::string> &builderLines, const std::string &relation,
                      const std::vector<std::string> &arguments);

/**
 * Builds the execution lines for the delete method.
 * @param builderLines Builder lines to save for execution.
 * @param relation Relation to build.
 * @param whereExpression Expression from the where clause.
 */
void buildRelationDelete(std::vector<std::string> &builderLines, const std::string &relation,
                         const std::string &whereExpression);

/**
 * Builds the execution lines for the update method.
 * @param builderLines Builder lines to save for execution.
 * @param relation Relation to build.
 * @param whereExpression Expression from the where clause.
 * @param setExpression Expression from the set clause.
 */
void buildRelationUpdate(std::vector<std::string> &builderLines, const std::string &relation,
                      const std::string &whereExpression, const std::string &setExpression);

/**
 * Builds the execution lines for the array declaration.
 * @param builderLines Builder lines to save for execution.
 * @param array Array to build.
 */
void buildArray(std::vector<std::string> &builderLines, const std::string &array);

/**
 * Builds the execution lines for the fetch method.
 * @param builderLines Builder lines to save for the execution.
 * @param relation Relation to fetch from.
 * @param attributes Attributes to fetch from the relation.
 */
void buildFetch(std::vector<std::string> &builderLines, const std::string &relation,
                const std::vector<std::string> &attributes);

/**
 * Builds the execution lines for the where clause of the fetch method.
 * @param builderLines Builder lines to save for the execution.
 * @param whereExpression  Expression from the where clause.
 */
void buildWhere(std::vector<std::string> &builderLines, const std::string &whereExpression);

/**
 * Builds the execution lines for the concatenation of arrays.
 * @param builderLines Builder lines to save for the execution.
 * @param op Operator to concatenate.
 */
void buildConcatenate(std::vector<std::string> &builderLines, const std::string &op);

#endif //FQL_BUILDER_H

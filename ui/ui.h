#ifndef FQL_UI_H
#define FQL_UI_H

/**
 * Displays a given vector of lines (in CSV format).
 * @param filePath Path of the file with the lines.
 * @param relation Name of the relation.
 */
void showRelation(const std::string &filePath, const std::string &relation);

/**
 * Displays the relation name in the middle of the header.
 * @param relationName Name of the relation.
 */
void showRelationName(const std::string &relationName, unsigned long length);

/**
 * Displays a line of the form "+----------+" of a given length.
 * @param length Total length of the line.
 * @param headerNumber Number of headers the schema has.
 */
void showEmptyLine(unsigned long length, unsigned long headerNumber);

/**
 * Displays the lines (in CSV format) as the elements of a schema.
 * @param lines Lines in the schema.
 */
void showLines(const std::vector<std::string>& lines);

/**
 * Auxiliary function to help compute the largest element under each header of a schema.
 * @param lines Lines in the schema.
 * @return Vector where the element on each index represents the maximum line
 * of the element under the header at that index.
 */
std::vector<unsigned long> computeLengthVector(const std::vector<std::string>& lines);

/**
 * Computes the maximum length of a line
 * @param lengthVector Length vector computed at preprocessing.
 * @param headerNumber Number of headers the schema has.
 * @return Maximum length of all lines.
 */
unsigned long getMaxLength(const std::vector<unsigned long>& lengthVector, unsigned long headerNumber);

#endif //FQL_UI_H

#ifndef FQL_IO_H
#define FQL_IO_H

/**
 * Checks if a file is valid to open.
 * @param filePath Path of the file.
 * @return True if the file is valid and can be opened, false otherwise.
 */
bool validFile(const std::string &filePath);

/**
 * Checks if a directory is valid to open.
 * @param dirPath Path of the directory.
 * @return True if the directory is valid and can be opened, false otherwise.
 */
bool validDirectory(const std::string &dirPath);

/**
 * Reads all the lines from a file.
 * @param filePath Path of the file.
 * @return Vector of strings containing all the read lines.
 */
std::vector<std::string> readLines(const std::string &filePath);

/**
 * Writes a vector of strings to a file.
 * @param filePath Path of the file.
 * @param lines Vector of strings to write.
 */
void writeLines(const std::string &filePath, const std::vector<std::string> &lines);

/**
 * Creates a file with a given path.
 * @param filePath Path of the new file.
 */
void createFile(const std::string &filePath);

/**
 * Deletes a file with a given path.
 * @param filePath Path of the deleted file.
 */
void deleteFile(const char *filePath);

/**
 * Creates a directory with a given path.
 * @param dirPath Path of the new directory.
 */
void createDirectory(const char *dirPath);

/**
 * Deletes a directory and all the content within it.
 * @param dirPath Path of the deleted directory.
 */
void deleteDirectory(const char *dirPath);

#endif //FQL_IO_H

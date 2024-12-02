#ifndef FQL_OUTPUT_H
#define FQL_OUTPUT_H

bool validFile(const std::string &filePath);

bool validDirectory(const std::string &dirPath);

std::vector<std::string> readLines(const std::string &filePath);

void writeLines(const std::string &filePath, const std::vector<std::string> &lines);

void createFile(const std::string &filePath);

void deleteFile(const char *filePath);

void createDirectory(const char *dirPath);

void deleteDirectory(const char *dirPath);

#endif //FQL_OUTPUT_H

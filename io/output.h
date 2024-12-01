#ifndef FQL_OUTPUT_H
#define FQL_OUTPUT_H

bool validFile(const std::string &filePath);

std::vector<std::string> readLines(const std::string &filePath);

void writeLines(const std::string &filePath, const std::vector<std::string> &lines);

void createFile(const std::string &filePath);

void deleteFile(const char *filePath);

#endif //FQL_OUTPUT_H

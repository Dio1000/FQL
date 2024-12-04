#ifndef FQL_UI_H
#define FQL_UI_H

void showSchema(const std::vector<std::string>& lines);

void showEmptyLine(unsigned long length, unsigned long headerNumber);

void showLines(const std::vector<std::string>& lines);

std::vector<unsigned long> computeLengthVector(const std::vector<std::string>& lines);

unsigned long getMaxLength(const std::vector<unsigned long>& lengthVector, unsigned long headerNumber);

#endif //FQL_UI_H

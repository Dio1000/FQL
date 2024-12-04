#include <vector>
#include <string>
#include <iostream>

#include "../utils/algorithms/algorithms.h"
#include "ui.h"

int offset = 5;

void showSchema(const std::vector<std::string>& lines){
    std::vector<unsigned long> lengthVector = computeLengthVector(lines);
    std::vector<std::string> headers = split(lines[0], ",");

    unsigned long headerNumber = headers.size();
    unsigned long lineLength = getMaxLength(lengthVector, headerNumber);

    showEmptyLine(lineLength, headerNumber);
    showLines(lines);
    showEmptyLine(lineLength, headerNumber);
}

void showEmptyLine(unsigned long length, unsigned long headerNumber){
    std::cout << "+";
    for (int index = 1 ; index < length + headerNumber * offset - 1 ; index++) std::cout << "-";
    std::cout << "+";
    std::cout << std::endl;
}

void showLines(const std::vector<std::string>& lines){
    std::vector<unsigned long> lengthVector = computeLengthVector(lines);

    for (const auto& line : lines){
        std::vector<std::string> headers = split(line, ",");

        int index = 0;
        while (index < headers.size()){
            unsigned long totalLength = lengthVector[index] + offset + headers[index].size();
            unsigned long currentLength = headers[index].size() + offset;

            std::cout << headers[index];
            for (int i = 0 ; i < offset ; i++) std::cout << " ";

            for (int i = 0 ; i < totalLength - currentLength ; i++) std::cout << " ";
            std::cout << "|";

            index++;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

std::vector<unsigned long> computeLengthVector(const std::vector<std::string>& lines){
    std::vector<std::string> _headers = split(lines[0], ",");
    std::vector<unsigned long> lengthVector(_headers.size(), 0);

    for (const auto& line : lines){
        std::vector<std::string> headers = split(line, ",");

        int index = 0;
        while(index < headers.size()){
            if (lengthVector[index] < headers[index].size())
                lengthVector[index] = headers[index].size();

            index++;
        }
    }

    return lengthVector;
}

unsigned long getMaxLength(const std::vector<unsigned long>& lengthVector, unsigned long headerNumber){
    unsigned long total = 0;
    for (auto elem : lengthVector) total += elem;

    return total + offset * headerNumber;
}

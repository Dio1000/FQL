#include <vector>
#include <string>
#include <iostream>

#include "../utils/algorithms/algorithms.h"
#include "ui.h"

int offset = 10;
unsigned long headerSize;
unsigned long lineLength;

void showSchema(const std::vector<std::string>& lines){
    std::vector<unsigned long> lengthVector = computeLengthVector(lines);
    std::vector<std::string> headers = split(lines[0], ",");

    headerSize = headers.size();
    lineLength = getMaxLength(lengthVector, headerSize);

    showEmptyLine(lineLength, headerSize);
    showLines(lines);
    showEmptyLine(lineLength, headerSize);
}

void showEmptyLine(unsigned long length, unsigned long headerNumber){
    std::cout << "+";
    for (int index = 1 ; index < length + offset - 1 ; index++) std::cout << "-";
    std::cout << "+";
    std::cout << std::endl;
}

void showLines(const std::vector<std::string>& lines){
    std::vector<unsigned long> lengthVector = computeLengthVector(lines);

    for (int lineIndex = 0; lineIndex < lines.size(); lineIndex++){
        std::cout << "|";
        std::vector<std::string> headers = split(lines[lineIndex], ",");

        int index = 0;
        while (index < headers.size()){
            unsigned long totalLength = lengthVector[index] + offset;
            unsigned long currentLength = headers[index].size();

            std::cout << headers[index];
            for (int i = 0 ; i < totalLength - currentLength ; i++) std::cout << " ";
            std::cout << "|";

            index++;
        }
        std::cout << std::endl;

        if (lineIndex == 0) showEmptyLine(lineLength, headerSize);
    }
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

    return total + offset * headerNumber - 4;
}

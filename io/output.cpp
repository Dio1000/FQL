#include <string>
#include <fstream>
#include <vector>

#include "output.h"

bool validFile(const std::string &filePath){
    if (filePath.empty()){
        throw std::runtime_error("File path " + filePath + " was not provided!");
    }

    std::ifstream fin(filePath);
    return fin.good();
}

std::vector<std::string> readLines(const std::string &filePath){
    if (filePath.empty()){
        throw std::runtime_error("File path " + filePath + " was not provided!");
    }

    if (!validFile(filePath)){
        throw std::runtime_error("File path " + filePath + " does not exist!");
    }

    std::ifstream fin(filePath);
    std::vector<std::string> lines;

    std::string line;
    while (getline(fin, line)){
        lines.push_back(line);
    }
    fin.close();

    return lines;
}

void writeLines(const std::string &filePath, const std::vector<std::string> &lines){
    if (filePath.empty()){
        throw std::runtime_error("File path " + filePath + " was not provided!");
    }

    if (!validFile(filePath)){
        throw std::runtime_error("File path " + filePath + " does not exist!");
    }

    std::ofstream fout(filePath);

    for (const auto& line : lines){
        fout << line << std::endl;
    }
    fout.close();
}

void createFile(const std::string &filePath){
    if (filePath.empty()){
        throw std::runtime_error("File path " + filePath + " was not provided!");
    }

    std::ofstream fout;
    fout.open(filePath);
    fout.close();
}

void deleteFile(const char *filePath){
    if (filePath == nullptr){
        return;
    }

    bool deleted = remove(filePath);
    if (deleted){
        throw std::runtime_error("Could not remove file!");
    }
}
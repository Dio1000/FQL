#include <string>
#include <fstream>
#include <vector>
#include <sys/stat.h>
#include <filesystem>
namespace fs = std::filesystem;

#include "io.h"

bool validFile(const std::string &filePath){
    if (filePath.empty()){
        throw std::runtime_error("File path " + filePath + " was not provided!");
    }

    std::ifstream fin(filePath);
    return fin.good();
}

bool validDirectory(const std::string &dirPath) {
    if (dirPath.empty()){
        throw std::runtime_error("Directory path " + dirPath + " was not provided!");
    }

    struct stat info{};

    if (stat(dirPath.c_str(), &info) != 0) return false;
    return (info.st_mode & S_IFDIR) != 0;
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

void createDirectory(const std::string& dirPath) {
    if (validDirectory(dirPath)) return;

    if (mkdir(dirPath.c_str(), 0755) == -1) {
        std::string errorMessage = "Could not create directory: " + dirPath +
                                   ". Error: " + strerror(errno);
        throw std::runtime_error(errorMessage);
    }
}

void deleteDirectory(const char *dirPath) {
    if (!validDirectory(dirPath)) return;

    try {
        fs::remove_all(dirPath);
    } catch (const std::filesystem::filesystem_error& e) {
        throw std::runtime_error("Could not remove directory: " + std::string(e.what()));
    }
}

void writeLine(const std::string &filePath, const std::string &line) {
    if (filePath.empty()) throw std::runtime_error("File path is empty. Cannot append line.");

    std::ofstream fout(filePath, std::ios::app);
    if (!fout.is_open()) throw std::runtime_error("Unable to open file: " + filePath);

    fout << line << std::endl;
    fout.close();
}

void deleteLine(const std::string &filePath, const std::string &line){
    if (filePath.empty()) throw std::runtime_error("File path is empty. Cannot delete line.");
    std::vector<std::string> lines = readLines(filePath);
    std::vector<std::string> newLines;

    for (auto const &_line : lines){
        if (_line != line) newLines.push_back(_line);
    }

    writeLines(filePath, newLines);
}

std::string getLine(const std::string &filePath, int index){
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

    if (index < 0 || index >= lines.size()){
        throw std::out_of_range("Index " + std::to_string(index) + " is out of range!");
    }

    return lines[index];
}